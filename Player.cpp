#include "Player.h"

Player::Player() {}

Player::Player(int width, int height, float speed, int x, int y) {
    LEFT_WIDTH = width / 2;
    RIGHT_WIDTH = width / 2;
    HEIGHT = height;
    rateOfFire = 330;
    upgrade = 0;
    spd = speed;
    xx = x;
    yy = y;
    health = 100;
}

float Player::GetX() const {
    return xx;
}

float Player::GetY() const {
    return yy;
}

void Player::MoveX(float x) {
    xx = x;
}

void Player::MoveY(float y) {
    yy = y;
}

int Player::GetWidth() const {
    return LEFT_WIDTH + RIGHT_WIDTH;
}

int Player::GetHeight() const {
    return HEIGHT;
}

int Player::GetHealth() {
    return health;
}

void Player::SetHealth(int newHealth) {
    health = newHealth;
}

int Player::GetUpgrade() {
    return upgrade;
}

void Player::SetUpgrade(int newUpgrade) {
    upgrade = newUpgrade;
}

void Player::SetSpeed(float newSpeed) {
    spd = newSpeed;
}

float Player::GetSpeed() {
    return spd;
}

void Player::PlayerMovement(wxSize size) {
    if (wxGetKeyState(WXK_UP)) {
        MoveY((GetY() - spd));
    }
    if (wxGetKeyState(WXK_DOWN)) {
        MoveY(GetY() + spd);
    }
    if (wxGetKeyState(WXK_LEFT)) {
        MoveX(GetX() - spd);
    }
    if (wxGetKeyState(WXK_RIGHT)) {
        MoveX(GetX() + spd);
    }

    CheckPlayerBoundary(size);
}

void Player::CheckPlayerBoundary(wxSize size) {
    int halfOfSpaceshipWidth = GetWidth() / 2;

    if (GetX() - halfOfSpaceshipWidth < 0) {
        MoveX(halfOfSpaceshipWidth);
    }
    if (GetX() + halfOfSpaceshipWidth > size.GetWidth()) {
        MoveX(size.GetWidth() - GetWidth() / 2);
    }
    if (GetY() < 0) {
        MoveY(0);
    }
    if (GetY() >= size.GetHeight() - GetHeight()) {
        MoveY(size.GetHeight() - GetHeight());
    }
}

void Player::DrawPlayer(wxPaintDC &dc) {
    dc.SetPen(wxPen(*wxGREEN, 1));
    dc.SetBrush(wxBrush(wxColour(59, 128, 59)));
    wxPoint triangle[3];
    triangle[0] = wxPoint(GetX(), GetY());
    triangle[1] = wxPoint(GetX() - GetWidth() / 2, GetY() + GetHeight());
    triangle[2] = wxPoint(GetX() + GetWidth() / 2, GetY() + GetHeight());
    dc.DrawPolygon(3, triangle);
    if (GetUpgrade() == 1) {
        dc.DrawRectangle(GetX() - GetWidth() / 2, GetY() + 2, 1, GetHeight() - 2);
        dc.DrawRectangle(GetX() + GetWidth() / 2, GetY() + 2, 1, GetHeight() - 2);
    }
    if (GetUpgrade() == 2) {
        dc.DrawRectangle(GetX() - GetWidth() / 2, GetY() + 2, 1, GetHeight() - 2);
        dc.DrawRectangle(GetX() + GetWidth() / 2, GetY() + 2, 1, GetHeight() - 2);
        dc.DrawLine(GetX() - GetWidth(), GetY() + GetHeight() / 2 + 4, GetX() - GetWidth() / 2, GetY() + GetHeight());
        dc.DrawLine(GetX() + GetWidth(), GetY() + GetHeight() / 2 + 4, GetX() + GetWidth() / 2, GetY() + GetHeight());
        dc.DrawLine(GetX() - GetWidth(), GetY() + GetHeight() / 2 + 4, GetX() - GetWidth(), GetY() + 4);
        dc.DrawLine(GetX() + GetWidth(), GetY() + GetHeight() / 2 + 4, GetX() + GetWidth(), GetY() + 4);
    }
}

void Player::Fire() {
    if (wxGetKeyState(WXK_SPACE)) {
        ++timeheld;
        if (timeheld % GetRateOfFire() == 0 || timeheld == 1) {
            Bullet b;
            b = Bullet(GetX() - 1, GetY(), 2);
            b.SetTrigger(true);
            GetBullets().push_back(b);
            if (GetUpgrade() == 1) {
                Bullet b1, b2;
                b1 = Bullet((GetX() - GetWidth() / 2) - 1, GetY() + 1, 2);
                b2 = Bullet((GetX() + GetWidth() / 2) - 1, GetY() + 1, 2);
                b1.SetTrigger(true);
                b2.SetTrigger(true);
                GetBullets().push_back(b1);
                GetBullets().push_back(b2);
            }
            if (GetUpgrade() == 2) {
                Bullet b1, b2, b3, b4;
                b1 = Bullet((GetX() - GetWidth() / 2) - 1, GetY() + 1, 2);
                b2 = Bullet((GetX() + GetWidth() / 2) - 1, GetY() + 1, 2);
                b3 = Bullet((GetX() - GetWidth()) - 1, GetY() + 2, 2);
                b4 = Bullet((GetX() + GetWidth()) - 1, GetY() + 2, 2);
                b1.SetTrigger(true);
                b2.SetTrigger(true);
                b3.SetTrigger(true);
                b4.SetTrigger(true);
                GetBullets().push_back(b1);
                GetBullets().push_back(b2);
                GetBullets().push_back(b3);
                GetBullets().push_back(b4);
            }
        }
    }
    if (!wxGetKeyState(WXK_SPACE)) {
        if (timeheld != 0) {
            timeheld++;
        }
        if (timeheld % GetRateOfFire() == 0) {
            timeheld = 0;
        }
    }

    for (int i = 0; i < GetBullets().size(); i++) {
        if (GetBullets()[i].IsFired()) {
            GetBullets()[i].Move();
        }
        if (GetBullets()[i].GetY() <= 1) {
            GetBullets().erase(std::remove(GetBullets().begin(), GetBullets().end(), GetBullets()[i]));
        }
    }

}

void Player::DrawBullets(wxPaintDC &dc) {
    for (auto &i: GetBullets()) {
        if (i.IsFired()) {
            i.DrawBullet(dc);
        }
    }
}

int Player::GetRateOfFire() {
    return rateOfFire;
}

void Player::SetRateOfFire(int newROF) {
    rateOfFire = newROF;
}


std::vector<Bullet> &Player::GetBullets() {
    return bullets;
}

