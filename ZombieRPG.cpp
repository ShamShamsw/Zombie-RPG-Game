#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <ctime>

using namespace std;

// Constants
//Map size
const int MAP_SIZE = 5;

//Max values
// Player stats Health and Hunger
const int MAX_HEALTH = 100;
const int MAX_HUNGER = 100;

// Player stats Damage
const int MAX_DAMAGE = 10;

// Player stats Heal and Food
const int MAX_HEAL = 20;
const int MAX_FOOD = 20;

// Player stats Medkits and Weapons
const int MAX_MEDKITS = 5;
const int MAX_WEAPONS = 5;

//Max values
// Zombie stats Health
const int MAX_ZOMBIE_HEALTH = 50;

// Zombie stats Damage
const int MAX_ZOMBIE_DAMAGE = 5;

// Max Zombies
const int MAX_ZOMBIES = 5;

// Classes
class Player {
public:
    Player() {
        health = MAX_HEALTH;
        hunger = MAX_HUNGER;
        damage = 1;
        medkits = 0;
        weapons = 0;
        location = 0;
    }

void takeDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}

void heal(int heal) {
    health += heal;
    if (health > MAX_HEALTH) {
        health = MAX_HEALTH;
    }
}

void eat(int food) {
    hunger += food;
    if (hunger > MAX_HUNGER) {
        hunger = MAX_HUNGER;
    }
}

void addMedkit() {
    medkits++;
}

void addWeapon() {
    weapons++;
}

void addZombieKill() {
    zombieKills++;
}

void increaseDamage() {
    damage++;
}

void decreaseDamage() {
    damage--;
}

int getHealth() {
    return health;
}

int getHunger() {
    return hunger;
}

int getMedkits() {
    return medkits;
}

int getWeapons() {
    return weapons;
}

int getZombiesKilled() {
    return zombieKills;
}

int getDamage() {
    return damage;
}


private:
    int health;
    int hunger;
    int medkits;
    int weapons;
    int location;
    int zombieKills;
    int damage;
};

class Item {
public:
    Item(string name, int heal, int food, int damage) {
        this->name = name;
        this->heal = heal;
        this->food = food;
        this->damage = damage;
    }

string getName() {
    return name;
}

int getHeal() {
    return heal;
}

int getFood() {
    return food;
}

int getDamage() {
    return damage;
}

private:
    string name;
    int heal;
    int food;
    int damage;
};

class Location {
public:
    Location(string name, string description) {
        this->name = name;
        this->description = description;
    }

string getName() {
    return name;
}

string getDescription() {
    return description;
}

private:
    string name;
    string description;
};

class Zombie {
public:
    Zombie(int zombieHealth, int zombieDamage) {
        zombieHealth = MAX_ZOMBIE_HEALTH;
        zombieDamage = MAX_ZOMBIE_DAMAGE;
    }

    int getZombieHealth() {
        return zombieHealth;
    }

    int getZDamage() {
        return zombieDamage;
    }

    void takeDamage(int damage) {
        zombieHealth -= damage;
        if (zombieHealth < 0) {
            zombieHealth = 0;
        }

    }

    private:
        int zombieHealth;
        int zombieDamage;
        int damage;
    };
}

// Functions
void printHelp() {
    cout << "Commands:" << endl;
    cout << "help - Show this help" << endl;
    cout << "map - Show the map" << endl;
    cout << "stats - Show the stats" << endl;
    cout << "inventory - Show the inventory" << endl;
    cout << "move [location] - Move to a location" << endl;
    cout << "pick [item] - Pick up an item" << endl;
    cout << "eat - Eat food" << endl;
    cout << "heal - Use a medkit" << endl;
    cout << "fight - Fight a zombie" << endl;
    cout << "exit - Exit the game" << endl;
}

void printMap(int location) {
    for (int i = 0; i < MAP_SIZE; i++) {
        if (i == location) {
            cout << "X";
        } else {
            cout << ".";
        }
    }
    cout << endl;
}

void printStats(Player player) {
    cout << "Health: " << player.getHealth() << endl;
    cout << "Hunger: " << player.getHunger() << endl;
    cout << "Medkits: " << player.getMedkits() << endl;
    cout << "Weapons: " << player.getWeapons() << endl;
    cout << "Zombies Killed: " << player.getZombiesKilled() << endl;
    cout << "Damage: " << player.getDamage() << endl;
}

void printInventory(vector<Item> inventory) {
    for (int i = 0; i < inventory.size(); i++) {
        cout << inventory[i].getName() << endl;
    }
}

void printLocation(int location, map<int, Location> locations) {
    cout << locations[location].getDescription() << endl;
}

void fightZombie(Player& player, Zombie& zombie) {
    while (player.getHealth() > 0 && zombie.getZombieHealth() > 0) {
        player.takeDamage(zombie.getZDamage());
        zombie.takeDamage(player.getDamage());
    }

    if (player.getHealth() > 0) {
        player.addZombieKill();
    } else {
        cout << "You died!" << endl;
    }
}

int main() {
    // Initialize player
    Player player;

    // Initialize items
    Item medkit("Medkit", MAX_HEAL, 0, 0);
    Item food("Food", 0, MAX_FOOD, 0);
    Item weapon("Weapon", 0, 0, MAX_DAMAGE);

    // Initialize locations
    map<int, Location> locations;
    locations[0] = Location("House", "You are in a house. There is a medkit here.");
    locations[1] = Location("Store", "You are in a store. There is food here.");
    locations[2] = Location("Police Station", "You are in a police station. There is a weapon here.");
    locations[3] = Location("Hospital", "You are in a hospital. There is a medkit here.");
    locations[4] = Location("Street", "You are in the street.");

    // Initialize zombies
    vector<Zombie> zombies;
    for (int i = 0; i < MAX_ZOMBIES; i++) {
        zombies.push_back(Zombie(MAX_HEALTH, MAX_DAMAGE));
    }

    // Initialize inventory
    vector<Item> inventory;

    // Initialize random number generator
    mt19937 randomGenerator(time(0));
    uniform_int_distribution<int> locationDistribution(0, MAP_SIZE - 1);
    uniform_int_distribution<int> itemDistribution(0, 2);
    uniform_int_distribution<int> zombieDistribution(0, MAX_ZOMBIES - 1);

    // Game loop
    string command;
    while (true) {
        cout << "> ";
        cin >> command;

        if (command == "help") {
            printHelp();
        } else if (command == "map") {
            printMap(player.getLocation());
        } else if (command == "stats") {
            printStats(player);
        } else if (command == "inventory") {
            printInventory(inventory);
        } else if (command == "move") {
            int location = locationDistribution(randomGenerator);
            player.setLocation(location);
            printLocation(location, locations);
            if (location == 4) {
                int zombieIndex = zombieDistribution(randomGenerator);
                fightZombie(player, zombies[zombieIndex]);
            }
        } else if (command == "pick") {
            int itemIndex = itemDistribution(randomGenerator);
            if (itemIndex == 0) {
                inventory.push_back(medkit);
            } else if (itemIndex == 1) {
                inventory.push_back(food);
            } else if (itemIndex == 2) {
                inventory.push_back(weapon);
            }
        } else if (command == "eat") {

        } else if (command == "heal") {

        } else if (command == "fight") {

        } else if (command == "exit") {
            break;
        } else {
            cout << "Invalid command!" << endl;
        }

    }

    return 0;