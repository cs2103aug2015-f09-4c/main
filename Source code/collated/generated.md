# generated
###### UI\UI.h
``` h
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

```
###### UI\UI.h
``` h
		System::Windows::Forms::DataGridViewTextBoxColumn^  number;
		System::Windows::Forms::DataGridViewTextBoxColumn^  tasks;
		System::Windows::Forms::DataGridViewTextBoxColumn^  start;
		System::Windows::Forms::DataGridViewTextBoxColumn^  end;
		System::Windows::Forms::DataGridViewTextBoxColumn^  tags;
		System::Windows::Forms::DataGridViewTextBoxColumn^  done;

	public:
```
###### UI\UI.h
``` h
		System::Windows::Forms::DataGridView^  outputBox;
		System::Windows::Forms::TextBox^  commandBox;
		System::Windows::Forms::Label^  results;

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
			this->number = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->tasks = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->start = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->end = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->tags = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->done = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->commandBox = (gcnew System::Windows::Forms::TextBox());
			this->results = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// outputBox
			// 
			this->outputBox->AllowUserToAddRows = false;
			this->outputBox->AllowUserToDeleteRows = false;
			this->outputBox->AllowUserToResizeRows = false;
			this->outputBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->outputBox->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->outputBox->BackgroundColor = System::Drawing::SystemColors::ControlLightLight;
			this->outputBox->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::None;
			this->outputBox->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::None;
			this->outputBox->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->outputBox->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(6) {this->number, this->tasks, 
				this->start, this->end, this->tags, this->done});
			this->outputBox->Location = System::Drawing::Point(0, 1);
			this->outputBox->Name = L"outputBox";
			this->outputBox->ReadOnly = true;
			this->outputBox->RowHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::None;
			this->outputBox->Size = System::Drawing::Size(763, 275);
			this->outputBox->TabIndex = 0;
			// 
			// number
			// 
			this->number->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->number->FillWeight = 40.83333F;
			this->number->Frozen = true;
			this->number->HeaderText = L"No.";
			this->number->Name = L"number";
			this->number->ReadOnly = true;
			this->number->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->number->Width = 32;
			// 
			// tasks
			// 
			this->tasks->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->tasks->FillWeight = 77.49965F;
			this->tasks->HeaderText = L"Tasks";
			this->tasks->Name = L"tasks";
			this->tasks->ReadOnly = true;
			// 
			// start
			// 
			this->start->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->start->FillWeight = 89.46249F;
			this->start->HeaderText = L"Start";
			this->start->Name = L"start";
			this->start->ReadOnly = true;
			this->start->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->start->Width = 128;
			// 
			// end
			// 
			this->end->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->end->FillWeight = 103.3426F;
			this->end->HeaderText = L"End";
			this->end->Name = L"end";
			this->end->ReadOnly = true;
			this->end->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->end->Width = 128;
			// 
			// tags
			// 
			this->tags->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->tags->FillWeight = 133.0929F;
			this->tags->HeaderText = L"Tags";
			this->tags->Name = L"tags";
			this->tags->ReadOnly = true;
			this->tags->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->tags->Width = 128;
			// 
			// done
			// 
			this->done->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::None;
			this->done->FillWeight = 155.769F;
			this->done->HeaderText = L"Done";
			this->done->Name = L"done";
			this->done->ReadOnly = true;
			this->done->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->done->Width = 48;
			// 
			// commandBox
			// 
			this->commandBox->AutoCompleteCustomSource->AddRange(gcnew cli::array< System::String^  >(50) {L"ADD taskname FROM datetime TO datetime (tags)", 
				L"ADD taskname BY datetime (tags)", L"ADD taskname (tags)", L"", L"COMPLETE index", L"", L"CONFIGURE SAVE LOCATION saveLocation", 
				L"", L"DELETE ALL", L"DELETE COMPLETED", L"DELETE index", L"DELETE BY datetime", L"DELETE FROM datetime TO datetime", L"DELETE FROM datetime", 
				L"", L"DISPLAY ALL", L"DISPLAY ACTIVITY", L"DISPLAY TODO", L"DISPLAY FLOATING", L"", L"EDIT NAME index newName", L"EDIT START index newStartDatetime", 
				L"EDIT END index newEndDatetime", L"", L"EXPORT exportLocation", L"", L"IMPORT importLocation", L"", L"REFRESH", L"", L"SEARCH NAME queryName", 
				L"SEARCH FROM datetime TO datetime", L"SEARCH START BEFORE queryDatetime", L"SEARCH START AFTER queryDatetime", L"SEARCH END BEFORE queryDatetime", 
				L"SEARCH END AFTER queryDatetime", L"SEARCH TAGS tags", L"", L"SORT NAME", L"SORT NAME DESC", L"SORT START", L"SORT START DESC", 
				L"SORT END", L"SORT END DESC", L"", L"TAG index tags", L"", L"UNDO", L"", L"UNTAG index tags"});
			this->commandBox->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Suggest;
			this->commandBox->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::CustomSource;
			this->commandBox->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->commandBox->Location = System::Drawing::Point(0, 315);
			this->commandBox->MaxLength = 144;
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
			this->MinimumSize = System::Drawing::Size(579, 374);
			this->Name = L"Swiftask";
			this->Text = L"Swiftask";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: 
```
