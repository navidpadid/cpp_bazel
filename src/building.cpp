#include <string>
#include "building.h"

using namespace std;

Building::Building(const string& name, const BuildingType& type):
    name(name),
    type(type)
    {}