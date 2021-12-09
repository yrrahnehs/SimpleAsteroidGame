//
// Created by Harry Shen on 2021-12-09.
//

#ifndef SIMPLEASTEROIDGAME_GAMEPLAY_H
#define SIMPLEASTEROIDGAME_GAMEPLAY_H

#include <wx/wx.h>
#include "Player.h"
#include "Enemy.h"
#include "Powerup.h"

class Gameplay : public wxPanel {
private:
    wxTimer *timer;
    Upgrades upgrades;
    Player player;
    Enemy enemy;

    std::vector<Enemy> enemies;

    std::vector<Powerup> powerups;
    int points;
    int destroyed, wave;
    int nextUpgrade;
    wxStatusBar *m_stsbar;

    void UpdateStatusbar(int addPoints, int addHealth);

public:
    Gameplay(wxFrame *parent);

    void Start();

    void Pause();

    void RemoveEnemy(wxSize size);

    int GetDestroyed();

    void CheckCollision(std::vector<Bullet> &bullets, std::vector<Enemy> &enemy, std::vector<Powerup> &powerups);

protected:
    void OnPaint(wxPaintEvent &event);

    void OnKeyDown(wxKeyEvent &event);

    void OnTimer(wxCommandEvent &event);
};

#endif //SIMPLEASTEROIDGAME_GAMEPLAY_H
