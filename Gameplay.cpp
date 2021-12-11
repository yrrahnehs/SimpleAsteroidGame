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

    player = Player(10, 15, 0.8, size.GetWidth() / 2 - 5, size.GetHeight() * 5 / 6);
    destroyed = 0;
    points = 0;
    i = 0;

    isStarted = false;
    isPaused = false;
    secondPhase = false;

    Connect(wxEVT_PAINT, wxPaintEventHandler(Gameplay::OnPaint));
    Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(Gameplay::OnKeyDown));
    Connect(wxEVT_TIMER, wxCommandEventHandler(Gameplay::OnTimer));
}

void Gameplay::Start() {
    if (isPaused) {
        return;
    }
    timeToSpawn1 = false;
    isStarted = true;
    destroyed = 0;
    totalDestroyed = 0;
    points = 0;
    wave = 1;
    nextUpgrade = 5;
    secondPhase = false;
    enemy.SetSpeed(0.3);

    UpdateStatusbar(0, 0);

    timer->Start(5);
}

void Gameplay::Pause() {
    if (!isStarted) {
        return;
    }
    isPaused = !isPaused;
    if (isPaused) {
        timer->Stop();
        m_stsbar->SetStatusText("Paused");
    } else {
        timer->Start(5);
        UpdateStatusbar(0, 0);
    }
    Refresh();
}


void Gameplay::OnKeyDown(wxKeyEvent &event) {
    int keycode = event.GetKeyCode();
    if (keycode == 'p' || keycode == 'P') {
        Pause();
        return;
    }
    if (keycode == 'z' || keycode == 'Z') {
        player.SetNuke(true);
        return;
    }
    if (keycode == 'd' || keycode == 'D') {
        player.SetHealth(9999999);
        player.SetUpgrade(2);
        player.SetMax(true);
        player.SetRateOfFire(10);
        player.SetSpeed(2.4);
        return;
    }
    if (isPaused) {
        return;
    }
}

void Gameplay::ChooseUpgrade(float newPosX, float newPosY, std::vector<Powerup> &powerups) {
    Upgrades upgrades1;
    int randomPowerup = rand() % 99 + 1;
    // if random number is less than = 40,
    // powerup is IncreaseSpeed
    if (!secondPhase) {
        if (randomPowerup <= 40) {
            if (player.GetSpeed() == 2.3) {
                upgrades1 = IncreaseFire;
            } else {
                upgrades1 = IncreaseSpeed;
            }
        }
        // if random number is greater than 40,
        // powerup is IncreaseFire
        if (randomPowerup > 40) {
            if (player.GetRateOfFire() == 10) {
                upgrades1 = IncreaseSpeed;
            } else {
                upgrades1 = IncreaseFire;
            }
        }
        if (nextUpgrade % 14 == 0) {
            upgrades1 = IncreaseGun;
        }

        if (nextUpgrade % 6 == 0) {
            upgrades1 = IncreaseHealth;
        }
    } else {
        upgrades1 = IncreaseHealth;
    }
    powerups.emplace_back(upgrades1, newPosX, newPosY);
}

// Removes enemy from array
void Gameplay::RemoveEnemy(wxSize size, std::vector<Enemy> &nmes) {
    for (int i = 0; i < nmes.size(); i++) {
        // if enemy is considered dead, remove from list, add to points
        if (nmes[i].GetStatus() == false) {
            float newPosX = nmes[i].GetX();
            float newPosY = nmes[i].GetY();
            if (nmes[i].GetEnemyType() == 2) {
                newPosX = nmes[i].GetX() + nmes[i].GetRadius() / 2;;
                newPosY = nmes[i].GetY() + nmes[i].GetRadius() / 2;;
            }
            // if the enemy was shot, increase destroyed and point, and erase enemy from array
            if (nmes[i].GetShot()) {
                if ((int)(player.GetSpeed()*10) == 24 && player.GetRateOfFire() == 10 && player.GetMax()) {
                    secondPhase = true;
                }
                if (nmes[i].GetEnemyType() != 2) {
                    newPosX = nmes[i].GetX();
                    newPosY = nmes[i].GetY();
                } else {
                    newPosX = nmes[i].GetX() + nmes[i].GetRadius() / 2;
                    newPosY = nmes[i].GetY() + nmes[i].GetRadius() / 2;
                }
                totalDestroyed++;

                // spawns x-moving enemy
                if (totalDestroyed % 30 == 0) {
                    timeToSpawn1 = true;
                }
                destroyed++;
                nmes.erase(std::remove(nmes.begin(), nmes.end(), nmes[i]));

                UpdateStatusbar(1, 0);
            }

            // positions for when powerups spawn
            if (nmes[i].GetX() <= 14) {
                newPosX = 25;
            }
            if (nmes[i].GetX() >= size.GetWidth() - 1) {
                newPosX = size.GetWidth() - 25;
            }
            if (nmes[i].GetY() <= 14) {
                newPosY = 20;
            }
            if (nmes[i].GetY() >= size.GetHeight()) {
                newPosY = size.GetHeight() - 20;
            }

            if (destroyed == nextUpgrade) {
                ChooseUpgrade(newPosX, newPosY, powerups);

                // increase enemy speed per wave
                if (nextUpgrade % 4 == 0) {
                    wave++;
                    if (enemy.GetSpeed() < 2.1) {
                        enemy.SetSpeed(enemy.GetSpeed() + 0.1);
                    }
                }
                nextUpgrade += 1;
                destroyed = 0;
            }
        }

        // if enemy moves out of bounds
        if (nmes[i].GetY() - nmes[i].GetRadius() >= size.GetHeight()) {
            nmes[i].SetStatus(false);
            nmes.erase(std::remove(nmes.begin(), nmes.end(), nmes[i]));
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
            enemies.emplace_back(newRadius, enemy.EnemySpawn(size, newRadius), -newRadius * 2, enemy.GetSpeed(), 0);
        }
    }

    // spawn x-moving enemy every 30 enemy deaths, max 25
    if (timeToSpawn1) {
        if ((totalDestroyed / 30) < 25) {
            for (int i = 0; i < (totalDestroyed / 30); i++) {
                specialEnemies.emplace_back(13, enemy.EnemySpawn(size, 13), -26, enemy.GetSpeed() * 2 / 3, 1);
            }
        } else {
            if (specialEnemies.size() < 25) {
                for (int i = 0; i < 25 - (specialEnemies.size()); i++) {
                    specialEnemies.emplace_back(13, enemy.EnemySpawn(size, 13), -26, enemy.GetSpeed() * 2 / 3, 1);
                }
            }
        }
        timeToSpawn1 = false;
    }

    // start spawning WALL enemy when second phase starts
    if (secondPhase) {
        i++;
        if (i >= 1500) {
            float quarter = (size.GetWidth() / 4);
            int random = rand() % 4;
            specialEnemies.emplace_back(size.GetWidth() / 4, (quarter * random), -15, enemy.GetSpeed() * 2 / 5, 2);
            i = 0;
        }
    }


// normal enemy movement
    for (auto &enemie: enemies) {
        enemie.EnemyMovement(size);
    }

// special enemy movement
    for (auto &spEnemie: specialEnemies) {
        spEnemie.EnemyMovement(size);
    }

// enemy removal
    RemoveEnemy(size, enemies);
    RemoveEnemy(size, specialEnemies);

// player movement and shots
    player.PlayerMovement(size);
    player.Fire();

// powerup movement
    for (auto &powerup: powerups) {
        powerup.Move(size);
    }

// checks collision in game
    CheckCollision(player.GetBullets(), enemies, powerups);
    CheckCollision(player.GetBullets(), specialEnemies, powerups);

    CheckGameOver();

    wxWindow::Refresh();

}

// Paints objects
void Gameplay::OnPaint(wxPaintEvent &event) {
    wxPaintDC dc(this);
    // paints enemies
    for (auto &enemie: enemies) {
        enemie.DrawEnemy(dc);
    }

    for (auto &spEnemie: specialEnemies) {
        spEnemie.DrawEnemy(dc);
    }

    // paints powerups
    for (auto &powerup: powerups) {
        powerup.DrawPowerup(dc);
    }

    // paints bullets and player
    player.DrawBullets(dc);
    player.DrawPlayer(dc);

}

bool Gameplay::GetDistance(double x1, double y1, float radius1, double x2, double y2, float radius2) {
    double widthBetweenEachOther = abs(x2 - x1);
    double heightBetweenEachOther = abs(y2 - y1);
    double k = pow(widthBetweenEachOther, 2) + pow(heightBetweenEachOther, 2);
    double distance = sqrt(k);
    if (distance <= (radius1 + radius2) + 5 && distance >= 0) {
        return true;
    }
    return false;
}


// checks collision in the game
// Arguments: array of bullets, array of enemies, array of powerups
void Gameplay::CheckCollision(std::vector<Bullet> &bullets, std::vector<Enemy> &nmes, std::vector<Powerup> &powerups) {
    // nmes collision with bullet
    for (int i = 0; i < nmes.size(); i++) {
        for (int j = 0; j < bullets.size(); j++) {
            if (nmes[i].GetEnemyType() == 2) {
                if (bullets[j].GetX() + bullets[j].GetWidth() > nmes[i].GetX() &&
                    bullets[j].GetX() < nmes[i].GetX() + nmes[i].GetRadius()) {
                    if (bullets[j].GetY() < nmes[i].GetY() + 15 &&
                        bullets[j].GetY() + bullets[j].GetHeight() > nmes[i].GetY()) {
                        nmes[i].SetHealth(nmes[i].GetHealth() - 1);
                        bullets.erase(std::remove(bullets.begin(), bullets.end(), bullets[j]));
                        if (nmes[i].GetHealth() <= 0) {
                            nmes[i].SetStatus(false);
                            nmes[i].SetShot(true);
                        }
                    }
                }
            } else {
                if (bullets[j].GetX() + bullets[j].GetWidth() > nmes[i].GetX() - nmes[i].GetRadius() &&
                    bullets[j].GetX() < nmes[i].GetX() + nmes[i].GetRadius()) {
                    if (bullets[j].GetY() < nmes[i].GetY() + nmes[i].GetRadius() &&
                        bullets[j].GetY() + bullets[j].GetHeight() > nmes[i].GetY() - nmes[i].GetRadius()) {
                        nmes[i].SetStatus(false);
                        nmes[i].SetShot(true);
                        bullets.erase(std::remove(bullets.begin(), bullets.end(), bullets[j]));
                    }
                }
            }
        }
    }
    // nuke powerup
    if (player.GetNuke()) {
        for (int i = 0; i < nmes.size(); i++) {
            if (GetDistance(player.GetX(), player.GetY() + player.GetHeight() / 2, player.GetIncreasingRadius(),
                            nmes[i].GetX(), nmes[i].GetY(), nmes[i].GetRadius())) {
                if (nmes[i].GetY() >= 0) {
                    nmes[i].SetStatus(false);
                    nmes[i].SetShot(true);
                }
            }
        }
    }
    // nmes collision with player
    for (int i = 0; i < nmes.size(); i++) {
        Enemy enemy1 = nmes[i];
        float distanceBetween1 = (enemy1.GetY() + enemy1.GetRadius()) - player.GetY();
        double topDegree = 0.32175;
        double k = distanceBetween1 * tan(topDegree);
        if (k > 5) {
            k = 5;
        }
        // if enemy type is "WALL"
        if (nmes[i].GetEnemyType() == 2) {
            if (player.GetY() < nmes[i].GetY() + 15 && player.GetY() + player.GetHeight() > nmes[i].GetY()) {
                if (player.GetX() + player.GetWidth() / 2 > nmes[i].GetX() &&
                    player.GetX() - player.GetWidth() / 2 < nmes[i].GetX() + nmes[i].GetRadius()) {
                    nmes[i].SetStatus(false);
                    UpdateStatusbar(0, -20);
                    if (player.GetHealth() <= 100) {
                        player.SetArmor(false);
                    }
                    if (player.GetHealth() != 0) {
                        nmes.erase(std::remove(nmes.begin(), nmes.end(), nmes[i]));
                    }
                }
            }
        }
        // enemy type is ASTEROID
        if (nmes[i].GetEnemyType() != 2) {
            if (player.GetY() < nmes[i].GetY() + nmes[i].GetRadius() - 2 &&
                player.GetY() + player.GetHeight() > nmes[i].GetY() - nmes[i].GetRadius() + 2) {
                if (player.GetX() + k > nmes[i].GetX() - nmes[i].GetRadius() &&
                    player.GetX() - k < nmes[i].GetX() + nmes[i].GetRadius()) {
                    nmes[i].SetStatus(false);
                    UpdateStatusbar(0, -20);
                    if (player.GetHealth() <= 100) {
                        player.SetArmor(false);
                    }
                    if (player.GetHealth() != 0) {
                        nmes.erase(std::remove(nmes.begin(), nmes.end(), nmes[i]));
                    }
                }
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
                    if (player.GetUpgrade() == 2 && player.GetMax()) {
                        player.SetNuke(true);
                    }
                    if (player.GetUpgrade() != 2) {
                        player.SetUpgrade(player.GetUpgrade() + 1);
                    }
                    if (player.GetUpgrade() == 2 && !player.GetMax()) {
                        player.SetMax(true);
                        UpdateStatusbar(10, 0);
                    }
                }
                // if powerup is increaseFire
                if (powerups[i].GetUpgrade() == IncreaseFire) {
                    if (player.GetRateOfFire() <= 10) {
                        UpdateStatusbar(10, 0);
                    } else {
                        player.SetRateOfFire(player.GetRateOfFire() - 20);
                        UpdateStatusbar(0, 0);
                    }
                }
                    // if powerup is increaseHealth
                else if (powerups[i].GetUpgrade() == IncreaseHealth) {
                    // if max health, add 10 points
                    if (player.GetHealth() >= 100) {
                        player.SetArmor(true);
                        UpdateStatusbar(0, 20);
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
                        UpdateStatusbar(0, 0);
                    } else {
                        UpdateStatusbar(10, 0);
                    }
                }
                powerups.erase(std::remove(powerups.begin(), powerups.end(), powerups[i]));
            }
        }
    }
}

void Gameplay::SetPoints(int newPoints) {
    points = newPoints;
}

void Gameplay::UpdateStatusbar(int addPoints, int addHealth) {
    int newPoint = points + addPoints;
    int newHealth = player.GetHealth() + addHealth;
    SetPoints(newPoint);
    player.SetHealth(newHealth);
    wxString str;
    str.Printf(wxT("Points: %d     Health: %d     Speed: %.1f     Fire: %.1f"), newPoint, newHealth,
               (player.GetSpeed()), player.GetRateOfFire() / 10);
    m_stsbar->SetStatusText(str);

    if (player.GetSpeed() >= 2.4) {
        str.Printf(wxT("Points: %d     Health: %d     Speed: MAX     Fire: %.1f"), newPoint, newHealth,
                   player.GetRateOfFire() / 10);
        m_stsbar->SetStatusText(str);
    }
    if (player.GetRateOfFire() <= 10) {
        str.Printf(wxT("Points: %d     Health: %d     Speed: %.1f     Fire: MAX"), newPoint, newHealth,
                   (player.GetSpeed()));
        m_stsbar->SetStatusText(str);
    }
    if (player.GetRateOfFire() <= 10 && player.GetSpeed() >= 2.4) {
        str.Printf(wxT("Points: %d     Health: %d     Speed: MAX    Fire: MAX"), newPoint, newHealth);
        m_stsbar->SetStatusText(str);
    }
}

void Gameplay::CheckGameOver() {
    if (player.GetHealth() <= 0) {
        timer->Stop();
        isStarted = false;
        wxString str;
        str.Printf(wxT("Game Over              Points: %d"), points);
        m_stsbar->SetStatusText(str);
    }
}
