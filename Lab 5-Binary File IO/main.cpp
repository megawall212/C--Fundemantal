#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits> // for int max function

using namespace std; // Correct placement

// weapon and variables!
struct Weapon {
    string name;
    int powerRating;
    float powerConsumption;
};

// starship and variables!
struct Starship {
    string name;
    string shipClass;
    short length;
    int shieldCapacity;
    float maxWarp;
    vector<Weapon> weapons;
    int totalFirepower; //total firepower of ALL weapons
};

// load ships from a binary file
vector<Starship> loadShips(const string& filename) {
    ifstream file(filename, ios::binary); //recall from quiz, open in binary
    if (!file.is_open()) {
        cerr << "Errors: can't open file!! " << filename << endl;
        return {};
        // you don't need that for test cases
    }

    vector<Starship> ships; //store all ships
    int shipCount;
    //now we need to read the number of chips
    //this line looks very horrible
    file.read(reinterpret_cast<char*>(&shipCount), sizeof(int));

    for (int i = 0; i < shipCount; ++i) {
        Starship ship;

        int nameLength;
        //now read the length of this name

        file.read(reinterpret_cast<char*>(&nameLength), sizeof(int));
        //allocate memory!
        char* nameBuffer = new char[nameLength];
        //read into buffer
        file.read(nameBuffer, nameLength);

        //now convert it to string
        ship.name = string(nameBuffer, nameLength - 1);
        //don't forget to free the memory
        delete[] nameBuffer;

        //read ship's class
        //basically do the same thing

        int classLength;
        file.read(reinterpret_cast<char*>(&classLength), sizeof(int));
        char* classBuffer = new char[classLength];
        file.read(classBuffer, classLength);
        ship.shipClass = string(classBuffer, classLength - 1);
        delete[] classBuffer;


        //read all varibales (length,capacity,speed)
        file.read(reinterpret_cast<char*>(&ship.length), sizeof(short));
        file.read(reinterpret_cast<char*>(&ship.shieldCapacity), sizeof(int));
        file.read(reinterpret_cast<char*>(&ship.maxWarp), sizeof(float));


        //read weapon numbers
        int weaponCount;
        file.read(reinterpret_cast<char*>(&weaponCount), sizeof(int));
        for (int j = 0; j < weaponCount; ++j) {
            Weapon weapon;

        //read the weapon name
        //same steps as before
        //don't forget to free the memory
            int weaponNameLength;
            file.read(reinterpret_cast<char*>(&weaponNameLength), sizeof(int));
            char* weaponNameBuffer = new char[weaponNameLength];
            file.read(weaponNameBuffer, weaponNameLength);
            weapon.name = string(weaponNameBuffer, weaponNameLength - 1);
            delete[] weaponNameBuffer;

            //read the file
            //weapon's power rating and powerConsumption

            file.read(reinterpret_cast<char*>(&weapon.powerRating), sizeof(int));
            file.read(reinterpret_cast<char*>(&weapon.powerConsumption), sizeof(float));

            //remember pushback command for adding stuff to the ship list
            ship.weapons.push_back(weapon);
        }

        //get the total firepower
        ship.totalFirepower = 0;
        for (const auto& weapon : ship.weapons) {
            ship.totalFirepower += weapon.powerRating;
        }

        ships.push_back(ship); //add to the vecotr
    }

    file.close(); //always close the file
    return ships;
}

// Function to print ship details
// that's the trickest part...
//be very careful with the format
void printShip(const Starship& ship) {
    cout << "Name: " << ship.name << endl;
    cout << "Class: " << ship.shipClass << endl;
    cout << "Length: " << ship.length << endl;
    cout << "Shield capacity: " << ship.shieldCapacity << endl;
    cout << "Maximum Warp: " << ship.maxWarp << endl;
    cout << "Armaments: " << endl;

    if (ship.weapons.empty()) {
        cout << "Unarmed" << endl;
    } else {
        for (const auto& weapon : ship.weapons) {
            cout << weapon.name << ", " << weapon.powerRating << ", " << weapon.powerConsumption << endl;
        }
        cout << "Total firepower: " << ship.totalFirepower << endl;
    }
    cout << endl;
}

int main() {
    cout << "Which file(s) to open?\n";
    cout << "1. friendlyships.shp" << endl;
    cout << "2. enemyships.shp" << endl;
    cout << "3. Both files" << endl;

    int option;
    cin >> option;
    cin.ignore();

    vector<Starship> ships;

    //base on different input, we load ship options

    if (option == 1) {
        ships = loadShips("friendlyships.shp");
    } else if (option == 2) {
        ships = loadShips("enemyships.shp");
    } else if (option == 3) {
        auto friendlyShips = loadShips("friendlyships.shp");
        auto enemyShips = loadShips("enemyships.shp");
        ships.insert(ships.end(), friendlyShips.begin(), friendlyShips.end());
        ships.insert(ships.end(), enemyShips.begin(), enemyShips.end());
    } else {
        cerr << "Invalid option!" << endl;
        return 1;
    }

    //menu
    //be careful with space...
    cout << "1. Print all ships" << endl;
    cout << "2. Starship with the strongest weapon" << endl;
    cout << "3. Strongest starship overall" << endl;
    cout << "4. Weakest ship (ignoring unarmed)" << endl;
    cout << "5. Unarmed ships" << endl;
    cin >> option;
    cin.ignore();

    //now it comes to detailed options

    switch (option) {
        case 1:
            for (const auto& ship : ships) {
                printShip(ship); //print all
            }
            break;

        case 2: {
            Starship* strongestWeaponShip = nullptr;
            int maxWeaponPower = 0;
            //only the strongest weapon
            for (auto& ship : ships) {
                for (const auto& weapon : ship.weapons) {
                    if (weapon.powerRating > maxWeaponPower) {
                        maxWeaponPower = weapon.powerRating;
                        strongestWeaponShip = &ship;
                    }
                }
            }

            if (strongestWeaponShip) {
                printShip(*strongestWeaponShip);
            }
            break;
        }

        case 3: {
            Starship* strongestShip = nullptr;
            int maxFirepower = 0;
            // the strongest ship overall
            for (auto& ship : ships) {
                if (ship.totalFirepower > maxFirepower) {
                    maxFirepower = ship.totalFirepower;
                    strongestShip = &ship;
                }
            }

            if (strongestShip) {
                printShip(*strongestShip);
            }
            break;
        }

        case 4: { //weakestShip
            Starship* weakestShip = nullptr;
            int minFirepower = INT_MAX;
            //ignore unarmed

            for (auto& ship : ships) {
                if (!ship.weapons.empty() && ship.totalFirepower < minFirepower) {
                    minFirepower = ship.totalFirepower;
                    weakestShip = &ship;
                }
            }

            if (weakestShip) {
                printShip(*weakestShip);
            }
            break;
        }

        case 5: //finally print unarmed ships !!
            for (const auto& ship : ships) {
                if (ship.weapons.empty()) {
                    printShip(ship);
                }
            }
            break;

        default: //do we need this? nope
            cerr << "Invalid option!" << endl;
            //deal with invalid options
            return 1;
    }

    return 0;
}