#pragma once
#include<opencv\cv.h>;
#include<opencv\highgui.h>;
#include<opencv\ml.h>;
#include<opencv\cxcore.h>;
#include<stdio.h>;


namespace LicenseRecognition {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	private:
		IplImage *src;
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
			if (src)
				src = NULL;
		}
	private: System::Windows::Forms::GroupBox^  gImage;
	protected:
	private: System::Windows::Forms::PictureBox^  pb_Source;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Button^  btn_ml;
	private: System::Windows::Forms::Button^  btn_process;
	private: System::Windows::Forms::Button^  btn_loadimage;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::PictureBox^  pb_Plate;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->gImage = (gcnew System::Windows::Forms::GroupBox());
			this->pb_Source = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->btn_ml = (gcnew System::Windows::Forms::Button());
			this->btn_process = (gcnew System::Windows::Forms::Button());
			this->btn_loadimage = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pb_Plate = (gcnew System::Windows::Forms::PictureBox());
			this->gImage->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Source))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Plate))->BeginInit();
			this->SuspendLayout();
			// 
			// gImage
			// 
			this->gImage->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->gImage->Controls->Add(this->pb_Source);
			this->gImage->Location = System::Drawing::Point(12, 1);
			this->gImage->Name = L"gImage";
			this->gImage->Size = System::Drawing::Size(600, 429);
			this->gImage->TabIndex = 0;
			this->gImage->TabStop = false;
			this->gImage->Text = L"Source Image";
			// 
			// pb_Source
			// 
			this->pb_Source->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pb_Source->Location = System::Drawing::Point(3, 16);
			this->pb_Source->Name = L"pb_Source";
			this->pb_Source->Size = System::Drawing::Size(594, 410);
			this->pb_Source->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pb_Source->TabIndex = 0;
			this->pb_Source->TabStop = false;
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->Controls->Add(this->btn_ml);
			this->groupBox1->Controls->Add(this->btn_process);
			this->groupBox1->Controls->Add(this->btn_loadimage);
			this->groupBox1->Location = System::Drawing::Point(618, 324);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(154, 106);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Control Bar";
			// 
			// btn_ml
			// 
			this->btn_ml->Location = System::Drawing::Point(6, 77);
			this->btn_ml->Name = L"btn_ml";
			this->btn_ml->Size = System::Drawing::Size(142, 23);
			this->btn_ml->TabIndex = 2;
			this->btn_ml->Text = L"Machine Learning";
			this->btn_ml->UseVisualStyleBackColor = true;
			// 
			// btn_process
			// 
			this->btn_process->Location = System::Drawing::Point(6, 48);
			this->btn_process->Name = L"btn_process";
			this->btn_process->Size = System::Drawing::Size(142, 23);
			this->btn_process->TabIndex = 1;
			this->btn_process->Text = L"Recognise";
			this->btn_process->UseVisualStyleBackColor = true;
			// 
			// btn_loadimage
			// 
			this->btn_loadimage->Location = System::Drawing::Point(6, 19);
			this->btn_loadimage->Name = L"btn_loadimage";
			this->btn_loadimage->Size = System::Drawing::Size(142, 23);
			this->btn_loadimage->TabIndex = 0;
			this->btn_loadimage->Text = L"Load Image";
			this->btn_loadimage->UseVisualStyleBackColor = true;
			this->btn_loadimage->Click += gcnew System::EventHandler(this, &MainForm::btn_loadimage_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->textBox1);
			this->groupBox2->Controls->Add(this->label1);
			this->groupBox2->Controls->Add(this->pb_Plate);
			this->groupBox2->Location = System::Drawing::Point(619, 1);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(153, 155);
			this->groupBox2->TabIndex = 2;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Result";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 113);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(64, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Plate Result";
			// 
			// textBox1
			// 
			this->textBox1->Enabled = false;
			this->textBox1->Location = System::Drawing::Point(6, 129);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(140, 20);
			this->textBox1->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 16);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(31, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Plate";
			// 
			// pb_Plate
			// 
			this->pb_Plate->Location = System::Drawing::Point(5, 31);
			this->pb_Plate->Name = L"pb_Plate";
			this->pb_Plate->Size = System::Drawing::Size(141, 50);
			this->pb_Plate->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pb_Plate->TabIndex = 0;
			this->pb_Plate->TabStop = false;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 442);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->gImage);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Name = L"MainForm";
			this->Text = L"License Recognition System";
			this->gImage->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Source))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Plate))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
/*	Load source image to Picture box
* @Author: An Ngo Trieu Gia
* @Date modified: 3/24/2017
*/
	/// <summary>
	/// Load source image to Picture box
	/// @Author: An Ngo Trieu Gia
	/// @Date modified: 3 / 24 / 2017
	/// </summary>
	private: char* convertStringToChars(System::String ^str) {
		return (char*)(void*)Marshal::StringToHGlobalAnsi(str);
	}
	private: bool isCancel(System::Windows::Forms::DialogResult dlgResult) {
		return dlgResult == System::Windows::Forms::DialogResult::Cancel;
	}
	private: void showSourceImage(System::String ^dlgFileName) {
		Bitmap ^bmp = gcnew Bitmap(dlgFileName);
		pb_Source->Image = bmp;
		pb_Source->Refresh();
	}
	private: System::Void btn_loadimage_Click(System::Object^  sender, System::EventArgs^  e) {
		// gcnew help .NET know which Obj should be delete
		OpenFileDialog^ dlg = gcnew OpenFileDialog;
		
		// Filters Image in Folder
		dlg->Filter = "Image (*.bmp; *.jpg; *.jpeg; *.png) |*.bmp; *.jpg; *.jpeg; *.png|All files (*.*)|*.*||";
		if (isCancel(dlg->ShowDialog()))
			return;
		
		// Need to write func to convert String to Char*
		src = cvLoadImage(convertStringToChars(dlg->FileName));
		showSourceImage(dlg->FileName);
	}
};
}
