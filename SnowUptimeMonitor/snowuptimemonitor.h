#pragma once
#include "pingsnow.h"

#include "sendemail.h"
#include <cstdio>
#include <Windows.h>

namespace SnowUptimeMonitor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Resources;
	using namespace System::Threading;
	using namespace System::IO;
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class SnowUptimeMonitorForm : public System::Windows::Forms::Form
	{
	private:
		static System::Windows::Forms::Timer ^_timer = gcnew System::Windows::Forms::Timer();
	public:
		SnowUptimeMonitorForm(void)
		{
			int Ping();
			//int Smsg();
			InitializeComponent();
			_timer->Tick += gcnew System::EventHandler(this, &SnowUptimeMonitor::SnowUptimeMonitorForm::_timer_Tick);
			_timer->Interval = 6000; // 1 hour			
			_timer->Start();

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SnowUptimeMonitorForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::NotifyIcon^  notifyIcon1;

	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->notifyIcon1 = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::SystemColors::Highlight;
			this->label1->Location = System::Drawing::Point(100, 45);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(132, 24);
			this->label1->TabIndex = 0;
			this->label1->Text = L"PI 1 ";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(324, 29);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(157, 122);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->WorkerReportsProgress = true;
			this->backgroundWorker1->WorkerSupportsCancellation = true;
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &SnowUptimeMonitorForm::backgroundWorker1_DoWork);
			this->backgroundWorker1->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &SnowUptimeMonitorForm::backgroundWorker1_ProgressChanged);
			this->backgroundWorker1->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &SnowUptimeMonitorForm::backgroundWorker1_RunWorkerCompleted);
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(92, 107);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(185, 148);
			this->pictureBox2->TabIndex = 2;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->Location = System::Drawing::Point(324, 157);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(157, 122);
			this->pictureBox3->TabIndex = 3;
			this->pictureBox3->TabStop = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::SystemColors::Highlight;
			this->label2->Location = System::Drawing::Point(100, 196);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(80, 24);
			this->label2->TabIndex = 4;
			this->label2->Text = L"PI 2";
			// 
			// notifyIcon1
			// 
			this->notifyIcon1->Text = L"SnowUptimeMonitor";
			this->notifyIcon1->Visible = true;
			// 
			// SnowUptimeMonitorForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->ClientSize = System::Drawing::Size(551, 309);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label1);
			this->MaximizeBox = false;
			this->Name = L"SnowUptimeMonitorForm";
			this->Text = L"SnowUptimeMonitor";
			this->Load += gcnew System::EventHandler(this, &SnowUptimeMonitorForm::SnowUptimeMonitorForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		Bitmap^ up;
		Bitmap^ down;

	public:
		void set_png()
		{
			try
			{
				up = dynamic_cast<Bitmap^>(Image::FromFile("\\\\Asus-pc\\asus_share\\Images\\up.png", true));
				down = dynamic_cast<Bitmap^>(Image::FromFile("\\\\Asus-pc\\asus_share\\Images\\down.png", true));

				TextureBrush^ texture = gcnew TextureBrush(down);
				TextureBrush^ texture2 = gcnew TextureBrush(up);
				texture->WrapMode = System::Drawing::Drawing2D::WrapMode::Tile;
				texture2->WrapMode = System::Drawing::Drawing2D::WrapMode::Tile;
				Graphics^ formGraphics = this->CreateGraphics();
				Graphics^ formGraphics1 = this->CreateGraphics();

				formGraphics->FillEllipse(texture, RectangleF(100.0F, 110.0F, 100, 100));
				formGraphics1->FillEllipse(texture2, RectangleF(100.0F, 110.0F, 100, 100));

				delete formGraphics;
				delete formGraphics1;

			}
			catch (System::IO::FileNotFoundException^)
			{
				MessageBox::Show("There was an error opening the bitmap."
					"Please check the path.");
			}
		}

	public:
		void check_status()
		{
			//Server 1
			set_png();
			bool data;
			String ^message;
			std::string ip = "192.168.254.94";
			data = Ping(ip);
			String^ s_ip = gcnew String(ip.c_str());

			if (data == true) {
				pictureBox1->Image = up;
				String^ fileName = "\\\\Asus-pc\\asus_share\\ServerStatus.txt";
				StreamWriter^ sw = gcnew StreamWriter(fileName);
				sw->WriteLine("");
				sw->Close();
				Console::WriteLine("a new file ('{0}') has been written", fileName);


				//Email();


			}
			else {
				pictureBox1->Image = down;
				message = "Server " + s_ip + " is DOWN";
				String^ fileName = "\\\\Asus-pc\\asus_share\\ServerStatus.txt";
				StreamWriter^ sw = gcnew StreamWriter(fileName);
				sw->WriteLine(message);
				sw->Close();
				Console::WriteLine("a new file ('{0}') has been written", fileName);
			}


		}

		void check_status_2()
		{
			//Server 2
			set_png();
			bool data;
			String ^message;
			std::string ip = "192.168.254.65";
			String^ s_ip = gcnew String(ip.c_str());
			data = Ping(ip);

			if (data == true) {
				pictureBox3->Image = up;
				String^ fileName = "\\\\Asus-pc\\asus_share\\ServerStatus.txt";
				StreamWriter^ sw = gcnew StreamWriter(fileName);
				sw->WriteLine("");
				sw->Close();
				Console::WriteLine("a new file ('{0}') has been written", fileName);


			}
			else {
				pictureBox3->Image = down;
				message = "Server " + s_ip + " is DOWN";
				String^ fileName = "\\\\Asus-pc\\asus_share\\ServerStatus.txt";
				StreamWriter^ sw = gcnew StreamWriter(fileName);
				sw->WriteLine(message);
				sw->Close();
				Console::WriteLine("a new file ('{0}') has been written", fileName);
			}


		}
	private: System::Void _timer_Tick(System::Object^ sender, EventArgs ^e)
	{
		backgroundWorker1->RunWorkerAsync();  //starting background worker

	}

	private: System::Void SnowUptimeMonitorForm_Load(System::Object^  sender, System::EventArgs^  e) {
		check_status();
		check_status_2();
	}
	private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {

		while (true)
		{
			if (backgroundWorker1->CancellationPending) //if it was cancelled
			{
				e->Cancel = true;
				break;
			}

			backgroundWorker1->ReportProgress(0, "right");  //reporting progress
			Thread::Sleep(1000);   //wait for 1 second
			break;

		}
	}
	private: System::Void backgroundWorker1_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) {
		check_status();
		check_status_2();

	}
	private: System::Void backgroundWorker1_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {

		if (e->Cancelled)    //Messages for the events
		{
			MessageBox::Show("You have cancelled background worker!!!");
		}

	}
	};
}
