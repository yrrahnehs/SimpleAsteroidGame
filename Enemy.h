#ifndef SIMPLEASTEROIDGAME_ENEMY_H
#define SIMPLEASTEROIDGAME_ENEMY_H

#include <wx/wx.h>

class Enemy {
private:
    int radius;
    float x, y, speed;
    bool isAlive, shot;

public:
    Enemy();

    Enemy(int radius, float x, float y, double speed);

    float GetX() const;

    float GetY() const;

    void SetX(float newX);

    void SetY(float newY);

    int GetRadius() const;

    void SetRadius(int newRadius);

    void DrawEnemy(wxPaintDC &dc);

    void DrawBullets(wxPaintDC &dc);

    void EnemyMovement();

    int EnemySpawn(wxSize size, int offset);

    void Fire();

    void SetSpeed(float newSpeed);

    float GetSpeed() const;

    bool GetStatus();

    bool GetShot();

    void SetShot(bool newShot);

    void SetStatus(bool newStatus);

    void SetRateOfFire(int newROF);

    bool operator==(const Enemy &e) const;

protected:
};


#endif //SIMPLEASTEROIDGAME_ENEMY_H
