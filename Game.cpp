#include "Game.h"
Game::Game()
{
}

void Game::LoadShips()
{
    int currentShip = 0;
    string filename = "proj2_ships.txt";
    ifstream infile;
    infile.open(filename);
    if (!infile) {
        cout << "Unable to open proj2_ships.txt\n";
        exit(0);
    }
    string line;
    string type;
    int cannon;
    int toughness;
    int speed;
    string desc;
    int totalTokensRequired;
    while (!infile.eof()) {
        totalTokensRequired = 0;
        getline(infile, line);
        if (line == "") {
            break;
        }
        string tokens[4];
        char str[2048];
        strcpy(str, line.c_str());
        int bytesRead = line.length();
        str[bytesRead + 1] = '\0';
        
        char* token = strtok(str, ",");
        type = token;
        while (token != NULL && totalTokensRequired < 3)
        {
            token = strtok(NULL, ",");
            if (totalTokensRequired == 0) {
                cannon = atoi(token);
            }
            if (totalTokensRequired == 1) {
                toughness = atoi(token);
            }
            if (totalTokensRequired == 2) {
                speed = atoi(token);
            }

            totalTokensRequired++;
        }
        token = strtok(NULL, "");
        desc = token;

        Ship temp(type, cannon, toughness, speed, desc);
        this->m_ships[currentShip++] = temp;

    }

    cout << currentShip << " ships loaded.\n";
}

void Game::LoadPirates()
{
    int currentPirate = 0;
    string filename = "proj2_pirates.txt";
    ifstream infile;
    infile.open(filename);
    if (!infile) {
        cout << "Unable to open proj2_ships.txt\n";
        exit(0);
    }
    string line;
    int totalTokensRequired;
    while (!infile.eof()) {
        totalTokensRequired = 0;
        string name;
        int rating;
        string origin;
        string description;
        getline(infile, line);
        if (line == "") {
            break;
        }
        string tokens[4];
        char str[2048];
        strcpy(str, line.c_str());
        int bytesRead = line.length();
        str[bytesRead + 1] = '\0';

        char* token = strtok(str, ",");
        name = token;
        while (token != NULL && totalTokensRequired < 2)
        {
            token = strtok(NULL, ",");
            if (totalTokensRequired == 0) {
               rating = atoi(token);
            }
            if (totalTokensRequired == 1) {
                origin = token;
            }

            totalTokensRequired++;
        }
        token = strtok(NULL, "");
       description = token;
       Pirate P(name, rating, origin, description);
        this->m_allPirates[currentPirate++] = P;

    }

    cout << currentPirate << " pirates loaded.\n";
}

void Game::StartGame()
{
    GameTitle();
    LoadShips();
    LoadPirates();
    int Pirate = rand() % 352;
    int Ship = rand() % 15;
    this->m_myPirate = this->m_allPirates[Pirate];
    this->m_myPirate.SetCurShip(this->m_ships[Ship]);
    cout << "Congratulations! " << m_myPirate.GetName() << " is now available to plunder!" << endl;
    cout << m_myPirate.GetName() << " is aboard a Clipper." << endl;
    
    int choice = MainMenu();
    while (true) {
        if (choice == 1) {
            SearchTreasure();
        }
        if (choice == 2) {
            this->m_myPirate.RepairShip();
        }
        if (choice == 3) {
            this->m_myPirate.DisplayScore();
        }
        if (choice == 4) {
            this->m_myPirate.DisplayScore();
            cout << this->m_myPirate.GetName() << " sails off into retirement!" << endl;
            cout << "Thanks for playing Pirates.\n";
            break;
        }

        choice = MainMenu();
    }

}

int Game::MainMenu()
{
    cout << "\n\nWhat would you like to do ?\n1. Search for Treasure\n2. Repair Ship\n3. See Score\n4. Retire\n";
    int choice = 0;
    while (choice != 1 && choice != 2 && choice != 3 && choice != 4) {
        cin >> choice;
    }
    return choice;
}

void Game::SearchTreasure()
{
    int enemyPirate = rand() % 352;
    int enemyShip = rand() % 15;
    Pirate ePirate = this->m_allPirates[enemyPirate];
    Ship eShip = this->m_ships[enemyShip];
    cout << "\nYou scan the horizon for prospective targets...\n";
    cout << "Off in the distance, you see " << ePirate.GetName() << " on a Man O War!\n" << endl;

    cout << "What would you like to do?\n";
    cout << "1. Attack " << ePirate.GetName() << "\n";
    cout << "2. Attemp to flee from " << ePirate.GetName() << "\n";
    
    int choice = 0;
    while (choice != 1 && choice != 2) {
        cin >> choice;
    }

    if (choice == 1) {
        this->m_myPirate.Battle(ePirate, eShip);
    }
    if (choice == 2) {
        this->m_myPirate.Flee(ePirate, eShip);
    }
}

void Game::RequestShip(int& choice)
{
}
