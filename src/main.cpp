#include <iostream>
#include "scheduler.h"

int main() {
    // a main while loop that take a command and then a switch case over the commands
    // "add emp", "add building", "schedule", "update employee" would be nice to get user from input and have dynamic interaction!


    std::vector<Building> buildings = {
        {"Build 0", BuildingType::TWO_STORY},
        {"Build 1", BuildingType::COMMERCIAL},
        {"Build 2", BuildingType::TWO_STORY},
        {"Build 3", BuildingType::SINGLE_STORY},
        {"Build 4", BuildingType::SINGLE_STORY}
    };

    std::vector<Employee> employees = {
        {1, EmployeeType::CERTIFIED_INSTALLER, {true, true, true, true, true}},
        {2, EmployeeType::CERTIFIED_INSTALLER, {true, true, true, false, true}},
        {3, EmployeeType::INSTALLER_PENDING_CERTIFICATION, {true, true, false, true, false}},
        {4, EmployeeType::LABORER, {true, true, true, false, false}},
        {5, EmployeeType::LABORER, {true, true, false, true, true}},
        {6, EmployeeType::CERTIFIED_INSTALLER, {false, true, true, false, true}},
        {7, EmployeeType::LABORER, {true, true, true, false, true}},
        {8, EmployeeType::LABORER, {true, true, true, false, true}},
        {9, EmployeeType::INSTALLER_PENDING_CERTIFICATION, {true, false, true, false, true}},
        {10, EmployeeType::INSTALLER_PENDING_CERTIFICATION, {true, true, true, true, true}}
    };

    Scheduler scheduler;

    // a helper function could come handy to load building and employees from a vector
    for (const Building& building: buildings) {             
        scheduler.addBuilding(building.name, building.type);
    }

    for (const auto& employee : employees) {
        scheduler.addEmployee(employee.id, employee.type, employee.availability);
    }
    
    scheduler.updateAvailability(1, {false, false, false, false, false}); //multi update helper function could be handy
    scheduler.updateAvailability(1, {true, true, true, true, true});
    scheduler.schedule();   //a method to get the scheduler for the unit tests would have been nice
    scheduler.printSchedule();

    return 0;
}