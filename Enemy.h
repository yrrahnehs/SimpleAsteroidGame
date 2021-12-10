#ifndef SIMPLEASTEROIDGAME_ENEMY_H
#define SIMPLEASTEROIDGAME_ENEMY_H

#include <wx/wx.h>

class Enemy {
private:
    float x, y, speed, xVel, radius;
    bool isAlive, shot;
    int enemyType;
    double rotation, degree;

public:
    Enemy();

    Enemy(float radius, float x, float y, double speed, int type);

    float GetX() const;

    float GetY() const;

    void SetX(float newX);

    void SetY(float newY);

    int GetRadius() const;

    void SetRadius(int newRadius);

    void DrawEnemy(wxPaintDC &dc);

    void DrawBullets(wxPaintDC &dc);

    void EnemyMovement(wxSize size);

    int EnemySpawn(wxSize size, int offset);

    void Fire();

    void SetSpeed(float newSpeed);

    float GetSpeed() const;

    bool GetStatus();

    bool GetShot();

    void SetShot(bool newShot);

    void SetStatus(bool newStatus);

    int GetEnemyType();

    double GetRotation();

    void SetRotation(double newRotation);

    void SetRateOfFire(int newROF);

    void CheckBoundary(wxSize size);

    bool operator==(const Enemy &e) const;

protected:
};


#endif //SIMPLEASTEROIDGAME_ENEMY_H
