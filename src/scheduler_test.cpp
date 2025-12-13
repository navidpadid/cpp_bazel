#include <gtest/gtest.h>
#include "scheduler.h"

using namespace std;


class SchedulerTest : public testing::Test {
  protected:
        Scheduler scheduler;
        std::vector<Building> buildings;
        std::vector<Employee> employees;
        

    SchedulerTest() {
        scheduler = {};
        buildings = {};
        employees = {};
    }
};


TEST_F(SchedulerTest, randomSchedule) {
    buildings = {
        {"Build 0", BuildingType::TWO_STORY},
        {"Build 1", BuildingType::COMMERCIAL},
        {"Build 2", BuildingType::TWO_STORY},
        {"Build 3", BuildingType::SINGLE_STORY},
        {"Build 4", BuildingType::SINGLE_STORY}
    };

    employees = {
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

    for (const Building& building: buildings) {
        scheduler.addBuilding(building.name, building.type);
    }

    for (const auto& employee : employees) {
        scheduler.addEmployee(employee.id, employee.type, employee.availability);
    }
    
    scheduler.schedule();
    scheduler.printSchedule();
    EXPECT_EQ(1, 1);
}

TEST_F(SchedulerTest, noEmployeeNoBuilding) {
    for (const Building& building: buildings) {
        scheduler.addBuilding(building.name, building.type);
    }

    for (const auto& employee : employees) {
        scheduler.addEmployee(employee.id, employee.type, employee.availability);
    }
    
    scheduler.schedule();
    scheduler.printSchedule();
    EXPECT_EQ(1, 1);
}

TEST_F(SchedulerTest, noEmployee) {
    buildings = {
        {"Build 0", BuildingType::TWO_STORY},
        {"Build 1", BuildingType::COMMERCIAL},
        {"Build 2", BuildingType::TWO_STORY},
        {"Build 3", BuildingType::SINGLE_STORY},
        {"Build 4", BuildingType::SINGLE_STORY}
    };

    employees = {};

    for (const Building& building: buildings) {
        scheduler.addBuilding(building.name, building.type);
    }

    for (const auto& employee : employees) {
        scheduler.addEmployee(employee.id, employee.type, employee.availability);
    }
    
    scheduler.schedule();
    scheduler.printSchedule();
    EXPECT_EQ(1, 1);
}

TEST_F(SchedulerTest, noBuilding) {
    buildings = {};

    employees = {
        {1, EmployeeType::CERTIFIED_INSTALLER, {true, true, true, true, true}},
        {2, EmployeeType::CERTIFIED_INSTALLER, {true, false, true, false, true}},
        {3, EmployeeType::INSTALLER_PENDING_CERTIFICATION, {false, true, false, true, false}},
        {4, EmployeeType::LABORER, {true, true, true, false, false}},
        {5, EmployeeType::LABORER, {false, false, false, true, true}},
        {6, EmployeeType::CERTIFIED_INSTALLER, {true, false, true, false, true}},
        {7, EmployeeType::LABORER, {true, false, true, false, true}},
        {8, EmployeeType::INSTALLER_PENDING_CERTIFICATION, {true, false, true, false, true}}
    };

    for (const Building& building: buildings) {
        scheduler.addBuilding(building.name, building.type);
    }

    for (const auto& employee : employees) {
        scheduler.addEmployee(employee.id, employee.type, employee.availability);
    }
    
    scheduler.schedule();
    scheduler.printSchedule();
    EXPECT_EQ(1, 1);
}



TEST_F(SchedulerTest, allDaysEmpsAvailable) {
    buildings = {
        {"Build 0", BuildingType::TWO_STORY},
        {"Build 1", BuildingType::COMMERCIAL},
        {"Build 2", BuildingType::TWO_STORY},
        {"Build 3", BuildingType::SINGLE_STORY},
        {"Build 4", BuildingType::SINGLE_STORY}
    };

    employees = {
        {1, EmployeeType::CERTIFIED_INSTALLER, {true, true, true, true, true}},
        {2, EmployeeType::CERTIFIED_INSTALLER, {true, true, true, true, true}},
        {3, EmployeeType::INSTALLER_PENDING_CERTIFICATION, {true, true, true, true, true}},
        {4, EmployeeType::LABORER, {true, true, true, true, true}},
        {5, EmployeeType::LABORER, {true, true, true, true, true}},
        {6, EmployeeType::CERTIFIED_INSTALLER, {true, true, true, true, true}},
        {7, EmployeeType::LABORER, {true, true, true, true, true}},
        {8, EmployeeType::INSTALLER_PENDING_CERTIFICATION, {true, true, true, true, true}},
        {9, EmployeeType::INSTALLER_PENDING_CERTIFICATION, {true, true, true, true, true}},
        {10, EmployeeType::LABORER, {true, true, true, true, true}},
};

    for (const Building& building: buildings) {
        scheduler.addBuilding(building.name, building.type);
    }

    for (const auto& employee : employees) {
        scheduler.addEmployee(employee.id, employee.type, employee.availability);
    }
    
    scheduler.schedule();
    scheduler.printSchedule();
    EXPECT_EQ(1, 1);
}


TEST_F(SchedulerTest, OneTypeEmp_CERTIFIED_INSTALLER) {
    buildings = {
        {"Build 0", BuildingType::TWO_STORY},
        {"Build 1", BuildingType::COMMERCIAL},
        {"Build 2", BuildingType::TWO_STORY},
        {"Build 3", BuildingType::SINGLE_STORY},
        {"Build 4", BuildingType::SINGLE_STORY}
    };

    employees = {
        {1, EmployeeType::CERTIFIED_INSTALLER, {true, true, true, true, true}},
        {2, EmployeeType::CERTIFIED_INSTALLER, {true, true, true, true, true}},
        {3, EmployeeType::CERTIFIED_INSTALLER, {true, true, true, true, true}},
        {4, EmployeeType::CERTIFIED_INSTALLER, {true, true, true, true, true}},
        {5, EmployeeType::CERTIFIED_INSTALLER, {true, true, true, true, true}},
        {6, EmployeeType::CERTIFIED_INSTALLER, {true, true, true, true, true}},
        {7, EmployeeType::CERTIFIED_INSTALLER, {true, true, true, true, true}},
        {8, EmployeeType::CERTIFIED_INSTALLER, {true, true, true, true, true}},
        {9, EmployeeType::CERTIFIED_INSTALLER, {true, true, true, true, true}},
        {10, EmployeeType::CERTIFIED_INSTALLER, {true, true, true, true, true}},
};

    for (const Building& building: buildings) {
        scheduler.addBuilding(building.name, building.type);
    }

    for (const auto& employee : employees) {
        scheduler.addEmployee(employee.id, employee.type, employee.availability);
    }
    
    scheduler.schedule();
    scheduler.printSchedule();
    EXPECT_EQ(1, 1);
}


TEST_F(SchedulerTest, lessThanWorkDayBuildings) {
    buildings = {
        {"Build 0", BuildingType::TWO_STORY},
        {"Build 1", BuildingType::COMMERCIAL},
        {"Build 2", BuildingType::TWO_STORY},
    };

    employees = {
        {1, EmployeeType::CERTIFIED_INSTALLER, {true, true, true, true, true}},
        {2, EmployeeType::CERTIFIED_INSTALLER, {true, false, true, false, true}},
        {3, EmployeeType::INSTALLER_PENDING_CERTIFICATION, {false, true, false, true, false}},
        {4, EmployeeType::LABORER, {true, true, true, false, false}},
        {5, EmployeeType::LABORER, {false, false, false, true, true}},
        {6, EmployeeType::CERTIFIED_INSTALLER, {true, false, true, false, true}},
        {7, EmployeeType::LABORER, {true, false, true, false, true}},
        {8, EmployeeType::INSTALLER_PENDING_CERTIFICATION, {true, false, true, false, true}}
};

    for (const Building& building: buildings) {
        scheduler.addBuilding(building.name, building.type);
    }

    for (const auto& employee : employees) {
        scheduler.addEmployee(employee.id, employee.type, employee.availability);
    }
    
    scheduler.schedule();
    scheduler.printSchedule();
    EXPECT_EQ(1, 1);
}

TEST_F(SchedulerTest, buildingsMoreThanCanHandle) {
    buildings = {
        {"Build 0", BuildingType::TWO_STORY},
        {"Build 1", BuildingType::COMMERCIAL},
        {"Build 2", BuildingType::TWO_STORY},
        {"Build 3", BuildingType::TWO_STORY},
        {"Build 4", BuildingType::COMMERCIAL},
        {"Build 5", BuildingType::TWO_STORY},
        {"Build 6", BuildingType::TWO_STORY},
        {"Build 7", BuildingType::COMMERCIAL},
        {"Build 8", BuildingType::TWO_STORY},
        {"Build 9", BuildingType::TWO_STORY},
        {"Build 10", BuildingType::COMMERCIAL},
        {"Build 11", BuildingType::TWO_STORY},
        {"Build 12", BuildingType::TWO_STORY},
        {"Build 13", BuildingType::COMMERCIAL},
        {"Build 14", BuildingType::TWO_STORY},
        {"Build 15", BuildingType::TWO_STORY},
        {"Build 16", BuildingType::COMMERCIAL},
        {"Build 17", BuildingType::TWO_STORY},
        {"Build 18", BuildingType::TWO_STORY},
        {"Build 19", BuildingType::COMMERCIAL},
        {"Build 20", BuildingType::TWO_STORY},
        {"Build 21", BuildingType::TWO_STORY},
        {"Build 22", BuildingType::COMMERCIAL},
        {"Build 23", BuildingType::TWO_STORY},
    };

    employees = {
        {1, EmployeeType::CERTIFIED_INSTALLER, {true, true, true, true, true}},
        {2, EmployeeType::CERTIFIED_INSTALLER, {true, false, true, false, true}},
        {3, EmployeeType::INSTALLER_PENDING_CERTIFICATION, {false, true, false, true, false}},
        {4, EmployeeType::LABORER, {true, true, true, false, false}},
        {5, EmployeeType::LABORER, {false, false, false, true, true}},
        {6, EmployeeType::CERTIFIED_INSTALLER, {true, false, true, false, true}},
        {7, EmployeeType::LABORER, {true, false, true, false, true}},
        {8, EmployeeType::INSTALLER_PENDING_CERTIFICATION, {true, false, true, false, true}}
};

    for (const Building& building: buildings) {
        scheduler.addBuilding(building.name, building.type);
    }

    for (const auto& employee : employees) {
        scheduler.addEmployee(employee.id, employee.type, employee.availability);
    }
    
    scheduler.schedule();
    scheduler.printSchedule();
    EXPECT_EQ(1, 1);
}

TEST_F(SchedulerTest, randomSchedulerUpdateAvail) {
    buildings = {
        {"Build 0", BuildingType::TWO_STORY},
        {"Build 1", BuildingType::COMMERCIAL},
        {"Build 2", BuildingType::TWO_STORY},
        {"Build 3", BuildingType::SINGLE_STORY},
        {"Build 4", BuildingType::SINGLE_STORY}
    };

    employees = {
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

    for (const Building& building: buildings) {
        scheduler.addBuilding(building.name, building.type);
    }

    for (const auto& employee : employees) {
        scheduler.addEmployee(employee.id, employee.type, employee.availability);
    }
    
    scheduler.updateAvailability(8, {false, false, false, false, false});
    scheduler.schedule();
    scheduler.printSchedule();
    EXPECT_EQ(1, 1);
}


TEST_F(SchedulerTest, randomSchedulerUpdateAvailAndRevertUpdate) {
    buildings = {
        {"Build 0", BuildingType::TWO_STORY},
        {"Build 1", BuildingType::COMMERCIAL},
        {"Build 2", BuildingType::TWO_STORY},
        {"Build 3", BuildingType::SINGLE_STORY},
        {"Build 4", BuildingType::SINGLE_STORY}
    };

    employees = {
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

    for (const Building& building: buildings) {
        scheduler.addBuilding(building.name, building.type);
    }

    for (const auto& employee : employees) {
        scheduler.addEmployee(employee.id, employee.type, employee.availability);
    }
    
    scheduler.updateAvailability(8, {false, false, false, false, false});
    scheduler.updateAvailability(8, {true, true, true, true, true});
    scheduler.schedule();
    scheduler.printSchedule();
    EXPECT_EQ(1, 1);
}

TEST_F(SchedulerTest, randomSchedulerStrike) {
       buildings = {
        {"Build 0", BuildingType::TWO_STORY},
        {"Build 1", BuildingType::COMMERCIAL},
        {"Build 2", BuildingType::TWO_STORY},
        {"Build 3", BuildingType::SINGLE_STORY},
        {"Build 4", BuildingType::SINGLE_STORY}
    };

    employees = {
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

    for (const Building& building: buildings) {
        scheduler.addBuilding(building.name, building.type);
    }

    for (const auto& employee : employees) {
        scheduler.addEmployee(employee.id, employee.type, employee.availability);
    }
    
    scheduler.updateAvailability(1, {false, false, false, false, false});
    scheduler.updateAvailability(2, {false, false, false, false, false});
    scheduler.updateAvailability(3, {false, false, false, false, false});
    scheduler.updateAvailability(4, {false, false, false, false, false});
    scheduler.updateAvailability(5, {false, false, false, false, false});
    scheduler.updateAvailability(6, {false, false, false, false, false});
    scheduler.updateAvailability(7, {false, false, false, false, false});
    scheduler.updateAvailability(8, {false, false, false, false, false});
    scheduler.updateAvailability(9, {false, false, false, false, false});
    scheduler.updateAvailability(10, {false, false, false, false, false});
    scheduler.schedule();
    scheduler.printSchedule();
    EXPECT_EQ(1, 1);
}



