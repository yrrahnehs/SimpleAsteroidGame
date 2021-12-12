#ifndef SIMPLEASTEROIDGAME_PLAYER_H
#define SIMPLEASTEROIDGAME_PLAYER_H

#include <wx/wx.h>
#include "vector"
#include "Bullet.h"

class Player {
private:
    float xx, yy, spd;
    double rateOfFire;
    int tier;
    int LEFT_WIDTH, RIGHT_WIDTH, HEIGHT;
    float rotation, growingSphere, growingLaser;
    std::vector<Bullet> bullets;
    int health;
    int timeheld = 0;
    int timeheld1 = 0;
    bool armor, nuke, laserGun, forceField;
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

    void SetArmor(bool armorStatus);

    bool GetNuke();

    void SetNuke(bool newNuke);

    bool GetLaserGun();

    void SetLaserGun(bool newLaserGun);

    bool GetForcefield();

    void SetForcefield(bool Forcefield);

    double GetRateOfFire();

    void SetRateOfFire(double newROF);

    float GetIncreasingRadius();

    float GetGrowingLaser();

    void DrawPlayer(wxPaintDC &dc);

    void PlayerMovement(wxSize size);

    void Fire();

    std::vector<Bullet> &GetBullets();

    void DrawBullets(wxPaintDC &dc);

    int GetTier();

    void SetTier(int newTier);

protected:
};


#endif //SIMPLEASTEROIDGAME_PLAYER_H
