#include "MyForm.h"

using namespace Rename;
[STAThreadAttribute]
int main(array<System::String^>^args)
{
	Application::EnableVisualStyles();
	Application::Run(gcnew MyForm());
	return 0;
}



System::Void Rename::MyForm::Path_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	using namespace System::IO;
	if (Directory::Exists(Pathtext->Text)) {
		Folderbrowse->SelectedPath = Pathtext->Text;
	}
	if (Folderbrowse->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		Pathtext->Text = Folderbrowse->SelectedPath;
		searchfileregex();
	}
	return System::Void();
}
System::Void Rename::MyForm::Replace_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	using namespace msclr::interop;
	using namespace std;
	using namespace System::IO;
	using namespace System::Text::RegularExpressions;
	String^ search = SearchText->Text;
	String^ replace = Replacetext->Text;
	Regex^ searchreg = gcnew Regex(returnregt(search));
	Regex^ searchany = gcnew Regex("(.+?)\\*");
	Regex^ key = gcnew Regex("\\*|\\\\");
	MatchCollection^ searchkey = key->Matches(search);
	if (!search->EndsWith("*"))search += "*";
	MatchCollection^ searchmatch = searchany->Matches(search);
	MatchCollection^ replacekey = key->Matches(replace);
	vector<string> oldbackups;
	vector<string> renewbackups;
	if (searchkey->Count != replacekey->Count || search == replace) {
		MessageBox::Show(this, "无法重命名，请检查要替换的文本输入是否正确！", "Rename", MessageBoxButtons::OK);
	}
	else {
		bool flag = true, none = true;
		if (Directory::Exists(Pathtext->Text)) {
			DirectoryInfo path(Pathtext->Text);
			auto files = path.GetFiles();
			if (files->Length == 0) {
				MessageBox::Show(this, "无法重命名，请检查文件夹是否为空！", "Rename", MessageBoxButtons::OK);
				flag = false;
			}
			int k = 0;
#pragma omp parallel for ordered shared(oldbackups,renewbackups,searchmatch) firstprivate(k)
			for (k = 0; k < files->Length; k++) {
				String^ old = files[k]->Name;
				String^ renewmatch = replace;
				if (searchreg->IsMatch(old)) {
					none = false;
					String^ searchrep = "";
					String^ searchrenew = searchreg->Match(old)->Value;
					String^ oldmatch = searchrenew;
					int start = 0, startl = 0;
					for (int i = 0; i < searchmatch->Count; i++) {
						startl = start;
						searchrep = searchmatch[i]->ToString();
						searchrep = searchrep->Replace("*", "");
						start = searchrenew->IndexOf(searchrep, startl);
						searchrenew = searchrenew->Substring(0, start) + "||" + searchrenew->Substring(start + searchrep->Length);
					}
					while (searchrenew->StartsWith("|")) searchrenew = searchrenew->Remove(0, 1);
					while (searchrenew->EndsWith("|")) searchrenew = searchrenew->Remove(searchrenew->Length - 1);
					searchrenew = "|" + searchrenew + "|";
					Regex^ newkey = gcnew Regex("(\\|(.+?)\\|)");
					MatchCollection^ newkeymatch = newkey->Matches(searchrenew);
					String^ newkeyadd = "";
					for (int j = 0; j < replacekey->Count; j++) {
						if (replacekey[j]->ToString() != "\\") {
							newkeyadd = newkeymatch[j]->ToString();
							newkeyadd = newkeyadd->Replace("|", "");
						}
						else newkeyadd = "";
						renewmatch = key->Replace(renewmatch, newkeyadd, 1);
					}
					String^ renew = old->Replace(oldmatch, renewmatch);
					old = path.ToString() + "\\" + old;
					renew = path.ToString() + "\\" + renew;
					if (old != renew) {
						flag = renamefile(old, renew, false);
						if (flag) {
							oldbackups.push_back(marshal_as<string>(old));
							renewbackups.push_back(marshal_as<string>(renew));
						}
					}
				}
			}
		}
		else {
			MessageBox::Show(this, "无法重命名，所选文件夹不存在！", "Rename", MessageBoxButtons::OK);
			flag = false;
		}
		System::Windows::Forms::DialogResult result = Windows::Forms::DialogResult::Yes;
		if (flag) {
			if (!none) result = MessageBox::Show(this, "重命名成功！是否保存更改？", "Rename", MessageBoxButtons::YesNo);
			else MessageBox::Show(this, "未找到需要重命名的文件！", "Rename", MessageBoxButtons::OK);
		}
		if (result == Windows::Forms::DialogResult::No || flag == false)
		{
			for (auto p = renewbackups.begin(), q = oldbackups.begin(); p<renewbackups.end(); p++, q++) {
				renamefile(marshal_as<String^>(*p), marshal_as<String^>(*q), true);
			}
		}
		else {
			SearchText->Items->Insert(0, SearchText->Text);
			Replacetext->Items->Insert(1, Replacetext->Text);
			dropnum++;
			if (dropnum > 10) {
				SearchText->Items->RemoveAt(dropnum - 1);
				Replacetext->Items->RemoveAt(dropnum);
				dropnum = 10;
			}
			searchfileregex();
		}
	}
	return System::Void();
}
bool MyForm::renamefile(String^ old, String^ renew, bool recovermode) {
	using namespace System;
	using namespace System::IO;
	try
	{
		if (!File::Exists(old))
		{
			String^ message = "无法重命名，源文件\"" + old + "\"不存在！\n";
			if (!recovermode) message += "将尝试还原所有更改。";
			else message += "还原失败！";
			MessageBox::Show(this, message, "Rename", MessageBoxButtons::OK);
			return false;
		}

		// Ensure that the target does not exist.
		if (File::Exists(renew)) {
			String^ message = "无法重命名，已存在同名文件\"" + renew + "\"！\n";
			if (!recovermode) message += "将尝试还原所有更改。";
			else message += "还原失败！";
			MessageBox::Show(this, message, "Rename", MessageBoxButtons::OK);
			return false;
		}

		// Move the file.
		File::Move(old, renew);

		// See if the original exists now.
		if (File::Exists(old))
		{
			MessageBox::Show(this, "出现异常，源文件依然存在！", "Rename", MessageBoxButtons::OK);
			return true;
		}
	}
	catch (Exception^ e)
	{
		String^ message = "无法重命名！错误如下：\n" + e->ToString() + "\n";
		if (!recovermode) message += "将尝试还原所有更改。";
		else message += "还原失败！";
		MessageBox::Show(this, message, "Rename", MessageBoxButtons::OK);
		return false;
	}
	return true;
}
String ^ Rename::MyForm::returnregt(String ^ search)
{
	String^ searchregs = search->Replace("[", "\\[");
	searchregs = searchregs->Replace("]", "\\]");
	searchregs = searchregs->Replace("(", "\\(");
	searchregs = searchregs->Replace(")", "\\)");
	searchregs = searchregs->Replace("{", "\\{");
	searchregs = searchregs->Replace("}", "\\}");
	searchregs = searchregs->Replace("+", "\\+");
	searchregs = searchregs->Replace(".", "\\.");
	searchregs = searchregs->Replace("^", "\\^");
	searchregs = searchregs->Replace("$", "\\$");
	searchregs = searchregs->Replace("*", "(.+?)");
	return searchregs;
}
int Rename::MyForm::searchfileregex()
{
	using namespace System::IO;
	if (SearchText->Items->Count > 0) {
		for (int k = SearchText->Items->Count - 1; k >= dropnum; k--) {
			SearchText->Items->RemoveAt(k);
			Replacetext->Items->RemoveAt(k + 1);
		}
	}
	if (Directory::Exists(Pathtext->Text)) {
		DirectoryInfo path(Pathtext->Text);
		auto files = path.GetFiles();
		if (files->Length == 0) return -1;
		using namespace System::Text::RegularExpressions;
		using namespace msclr::interop;
		using namespace std;
		unsigned int j = 0;
		vector<string> namereg, searchadd, replaceadd;
		Regex^ romenum = gcnew Regex("(X{0,3})(IX|IV|VI{1,3}|V|I{1,3})");
		String^ numstr = "([0-9]+(\\.[0-9])*([-_vV][A-Za-z0-9])*)";
		String^ numstrreg = "([0-9]+(\\\\\\.[0-9])*([-_vV][A-Za-z0-9])*)";
		Regex^ num = gcnew Regex(numstr);
		Regex^ numreg = gcnew Regex(numstrreg);
		Regex^ end = gcnew Regex("(\\[[eE][nN][dD]\\])|(( *)[-_]( *)[eE][nN][dD])");
		Regex^ numkey = gcnew Regex("(\\[" + numstr + "\\])|((-( +)|([^0-9]-))" + numstr + ")|" +
			"(_( *)" + numstr + "(\\W| ))|( " + numstr + " )|(ep(isode)?(\\.)*" + numstr + "(\\W| ))|" +
			"(^" + numstr + "\\.[^0-9])");
		Regex^ numkey1 = gcnew Regex("([ \\[-](X{0,3})(IX|IV|VI{1,3}|V|I{1,3})[ \\]-])");
		Regex^ codekey = gcnew Regex("(\\((CRC32_)?([0-9A-Z]{8})\\)\\.)|(\\[(CRC32_)?([0-9A-Z]{8})\\]\\.)");
		Regex^ wordkey = gcnew Regex("((NCED|NCOP|SP|OVA|ova|OAD|oad|DISC|Disc|MENU|Menu)( *)" + numstr + ")");
		Regex^ wordkey1 = gcnew Regex("([0-9]\\]\\[[eE][nN][dD]\\])|([0-9]( *)[-_]( *)[eE][nN][dD])");
		Regex^ numkeyreg = gcnew Regex("(\\\\\\[" + numstrreg + "\\\\\\])|((-( +)|([^0-9]-))" + numstrreg + ")|" +
			"(_( *)" + numstrreg + "(\\\\\\W| ))|( " + numstrreg + " )|" +
			"(ep(isode)?(\\\\\\.)*" + numstrreg + "(\\\\\\W| ))|(^" + numstrreg + "\\\\\\.[^0-9])");
		Regex^ numkeyreg1 = gcnew Regex("([ \\\\\\[-](X{0,3})(IX|IV|VI{1,3}|V|I{1,3})[ \\\\\\]-])");
		Regex^ codekeyreg = gcnew Regex("(\\\\\\((CRC32_)?([0-9A-Z]{8})\\\\\\)\\\\\\.)|(\\\\\\[(CRC32_)?([0-9A-Z]{8})\\\\\\]\\\\\\.)");
		Regex^ wordkeyreg = gcnew Regex("((NCED|NCOP|SP|OVA|ova|OAD|oad|DISC|Disc|MENU|Menu)( *)" + numstrreg + ")");
		std::vector<int> sortfiles;
		int index = 0;
		Regex^ exten = gcnew Regex("\\.(mp4|mov|mkv|avi|wmv|mpeg|mpg|qt|rmvb|flv|ass)");
		int m = 0;
		for (m = 0; m < files->Length; m++) {
			if ((numkey->IsMatch(files[m]->Name) || numkey1->IsMatch(files[m]->Name) ||
				wordkey->IsMatch(files[m]->Name) || codekey->IsMatch(files[m]->Name)) && exten->IsMatch(files[m]->Name)) {
				sortfiles.insert(sortfiles.begin() + index++, m);
			}
			else {
				sortfiles.push_back(m);
			}
		}
		int i = 0;
		for (i = dropnum; i < SearchText->MaxDropDownItems; i++) {
			bool stop = false, stop1 = false;
			String^ file = "";
			while (!stop1) {
				bool *check = new bool[namereg.size()];
				file = files[sortfiles[min(j, sortfiles.size() - 1)]]->Name;
				file = keyreplace(file, "", wordkey1, end);
				int k = 0;

#pragma omp parallel for shared(file,check)
				for (k = 0; k < namereg.size(); k++) {
					Regex^ reg = gcnew Regex(marshal_as<String^>(namereg[k]));
					if (check[k])check[k] = !reg->IsMatch(file);
					if (!check[k])break;
				}
				stop1 = true;
				for (int i = 0; i < namereg.size(); i++) 
					if (!check[i]) {
						stop1 = false;
						j++;
						break;
					}
				if (j > sortfiles.size() - 1) {
					stop = true;
					break;
				}
			}
			if (stop)break;
			String^ name = returnregt(file), ^ listname = file;
			name = keyreplace(name, numstr, numkeyreg, numreg);
			name = keyreplace(name, romenum->ToString(), numkeyreg1, romenum);
			name = keyreplace(name, numstr, wordkeyreg, numreg);
			name = codekeyreg->Replace(name, codekey->ToString());
			listname = keyreplace(listname, "*", numkey, num);
			listname = keyreplace(listname, "*", numkey1, romenum);
			listname = keyreplace(listname, "*", wordkey, num);
			String^ listname2 = listname;
			listname = codekey->Replace(listname, "*.");
			listname2 = codekey->Replace(listname2, "\\.");
			namereg.push_back(marshal_as<string>(name));
			searchadd.push_back(marshal_as<string>(listname));
			replaceadd.push_back(marshal_as<string>(listname2));
		}
		for (auto &m : searchadd) {
			SearchText->Items->Add(marshal_as<String^>(m));
		}
		if (Replacetext->Items->Count == 0)Replacetext->Items->Add("");
		for (auto &n : replaceadd) {
			Replacetext->Items->Add(marshal_as<String^>(n));
		}
	}
	return 0;
}
String ^ Rename::MyForm::keyreplace(String ^ str, String ^ replace, System::Text::RegularExpressions::Regex ^ key, System::Text::RegularExpressions::Regex ^ subkey)
{
	using namespace System::Text::RegularExpressions;
	if (str != nullptr  && key->IsMatch(str)) {
		String^ result = str;
		MatchCollection^ keymatch = key->Matches(str);
		for (int kn = 0; kn < keymatch->Count; kn++) {
			result = result->Replace(keymatch[kn]->Value, subkey->Replace(keymatch[kn]->Value, replace));//eg. OAD2->OAD[numstr]
		}
		return result;
	}
	else return str;
}

System::Void Rename::MyForm::SearchText_TextChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	if (Replacetext->Items->Count > 0) {
		Replacetext->Items->RemoveAt(0);
		Replacetext->Items->Insert(0, SearchText->Text);
	}
	else Replacetext->Items->Add(SearchText->Text);
	return System::Void();
}

System::Void Rename::MyForm::Filefind_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	using namespace System::IO;
	Stream^ myStream;
	Filebrowse->Title = "获取文件名";
	Filebrowse->FileName = "";
	if (Directory::Exists(Pathtext->Text)) Filebrowse->InitialDirectory = Pathtext->Text;
	Filebrowse->Filter = "All Files|*.*|Video Files|*.mp4;*.mov;*.mkv;*.avi;*.wmv;*.mpeg;*.mpg;*.qt;*.rmvb;*.flv|Ass Files|*.ass";
	Filebrowse->FilterIndex = 0;
	Filebrowse->RestoreDirectory = true;
	if (Filebrowse->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		if ((myStream = Filebrowse->OpenFile()) != nullptr)
		{
			using namespace System::Text::RegularExpressions;
			Regex^ namekey = gcnew Regex("\\\\([^\\\\]+?)$");
			Pathtext->Text = namekey->Replace(Filebrowse->FileName, "");
			SearchText->Text = namekey->Match(Filebrowse->FileName)->Value->Replace("\\", "");
			myStream->Close();
			searchfileregex();
		}
	}
	return System::Void();
}
System::Void Rename::MyForm::Filefindre_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	using namespace System::IO;
	Stream^ myStream;
	Filebrowse->Title = "获取文件名";
	Filebrowse->FileName = "";
	if (Directory::Exists(Pathtext->Text)) Filebrowse->InitialDirectory = Pathtext->Text;
	Filebrowse->Filter = "All Files|*.*|Video Files|*.mp4;*.mov;*.mkv;*.avi;*.wmv;*.mpeg;*.mpg;*.qt;*.rmvb;*.flv|Ass Files|*.ass";
	Filebrowse->FilterIndex = 0;
	Filebrowse->RestoreDirectory = true;
	if (Filebrowse->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		if ((myStream = Filebrowse->OpenFile()) != nullptr)
		{
			using namespace System::Text::RegularExpressions;
			Regex^ namekey = gcnew Regex("\\\\([^\\\\]+?)$");
			Replacetext->Text = namekey->Match(Filebrowse->FileName)->Value->Replace("\\", "");
			myStream->Close();
		}
	}
	return System::Void();
}

System::Void Rename::MyForm::Pathtext_DragDrop(System::Object ^ sender, System::Windows::Forms::DragEventArgs ^ e)
{
	using namespace System::Text::RegularExpressions;
	using namespace System::IO;
	if (e->Data->GetDataPresent(DataFormats::FileDrop)) {
		array<String^>^files = (array<String^>^)e->Data->GetData(DataFormats::FileDrop);
		if (!Directory::Exists(files[0])) Pathtext->Text = Regex::Replace(files[0], "\\\\.+?$", "", RegexOptions::RightToLeft);
		else Pathtext->Text = files[0];
		searchfileregex();
	}
	else
		if (e->Data->GetDataPresent(DataFormats::StringFormat)) {
			String^str = (String^)e->Data->GetData(DataFormats::StringFormat);
			if (!Directory::Exists(str)) Pathtext->Text = Regex::Replace(str, "\\\\.+?$", "", RegexOptions::RightToLeft);
			else Pathtext->Text = str;
			searchfileregex();
		}
	return System::Void();
}
System::Void Rename::MyForm::Pathtext_DragEnter(System::Object ^ sender, System::Windows::Forms::DragEventArgs ^ e)
{
	if (e->Data->GetDataPresent(DataFormats::FileDrop) || e->Data->GetDataPresent(DataFormats::StringFormat))
	{
		e->Effect = DragDropEffects::Copy;
	}
	else
	{
		e->Effect = DragDropEffects::None;
	}
	return System::Void();
}
System::Void Rename::MyForm::SearchText_DragEnter(System::Object ^ sender, System::Windows::Forms::DragEventArgs ^ e)
{
	if (e->Data->GetDataPresent(DataFormats::FileDrop) || e->Data->GetDataPresent(DataFormats::StringFormat))
	{
		e->Effect = DragDropEffects::Copy;
	}
	else
	{
		e->Effect = DragDropEffects::None;
	}
	return System::Void();
}
System::Void Rename::MyForm::SearchText_DragDrop(System::Object ^ sender, System::Windows::Forms::DragEventArgs ^ e)
{
	using namespace System::Text::RegularExpressions;
	using namespace System::IO;
	Regex^ filekey = gcnew Regex("^.+\\\\");
	if (e->Data->GetDataPresent(DataFormats::FileDrop)) {
		array<String^>^files = (array<String^>^)e->Data->GetData(DataFormats::FileDrop);
		SearchText->Text = filekey->Replace(files[0], "");
		if (files[0]->IndexOf(".") >= 0 || !Directory::Exists(files[0])) Pathtext->Text = Regex::Replace(files[0], "\\\\.+?$", "", RegexOptions::RightToLeft);
		else Pathtext->Text = files[0];
		searchfileregex();
	}
	else
		if (e->Data->GetDataPresent(DataFormats::StringFormat)) {
			String^str = (String^)e->Data->GetData(DataFormats::StringFormat);
			SearchText->Text = filekey->Replace(str, "");
			if (str->IndexOf(".") >= 0 || !Directory::Exists(str)) Pathtext->Text = Regex::Replace(str, "\\\\.+?$", "", RegexOptions::RightToLeft);
			else Pathtext->Text = str;
			searchfileregex();
		}
	return System::Void();
}
System::Void Rename::MyForm::Replacetext_DragEnter(System::Object ^ sender, System::Windows::Forms::DragEventArgs ^ e)
{
	if (e->Data->GetDataPresent(DataFormats::FileDrop) || e->Data->GetDataPresent(DataFormats::StringFormat))
	{
		e->Effect = DragDropEffects::Copy;
	}
	else
	{
		e->Effect = DragDropEffects::None;
	}
	return System::Void();
}
System::Void Rename::MyForm::Replacetext_DragDrop(System::Object ^ sender, System::Windows::Forms::DragEventArgs ^ e)
{
	using namespace System::Text::RegularExpressions;
	Regex^ filekey = gcnew Regex("^.+\\\\");
	if (e->Data->GetDataPresent(DataFormats::FileDrop)) {
		array<String^>^files = (array<String^>^)e->Data->GetData(DataFormats::FileDrop);
		Replacetext->Text = filekey->Replace(files[0], "");
	}
	else
		if (e->Data->GetDataPresent(DataFormats::StringFormat)) {
			String^str = (String^)e->Data->GetData(DataFormats::StringFormat);
			Replacetext->Text = filekey->Replace(str, "");
		}
	return System::Void();
}

System::Void Rename::MyForm::label4_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	MessageBox::Show(this, "Rename\nVersion 1.3.0\nBy Thomasys, 2017", "关于", MessageBoxButtons::OK);
	return System::Void();
}
