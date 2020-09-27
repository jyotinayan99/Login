#pragma once
#include <string>
#include <msclr\marshal_cppstd.h>
#include <regex>
#using <System.dll>
#using <System.data.dll>

//using namespace std;
using namespace System;
using namespace System::Diagnostics;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Data::OleDb;
namespace CppCLRWinformsProjekt {

	
	
	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	protected:
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button1;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(164, 125);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(198, 22);
			this->textBox1->TabIndex = 0;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(164, 178);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(198, 22);
			this->textBox2->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(50, 125);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(73, 17);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Username";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(50, 183);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(69, 17);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Password";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(216, 259);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Login";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(471, 431);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

		String^ stored_pass;
		try {

			OleDb::OleDbConnection^ DB_Connection = gcnew OleDb::OleDbConnection();
			DB_Connection->ConnectionString = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=Dataset.accdb";
			DB_Connection->Open();

			std::string sname = msclr::interop::marshal_as<std::string>(textBox1->Text);
			//remove_if(sname.begin(), sname.end(), isspace);
			std::string spassword = msclr::interop::marshal_as<std::string>(textBox2->Text);
			//remove_if(spassword.begin(), spassword.end(), isspace);

			std::regex rx("^[A-Z|a-z|.|0-9|_']+$");
			if (!regex_match(sname.cbegin(), sname.cend(), rx)) {
				MessageBox::Show("Enter Username in Correct Format");
				goto ErrExit;
			}

			String^ username = textBox1->Text;
			String^ password = textBox2->Text;
			int hash = password->GetHashCode();
			//password = Convert::ToString(hash);

			String^ getUserData = "Select * from User_Table where [Username] = '" + username + "';";

			//Debug::WriteLine(inputString);
			String^ isApproved;
			//String ^ userCategory; 
			String^ stored_username;
			OleDb::OleDbCommand^ cmd = gcnew OleDb::OleDbCommand(getUserData, DB_Connection);

			OleDb::OleDbDataReader^ user_data = cmd->ExecuteReader();

			while (user_data->Read() == true)
			{
				stored_username = user_data->GetString(1);
				stored_pass = user_data->GetString(2);
			}
			
			DB_Connection->Close();
			if (isApproved == "NO")
			{
				MessageBox::Show("Not approved Yet!");
			}
			else
			{
				if (stored_pass == password)
				{
					if (stored_username == "admin")
					{
						MessageBox::Show("Admin Login Successful!");
						
					}
					else
					{

						MessageBox::Show("User Login Successful!");
					}

				}
				else
				{
					MessageBox::Show("Wrong login credentials");
				}
			}

		}

		catch (Exception^ ex)
		{
			MessageBox::Show(ex->Message);

		}
	ErrExit:
		;

	}
};
}
