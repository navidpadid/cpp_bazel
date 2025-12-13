#include <iostream>
#include <algorithm>

#include "scheduler.h"

using namespace std;

Scheduler::BuildingRequrement_Type Scheduler::buildingRequirements = {
            {BuildingType::SINGLE_STORY, {{EmployeeType::CERTIFIED_INSTALLER, 1}}},
            {BuildingType::TWO_STORY, {{EmployeeType::CERTIFIED_INSTALLER, 1}, {EmployeeType::INSTALLER_PENDING_CERTIFICATION, 1}}},
            {BuildingType::TWO_STORY, {{EmployeeType::CERTIFIED_INSTALLER, 1}, {EmployeeType::LABORER, 1}}},
            {BuildingType::COMMERCIAL, {{EmployeeType::CERTIFIED_INSTALLER, 2}, {EmployeeType::INSTALLER_PENDING_CERTIFICATION, 6}}},
            {BuildingType::COMMERCIAL, {{EmployeeType::CERTIFIED_INSTALLER, 6}, {EmployeeType::INSTALLER_PENDING_CERTIFICATION, 2}}},
            {BuildingType::COMMERCIAL, {{EmployeeType::CERTIFIED_INSTALLER, 2}, {EmployeeType::INSTALLER_PENDING_CERTIFICATION, 2}, {EmployeeType::LABORER, 4}}}
        };

Scheduler::Scheduler():
    __buildings(),
    __employees_by_id(),
    __employees_by_type_and_day(),
    __daily_schedule()
    {}


void Scheduler::__addEmployeeToAvailByTypeAndDay(const EmployeeType& empType, const int& employeeId, const std::vector<bool>& empAvailability) {
    for (DayOfWeek day = DayOfWeek::MONDAY; static_cast<int>(day) < WORK_DAYS; ++day) {
        int int_day = static_cast<int>(day);
        if (empAvailability[int_day]) {
            __employees_by_type_and_day[empType][int_day].push_back(&(__employees_by_id[employeeId]));
        }
    }
}


void Scheduler::addEmployee(const int& employeeId, const EmployeeType& empType, const std::vector<bool>& empAvailability) {
    __employees_by_id[employeeId] = Employee(employeeId, empType, empAvailability);

    if (__employees_by_type_and_day.find(empType) != __employees_by_type_and_day.end()) {
        __addEmployeeToAvailByTypeAndDay(empType, employeeId, empAvailability);
    } else {
        __employees_by_type_and_day[empType] = {};
        for (auto& employeePtrs : __employees_by_type_and_day[empType]) {
            employeePtrs = {};
        }
        __addEmployeeToAvailByTypeAndDay(empType, employeeId, empAvailability);
    }
}



void Scheduler::addBuilding(const std::string& buildName, const BuildingType& buildType) {
    __buildings.push_back(Building(buildName, buildType));
}

void Scheduler::schedule() {
    for (DayOfWeek day = DayOfWeek::MONDAY; static_cast<int>(day) < WORK_DAYS; ++day) {
        int int_day = static_cast<int>(day);
        for (auto it = __buildings.begin(); it != __buildings.end(); ) {
            auto building = *it;
            std::vector<int> assignedEmployees;

            if (__canBuild(building, int_day, assignedEmployees)) {
                __assignEmployees(building, int_day, assignedEmployees);
                it = __buildings.erase(it);
            } else {
                ++it;
            }
        }
    }
}

bool Scheduler::__canBuild(const Building& building, int day, std::vector<int>& assignedEmployees) {

    auto conditions = buildingRequirements.equal_range(building.type);
    bool cond_met_so_far = true;
    auto condition = (conditions.first)->second;

    for (auto it = conditions.first; it != conditions.second; ++it) {
        cond_met_so_far = true;
        condition = it->second;
        
        for (const auto& [employeeType, employeeTypeCount] : condition) {
            if (static_cast<int>(__employees_by_type_and_day[employeeType][day].size()) < employeeTypeCount) {
                cond_met_so_far = false;
            }
            if (!cond_met_so_far) {
                break;
            }
        }

        if (cond_met_so_far) {
            break;
        }
    }

    if (cond_met_so_far) {
        for (const auto& [employeeType, employeeTypeCount] : condition) {
            int workers_count = employeeTypeCount;
            while (workers_count > 0) {
                Employee *emp = __employees_by_type_and_day[employeeType][day].back();
                __employees_by_type_and_day[employeeType][day].pop_back();
                assignedEmployees.push_back(emp->id);
                workers_count--;
            }
        }
    }

    return cond_met_so_far;
}

void Scheduler::__assignEmployees(const Building& building, int day, const std::vector<int>& assignedEmployees) {
    __daily_schedule[day].push_back(make_pair(building.name, assignedEmployees));
}

void Scheduler::printSchedule() const {
    cout << "************ SCHEDULE ***************" << endl;
    for (DayOfWeek currDay = DayOfWeek::MONDAY; static_cast<int>(currDay) < WORK_DAYS; ++currDay) {
        for (const auto& buldingAssignedEmpsPair : __daily_schedule[static_cast<int>(currDay)]) {
            cout << dayToStr.at(currDay) << ": ";
            cout << "Building -> " << buldingAssignedEmpsPair.first << ": | Employees -> ";
            for (const auto& empId : buldingAssignedEmpsPair.second) {
                cout << "[" << empId << "] ";
            }
            cout << endl;
        }
    }
    cout << "*************************************" << endl;
}

void Scheduler::updateAvailability(const int& employeeId, const std::vector<bool>& newAvailability) {
    for (DayOfWeek day = DayOfWeek::MONDAY; static_cast<int>(day) < WORK_DAYS; ++day) {
        int int_day = static_cast<int>(day);
        bool future_avail = newAvailability[int_day];
        EmployeeType type_to_check = __employees_by_id[employeeId].type;
        auto to_check_emps = &__employees_by_type_and_day[type_to_check][int_day];
        auto was_available_already = find_if((*to_check_emps).begin(), (*to_check_emps).end(), [&] (Employee *emp_ptr) -> bool {
            return emp_ptr->id == employeeId && emp_ptr->availability[int_day];
        });

        if (future_avail) {
            if (was_available_already == (*to_check_emps).end()) {
                (*to_check_emps).push_back(&__employees_by_id[employeeId]);
            }
        } else {
            if (was_available_already != (*to_check_emps).end()) {
                (*to_check_emps).erase(was_available_already);
            }
        }
        
    }
    __employees_by_id[employeeId].availability = newAvailability;
}