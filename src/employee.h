#pragma once
#include <vector>

enum class EmployeeType {
    CERTIFIED_INSTALLER,
    INSTALLER_PENDING_CERTIFICATION,
    LABORER
};

class Employee {
    public:
        int id;
        EmployeeType type;
        std::vector<bool> availability;
        Employee();
        Employee(const int& id, const EmployeeType& type, const std::vector<bool>& availability);
};