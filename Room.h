#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <map>
#include <vector>

using namespace std;

class Room {
private:
    string id;
    string description;
    map<string, Room*> exits;
    vector<string> items;
    string enemy; 
    bool locked;
    vector<string> requiredItems;
    bool isDeadly;
    bool visited;

public:
    Room();
    Room(const string& id, const string& desc, bool locked = false, bool isDeadly = false);

    void setExit(const string& direction, Room* room);
    Room* getExit(const string& direction) const;

    void addItem(const string& item);
    void removeItem(const string& item);
    bool hasItem(const string& item) const;

    void setEnemy(const string& enemy);
    void removeEnemy();
    string getEnemy() const; 

    string getId() const;
    string getDescription() const;
    map<string, Room*> getExits() const;
    vector<string> getItems() const;

    bool isLocked() const;
    void unlock();
    void setRequiredItems(const vector<string>& items);
    const vector<string>& getRequiredItems() const;
    bool canUnlock(const vector<string>& playerItems) const;

    bool isRoomDeadly() const;
    void markVisited();
    bool hasBeenVisited() const;
};

#endif
