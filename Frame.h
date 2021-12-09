#ifndef SIMPLEASTEROIDGAME_FRAME_H
#define SIMPLEASTEROIDGAME_FRAME_H

#include <wx/wx.h>

class Frame : public wxFrame {
public:
    Frame(const std::string &title, const int &frameWidth, const int &frameHeight);
};


#endif //SIMPLEASTEROIDGAME_FRAME_H
