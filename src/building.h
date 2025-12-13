#pragma once
#include <string>

enum class BuildingType {
    SINGLE_STORY,
    TWO_STORY,
    COMMERCIAL
};

class Building {
    public:
        std::string name;
        BuildingType type;
        Building(const std::string& name, const BuildingType& type);
};