#ifndef SIMPLEASTEROIDGAME_PLAYER_H
#define SIMPLEASTEROIDGAME_PLAYER_H

#include <wx/wx.h>
#include "vector"
#include "Bullet.h"

class Player {
private:
    float xx, yy;
    int rateOfFire;
    int upgrade;
    int LEFT_WIDTH, RIGHT_WIDTH, HEIGHT;
    float spd;
    std::vector<Bullet> bullets;
    int health;
    int timeheld = 0;

    void CheckPlayerBoundary(wxSize size);

public:
    Player();

    Player(int width, int height, float speed, int x, int y);

    float GetX() const;

    float GetY() const;

    void MoveX(float x);

    void MoveY(float y);

    int GetWidth() const;

    int GetHeight() const;

    void DrawPlayer(wxPaintDC &dc);

    void DrawBullets(wxPaintDC &dc);

    void PlayerMovement(wxSize size);

    void Fire();

    void SetSpeed(float newSpeed);

    float GetSpeed();

    int GetRateOfFire();

    int GetUpgrade();

    int GetHealth();

    void SetHealth(int newHealth);

    void SetUpgrade(int newUpgrade);

    void SetRateOfFire(int newROF);

    std::vector<Bullet> &GetBullets();

protected:
};




#endif //SIMPLEASTEROIDGAME_PLAYER_H
