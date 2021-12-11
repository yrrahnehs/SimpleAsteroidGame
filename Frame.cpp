#include "Frame.h"
#include "Gameplay.h"

int style = wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX | wxMINIMIZE_BOX;
Frame::Frame(const std::string &title, const int &frameWidth, const int &frameHeight) :
        wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(frameWidth, frameHeight), style) {
    wxStatusBar *statusBar = CreateStatusBar();
    statusBar->SetStatusText("Points: 0  Health: 100  Speed: 0.7  Fire Rate: 3.3");
    Gameplay *gameplay = new Gameplay(this);
    gameplay->SetFocus();
    gameplay->Start();

}