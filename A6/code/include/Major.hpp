#pragma once
#ifndef MAJOR_INCLUDE
#define MAJOR_INCLUDE

#include "Global.hpp"
#include "Entity.hpp"

class Major : public Entity {
public:
    Major(string id, string name);
    ~Major(){};
protected:

private:
};

#endif