#include "room.h"
#include <algorithm>
#include <iostream>

using namespace std;


Room::Room() : 
    id(""), 
    description(""),
    locked(false),
    isDeadly(false),
    visited(false) {}


Room::Room(const string& id, const string& desc, bool locked, bool isDeadly)
    : id(id), description(desc), locked(locked), isDeadly(isDeadly), visited(false) {}


void Room::setExit(const string& direction, Room* room) {
    exits[direction] = room;
}


Room* Room::getExit(const string& direction) const {
    auto it = exits.find(direction);
    return (it != exits.end()) ? it->second : nullptr;
}



void Room::addItem(const string& item) {
    items.push_back(item);
}


void Room::removeItem(const string& item) {
    auto it = find(items.begin(), items.end(), item);
    if (it != items.end()) {
        items.erase(it);
    } else {
        cout << "Item " << item << " not found in this room." << endl;
    }
}


bool Room::hasItem(const string& item) const {
    return find(items.begin(), items.end(), item) != items.end();
}


void Room::setEnemy(const string& enemy) {
    this->enemy = enemy;
}


void Room::removeEnemy() {
    enemy = "";
}

string Room::getEnemy() const {
    return enemy;
}

string Room::getId() const {
    return id;
}

string Room::getDescription() const {
    string updatedDescription = description;

    if (items.empty()) {
        updatedDescription += " The room appears empty now.";
    } else {
        updatedDescription += " You see some objects here.";
    }

    if (!enemy.empty()) {
        updatedDescription += " There's a dangerous presence: " + enemy + "!";
    }

    return updatedDescription;
}

map<string, Room*> Room::getExits() const {
    return exits;
}

vector<string> Room::getItems() const {
    return items;
}

bool Room::isLocked() const {
    return locked;
}

void Room::unlock() {
    locked = false;
}

void Room::setRequiredItems(const vector<string>& items) {
    requiredItems = items;
}

const vector<string>& Room::getRequiredItems() const {
    return requiredItems;
}

bool Room::canUnlock(const vector<string>& playerItems) const {
    for (const auto& item : requiredItems) {
        if (find(playerItems.begin(), playerItems.end(), item) == playerItems.end()) {
            return false;
        }
    }
    return true;
}

bool Room::isRoomDeadly() const {
    return isDeadly;
}

void Room::markVisited() {
    visited = true;
}

bool Room::hasBeenVisited() const {
    return visited;
}
