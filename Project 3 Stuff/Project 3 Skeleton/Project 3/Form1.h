
#pragma once

namespace Project3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  picTriangle;
	protected: 
	private: System::Windows::Forms::Label^  lblDescription;
	private: System::Windows::Forms::Label^  lblA;
	private: System::Windows::Forms::Label^  lblB;
	private: System::Windows::Forms::Label^  lblC;
	private: System::Windows::Forms::TextBox^  txtAx;
	private: System::Windows::Forms::TextBox^  txtAy;
	private: System::Windows::Forms::TextBox^  txtAz;
	private: System::Windows::Forms::TextBox^  txtBx;
	private: System::Windows::Forms::TextBox^  txtBy;
	private: System::Windows::Forms::TextBox^  txtBz;
	private: System::Windows::Forms::TextBox^  txtCz;
	private: System::Windows::Forms::TextBox^  txtCy;
	private: System::Windows::Forms::TextBox^  txtCx;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  lblLenA;
	private: System::Windows::Forms::Label^  lblLenB;
	private: System::Windows::Forms::Label^  lblLenC;
	private: System::Windows::Forms::Label^  lblAngleC;
	private: System::Windows::Forms::Label^  lblAngleB;
	private: System::Windows::Forms::Label^  lblAngleA;
	private: System::Windows::Forms::Button^  btnCalculate;
	private: System::Windows::Forms::Button^  btnClear;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->picTriangle = (gcnew System::Windows::Forms::PictureBox());
			this->lblDescription = (gcnew System::Windows::Forms::Label());
			this->lblA = (gcnew System::Windows::Forms::Label());
			this->lblB = (gcnew System::Windows::Forms::Label());
			this->lblC = (gcnew System::Windows::Forms::Label());
			this->txtAx = (gcnew System::Windows::Forms::TextBox());
			this->txtAy = (gcnew System::Windows::Forms::TextBox());
			this->txtAz = (gcnew System::Windows::Forms::TextBox());
			this->txtBx = (gcnew System::Windows::Forms::TextBox());
			this->txtBy = (gcnew System::Windows::Forms::TextBox());
			this->txtBz = (gcnew System::Windows::Forms::TextBox());
			this->txtCz = (gcnew System::Windows::Forms::TextBox());
			this->txtCy = (gcnew System::Windows::Forms::TextBox());
			this->txtCx = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->lblLenA = (gcnew System::Windows::Forms::Label());
			this->lblLenB = (gcnew System::Windows::Forms::Label());
			this->lblLenC = (gcnew System::Windows::Forms::Label());
			this->lblAngleC = (gcnew System::Windows::Forms::Label());
			this->lblAngleB = (gcnew System::Windows::Forms::Label());
			this->lblAngleA = (gcnew System::Windows::Forms::Label());
			this->btnCalculate = (gcnew System::Windows::Forms::Button());
			this->btnClear = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picTriangle))->BeginInit();
			this->SuspendLayout();
			// 
			// picTriangle
			// 
			this->picTriangle->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->picTriangle->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"picTriangle.Image")));
			this->picTriangle->Location = System::Drawing::Point(312, 12);
			this->picTriangle->Name = L"picTriangle";
			this->picTriangle->Size = System::Drawing::Size(372, 158);
			this->picTriangle->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->picTriangle->TabIndex = 0;
			this->picTriangle->TabStop = false;
			// 
			// lblDescription
			// 
			this->lblDescription->AutoSize = true;
			this->lblDescription->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblDescription->Location = System::Drawing::Point(18, 48);
			this->lblDescription->Name = L"lblDescription";
			this->lblDescription->Size = System::Drawing::Size(288, 80);
			this->lblDescription->TabIndex = 1;
			this->lblDescription->Text = L"Three points in 3D space define a triangle.\r\n\r\nSupply three points A, B and C and" 
				L" the program\r\nwill determine the distances a, b and c and the\r\nangles at A, B an" 
				L"d C.";
			// 
			// lblA
			// 
			this->lblA->AutoSize = true;
			this->lblA->Location = System::Drawing::Point(29, 214);
			this->lblA->Name = L"lblA";
			this->lblA->Size = System::Drawing::Size(44, 13);
			this->lblA->TabIndex = 2;
			this->lblA->Text = L"Point A:";
			// 
			// lblB
			// 
			this->lblB->AutoSize = true;
			this->lblB->Location = System::Drawing::Point(29, 243);
			this->lblB->Name = L"lblB";
			this->lblB->Size = System::Drawing::Size(44, 13);
			this->lblB->TabIndex = 3;
			this->lblB->Text = L"Point B:";
			// 
			// lblC
			// 
			this->lblC->AutoSize = true;
			this->lblC->Location = System::Drawing::Point(29, 269);
			this->lblC->Name = L"lblC";
			this->lblC->Size = System::Drawing::Size(44, 13);
			this->lblC->TabIndex = 4;
			this->lblC->Text = L"Point C:";
			// 
			// txtAx
			// 
			this->txtAx->Location = System::Drawing::Point(95, 212);
			this->txtAx->Name = L"txtAx";
			this->txtAx->Size = System::Drawing::Size(40, 20);
			this->txtAx->TabIndex = 5;
			// 
			// txtAy
			// 
			this->txtAy->Location = System::Drawing::Point(141, 212);
			this->txtAy->Name = L"txtAy";
			this->txtAy->Size = System::Drawing::Size(40, 20);
			this->txtAy->TabIndex = 6;
			// 
			// txtAz
			// 
			this->txtAz->Location = System::Drawing::Point(187, 212);
			this->txtAz->Name = L"txtAz";
			this->txtAz->Size = System::Drawing::Size(40, 20);
			this->txtAz->TabIndex = 7;
			// 
			// txtBx
			// 
			this->txtBx->Location = System::Drawing::Point(95, 239);
			this->txtBx->Name = L"txtBx";
			this->txtBx->Size = System::Drawing::Size(40, 20);
			this->txtBx->TabIndex = 8;
			// 
			// txtBy
			// 
			this->txtBy->Location = System::Drawing::Point(141, 239);
			this->txtBy->Name = L"txtBy";
			this->txtBy->Size = System::Drawing::Size(40, 20);
			this->txtBy->TabIndex = 9;
			// 
			// txtBz
			// 
			this->txtBz->Location = System::Drawing::Point(187, 239);
			this->txtBz->Name = L"txtBz";
			this->txtBz->Size = System::Drawing::Size(40, 20);
			this->txtBz->TabIndex = 10;
			// 
			// txtCz
			// 
			this->txtCz->Location = System::Drawing::Point(187, 266);
			this->txtCz->Name = L"txtCz";
			this->txtCz->Size = System::Drawing::Size(40, 20);
			this->txtCz->TabIndex = 13;
			// 
			// txtCy
			// 
			this->txtCy->Location = System::Drawing::Point(141, 266);
			this->txtCy->Name = L"txtCy";
			this->txtCy->Size = System::Drawing::Size(40, 20);
			this->txtCy->TabIndex = 12;
			// 
			// txtCx
			// 
			this->txtCx->Location = System::Drawing::Point(95, 266);
			this->txtCx->Name = L"txtCx";
			this->txtCx->Size = System::Drawing::Size(40, 20);
			this->txtCx->TabIndex = 11;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(108, 196);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(109, 13);
			this->label4->TabIndex = 14;
			this->label4->Text = L"x               y              z";
			// 
			// lblLenA
			// 
			this->lblLenA->AutoSize = true;
			this->lblLenA->Location = System::Drawing::Point(398, 216);
			this->lblLenA->Name = L"lblLenA";
			this->lblLenA->Size = System::Drawing::Size(49, 13);
			this->lblLenA->TabIndex = 15;
			this->lblLenA->Text = L"Length a";
			this->lblLenA->Visible = false;
			// 
			// lblLenB
			// 
			this->lblLenB->AutoSize = true;
			this->lblLenB->Location = System::Drawing::Point(396, 243);
			this->lblLenB->Name = L"lblLenB";
			this->lblLenB->Size = System::Drawing::Size(49, 13);
			this->lblLenB->TabIndex = 16;
			this->lblLenB->Text = L"Length b";
			this->lblLenB->Visible = false;
			// 
			// lblLenC
			// 
			this->lblLenC->AutoSize = true;
			this->lblLenC->Location = System::Drawing::Point(396, 270);
			this->lblLenC->Name = L"lblLenC";
			this->lblLenC->Size = System::Drawing::Size(49, 13);
			this->lblLenC->TabIndex = 17;
			this->lblLenC->Text = L"Length c";
			this->lblLenC->Visible = false;
			// 
			// lblAngleC
			// 
			this->lblAngleC->AutoSize = true;
			this->lblAngleC->Location = System::Drawing::Point(526, 270);
			this->lblAngleC->Name = L"lblAngleC";
			this->lblAngleC->Size = System::Drawing::Size(44, 13);
			this->lblAngleC->TabIndex = 20;
			this->lblAngleC->Text = L"Angle C";
			this->lblAngleC->Visible = false;
			// 
			// lblAngleB
			// 
			this->lblAngleB->AutoSize = true;
			this->lblAngleB->Location = System::Drawing::Point(526, 243);
			this->lblAngleB->Name = L"lblAngleB";
			this->lblAngleB->Size = System::Drawing::Size(44, 13);
			this->lblAngleB->TabIndex = 19;
			this->lblAngleB->Text = L"Angle B";
			this->lblAngleB->Visible = false;
			// 
			// lblAngleA
			// 
			this->lblAngleA->AutoSize = true;
			this->lblAngleA->Location = System::Drawing::Point(526, 216);
			this->lblAngleA->Name = L"lblAngleA";
			this->lblAngleA->Size = System::Drawing::Size(44, 13);
			this->lblAngleA->TabIndex = 18;
			this->lblAngleA->Text = L"Angle A";
			this->lblAngleA->Visible = false;
			// 
			// btnCalculate
			// 
			this->btnCalculate->Location = System::Drawing::Point(273, 227);
			this->btnCalculate->Name = L"btnCalculate";
			this->btnCalculate->Size = System::Drawing::Size(88, 20);
			this->btnCalculate->TabIndex = 21;
			this->btnCalculate->Text = L"Calculate";
			this->btnCalculate->UseVisualStyleBackColor = true;
			this->btnCalculate->Click += gcnew System::EventHandler(this, &Form1::btnCalculate_Click);
			// 
			// btnClear
			// 
			this->btnClear->Location = System::Drawing::Point(275, 264);
			this->btnClear->Name = L"btnClear";
			this->btnClear->Size = System::Drawing::Size(86, 22);
			this->btnClear->TabIndex = 22;
			this->btnClear->Text = L"Clear";
			this->btnClear->UseVisualStyleBackColor = true;
			this->btnClear->Click += gcnew System::EventHandler(this, &Form1::btnClear_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(696, 333);
			this->Controls->Add(this->btnClear);
			this->Controls->Add(this->btnCalculate);
			this->Controls->Add(this->lblAngleC);
			this->Controls->Add(this->lblAngleB);
			this->Controls->Add(this->lblAngleA);
			this->Controls->Add(this->lblLenC);
			this->Controls->Add(this->lblLenB);
			this->Controls->Add(this->lblLenA);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->txtCz);
			this->Controls->Add(this->txtCy);
			this->Controls->Add(this->txtCx);
			this->Controls->Add(this->txtBz);
			this->Controls->Add(this->txtBy);
			this->Controls->Add(this->txtBx);
			this->Controls->Add(this->txtAz);
			this->Controls->Add(this->txtAy);
			this->Controls->Add(this->txtAx);
			this->Controls->Add(this->lblC);
			this->Controls->Add(this->lblB);
			this->Controls->Add(this->lblA);
			this->Controls->Add(this->lblDescription);
			this->Controls->Add(this->picTriangle);
			this->Name = L"Form1";
			this->Text = L"3D Triangles";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picTriangle))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion



	private: System::Void btnCalculate_Click(System::Object^  sender, System::EventArgs^  e) 
	{

	}


private: System::Void btnClear_Click(System::Object^  sender, System::EventArgs^  e) 
	{

	}
};
}

