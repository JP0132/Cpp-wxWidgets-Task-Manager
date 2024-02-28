#include "MainFrame.h"
#include <wx/wx.h>
#include <string>
#include <vector>
#include "Task.h"


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	CreateControls();
	BindEventHandlers();
	AddSavedTasks();

}

void MainFrame::CreateControls()
{
	wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold());
	wxFont mainFont(wxFontInfo(wxSize(0, 24)));

	panel = new wxPanel(this);
	panel->SetFont(mainFont);

	headlineText = new wxStaticText(panel, wxID_ANY, "Task List",
		wxPoint(0, 22), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
	headlineText->SetFont(headlineFont);

	inputField = new wxTextCtrl(panel, wxID_ANY, "",
		wxPoint(100, 80), wxSize(495, 35), wxTE_PROCESS_ENTER);

	addButton = new wxButton(panel, wxID_ANY, "Add", wxPoint(600, 80), wxSize(100, 35));

	checkListBox = new wxCheckListBox(panel, wxID_ANY, wxPoint(100, 120), wxSize(600, 400));

	clearButton = new wxButton(panel, wxID_ANY, "Clear", wxPoint(100, 525), wxSize(100, 35));

}

void MainFrame::BindEventHandlers()
{	
	//Adding the event to the add button -> on click event
	addButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddButtonClicked, this);

	//Bind for when text is entered and you press enter
	inputField->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnInputKeyboardEnter, this);

	//Bind for when a key is pressed
	checkListBox->Bind(wxEVT_KEY_DOWN, &MainFrame::OnListKeyDown, this);

	//Bind for clear button click
	clearButton->Bind(wxEVT_BUTTON, &MainFrame::OnClearButtonClicked, this);

	this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnCloseWindow, this);


}

void MainFrame::AddSavedTasks()
{
	std::vector<Task> tasks = LoadTasksFromFile("tasks.txt");

	for (const Task& task : tasks) {
		int index = checkListBox->GetCount();
		checkListBox->Check(index, task.done);
	}

}

void MainFrame::OnAddButtonClicked(wxCommandEvent& evt)
{
	//Calls the method that handles what to do when clicked
	AddTaskFromInput();
}

void MainFrame::OnInputKeyboardEnter(wxCommandEvent& evt)
{
	AddTaskFromInput();
}

void MainFrame::OnListKeyDown(wxKeyEvent& evt)
{
	//Switch case for checking which key has been pressed and calling the appropiate method
	switch (evt.GetKeyCode()) {
		//Delete key
		case WXK_DELETE:
			DeleteSelectedTask();
			break;
		case WXK_UP:
			MoveSelectedTask(-1);
			break;
		case WXK_DOWN:
			MoveSelectedTask(1);
			break;
	}
}

void MainFrame::OnClearButtonClicked(wxCommandEvent& evt)
{
	if (checkListBox->IsEmpty()) {
		return;
	}

	wxMessageDialog dialog(this, "Do you want to clear all tasks?", "Clear", wxYES_NO | wxCANCEL);
	int result = dialog.ShowModal();

	if (result == wxID_YES) {
		checkListBox->Clear();
	}
}

void MainFrame::OnWindowClosed(wxCloseEvent& evt)
{
	std::vector<Task> tasks;

	for (int i = 0; i < checkListBox->GetCount(); i++) {
		Task task;
		task.description = checkListBox->GetString(i);
		task.done = checkListBox->IsChecked(i);
		tasks.push_back(task);
	}

	SaveTasksToFile(tasks, "tasks.txt");
	evt.Skip();
}

void MainFrame::AddTaskFromInput()
{
	//Get the value
	wxString description = inputField->GetValue();

	//Add the task to the checklistbox, and clear the input field of text
	if(!description.IsEmpty()) {
		checkListBox->Insert(description, checkListBox->GetCount());
		inputField->Clear();
	}

	//Keeps the input field active
	inputField->SetFocus();
}

void MainFrame::DeleteSelectedTask()
{
	//Gets the index of the task that has been selected
	int selectedIndex = checkListBox->GetSelection();

	//If nothing has been selected then it deletes nothing
	if (selectedIndex == wxNOT_FOUND) {
		return;
	}

	//Deletes the task from the check box widget
	checkListBox->Delete(selectedIndex);
}

void MainFrame::MoveSelectedTask(int offset)
{
	//Get selected task

	int selectedIndex = checkListBox->GetSelection();

	//If not found do nothing
	if (selectedIndex == wxNOT_FOUND) {
		return;
	}

	//The new index of where it will be swapped
	int newIndex = selectedIndex + offset;
	
	//Swaps the tasks around if need be
	if (newIndex >= 0 && newIndex < checkListBox->GetCount()) {
		SwapTasks(selectedIndex, newIndex);
		checkListBox->SetSelection(newIndex, true);
	}
}

void MainFrame::SwapTasks(int i, int j)
{
	Task taskSelected{
		checkListBox->GetString(i).ToStdString(),
		checkListBox->IsChecked(i)
	};

	Task taskToBeSwappedWith{
		checkListBox->GetString(j).ToStdString(),
		checkListBox->IsChecked(j)
	};

	checkListBox->SetString(i, taskToBeSwappedWith.description);
	checkListBox->Check(i, taskToBeSwappedWith.done);

	checkListBox->SetString(j, taskSelected.description);
	checkListBox->Check(j, taskSelected.done);

}
