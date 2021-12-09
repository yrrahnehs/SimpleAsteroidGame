#include "Enemy.h"

Enemy::Enemy() {}

Enemy::Enemy(int radius, float newX, float newY, double speed) {
    SetRadius(radius);
    SetSpeed(speed);
    SetX(newX);
    SetY(newY);
    isAlive = true;
    shot = false;
}

float Enemy::GetX() const {
    return x;
}

float Enemy::GetY() const {
    return y;
}

void Enemy::SetX(float newX) {
    x = newX;
}

void Enemy::SetY(float newY) {
    y = newY;
}

int Enemy::GetRadius() const {
    return radius;
}

void Enemy::SetRadius(int newRadius) {
    radius = newRadius;
}

void Enemy::SetSpeed(float newSpeed) {
    speed = newSpeed;
}

float Enemy::GetSpeed() const {
    return speed;
}

void Enemy::EnemyMovement() {
    SetY(GetY() + GetSpeed());
}

bool Enemy::GetStatus() {
    return isAlive;
}

bool Enemy::GetShot(){
    return shot;
}

void Enemy::SetShot(bool newShot) {
    shot = newShot;
}

void Enemy::SetStatus(bool newStatus) {
    isAlive = newStatus;
}


void Enemy::DrawEnemy(wxPaintDC &dc) {
    dc.SetPen(wxPen(*wxRED, 1));
    dc.SetBrush(wxBrush(wxColour(179, 12, 24)));
    dc.DrawCircle(GetX(), GetY(), GetRadius());
}

int Enemy::EnemySpawn(wxSize size, int offset) {
    return (rand() % (size.GetWidth() - offset) + offset);
}

bool Enemy::operator==(const Enemy &e) const {
    return (this == &e);
}
