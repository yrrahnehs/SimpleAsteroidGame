#ifndef SIMPLEASTEROIDGAME_PLAYER_H
#define SIMPLEASTEROIDGAME_PLAYER_H

#include <wx/wx.h>
#include "vector"
#include "Bullet.h"

class Player {
private:
    float xx, yy;
    double rateOfFire;
    int upgrade;
    int LEFT_WIDTH, RIGHT_WIDTH, HEIGHT;
    float spd;
    std::vector<Bullet> bullets;
    int health;
    int timeheld = 0;
    bool maxed, armor, nuke;
    float womp, glow, increasingRadius;

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

    void SetSpeed(float newSpeed);

    float GetSpeed();

    int GetHealth();

    void SetHealth(int newHealth);

    bool GetArmor();

    void SetArmor(bool armorStatus);

    bool GetMax();

    void SetMax(bool newMax);

    bool GetNuke();

    void SetNuke(bool newNuke);

    double GetRateOfFire();

    void SetRateOfFire(int newROF);

    float GetIncreasingRadius();

    void DrawPlayer(wxPaintDC &dc);

    void PlayerMovement(wxSize size);

    void Fire();

    std::vector<Bullet> &GetBullets();

    void DrawBullets(wxPaintDC &dc);

    int GetUpgrade();

    void SetUpgrade(int newUpgrade);

protected:
};




#endif //SIMPLEASTEROIDGAME_PLAYER_H
