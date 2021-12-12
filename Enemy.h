#ifndef SIMPLEASTEROIDGAME_ENEMY_H
#define SIMPLEASTEROIDGAME_ENEMY_H

#include <wx/wx.h>

class Enemy {
private:
    float x, y, speed, xVel, radius;
    bool isAlive, shot;
    int enemyType, health;
    double rotation, degree;

public:
    Enemy();

    Enemy(float newRadius, float x, float y, float newSpeed, int type);

    float GetX() const;

    float GetY() const;

    void SetX(float newX);

    void SetY(float newY);

    int GetRadius() const;

    void SetRadius(float newRadius);

    int GetHealth() const;

    void SetHealth(int newHealth);

    void DrawEnemy(wxPaintDC &dc);

    void EnemyMovement(wxSize size);

    float EnemySpawn(wxSize size, int offset);

    void SetSpeed(float newSpeed);

    float GetSpeed() const;

    bool GetStatus() const;

    bool GetShot() const;

    void SetShot(bool newShot);

    void SetStatus(bool newStatus);

    int GetEnemyType() const;

    void CheckBoundary(wxSize size);

    bool operator==(const Enemy &e) const;

protected:
};


#endif //SIMPLEASTEROIDGAME_ENEMY_H
