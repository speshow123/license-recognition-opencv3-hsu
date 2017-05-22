#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/ml.hpp>
#include<iostream>;
#include "dirent.h";
#include "feature.h";
#include "PlateFinder.h";


namespace LicenseRecognition {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	cv::Mat imgSrc;
	int count = 0;
	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	private:
		//IplImage *src;
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
			/*if (src)
				src = NULL;*/
		}
	private: System::Windows::Forms::GroupBox^  gImage;
	protected:
	private: System::Windows::Forms::PictureBox^  pb_Source;
	private: System::Windows::Forms::GroupBox^  groupBox1;


	private: System::Windows::Forms::Button^  btn_process;
	private: System::Windows::Forms::Button^  btn_loadimage;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  tb_license;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::PictureBox^  pb_Plate;
	private: System::Windows::Forms::Label^  imgSize;
	private: System::Windows::Forms::Button^  btn_learn;


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
			this->imgSize = (gcnew System::Windows::Forms::Label());
			this->pb_Source = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->btn_learn = (gcnew System::Windows::Forms::Button());
			this->btn_process = (gcnew System::Windows::Forms::Button());
			this->btn_loadimage = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->tb_license = (gcnew System::Windows::Forms::TextBox());
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
			this->gImage->Controls->Add(this->imgSize);
			this->gImage->Controls->Add(this->pb_Source);
			this->gImage->Location = System::Drawing::Point(12, 1);
			this->gImage->Name = L"gImage";
			this->gImage->Size = System::Drawing::Size(600, 429);
			this->gImage->TabIndex = 0;
			this->gImage->TabStop = false;
			this->gImage->Text = L"Source Image";
			// 
			// imgSize
			// 
			this->imgSize->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->imgSize->AutoSize = true;
			this->imgSize->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->imgSize->Location = System::Drawing::Point(480, 390);
			this->imgSize->Name = L"imgSize";
			this->imgSize->Size = System::Drawing::Size(79, 18);
			this->imgSize->TabIndex = 1;
			this->imgSize->Text = L"image size";
			// 
			// pb_Source
			// 
			this->pb_Source->BackColor = System::Drawing::SystemColors::ControlDark;
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
			this->groupBox1->Controls->Add(this->btn_learn);
			this->groupBox1->Controls->Add(this->btn_process);
			this->groupBox1->Controls->Add(this->btn_loadimage);
			this->groupBox1->Location = System::Drawing::Point(618, 324);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(154, 106);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Control Bar";
			// 
			// btn_learn
			// 
			this->btn_learn->Location = System::Drawing::Point(6, 77);
			this->btn_learn->Name = L"btn_learn";
			this->btn_learn->Size = System::Drawing::Size(142, 23);
			this->btn_learn->TabIndex = 2;
			this->btn_learn->Text = L"Machine Learning";
			this->btn_learn->UseVisualStyleBackColor = true;
			this->btn_learn->Click += gcnew System::EventHandler(this, &MainForm::btn_learn_Click);
			// 
			// btn_process
			// 
			this->btn_process->Location = System::Drawing::Point(6, 48);
			this->btn_process->Name = L"btn_process";
			this->btn_process->Size = System::Drawing::Size(142, 23);
			this->btn_process->TabIndex = 1;
			this->btn_process->Text = L"Recognise";
			this->btn_process->UseVisualStyleBackColor = true;
			this->btn_process->Click += gcnew System::EventHandler(this, &MainForm::btn_process_Click);
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
			this->groupBox2->Controls->Add(this->tb_license);
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
			this->label2->Location = System::Drawing::Point(6, 100);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(64, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Plate Result";
			// 
			// tb_license
			// 
			this->tb_license->Enabled = false;
			this->tb_license->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tb_license->ForeColor = System::Drawing::Color::Red;
			this->tb_license->Location = System::Drawing::Point(6, 123);
			this->tb_license->Name = L"tb_license";
			this->tb_license->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->tb_license->Size = System::Drawing::Size(140, 26);
			this->tb_license->TabIndex = 4;
			this->tb_license->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
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
			this->pb_Plate->BackColor = System::Drawing::SystemColors::ControlDark;
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
			this->gImage->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Source))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_Plate))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
/*
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
		Bitmap ^bmpScr = gcnew Bitmap(dlgFileName);
		pb_Source->Image = bmpScr;
		pb_Source->Refresh();
	}

	private: void showImageSize(cv::Mat imageSource) {
		System::String^ height = gcnew System::String(std::to_string(imageSource.rows).c_str());
		System::String^ width = gcnew System::String(std::to_string(imageSource.cols).c_str());
		imgSize->Text = width + "x" + height;
	}

	private: System::Void btn_loadimage_Click(System::Object^  sender, System::EventArgs^  e) {
		// gcnew help .NET know which Obj should be delete
		OpenFileDialog^ openImageDialog = gcnew OpenFileDialog;
		
		// Filters Image in Folder
		openImageDialog->Filter = "Image (*.bmp; *.jpg; *.jpeg; *.png) |*.bmp; *.jpg; *.jpeg; *.png|All files (*.*)|*.*||";
		if (isCancel(openImageDialog->ShowDialog()))
			return;
		if (tb_license->Text != "") {
			tb_license->Text = "";
			pb_Plate->Image = nullptr;
			pb_Plate->Refresh();
		}
		
		
		showSourceImage(openImageDialog->FileName);

		// New styles
		// Need to write func to convert String to Char*
		imgSrc = cv::imread(convertStringToChars(openImageDialog->FileName));
		showImageSize(imgSrc);
		btn_process->Enabled = true;
		
	}
	/// <summary>
	/// Detect image and regconise text
	/// @Author: An Ngo Trieu Gia
	/// @Date modified: 4 / 10 / 2017
	/// </summary>
	private: System::Void btn_process_Click(System::Object^  sender, System::EventArgs^  e) {
		if (imgSrc.empty()) {
			MessageBox::Show("No image loaded", "Error", MessageBoxButtons::OK);
			return;
		}
		PlateFinder plate("TrainSVM.txt", true);
		vector<Mat> characters = plate.findCharacters(imgSrc);
		
		/*pb_Plate->Image = Mat2Bimap(plate.getPlate());
		pb_Plate->Refresh();*/
		Mat platePicture = plate.getPlate();
		if (characters.size() < 6)
		{
			MessageBox::Show("Cannot regconition", "Error", MessageBoxButtons::OK);
			return;
		}
		
		
		std::ostringstream name;
		name << "test_" << count++ << ".bmp";
		imwrite(name.str(), plate.getPlate());
		System::String^ str1 = gcnew System::String(name.str().c_str());
		Bitmap ^bmpSrc = gcnew Bitmap(str1);
		pb_Plate->Image = bmpSrc;
		pb_Plate->Refresh();
		string license = plate.plateRecognition(characters);
		
		if (license.length() > 6) {
			System::String^ str = gcnew System::String(license.c_str());
			tb_license->Text = str;
			MessageBox::Show("Your license: " + str, "Car License",
				MessageBoxButtons::OK, MessageBoxIcon::Information);
			btn_process->Enabled = false;
			return;
		}
		else {
			MessageBox::Show("Cannot regconition", "Error", MessageBoxButtons::OK);
			return;
		}
	}
	private: vector<string> list_file(string folder_path)
	{
		vector<string> files;
		DIR *dir = opendir(folder_path.c_str());
		struct dirent *entry;
		while ((entry = readdir(dir)) != NULL)
		{
			if ((strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0))
			{
				string file_path = folder_path + "/" + string(entry->d_name);
				files.push_back(file_path);
			}
		}
		closedir(dir);
		return files;
	}
	private: vector<string> list_folder(string path)
	{
		vector<string> folders;
		DIR *dir = opendir(path.c_str());
		struct dirent *entry;
		while ((entry = readdir(dir)) != NULL)
		{
			if ((strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0))
			{
				string folder_path = path + "/" + string(entry->d_name);
				folders.push_back(folder_path);
			}
		}
		closedir(dir);
		return folders;

	}
	
	private: bool TrainSVM(string trainImgpath) {
		const int number_of_class = 30;
		const int number_of_sample = 10;
		const int number_of_feature = 32;

		//Train SVM OpenCV 3.1
		Ptr<SVM> svm = SVM::create();
		svm->setType(SVM::C_SVC);
		svm->setKernel(SVM::RBF);
		svm->setGamma(0.5);
		svm->setC(16);
		svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));

		vector<string> folders = list_folder(trainImgpath);
		if (folders.size() <= 0)
		{
			//do something
			return false;
		}
		if (number_of_class != folders.size() || number_of_sample <= 0 || number_of_class <= 0)
		{
			//do something
			return false;
		}
		Mat src;
		Mat data = Mat(number_of_sample * number_of_class, number_of_feature, CV_32FC1);
		Mat label = Mat(number_of_sample * number_of_class, 1, CV_32SC1);
		int index = 0;
		for (size_t i = 0; i < folders.size(); ++i)
		{
			vector<string> files = list_file(folders.at(i));
			if (files.size() <= 0 || files.size() != number_of_sample)
			{
				return false;
			}
			string folder_path = folders.at(i);
			string label_folder = folder_path.substr(folder_path.length() - 1);
			for (size_t j = 0; j < files.size(); ++j)
			{
				src = imread(files.at(j));
				if (src.empty())
				{
					return false;
				}
				vector<float> feature = calculate_feature(src);
				for (size_t t = 0; t < feature.size(); ++t)
					data.at<float>(index, t) = feature.at(t);
				label.at<int>(index, 0) = i;
				index++;
			}
		}
		// SVM Train OpenCV 3.1
		svm->trainAuto(ml::TrainData::create(data, ml::ROW_SAMPLE, label));
		svm->save("svm.txt");
		return true;
	}
	private: System::Void btn_learn_Click(System::Object^  sender, System::EventArgs^  e) {
		FolderBrowserDialog^ folderOpen = gcnew FolderBrowserDialog();
		if (folderOpen->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
		{
			return;
		}

		System::String^ sysImgpath;
		sysImgpath = folderOpen->SelectedPath;
		char cStr[50] = { 0 };
		if (sysImgpath->Length < sizeof(cStr))
			sprintf(cStr, "%s", sysImgpath);
		std::string imgpath(cStr);

		/*SaveFileDialog^ saveFile = gcnew SaveFileDialog();
		if (saveFile->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
		{
			return;
		}
		System::String^ sysSaveimg = saveFile->FileName;
		char cStr_[50] = { 0 };
		if (sysSaveimg->Length < sizeof(cStr))
			sprintf(cStr_, "%s", sysSaveimg);*/
		//std::string savesvm(cStr_);

		if (TrainSVM(imgpath))
		{
			MessageBox::Show("Training completed.");
		}
		else
			MessageBox::Show("ERROR");
	}
};
}
