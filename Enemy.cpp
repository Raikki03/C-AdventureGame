#include "enemy.h"
#include <algorithm>

using namespace std;

Enemy::Enemy() : 
    id(""), 
    description(""), 
    aggressiveness(0) {}

Enemy::Enemy(const string& id, const string& desc, int aggressiveness, const vector<string>& killedBy)
    : id(id), description(desc), aggressiveness(aggressiveness), killedBy(killedBy) {}

string Enemy::getId() const {
    return id;
}

string Enemy::getDescription() const {
    return description;
}

int Enemy::getAggressiveness() const {
    return aggressiveness;
}

bool Enemy::canBeKilledBy(const string& item) const {
    return find(killedBy.begin(), killedBy.end(), item) != killedBy.end();
}