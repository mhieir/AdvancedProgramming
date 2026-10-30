#pragma once
#ifndef ENTITY_INCLUDE
#define ENTITY_INCLUDE

#include "Global.hpp"

class Entity {
public:
    Entity(string id, string name);
    ~Entity() {};
    string getId() {return id;}
    string getName() {return name;}
protected:
    string id, name;
private:
};

#endif