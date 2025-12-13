#include <vector>
#include "employee.h"

using namespace std;

Employee::Employee(){};

Employee::Employee(const int& id, const EmployeeType& type, const vector<bool>& availability):
    id(id),
    type(type),
    availability(availability)
    {}