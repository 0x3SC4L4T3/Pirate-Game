#include "Pirate.h"

Pirate::Pirate()
{

}

Pirate::Pirate(string name, int rating, string origin, string desc)
{
    this->m_pirateName = name;
    this->m_pirateRating = rating;
    this->m_pirateOrigin = origin;
    this->m_pirateDesc = desc;
    this->m_pirateDays = 0;
    this->m_pirateCargo = 0;
}

string Pirate::GetName()
{
    return this->m_pirateName;
}

int Pirate::GetRating()
{
    return this->m_pirateRating;
}

void Pirate::SetRating(int rating)
{
    this->m_pirateRating = rating;
}

string Pirate::GetOrigin()
{
    return this->m_pirateOrigin;
}

string Pirate::GetDesc()
{
    return this->m_pirateDesc;
}

void Pirate::SetCurShip(Ship curShip)
{
    this->m_curShip = curShip;
}

void Pirate::CalcTreasure(Ship enemyShip)
{
    this->m_pirateCargo = (enemyShip.m_toughness + enemyShip.m_cannon + enemyShip.m_speed) / 3;
}

void Pirate::Battle(Pirate enemyPirate, Ship enemyShip)
{
    if (this->m_curShip.m_curToughness <= 0) {
        cout << "Please Repair your ship\n";
        return;
    }

    if (enemyShip.m_curToughness <= 0) {
        cout << "Enemy need to repair the ship\n";
        return;
    }
    

    int hitsUser = 0, hitsEnemy = 0;
    cout << "A naval battle of the ages commences between " << this->GetName() << " and " << enemyPirate.GetName() << endl;
    while (this->m_curShip.m_curToughness > 0 && enemyShip.m_curToughness > 0) {
        cout << this->GetName() << " fires " << this->m_curShip.m_cannon << " cannons!" << endl;
        for (int i = 0; i < this->m_curShip.m_cannon; i++) {
            if (rand() % 100 <= this->m_pirateRating) {
                hitsUser++;
            }
        }

        enemyShip.m_curToughness -= hitsUser;
        cout << hitsUser << " shots hit!\n";

        for (int i = 0; i < enemyShip.m_cannon; i++) {
            if (rand() % 100 <= enemyPirate.GetRating()) {
                hitsEnemy++;
            }
        }
        cout << enemyPirate.GetName() << " fires " << enemyShip.m_cannon << " back!" << endl;
        this->m_curShip.m_curToughness -= hitsEnemy;
        cout << hitsEnemy << " shots hit!\n";

        hitsUser = 0, hitsEnemy = 0;
    }

    if (this->m_curShip.m_curToughness < 1) {
        this->m_pirateCargo = this->m_pirateCargo / 2;
        cout << "You lose" << endl;
    }
    else {
        cout << "You win! ";
        CalcTreasure(enemyShip);
        cout << this->GetName() << " shares " << this->m_pirateCargo << " treasures with his creaw." << endl;
    }
}

void Pirate::RepairShip()
{
    while (this->m_curShip.m_toughness - this->m_curShip.m_curToughness != 0) {
        this->m_curShip.m_curToughness += 1;
        this->m_pirateDays += 1;
    }
    cout << "It takes " << this->m_pirateDays << " to repair your " << this->m_curShip.m_type << endl;
}

void Pirate::Flee(Pirate enemyPirate, Ship enemyShip)
{
    cout << "You attempt to flee from " << enemyPirate.GetName() << "!\n";
    if (enemyShip.m_speed > enemyShip.m_curToughness) {
        this->m_pirateDays += 1;
    }
    cout << "You narrowly escape from " << enemyPirate.GetName() << "!\n";
}

void Pirate::DisplayScore()
{
    cout << "**********************\n\n";
    cout << "Name: " << this->GetName() << endl;
    cout << "Rating: " << this->GetRating() << endl;;
    cout << "Country of Origin: " << this->GetOrigin() << endl;;
    cout << "Description: " << this->GetDesc() << endl;
    cout << "Days Sailing :" << this->m_pirateDays << endl;
    cout << "Cargo Captured : " << this->m_pirateCargo << endl;
    cout << "Cargo Per Day : " << this->m_pirateDays / this->m_pirateCargo << endl;
    cout << "Ship Type : " << this->m_curShip.m_type << endl;
    cout << "Ship Cannons :" << this->m_curShip.m_cannon << endl;
    cout << "Ship Current Toughness : " << this->m_curShip.m_curToughness << endl;
    cout << "Ship Max Toughness : " << this->m_curShip.m_toughness << endl;
    cout << "Ship Speed : " << this->m_curShip.m_speed << endl;
    cout << "\n********************\n" << endl;

}
