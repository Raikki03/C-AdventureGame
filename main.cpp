#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "json.hpp"
#include "room.h"
#include "object.h"
#include "enemy.h"
#include "player.h"
#include <cstdlib>  
#include <ctime>    

using json = nlohmann::json;
namespace fs = std::filesystem; 
using namespace std;

struct GameObj {
    enum Type { Collect, Room } type;
    vector<string> targets;
};

GameObj::Type ObjType(const string& typeStr) {
    if (typeStr == "collect") return GameObj::Collect;
    if (typeStr == "room") return GameObj::Room;

    cerr << "Cannot recognise objective type: " << typeStr << endl;
    throw runtime_error("Invalid objective type: " + typeStr);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <map_file.json>" << endl;
        cout << "Available maps in 'maps' directory:" << endl;


        string mapsDir = "maps";
        for (const auto& entry : fs::directory_iterator(mapsDir)) {
            if (entry.path().extension() == ".json") {
                cout << "  " << entry.path().filename() << endl;
            }
        }

        return 1;
    }

    string mapFile = "maps/" + string(argv[1]);

    ifstream ifs(mapFile);
    if (!ifs.is_open()) {
        cerr << "Cannot open the file: " << mapFile << endl;
        return 1;
    }

    json j;
    ifs >> j;
cout << "Loaded JSON file: " << argv[1] << endl;
cout << "JSON content: " << j.dump(4) << endl; 

if (!j.contains("objective")) {
    cerr << "Error: Missing 'objective' in JSON file." << endl;
    return 1;
}
if (!j.contains("rooms")) {
    cerr << "Error: Missing 'rooms' in JSON file." << endl;
    return 1;
}
if (!j.contains("objects")) {
    cerr << "Error: Missing 'objects' in JSON file." << endl;
    return 1;
}
if (!j.contains("enemies")) {
    cerr << "Error: Missing 'enemies' in JSON file." << endl;
    return 1;
}
if (!j.contains("player")) {
    cerr << "Error: Missing 'player' in JSON file." << endl;
    return 1;
}
    GameObj objective;
    objective.type = ObjType(j["objective"]["type"]);
    for (const auto& target : j["objective"]["what"]) {
        objective.targets.push_back(target);
    }

    unordered_map<string, Room> rooms;
    unordered_map<string, Object> objects;
    unordered_map<string, Enemy> enemies;
    Player* player = nullptr;

    for (const auto& room : j["rooms"]) {
        string id = room["id"];
        string desc = room["desc"];
        bool locked = room.value("locked", false);
        bool isDeadly = room.value("isDeadly", false);
        Room& currentRoom = rooms[id];
        currentRoom = Room(id, desc, locked, isDeadly);

        if (room.contains("requiredItems")) {
            vector<string> requiredItems = room["requiredItems"].get<vector<string>>();
            currentRoom.setRequiredItems(requiredItems);
        }

        if (room.contains("exits")) {
            for (auto& exit : room["exits"].items()) {
                string direction = exit.key();
                string exitRoomId = exit.value();
                currentRoom.setExit(direction, &rooms[exitRoomId]);
            }
        }
    }


    for (const auto& object : j["objects"]) {
        string id = object["id"];
        string desc = object["desc"];
        objects[id] = Object(id, desc);
        string room = object["initialroom"];
        rooms[room].addItem(id);
    }


    for (const auto& enemy : j["enemies"]) {
        string id = enemy["id"];
        string desc = enemy["desc"];
        int aggressiveness = enemy["aggressiveness"]; 
        vector<string> killedBy = enemy["killedby"].get<vector<string>>();
        enemies[id] = Enemy(id, desc, aggressiveness, killedBy);
        string room = enemy["initialroom"];
        rooms[room].setEnemy(id);
    }


    string initialRoom = j["player"]["initialroom"];
    player = new Player(&rooms[initialRoom]);

    cout << "Welcome to the Text Adventure Game!" << endl;
    cout << "Your goal is to reach the winning room. Be careful—some rooms are deadly!" << endl;
    bool activeGame = true;

    while (activeGame) {
        Room* currentRoom = player->getCurrentRoom();
        string enemyId = currentRoom->getEnemy();

        if (!enemyId.empty()) {
            Enemy& enemy = enemies[enemyId];
    
            if (player->hasItem("pistol")) {
                cout << "You see a " << enemyId << ": " << enemy.getDescription() << endl;
                cout << "You use the pistol to kill the " << enemyId << "!" << endl;
                currentRoom->removeEnemy(); 
            } else {
                cout << "You encounter a " << enemyId << ": " << enemy.getDescription() << endl;
                cout << "The " << enemyId << " attacks you and you die!" << endl;
                cout << "Game Over!" << endl;
                activeGame = false;
                break;
            }
        }

        cout << currentRoom->getDescription() << endl;

        const auto& roomItems = currentRoom->getItems();
        if (!roomItems.empty()) {
            cout << "You see the following items: ";
            for (const auto& item : roomItems) {
                cout << item << " ";
            }
            cout << endl;
        }

        const auto& exits = currentRoom->getExits();
        cout << "Exits: ";
        for (const auto& exit : exits) {
            cout << exit.first << " ";
        }
        cout << endl;

        string command;
        cout << "> ";
        getline(cin, command);
        stringstream ss(command);
        string playerAction, target;
        ss >> playerAction;
    
        if (playerAction == "quit") {
            activeGame = false;
        } else if (playerAction == "look") {
            cout << currentRoom->getDescription() << endl;
            if (!roomItems.empty()) {
                cout << "You see the following items: ";
                for (const auto& item : roomItems) {
                    cout << item << " ";
                }
                cout << endl;
            }
        } else if (playerAction == "go") {
            ss >> target;
            Room* nextRoom = currentRoom->getExit(target);
    
            if (nextRoom) {
                player->setCurrentRoom(nextRoom);
                cout << "You go " << target << "." << endl;
            } else {
                cout << "You cannot go that way." << endl;
            }
        } else if (playerAction == "take") {
            string objectName;
            getline(ss, objectName);
            objectName.erase(0, objectName.find_first_not_of(" \t"));
        
            if (currentRoom->hasItem(objectName)) {
                currentRoom->removeItem(objectName); 
                player->pickUpItem(objectName);
                cout << "You have taken the " << objectName << "." << endl;
            } else {
                cout << "There is no " << objectName << " here." << endl;
            }
        }
    
        if (objective.type == GameObj::Room) {
            if (currentRoom->getId() == objective.targets[0]) {
                cout << "Congratulations! You have reached the winning room!" << endl;
                activeGame = false;
            }
        }
    }

    delete player;
    return 0;
}