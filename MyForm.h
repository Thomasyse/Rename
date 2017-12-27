#pragma once
#include <vector>
#include <string>
#include <msclr\marshal_cppstd.h>  

namespace Rename {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm 摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  Pathtext;
	protected:

	protected:

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  Pathfind;

	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::Label^  label2;

	private: System::Windows::Forms::Label^  label3;


	private: System::Windows::Forms::Button^  Replace;
	private: System::Windows::Forms::FolderBrowserDialog^  Folderbrowse;
	private: System::Windows::Forms::ToolTip^  toolTip1;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ComboBox^  SearchText;
	private: System::Windows::Forms::ComboBox^  Replacetext;



	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::Button^  Filefind;
	private: System::Windows::Forms::OpenFileDialog^  Filebrowse;
	private: System::Windows::Forms::Button^  Filefindre;
	private: System::Windows::Forms::Label^  label5;








	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		int dropnum = 0;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->Pathtext = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->Pathfind = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->Filefindre = (gcnew System::Windows::Forms::Button());
			this->Filefind = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->Replace = (gcnew System::Windows::Forms::Button());
			this->SearchText = (gcnew System::Windows::Forms::ComboBox());
			this->Replacetext = (gcnew System::Windows::Forms::ComboBox());
			this->Folderbrowse = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->Filebrowse = (gcnew System::Windows::Forms::OpenFileDialog());
			this->tableLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// Pathtext
			// 
			this->Pathtext->AllowDrop = true;
			this->Pathtext->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Pathtext->Font = (gcnew System::Drawing::Font(L"微软雅黑", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->Pathtext->Location = System::Drawing::Point(115, 25);
			this->Pathtext->Margin = System::Windows::Forms::Padding(3, 5, 0, 3);
			this->Pathtext->Name = L"Pathtext";
			this->Pathtext->Size = System::Drawing::Size(671, 34);
			this->Pathtext->TabIndex = 1;
			this->Pathtext->TextChanged += gcnew System::EventHandler(this, &MyForm::Pathtext_TextChanged);
			this->Pathtext->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &MyForm::Pathtext_DragDrop);
			this->Pathtext->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &MyForm::Pathtext_DragEnter);
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label1->Font = (gcnew System::Drawing::Font(L"微软雅黑", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label1->Location = System::Drawing::Point(3, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(106, 44);
			this->label1->TabIndex = 0;
			this->label1->Text = L"路径：";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Pathfind
			// 
			this->Pathfind->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Pathfind->Font = (gcnew System::Drawing::Font(L"微软雅黑", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->Pathfind->Location = System::Drawing::Point(786, 24);
			this->Pathfind->Margin = System::Windows::Forms::Padding(0, 4, 18, 1);
			this->Pathfind->Name = L"Pathfind";
			this->Pathfind->Size = System::Drawing::Size(37, 39);
			this->Pathfind->TabIndex = 2;
			this->Pathfind->Text = L"…";
			this->toolTip1->SetToolTip(this->Pathfind, L"浏览以获取路径");
			this->Pathfind->UseVisualStyleBackColor = true;
			this->Pathfind->Click += gcnew System::EventHandler(this, &MyForm::Path_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 3;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				112)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				55)));
			this->tableLayoutPanel1->Controls->Add(this->label5, 0, 4);
			this->tableLayoutPanel1->Controls->Add(this->Filefindre, 2, 3);
			this->tableLayoutPanel1->Controls->Add(this->Filefind, 2, 2);
			this->tableLayoutPanel1->Controls->Add(this->label4, 2, 4);
			this->tableLayoutPanel1->Controls->Add(this->label3, 0, 3);
			this->tableLayoutPanel1->Controls->Add(this->label2, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->label1, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->Pathfind, 2, 1);
			this->tableLayoutPanel1->Controls->Add(this->Pathtext, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->Replace, 1, 4);
			this->tableLayoutPanel1->Controls->Add(this->SearchText, 1, 2);
			this->tableLayoutPanel1->Controls->Add(this->Replacetext, 1, 3);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 5;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 44)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 54)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 54)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(841, 248);
			this->tableLayoutPanel1->TabIndex = 3;
			// 
			// label5
			// 
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label5->Font = (gcnew System::Drawing::Font(L"微软雅黑", 9));
			this->label5->Location = System::Drawing::Point(3, 179);
			this->label5->Margin = System::Windows::Forms::Padding(3, 7, 0, 7);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(109, 62);
			this->label5->TabIndex = 12;
			this->label5->Text = L" v1.3.0";
			this->label5->TextAlign = System::Drawing::ContentAlignment::BottomLeft;
			// 
			// Filefindre
			// 
			this->Filefindre->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Filefindre->Font = (gcnew System::Drawing::Font(L"微软雅黑", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->Filefindre->Location = System::Drawing::Point(786, 133);
			this->Filefindre->Margin = System::Windows::Forms::Padding(0, 15, 18, 1);
			this->Filefindre->Name = L"Filefindre";
			this->Filefindre->Size = System::Drawing::Size(37, 38);
			this->Filefindre->TabIndex = 11;
			this->Filefindre->Text = L"…";
			this->toolTip1->SetToolTip(this->Filefindre, L"浏览以获取文件名");
			this->Filefindre->UseVisualStyleBackColor = true;
			this->Filefindre->Click += gcnew System::EventHandler(this, &MyForm::Filefindre_Click);
			// 
			// Filefind
			// 
			this->Filefind->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Filefind->Font = (gcnew System::Drawing::Font(L"微软雅黑", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->Filefind->Location = System::Drawing::Point(786, 79);
			this->Filefind->Margin = System::Windows::Forms::Padding(0, 15, 18, 1);
			this->Filefind->Name = L"Filefind";
			this->Filefind->Size = System::Drawing::Size(37, 38);
			this->Filefind->TabIndex = 10;
			this->Filefind->Text = L"…";
			this->toolTip1->SetToolTip(this->Filefind, L"浏览以获取文件名");
			this->Filefind->UseVisualStyleBackColor = true;
			this->Filefind->Click += gcnew System::EventHandler(this, &MyForm::Filefind_Click);
			// 
			// label4
			// 
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label4->Font = (gcnew System::Drawing::Font(L"微软雅黑", 9, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label4->Location = System::Drawing::Point(789, 179);
			this->label4->Margin = System::Windows::Forms::Padding(3, 7, 5, 7);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(47, 62);
			this->label4->TabIndex = 7;
			this->label4->Text = L"关于";
			this->label4->TextAlign = System::Drawing::ContentAlignment::BottomRight;
			this->label4->Click += gcnew System::EventHandler(this, &MyForm::label4_Click);
			// 
			// label3
			// 
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label3->Font = (gcnew System::Drawing::Font(L"微软雅黑", 13));
			this->label3->Location = System::Drawing::Point(8, 125);
			this->label3->Margin = System::Windows::Forms::Padding(8, 7, 0, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(104, 47);
			this->label3->TabIndex = 5;
			this->label3->Text = L"替换为：";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label2->Font = (gcnew System::Drawing::Font(L"微软雅黑", 13));
			this->label2->Location = System::Drawing::Point(8, 71);
			this->label2->Margin = System::Windows::Forms::Padding(8, 7, 0, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(104, 47);
			this->label2->TabIndex = 3;
			this->label2->Text = L"原名称：";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Replace
			// 
			this->Replace->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->Replace->Font = (gcnew System::Drawing::Font(L"微软雅黑", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->Replace->Location = System::Drawing::Point(371, 182);
			this->Replace->Margin = System::Windows::Forms::Padding(3, 10, 3, 3);
			this->Replace->MinimumSize = System::Drawing::Size(82, 43);
			this->Replace->Name = L"Replace";
			this->Replace->Size = System::Drawing::Size(155, 45);
			this->Replace->TabIndex = 8;
			this->Replace->Text = L"替换";
			this->toolTip1->SetToolTip(this->Replace, L"如有要求，将会替换扩展名");
			this->Replace->UseVisualStyleBackColor = true;
			this->Replace->Click += gcnew System::EventHandler(this, &MyForm::Replace_Click);
			// 
			// SearchText
			// 
			this->SearchText->AllowDrop = true;
			this->SearchText->Dock = System::Windows::Forms::DockStyle::Fill;
			this->SearchText->Font = (gcnew System::Drawing::Font(L"微软雅黑", 10.8F));
			this->SearchText->FormattingEnabled = true;
			this->SearchText->Location = System::Drawing::Point(115, 80);
			this->SearchText->Margin = System::Windows::Forms::Padding(3, 16, 0, 3);
			this->SearchText->MaxDropDownItems = 20;
			this->SearchText->Name = L"SearchText";
			this->SearchText->Size = System::Drawing::Size(671, 32);
			this->SearchText->TabIndex = 4;
			this->toolTip1->SetToolTip(this->SearchText, L"使用\"*\"代替任意文本");
			this->SearchText->TextChanged += gcnew System::EventHandler(this, &MyForm::SearchText_TextChanged);
			this->SearchText->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &MyForm::SearchText_DragDrop);
			this->SearchText->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &MyForm::SearchText_DragEnter);
			// 
			// Replacetext
			// 
			this->Replacetext->AllowDrop = true;
			this->Replacetext->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Replacetext->Font = (gcnew System::Drawing::Font(L"微软雅黑", 10.8F));
			this->Replacetext->FormattingEnabled = true;
			this->Replacetext->Location = System::Drawing::Point(115, 134);
			this->Replacetext->Margin = System::Windows::Forms::Padding(3, 16, 0, 3);
			this->Replacetext->MaxDropDownItems = 21;
			this->Replacetext->Name = L"Replacetext";
			this->Replacetext->Size = System::Drawing::Size(671, 32);
			this->Replacetext->TabIndex = 9;
			this->toolTip1->SetToolTip(this->Replacetext, L"使用\"*\"代替任意文本，使用\"\\\"删除对应的\"*\"文本");
			this->Replacetext->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &MyForm::Replacetext_DragDrop);
			this->Replacetext->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &MyForm::Replacetext_DragEnter);
			// 
			// Filebrowse
			// 
			this->Filebrowse->FileName = L"openFileDialog1";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(841, 248);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximumSize = System::Drawing::Size(8192, 295);
			this->MinimumSize = System::Drawing::Size(219, 295);
			this->Name = L"MyForm";
			this->Text = L"Rename";
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->ResumeLayout(false);

		}

	private: System::Void Path_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void Replace_Click(System::Object^  sender, System::EventArgs^  e);
	private: bool renamefile(String^ old, String^ renew, bool recovermode);
	private: String ^ returnregt(String^ search);
	private: System::Void Pathtext_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		searchfileregex();
	}
	private: int searchfileregex();
	private: String ^ keyreplace(String^ str, String^ replace, System::Text::RegularExpressions::Regex^ key,
		System::Text::RegularExpressions::Regex^ subkey);

	private: System::Void SearchText_TextChanged(System::Object^  sender, System::EventArgs^  e);

	private: System::Void Filefind_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void Filefindre_Click(System::Object^  sender, System::EventArgs^  e);
	
	private: System::Void Pathtext_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
	private: System::Void Pathtext_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
	private: System::Void SearchText_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
	private: System::Void SearchText_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
	private: System::Void Replacetext_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
	private: System::Void Replacetext_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);

	private: System::Void label4_Click(System::Object^  sender, System::EventArgs^  e);
};
}
