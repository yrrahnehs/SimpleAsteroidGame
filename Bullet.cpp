#include "Bullet.h"

Bullet::Bullet() {}

Bullet::Bullet(int bulletX, int bulletY, int bulletVelocity) {
    SetVelocity(bulletVelocity);
    trigger = false;
    SetX(bulletX);
    SetY(bulletY);
    SetWidth(2);
    SetHeight(5);
}

int Bullet::GetVelocity() {
    return velocity;
}

void Bullet::SetVelocity(int newVelocity) {
    velocity = newVelocity;
}

int Bullet::GetX() {
    return x;
}

int Bullet::GetY() {
    return y;
}

int Bullet::GetWidth() {
    return WIDTH;
}

int Bullet::GetHeight() {
    return HEIGHT;
}

void Bullet::SetX(int &newX) {
    x = newX;
}

void Bullet::SetY(int &newY) {
    y = newY;
}

void Bullet::SetWidth(int newWidth) {
    WIDTH = newWidth;
}

void Bullet::SetHeight(int newHeight) {
    HEIGHT = newHeight;
}

void Bullet::Move() {
    int newY = GetY() - velocity;
    SetY(newY);
}

void Bullet::OnKeyDown(wxKeyEvent &event) {
    int keycode = event.GetKeyCode();
    if (keycode == WXK_SPACE) {
        int newY = GetY() - velocity;
        SetY(newY);
    }
}

void Bullet::DrawBullet(wxPaintDC &dc) {
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBrush(wxBrush(wxColour(242, 245, 66)));
    dc.DrawRectangle(GetX(), GetY(), GetWidth(), GetHeight());
}

bool Bullet::IsFired() {
    return trigger;
}

void Bullet::SetTrigger(bool fire) {
    trigger = fire;
}

bool Bullet::operator==(const Bullet &e) const {
    return (this == &e);
}
