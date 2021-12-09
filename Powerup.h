#ifndef SIMPLEASTEROIDGAME_POWERUP_H
#define SIMPLEASTEROIDGAME_POWERUP_H

#include <wx/wx.h>

enum Upgrades {
    IncreaseGun, IncreaseSpeed, IncreaseHealth, IncreaseFire
};

class Powerup {
private:
    float x, y;
    int size;
    float rotation = 0;
    float xVelocity, yVelocity;
    Upgrades upgrade;

public:
    Powerup();

    Powerup(Upgrades upgrades, float posX, float posY);

    void SetUpgrade(Upgrades upgrade);

    Upgrades GetUpgrade();

    float GetX();

    float GetY();

    int GetSize();

    void Move(wxSize size);

    void CheckBoundary(wxSize size);

    void SetX(float newX);

    void SetY(float newY);

    void DrawPowerup(wxPaintDC &dc);

    bool operator==(const Powerup &p) const;

};

#endif //SIMPLEASTEROIDGAME_POWERUP_H
