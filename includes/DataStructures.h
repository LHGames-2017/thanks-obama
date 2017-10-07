#pragma once

#include <math.h>
#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include "json.hpp"

using namespace nlohmann;
using namespace std;

class Tile {

public:
    Tile(int x_, int y_, uint8_t content_) : X(x_), Y(y_), Content(content_) {}
    uint8_t Content;
    int X;
    int Y;


};

class Point
{
    int _x;
    int _y;

public:
    int getX() const
    {
        return _x;
    }

    int getY() const
    {
        return _y;
    }

    Point(int x = 0, int y = 0)
    {
        _x = x;
        _y = y;
    }


    Point operator- (const Point& rhs)
    {
        return Point(this->getX() - rhs.getX(), this->getY() - rhs.getY());
    }

    Point operator+ (const Point& rhs)
    {
        return Point(this->getX() + rhs.getX(), this->getY() + rhs.getY());
    }

    static double distance(Point p1, Point p2)
    {
        return sqrt((p1.getX() - p2.getX()) * (p1.getX() - p2.getX()) + (p1.getY() - p2.getY()) * (p1.getY() - p2.getY()));
    }

    std::string toString()
    {
        return "{{" + std::to_string(getX()) + ", " + std::to_string(getY()) + "}}";
    }

};

class Player {

public:

    Player(int health, int maxHealth, Point position, Point houseLocation, int score,
                  int carriedResources, int carryingCapacity)
    {
        Health = health;
        MaxHealth = maxHealth;
        Position = position;
        HouseLocation = houseLocation;
        Score = score;
        CarriedResources = carriedResources;
        CarryingCapacity = carryingCapacity;
    }

    void parsePlayer(json infoJson)
    {        
        Point position = Point(infoJson["Player"]["Position"]["X"], infoJson["Player"]["Position"]["Y"]);
        Point houseLocation = Point(infoJson["Player"]["HouseLocation"]["X"], infoJson["Player"]["HouseLocation"]["Y"]);

        Health = infoJson["Player"]["Health"];
        MaxHealth = infoJson["Player"]["MaxHealth"];
        CarriedResources = infoJson["Player"]["CarriedResources"];
        CarryingCapacity = infoJson["Player"]["CarryingCapacity"];
        Position = position;
        HouseLocation = houseLocation;
        Score = infoJson["Player"]["Score"];
    }

    Player() {}

    int Health;
    int MaxHealth;
    int CarriedResources;
    int CarryingCapacity;
    Point Position;
    Point HouseLocation;
    int Score;

    void print() {
        cout << "---------Player info ---------" << endl;
        cout << "Health : " << Health << endl;
        cout << "MaxHealth : " << MaxHealth << endl;
        cout << "CarriedResources : " << CarriedResources << endl;
        cout << "Position : " << Position.toString() << endl;
        cout << "HouseLocation : " << HouseLocation.toString() << endl;
        cout << "Score : " << Score << endl << flush;      
    }
};

enum PurchasableItem {
    MicrosoftSword,
    UbisoftShield,
    DevolutionsBackpack,
    DevolutionsPickaxe,
    HealthPotion,
};

enum TileContent {
    EmptyTC, ResourceTC, HouseTC, PlayerTC, WallTC, LavaTC, ShopTC
};

enum TileType {
    TileTT, WallTT, HouseTT, LavaTT, ResourceTT, ShopTT
};

enum UpgradeType {
    CarryingCapacity, AttackPower, Defence, MaximumHealth,
    CollectingSpeed
};

enum ActionTypes {
    DefaultAction, MoveAction, AttackAction, CollectAction,
    UpgradeAction, StealAction, PurchaseAction, HealAction
};

class PlayerInfo {

public:

    PlayerInfo(int health, int maxHealth, Point position)
    {
        Health = health;
        MaxHealth = maxHealth;
        Position = position;
    }

    int Health;
    int MaxHealth;
    Point Position;

};

class GameInfo {

public:

    Player player;
    string customSerializedMap;
    vector<map<string, PlayerInfo>> otherPlayers;

    GameInfo(Player player_, string serializedMap, vector<map<string, PlayerInfo>> otherPlayers_) {

        player = player_;
        customSerializedMap = serializedMap;
        otherPlayers = otherPlayers_;

    }

};

class ActionContent {

public:

    ActionContent() {}

    ActionContent(string actionName, string content) : ActionName(actionName), Content(content) {}

    string ActionName;
    string Content;

};
