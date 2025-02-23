#ifndef OBJECT_H
#define OBJECT_H

#include <string>

using namespace std;

class Object {
private:
    string id;
    string description;

public:
    Object();
    Object(const string& id, const string& desc);
    string getId() const;
    string getDescription() const;
};

#endif
