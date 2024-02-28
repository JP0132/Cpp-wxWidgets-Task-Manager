#pragma once
#include <wx/wx.h>


class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);

private:
	void CreateControls();
	void BindEventHandlers();
	void AddSavedTasks();

	void OnAddButtonClicked(wxCommandEvent& evt);
	void OnInputKeyboardEnter(wxCommandEvent& evt);
	void OnListKeyDown(wxKeyEvent& evt);
	void OnClearButtonClicked(wxCommandEvent& evt);
	void OnWindowClosed(wxCloseEvent& evt);
	


	void AddTaskFromInput();
	void DeleteSelectedTask();

	//The offset will be +1 or -1 depending on if the task is moved up or down
	void MoveSelectedTask(int offset);
	//Changes the order of the tasks
	void SwapTasks(int i, int j);




	wxPanel* panel;
	wxStaticText* headlineText;
	wxTextCtrl* inputField;
	wxButton* addButton;
	wxCheckListBox* checkListBox;
	wxButton* clearButton;
};
