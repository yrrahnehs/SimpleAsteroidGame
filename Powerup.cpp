#include "Powerup.h"

Powerup::Powerup() {
}


Powerup::Powerup(Upgrades upgrades, float posX, float posY) {
    size = 14;
    int k;
    if (rand()%2 == 0) {
        k = -1;
    } else {
        k = 1;
    }
    xVelocity = 0.4*k;
    yVelocity = 0.4;
    SetX(posX);
    SetY(posY);
    switch (upgrades) {
        case IncreaseFire:
            SetUpgrade(IncreaseFire);
            break;
        case IncreaseSpeed:
            SetUpgrade(IncreaseSpeed);
            break;
        case IncreaseHealth:
            SetUpgrade(IncreaseHealth);
            break;
        case IncreaseGun:
            SetUpgrade(IncreaseGun);
            break;
    }
}


void Powerup::SetUpgrade(Upgrades selection) {
    upgrade = selection;
}

Upgrades Powerup::GetUpgrade() {
    return upgrade;
}

int Powerup::GetSize() {
    return size;
}

float Powerup::GetX() {
    return x;
}

float Powerup::GetY() {
    return y;
}

void Powerup::SetX(float newX) {
    x = newX;
}

void Powerup::SetY(float newY) {
    y = newY;
}

void Powerup::Move(wxSize size) {
    rotation += 0.00872665;
    SetY(GetY() + yVelocity);
    SetX(GetX() + xVelocity);
    CheckBoundary(size);
}

void Powerup::CheckBoundary(wxSize size) {
    if (GetX() + GetSize() > size.GetWidth() || GetX() - GetSize() < 0) {
        xVelocity *= -1;
    }
    if (GetY() + GetSize() > size.GetHeight() || GetY() - GetSize() < 0) {
        yVelocity *= -1;
    }

}

void Powerup::DrawPowerup(wxPaintDC &dc) {
    dc.SetPen(wxPen(wxColor(122, 178, 255), 1));
    dc.SetBrush(wxBrush(wxColour(35, 102, 204)));
    wxPoint star[10];
    star[0] = wxPoint(GetSize() * cos(-1.5708 + rotation) + GetX(), GetSize() * sin(-1.5708 + rotation) + GetY());
    star[1] = wxPoint((3 * GetSize() / 4) * cos(-0.942478 + rotation) + GetX(),
                      (3 * GetSize() / 4) * sin(-0.942478 + rotation) + GetY());
    star[2] = wxPoint(GetSize() * cos(-0.314159 + rotation) + GetX(), GetSize() * sin(-0.314159 + rotation) + GetY());
    star[3] = wxPoint((3 * GetSize() / 4) * cos(0.314159 + rotation) + GetX(),
                      (3 * GetSize() / 4) * sin(0.314159 + rotation) + GetY());
    star[4] = wxPoint(GetSize() * cos(0.942478 + rotation) + GetX(), GetSize() * sin(0.942478 + rotation) + GetY());
    star[5] = wxPoint((3 * GetSize() / 4) * cos(1.5708 + rotation) + GetX(),
                      (3 * GetSize() / 4) * sin(1.5708 + rotation) + GetY());
    star[6] = wxPoint(GetSize() * cos(2.19911 + rotation) + GetX(), GetSize() * sin(2.19911 + rotation) + GetY());
    star[7] = wxPoint((3 * GetSize() / 4) * cos(2.82743 + rotation) + GetX(),
                      (3 * GetSize() / 4) * sin(2.82743 + rotation) + GetY());
    star[8] = wxPoint(GetSize() * cos(3.45575 + rotation) + GetX(), GetSize() * sin(3.45575 + rotation) + GetY());
    star[9] = wxPoint((3 * GetSize() / 4) * cos(4.08407 + rotation) + GetX(),
                      (3 * GetSize() / 4) * sin(4.08407 + rotation) + GetY());
    dc.DrawPolygon(10, star);

    wxPoint speed1[6];
    wxPoint speed2[6];
    wxPoint speed3[6];
    speed1[0] = wxPoint(GetX() - 5, GetY() - 11);
    speed1[1] = wxPoint(GetX() - 12, GetY());
    speed1[2] = wxPoint(GetX() - 5, GetY() + 11);
    speed1[3] = wxPoint(GetX() - 2, GetY() + 11);
    speed1[4] = wxPoint(GetX() - 9, GetY());
    speed1[5] = wxPoint(GetX() - 2, GetY() - 11);

    speed2[0] = wxPoint(GetX() + 2, GetY() - 9);
    speed2[1] = wxPoint(GetX() - 4, GetY());
    speed2[2] = wxPoint(GetX() + 2, GetY() + 9);
    speed2[3] = wxPoint(GetX() + 5, GetY() + 9);
    speed2[4] = wxPoint(GetX() - 1, GetY());
    speed2[5] = wxPoint(GetX() + 5, GetY() - 9);

    speed3[0] = wxPoint(GetX() + 8, GetY() - 7);
    speed3[1] = wxPoint(GetX() + 4, GetY());
    speed3[2] = wxPoint(GetX() + 8, GetY() + 7);
    speed3[3] = wxPoint(GetX() + 11, GetY() + 7);
    speed3[4] = wxPoint(GetX() + 7, GetY());
    speed3[5] = wxPoint(GetX() + 11, GetY() - 7);

    wxPoint health[12];
    health[0] = wxPoint(GetX() - 3, GetY() - GetSize()+2);
    health[1] = wxPoint(GetX() + 3, GetY() - GetSize()+2);
    health[2] = wxPoint(GetX() + 4, GetY() - 4);
    health[3] = wxPoint(GetX() + GetSize()-2, GetY() - 3);
    health[4] = wxPoint(GetX() + GetSize()-2, GetY() + 3);
    health[5] = wxPoint(GetX() + 4, GetY() + 4);
    health[6] = wxPoint(GetX() + 3, GetY() + GetSize()-2);
    health[7] = wxPoint(GetX() - 3, GetY() + GetSize()-2);
    health[8] = wxPoint(GetX() - 4, GetY() + 4);
    health[9] = wxPoint(GetX() - GetSize()+2, GetY() + 3);
    health[10] = wxPoint(GetX() - GetSize()+2, GetY() - 3);
    health[11] = wxPoint(GetX() - 4, GetY() - 4);

    wxPoint gunUpgrade[3];
    gunUpgrade[0] = wxPoint(10 * cos(-1.5708 - rotation) + GetX(), 10 * sin(-1.5708 - rotation) + GetY());
    gunUpgrade[1] = wxPoint(10 * cos(0.523599 - rotation) + GetX(), 10 * sin(0.523599 - rotation) + GetY());
    gunUpgrade[2] = wxPoint(10 * cos(2.61799 - rotation) + GetX(), 10 * sin(2.61799 - rotation) + GetY());


    switch (GetUpgrade()) {
        case IncreaseFire:
            dc.SetPen(wxPen(wxColour(252, 153, 10), 1));
            dc.SetBrush(wxBrush(wxColour(255, 221, 9)));
            dc.DrawEllipticArc(GetX() - 8, GetY() - 10, 6, 17, 0, 180);
            dc.DrawRectangle(GetX() - 8, GetY() - 4, 7, 13);
            dc.DrawEllipticArc(GetX() + 2, GetY() - 10, 6, 17, 0, 180);
            dc.DrawRectangle(GetX() + 2, GetY() - 4, 7, 13);
            break;
        case IncreaseSpeed:
            dc.SetPen(wxPen(wxColour(255, 87, 220), 1));
            dc.SetBrush(wxBrush(wxColour(252, 151, 231)));
            dc.DrawPolygon(6, speed1);
            dc.DrawPolygon(6, speed2);
            dc.DrawPolygon(6, speed3);
            break;
        case IncreaseHealth:
            dc.SetPen(wxPen(wxColour(21, 148, 40), 1));
            dc.SetBrush(wxBrush(wxColour(37, 230, 69)));
            dc.DrawPolygon(12, health);
            break;
        case IncreaseGun:
            dc.SetPen(wxPen(*wxGREEN, 1));
            dc.SetBrush(wxBrush(wxColour(0,0,0)));
            dc.DrawCircle(GetX(), GetY(), 10);
            dc.DrawPolygon(3, gunUpgrade);
            break;
    }
}

bool Powerup::operator==(const Powerup &p) const {
    return (this == &p);
}
