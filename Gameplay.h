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

    std::vector<Enemy> specialEnemies;

    std::vector<Powerup> powerups;
    int points;
    int destroyed, wave, totalDestroyed;
    int nextUpgrade;
    bool isStarted;
    bool isPaused;
    bool timeToSpawn;

    wxStatusBar *m_stsbar;

    void UpdateStatusbar(int addPoints, int addHealth);

public:
    Gameplay(wxFrame *parent);

    void Start();

    void Pause();

    void RemoveEnemy(wxSize size, std::vector<Enemy> &nmes);

    int GetDestroyed();

    void ChooseUpgrade(float newPosX, float newPosY, std::vector<Powerup> &powerups);

    void CheckCollision(std::vector<Bullet> &bullets, std::vector<Enemy> &nmes, std::vector<Powerup> &powerups);

    void CheckGameOver();

protected:
    void OnPaint(wxPaintEvent &event);

    void OnKeyDown(wxKeyEvent &event);

    void OnTimer(wxCommandEvent &event);
};

#endif //SIMPLEASTEROIDGAME_GAMEPLAY_H
