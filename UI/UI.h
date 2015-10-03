#pragma once
#include <msclr\marshal_cppstd.h>
#include "..\Logic\Logic.h"

namespace UI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Swiftask
	/// </summary>
	public ref class Swiftask : public System::Windows::Forms::Form
	{
	private: 
		bool isEntered;
		Logic* logic;
		UIFeedback* feedback;
		API::Task* task;
	public:
		Swiftask(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			isEntered = false;
			logic = new Logic("mytextfile.txt");
			feedback = new UIFeedback;
			task = new API::Task;
		}
	private: void updateOutputBox(void);
	private: void clearOutputBox(void);
	private: void displayInOutputBox(void);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Swiftask()
		{
			if (components)
			{
				delete components;
				delete logic;
			}
		}
	private: System::Windows::Forms::DataGridView^  outputBox;
	protected: 

	protected: 
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Task;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Start;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  End;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Tags;
	private: System::Windows::Forms::TextBox^  commandBox;
	private: System::Windows::Forms::Label^  results;

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
			this->outputBox = (gcnew System::Windows::Forms::DataGridView());
			this->Task = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Start = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->End = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Tags = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->commandBox = (gcnew System::Windows::Forms::TextBox());
			this->results = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// outputBox
			// 
			this->outputBox->AllowUserToAddRows = false;
			this->outputBox->AllowUserToDeleteRows = false;
			this->outputBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->outputBox->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->outputBox->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {this->Task, this->Start, 
				this->End, this->Tags});
			this->outputBox->Location = System::Drawing::Point(0, 1);
			this->outputBox->Name = L"outputBox";
			this->outputBox->ReadOnly = true;
			this->outputBox->Size = System::Drawing::Size(444, 201);
			this->outputBox->TabIndex = 0;
			// 
			// Task
			// 
			this->Task->HeaderText = L"Task";
			this->Task->Name = L"Task";
			this->Task->ReadOnly = true;
			// 
			// Start
			// 
			this->Start->HeaderText = L"Start";
			this->Start->Name = L"Start";
			this->Start->ReadOnly = true;
			// 
			// End
			// 
			this->End->HeaderText = L"End";
			this->End->Name = L"End";
			this->End->ReadOnly = true;
			// 
			// Tags
			// 
			this->Tags->HeaderText = L"Tags";
			this->Tags->Name = L"Tags";
			this->Tags->ReadOnly = true;
			// 
			// commandBox
			// 
			this->commandBox->AutoCompleteCustomSource->AddRange(gcnew cli::array< System::String^  >(7) {L"add", L"clear", L"delete", 
				L"display", L"exit", L"search", L"sort"});
			this->commandBox->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Suggest;
			this->commandBox->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::CustomSource;
			this->commandBox->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->commandBox->Location = System::Drawing::Point(0, 241);
			this->commandBox->Name = L"commandBox";
			this->commandBox->Size = System::Drawing::Size(444, 20);
			this->commandBox->TabIndex = 1;
			this->commandBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Swiftask::commandBox_KeyDown);
			// 
			// results
			// 
			this->results->AutoSize = true;
			this->results->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->results->Location = System::Drawing::Point(0, 228);
			this->results->Name = L"results";
			this->results->Size = System::Drawing::Size(253, 13);
			this->results->TabIndex = 2;
			this->results->Text = L"Switask is ready. Enter command below to continue.";
			// 
			// Swiftask
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(444, 261);
			this->Controls->Add(this->results);
			this->Controls->Add(this->commandBox);
			this->Controls->Add(this->outputBox);
			this->Name = L"Swiftask";
			this->Text = L"Swiftask";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void commandBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 if (e->KeyCode == Keys::Enter) {
					 if (isEntered) {
						 System::String^ managed;

						 managed = commandBox->Text;
						 commandBox->Text = "";

						 std::string unmanaged = msclr::interop::marshal_as<std::string>(managed);
						 (*feedback) = logic->executeCommand(unmanaged);

						 assert(feedback != NULL);

						 managed = gcnew String((*feedback).getFeedbackMessage().c_str());
						 results->Text = managed;
						 delete managed;

						 updateOutputBox();

						 isEntered = false;
					 } else {
						 results->Text = "Enter again to continue";
					 }
					 isEntered = true;
				 } else {
					 isEntered = false;
				 }
			 }
	};
}
