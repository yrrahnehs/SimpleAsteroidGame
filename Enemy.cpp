#include "Enemy.h"

Enemy::Enemy() {}

Enemy::Enemy(float radius, float newX, float newY, double speed, int type) {
    SetRadius(radius);
    SetSpeed(speed);
    SetX(newX);
    SetY(newY);
    int random = rand() % 2;
    double direction;
    if (random == 0) {
        direction = -1;
    } else {
        direction = 1;
    }
    xVel = GetSpeed() / 3 * direction;
    isAlive = true;
    shot = false;
    enemyType = type;
    rotation = 0;
    degree = -0.0122173;
    health = 25;
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

int Enemy::GetHealth() const {
    return health;
}

void Enemy::SetHealth(int newHealth) {
    health = newHealth;
}

void Enemy::SetSpeed(float newSpeed) {
    speed = newSpeed;
}

float Enemy::GetSpeed() const {
    return speed;
}

bool Enemy::GetStatus() {
    return isAlive;
}

bool Enemy::GetShot() {
    return shot;
}

void Enemy::SetShot(bool newShot) {
    shot = newShot;
}

void Enemy::SetStatus(bool newStatus) {
    isAlive = newStatus;
}

int Enemy::GetEnemyType() {
    return enemyType;
}

double Enemy::GetRotation() {
    return rotation;
}

void Enemy::SetRotation(double newRotation) {
    rotation = newRotation;
}

void Enemy::EnemyMovement(wxSize size) {
    SetY(GetY() + GetSpeed());

    if (GetEnemyType() == 1) {
        SetX(GetX() + xVel);
        rotation += degree;
        CheckBoundary(size);
    }

}

void Enemy::CheckBoundary(wxSize size) {
    if (GetX() + GetRadius() >= size.GetWidth() || GetX() - GetRadius() < 0) {
        xVel *= -1;
        degree *= -1;
    }
    if (GetY() - GetRadius() > size.GetHeight()) {
        SetY(-GetRadius() * 2);
    }
}

void Enemy::DrawEnemy(wxPaintDC &dc) {
    if (GetEnemyType() == 0) {
        dc.SetPen(wxPen(*wxRED, 1));
        dc.SetBrush(wxBrush(wxColour(179, 12, 24)));
        dc.DrawCircle(GetX(), GetY(), GetRadius());
    }
    if (GetEnemyType() == 1) {
        dc.SetPen(wxPen(*wxRED, 1));
        dc.SetBrush(wxBrush(wxColour(46, 8, 18)));
        wxPoint square[4];
        square[0] = wxPoint(
                ((sqrt(2 * pow(GetRadius(), 2)) - 2) * cos(-0.785398 + rotation) + GetX()),
                ((sqrt(2 * pow(GetRadius(), 2)) - 2) * sin(-0.785398 + rotation) + GetY()));
        square[1] = wxPoint(
                ((sqrt(2 * pow(GetRadius(), 2)) - 2) * cos(0.785398 + rotation) + GetX()),
                ((sqrt(2 * pow(GetRadius(), 2)) - 2) * sin(0.785398 + rotation) + GetY()));
        square[2] = wxPoint(
                ((sqrt(2 * pow(GetRadius(), 2)) - 2) * cos(2.35619 + rotation) + GetX()),
                ((sqrt(2 * pow(GetRadius(), 2)) - 2) * sin(2.35619 + rotation) + GetY()));
        square[3] = wxPoint(
                ((sqrt(2 * pow(GetRadius(), 2)) - 2) * cos(3.92699 + rotation) + GetX()),
                ((sqrt(2 * pow(GetRadius(), 2)) - 2) * sin(3.92699 + rotation) + GetY()));
        dc.DrawPolygon(4, square);
        dc.SetBrush(wxBrush(wxColour(179, 12, 24)));
        dc.DrawCircle(GetX(), GetY(), GetRadius());
    }
    if (GetEnemyType() == 2) {
        dc.SetPen(wxPen(*wxRED, 1));
        dc.SetBrush(wxBrush(wxColour(179, 12, 24)));
        dc.DrawRectangle(GetX(), GetY(), GetRadius(), 15);
    }
}

int Enemy::EnemySpawn(wxSize size, int offset) {
    if (GetEnemyType() == 2) {
        float quarter = (size.GetWidth() / 4);
        SetRadius((int) quarter);
        int random = rand() % 4 + 1;
        return (quarter * random);
    } else {
        return (rand() % (size.GetWidth() - (offset * 2)) + offset);
    }
}

bool Enemy::operator==(const Enemy &e) const {
    return (this == &e);
}
