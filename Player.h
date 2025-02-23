#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "room.h"

class Enemy;

class Player {
private:
    Room* currentRoom;
    vector<string> inventory;
    

public:
    Player(Room* startRoom);
    void setCurrentRoom(Room* room);
    Room* getCurrentRoom() const;
    void moveToRoom(Room* room);
    void pickUpItem(const string& item);
    void dropItem(const string& item);
    void listItems() const;
    bool hasItem(const string& item) const;
    const vector<string>& getInventory() const;
    bool canKill(const Enemy& enemy) const; 
};

#endif