#include "player.h"
#include "enemy.h"
#include <iostream>
#include <algorithm>

using namespace std;

Player::Player(Room* startRoom) : currentRoom(startRoom) {}

void Player::setCurrentRoom(Room* room) {
    currentRoom = room;
}

Room* Player::getCurrentRoom() const {
    return currentRoom;
}

void Player::moveToRoom(Room* room) {
    currentRoom = room;
}

void Player::pickUpItem(const string& item) {
    inventory.push_back(item);
}

void Player::dropItem(const string& item) {
    auto it = find(inventory.begin(), inventory.end(), item);
    if (it != inventory.end()) {
        inventory.erase(it);
    } else {
        cout << "You do not have a " << item << "." << endl;
    }
}

void Player::listItems() const {
    if (inventory.empty()) {
        cout << "You do not have any items." << endl;
    } else {
        cout << "You are carrying:" << endl;
        for (const auto& item : inventory) {
            cout << item << endl;
        }
    }
}

bool Player::hasItem(const string& item) const {
    return find(inventory.begin(), inventory.end(), item) != inventory.end();
}

const vector<string>& Player::getInventory() const {
    return inventory;
}

bool Player::canKill(const Enemy& enemy) const {
    for (const auto& item : inventory) {
        if (enemy.canBeKilledBy(item)) {
            return true;
        }
    }
    return false;
}