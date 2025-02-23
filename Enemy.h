#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <vector>

using namespace std;

class Enemy {
private:
    string id;
    string description;
    int aggressiveness;
    vector<string> killedBy; 

public:
    Enemy();
    Enemy(const string& id, const string& desc, int aggressiveness, const vector<string>& killedBy);
    string getId() const;
    string getDescription() const;
    int getAggressiveness() const;
    bool canBeKilledBy(const string& item) const; 
};

#endif