#pragma once
#include <msclr\marshal_cppstd.h>
#include <sstream>
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

	enum OutputBoxColumn {
		NUM, TASKTEXT, START, END, TAGS, DONE
	};

	public ref class Swiftask : public System::Windows::Forms::Form
	{
	private: 
		Logic* logic;
		UIFeedback* feedback;

	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Index;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Tasks;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Start;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  End;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Tags;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Completed;

	public:
		Swiftask(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			logic = new Logic("mytextfile.txt");
			feedback = new UIFeedback;

			// to load the saved file if any
			logic->executeCommand("");
			updateOutputBox();
		}
		// Gets user input command from commandBox and return it in std::string
		// Clears the commandBox
	private: std:: string getStdStringCommand(void);

		// Processes after the command is executed that update the UI components and their helper functions
	private: void updateUI(void);
	private: void updateResults(void);
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
			this->Index = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Tasks = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Start = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->End = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Tags = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Completed = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
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
			this->outputBox->BackgroundColor = System::Drawing::SystemColors::ControlLightLight;
			this->outputBox->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->outputBox->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(6) {this->Index, this->Tasks, 
				this->Start, this->End, this->Tags, this->Completed});
			this->outputBox->Location = System::Drawing::Point(0, 1);
			this->outputBox->Name = L"outputBox";
			this->outputBox->ReadOnly = true;
			this->outputBox->Size = System::Drawing::Size(763, 275);
			this->outputBox->TabIndex = 0;
			// 
			// Index
			// 
			this->Index->HeaderText = L"No.";
			this->Index->Name = L"Index";
			this->Index->ReadOnly = true;
			this->Index->Width = 32;
			// 
			// Tasks
			// 
			this->Tasks->HeaderText = L"Tasks";
			this->Tasks->Name = L"Tasks";
			this->Tasks->ReadOnly = true;
			this->Tasks->Width = 256;
			// 
			// Start
			// 
			this->Start->HeaderText = L"Start";
			this->Start->Name = L"Start";
			this->Start->ReadOnly = true;
			this->Start->Width = 128;
			// 
			// End
			// 
			this->End->HeaderText = L"End";
			this->End->Name = L"End";
			this->End->ReadOnly = true;
			this->End->Width = 128;
			// 
			// Tags
			// 
			this->Tags->HeaderText = L"Tags";
			this->Tags->Name = L"Tags";
			this->Tags->ReadOnly = true;
			this->Tags->Width = 128;
			// 
			// Completed
			// 
			this->Completed->HeaderText = L"Done";
			this->Completed->Name = L"Completed";
			this->Completed->ReadOnly = true;
			this->Completed->Resizable = System::Windows::Forms::DataGridViewTriState::True;
			this->Completed->Width = 48;
			// 
			// commandBox
			// 
			this->commandBox->AutoCompleteCustomSource->AddRange(gcnew cli::array< System::String^  >(8) {L"add ", L"clear ", L"complete ", 
				L"delete ", L"display ", L"exit ", L"search ", L"sort "});
			this->commandBox->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Suggest;
			this->commandBox->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::CustomSource;
			this->commandBox->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->commandBox->Location = System::Drawing::Point(0, 315);
			this->commandBox->Name = L"commandBox";
			this->commandBox->Size = System::Drawing::Size(763, 20);
			this->commandBox->TabIndex = 1;
			this->commandBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Swiftask::commandBox_KeyDown);
			// 
			// results
			// 
			this->results->AutoSize = true;
			this->results->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->results->Location = System::Drawing::Point(0, 302);
			this->results->Name = L"results";
			this->results->Size = System::Drawing::Size(253, 13);
			this->results->TabIndex = 2;
			this->results->Text = L"Switask is ready. Enter command below to continue.";
			// 
			// Swiftask
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->ClientSize = System::Drawing::Size(763, 335);
			this->Controls->Add(this->results);
			this->Controls->Add(this->commandBox);
			this->Controls->Add(this->outputBox);
			this->Name = L"Swiftask";
			this->Text = L"Swiftask";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// When the enter key is pressed, UI will take in the command string and call logic->executeCommand.
		// A UIFeedback obj is returned from logic->executeCommand and the UI is updated.
	private: System::Void commandBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 if (e->KeyCode == Keys::Enter) {
					 
					 (*feedback) = logic->executeCommand(getStdStringCommand());

					 assert(feedback != NULL);

					 updateUI();
				 }

				 return;
			 }

	};
}
