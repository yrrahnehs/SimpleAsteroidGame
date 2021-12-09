#include <iostream>
#include "main.h"
#include "Frame.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {
    Frame *frame = new Frame("Simple Asteroid Game", 300, 580);
    frame->Center();
    frame->Show(true);
    return true;
}
