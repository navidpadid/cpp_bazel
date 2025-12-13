#pragma once
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <utility>
#include "employee.h"
#include "building.h"
#include "days.h"


class Scheduler {
    public:
        using BuildingRequrement_Type = std::unordered_multimap<BuildingType,
                                            std::vector<
                                                std::pair<EmployeeType, int>
                                                >
                                            >;
        static BuildingRequrement_Type buildingRequirements; //the conditions for each building
        Scheduler();
        void schedule();
        void printSchedule() const; //a function to get the schedule for the unit tests is needed,
                                    // but for now just using the print and manual inspection
        void updateAvailability(const int& employeeId, const std::vector<bool>& newAvailability);
        void addEmployee(const int& employeeId, const EmployeeType& empType, const std::vector<bool>& empAvailability);
        void addBuilding(const std::string& buildName, const BuildingType& buildType);

    private:
        using __EmployeeAvailabilityByTypeAndDay_Type = std::unordered_map<EmployeeType, 
                                                            std::array<
                                                                std::vector<Employee*>
                                                            , WORK_DAYS>
                                                        >;
        using __DailySchedule_Type = std::array<
                                                std::vector<
                                                    std::pair<std::string, std::vector<int>>
                                                >
                                            , WORK_DAYS>;

        std::vector<Building> __buildings;
        std::unordered_map<int, Employee> __employees_by_id; //access employees by ID
        __EmployeeAvailabilityByTypeAndDay_Type __employees_by_type_and_day; //access available employees reference filtered by type and day,
                                                                             // employee ref points to employees in __employees_by_id
        __DailySchedule_Type __daily_schedule; // array of weekdays, each holding the name of the building(s) and the list of employees to work on it

        bool __canBuild(const Building& building, int day, std::vector<int>& assignedEmployees); //Checks if a building can be built on a given day and fill the assigned employees vector
        void __assignEmployees(const Building& building, int day, const std::vector<int>& assignedEmployees); //add the building and the assigned employees for that day to the schedule
        void __addEmployeeToAvailByTypeAndDay(const EmployeeType& empType, const int& employeeId, const std::vector<bool>& empAvailability);
};
