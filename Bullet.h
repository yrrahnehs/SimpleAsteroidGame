#ifndef SIMPLEASTEROIDGAME_BULLET_H
#define SIMPLEASTEROIDGAME_BULLET_H


#include <wx/wx.h>

class Bullet {

private:
    int x, y;
    int velocity;
    int WIDTH, HEIGHT;
    bool trigger;

public:
    Bullet();

    Bullet(int bulletX, int bulletY, int bulletVelocity);

    void SetVelocity(int newVelocity);

    int GetX();

    int GetY();

    int GetWidth();

    int GetHeight();

    bool IsFired();

    void SetTrigger(bool fire);

    void SetWidth(int newWidth);

    void SetHeight(int newHeight);

    void SetX(int &newX);

    void SetY(int &newY);

    void Move();

    void DrawBullet(wxPaintDC &dc);

    bool operator==(const Bullet &e) const;
};

#endif //SIMPLEASTEROIDGAME_BULLET_H
