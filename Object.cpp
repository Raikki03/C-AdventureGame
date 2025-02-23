#include "object.h"

using namespace std;

Object::Object(): 
    id(""), 
    description("") {}

Object::Object(const string& id, const string& desc)
    : id(id), description(desc) {}
string Object::getId() const {
    return id;
}

string Object::getDescription() const {
    return description;
}
