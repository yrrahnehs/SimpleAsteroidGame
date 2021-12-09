//
// Created by Harry Shen on 2021-11-27.
//

#include "Gameplay.h"
#include "Player.h"

Gameplay::Gameplay(wxFrame *parent) :
        wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE) {

    wxSize size = parent->GetClientSize();
    timer = new wxTimer(this, 1);
    m_stsbar = parent->GetStatusBar();

    player = Player(10, 15, 0.7, size.GetWidth() / 2 - 5, size.GetHeight() * 5 / 6);
    enemy = Enemy();
    destroyed = 0;
    points = 0;

    Connect(wxEVT_PAINT, wxPaintEventHandler(Gameplay::OnPaint));
    Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(Gameplay::OnKeyDown));
    Connect(wxEVT_TIMER, wxCommandEventHandler(Gameplay::OnTimer));
}

void Gameplay::Start() {
    destroyed = 0;
    points = 0;
    wave = 1;
    nextUpgrade = 5;
    enemy.SetSpeed(0.1);
    player.SetHealth(100);
    timer->Start(5);
}


void Gameplay::OnKeyDown(wxKeyEvent &event) {
    int keycode = event.GetKeyCode();
    if (keycode == 'p' || keycode == 'P') {
        std::cout << player.GetBullets().size() << std::endl;
    }
}

// Removes enemy from array
void Gameplay::RemoveEnemy(wxSize size) {
    for (int i = 0; i < enemies.size(); i++) {
        // if enemy is considered dead, remove from list, add to points
        if (!enemies[i].GetStatus()) {
            float newPosX = enemies[i].GetX();
            float newPosY = enemies[i].GetY();
            // if the enemy was shot, increase destroyed and point, and erase enemy from array
            if (enemies[i].GetShot()) {
                newPosX = enemies[i].GetX();
                newPosY = enemies[i].GetY();
                enemies.erase(std::remove(enemies.begin(), enemies.end(), enemies[i]));
                destroyed++;
                UpdateStatusbar(1, 0);
            }

            // keeps track of which powerup
            Upgrades upgrades1;
            if (destroyed == nextUpgrade) {
                int randomPowerup = rand() % 2;
                if (randomPowerup == 0) {
                    if (player.GetSpeed() == 2.4) {
                        upgrades1 = IncreaseFire;
                    } else {
                        upgrades1 = IncreaseSpeed;
                    }
                }
                if (randomPowerup == 1) {
                    if (player.GetRateOfFire() == 10) {
                        upgrades1 = IncreaseSpeed;
                    } else {
                        upgrades1 = IncreaseFire;
                    }
                }
                if (destroyed % 10 == 0) {
                    upgrades1 = IncreaseHealth;
                }
                if (destroyed % 16 == 0) {
                    upgrades1 = IncreaseGun;
                }

                if (enemies[i].GetX() <= 14) {
                    newPosX = 20;
                }
                if (enemies[i].GetX() >= size.GetWidth()) {
                    newPosX = size.GetWidth() - 20;
                }
                if (enemies[i].GetY() <= 14) {
                    newPosY = 20;
                }
                if (enemies[i].GetY() >= size.GetHeight()) {
                    newPosY = size.GetHeight() - 20;
                }
                powerups.emplace_back(upgrades1, newPosX, newPosY);
                nextUpgrade += 1;

                if (nextUpgrade % 4 == 0) {
                    wave++;
                    if (enemy.GetSpeed() < 3) {
                        enemy.SetSpeed(enemy.GetSpeed() + 0.1);
                    }
                }
                destroyed = 0;
            }
        }

        // if enemy moves out of bounds
        if (enemies[i].GetY() - enemies[i].GetRadius() >= size.GetHeight()) {
            points--;
            enemies[i].SetStatus(false);
            enemies.erase(std::remove(enemies.begin(), enemies.end(), enemies[i]));
        }
    }
}

// OnTick
void Gameplay::OnTimer(wxCommandEvent &event) {
    wxSize size = GetClientSize();
    // spawn enemy the same amount as wave
    if (enemies.size() != wave) {
        for (int i = 0; i < wave - enemies.size(); i++) {
            int newRadius = rand() % 15 + 5;
            enemies.emplace_back(newRadius, enemy.EnemySpawn(size, newRadius), -newRadius, enemy.GetSpeed());
        }
    }

    // enemy movement
    for (auto &enemie: enemies) {
        enemie.EnemyMovement();
    }

    // enemy removal
    RemoveEnemy(size);

    // player movement and shots
    player.PlayerMovement(size);
    player.Fire();

    // powerup movement
    for (auto &powerup: powerups) {
        powerup.Move(size);
    }

    // checks collision in game
    CheckCollision(player.GetBullets(), enemies, powerups);

    wxWindow::Refresh();
}

// Paints objects
void Gameplay::OnPaint(wxPaintEvent &event) {
    wxPaintDC dc(this);
    // paints enemies
    for (auto &enemie: enemies) {
        enemie.DrawEnemy(dc);
    }

    // paints powerups
    for (auto &powerup: powerups) {
        powerup.DrawPowerup(dc);
    }

    // paints bullets and player
    player.DrawBullets(dc);
    player.DrawPlayer(dc);
}

// checks collision in the game
// Arguments: array of bullets, array of enemies, array of powerups
void Gameplay::CheckCollision(std::vector<Bullet> &bullets, std::vector<Enemy> &enemy, std::vector<Powerup> &powerups) {
    // enemy collision with bullet
    for (int i = 0; i < enemy.size(); i++) {
        for (int j = 0; j < bullets.size(); j++) {
            if (bullets[j].GetX() + bullets[j].GetWidth() > enemy[i].GetX() - enemy[i].GetRadius() &&
                bullets[j].GetX() < enemy[i].GetX() + enemy[i].GetRadius()) {
                if (bullets[j].GetY() < enemy[i].GetY() + enemy[i].GetRadius() &&
                    bullets[j].GetY() + bullets[j].GetHeight() > enemy[i].GetY() - enemy[i].GetRadius()) {
                    enemy[i].SetStatus(false);
                    enemy[i].SetShot(true);
                    bullets.erase(std::remove(bullets.begin(), bullets.end(), bullets[j]));
                }
            }
        }
    }
    // enemy collision with player
    for (int i = 0; i < enemy.size(); i++) {
        Enemy enemy1 = enemy[i];
        float distanceBetween1 = (enemy1.GetY() + enemy1.GetRadius()) - player.GetY();
        double topDegree = 0.32175;
        double k = distanceBetween1 * tan(topDegree);
        if (k > 5) {
            k = 5;
        }
        if (player.GetY() < enemy[i].GetY() + enemy[i].GetRadius() - 2 &&
            player.GetY() + player.GetHeight() > enemy[i].GetY() - enemy[i].GetRadius() + 2) {
            if (player.GetX() + k > enemy[i].GetX() - enemy[i].GetRadius() &&
                player.GetX() - k < enemy[i].GetX() + enemy[i].GetRadius()) {
                enemy[i].SetStatus(false);
                UpdateStatusbar(0, -20);
                enemies.erase(std::remove(enemies.begin(), enemies.end(), enemies[i]));
            }
        }
    }

    // player collision with powerups
    for (int i = 0; i < powerups.size(); i++) {
        Powerup powerup1 = powerups[i];
        float distanceBetween1 = (powerup1.GetY() + powerup1.GetSize()) - player.GetY();
        double topDegree = 0.32175;
        double k = distanceBetween1 * tan(topDegree);
        if (k > 5) {
            k = 5;
        }
        if (player.GetY() < powerups[i].GetY() + powerups[i].GetSize() - 2 &&
            player.GetY() + player.GetHeight() > powerups[i].GetY() - powerups[i].GetSize() + 2) {
            if (player.GetX() + k > powerups[i].GetX() - powerups[i].GetSize() &&
                player.GetX() - k < powerups[i].GetX() + powerups[i].GetSize()) {

                // if powerups is increaseGun
                if (powerups[i].GetUpgrade() == IncreaseGun) {
                    if (player.GetUpgrade() != 2) {
                        player.SetUpgrade(player.GetUpgrade() + 1);
                    } else {
                        UpdateStatusbar(10, 0);
                    }
                }
                // if powerup is increaseFire
                if (powerups[i].GetUpgrade() == IncreaseFire) {
                    if (player.GetRateOfFire() <= 10) {
                        UpdateStatusbar(10, 0);
                    } else {
                        player.SetRateOfFire(player.GetRateOfFire() - 20);
                    }
                }
                    // if powerup is increaseHealth
                else if (powerups[i].GetUpgrade() == IncreaseHealth) {
                    // if max health, add 10 points
                    if (player.GetHealth() >= 100) {
                        player.SetHealth(100);
                        UpdateStatusbar(10, 0);
                    }
                        // if health is less than 80, just add health
                    else if (player.GetHealth() <= 80) {
                        UpdateStatusbar(0, 20);
                    }
                        // if health is between 81 and 99, add up to 100;
                    else {
                        UpdateStatusbar(0, 100 - player.GetHealth());
                    }
                }
                    // if powerup is increaseSpeed
                else if (powerups[i].GetUpgrade() == IncreaseSpeed) {
                    if (player.GetSpeed() < 2.4) {
                        player.SetSpeed(player.GetSpeed() + 0.1);
                    } else {
                        UpdateStatusbar(10, 0);
                    }
                }
                powerups.erase(std::remove(powerups.begin(), powerups.end(), powerups[i]));
            }
        }
    }

}

void Gameplay::UpdateStatusbar(int addPoints, int addHealth) {
    int newPoint = points + addPoints;
    points = newPoint;
    int newHealth = player.GetHealth() + addHealth;
    player.SetHealth(newHealth);
    wxString str;
    str.Printf(wxT("Points: %d       Health: %d"), newPoint, newHealth);
    m_stsbar->SetStatusText(str);
}



