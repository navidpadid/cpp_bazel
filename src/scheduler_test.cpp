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
    
    auto schedule = scheduler.getSchedule();
    // Verify exact schedule: Monday should have 2 buildings
    EXPECT_EQ(2, schedule[0].size());
    EXPECT_EQ("Build 0", schedule[0][0].first);
    EXPECT_EQ(std::vector<int>({2, 8}), schedule[0][0].second);
    EXPECT_EQ("Build 2", schedule[0][1].first);
    EXPECT_EQ(std::vector<int>({1, 7}), schedule[0][1].second);
    
    // Tuesday should have 2 buildings
    EXPECT_EQ(2, schedule[1].size());
    EXPECT_EQ("Build 1", schedule[1][0].first);
    EXPECT_EQ(std::vector<int>({6, 2, 10, 3, 8, 7, 5, 4}), schedule[1][0].second);
    EXPECT_EQ("Build 3", schedule[1][1].first);
    EXPECT_EQ(std::vector<int>({1}), schedule[1][1].second);
    
    // Wednesday should have 1 building
    EXPECT_EQ(1, schedule[2].size());
    EXPECT_EQ("Build 4", schedule[2][0].first);
    EXPECT_EQ(std::vector<int>({6}), schedule[2][0].second);
    
    // Thursday and Friday should be empty
    EXPECT_EQ(0, schedule[3].size());
    EXPECT_EQ(0, schedule[4].size());
    
    // Total: 5 buildings scheduled
    int totalScheduledBuildings = 0;
    for (int day = 0; day < 5; day++) {
        totalScheduledBuildings += schedule[day].size();
    }
    EXPECT_EQ(5, totalScheduledBuildings);
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
    
    auto schedule = scheduler.getSchedule();
    // Verify schedule is empty (no buildings, no employees)
    int totalScheduledBuildings = 0;
    for (int day = 0; day < 5; day++) {
        totalScheduledBuildings += schedule[day].size();
    }
    EXPECT_EQ(0, totalScheduledBuildings);
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
    
    auto schedule = scheduler.getSchedule();
    // Verify no buildings were scheduled (no employees available)
    int totalScheduledBuildings = 0;
    for (int day = 0; day < 5; day++) {
        totalScheduledBuildings += schedule[day].size();
    }
    EXPECT_EQ(0, totalScheduledBuildings);
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
    
    auto schedule = scheduler.getSchedule();
    // Verify schedule is empty (no buildings to schedule)
    int totalScheduledBuildings = 0;
    for (int day = 0; day < 5; day++) {
        totalScheduledBuildings += schedule[day].size();
    }
    EXPECT_EQ(0, totalScheduledBuildings);
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
    
    auto schedule = scheduler.getSchedule();
    // Verify exact schedule: Monday should have 3 buildings
    EXPECT_EQ(3, schedule[0].size());
    EXPECT_EQ("Build 0", schedule[0][0].first);
    EXPECT_EQ(std::vector<int>({6, 10}), schedule[0][0].second);
    EXPECT_EQ("Build 2", schedule[0][1].first);
    EXPECT_EQ(std::vector<int>({2, 7}), schedule[0][1].second);
    EXPECT_EQ("Build 3", schedule[0][2].first);
    EXPECT_EQ(std::vector<int>({1}), schedule[0][2].second);
    
    // Tuesday should have 2 buildings
    EXPECT_EQ(2, schedule[1].size());
    EXPECT_EQ("Build 1", schedule[1][0].first);
    EXPECT_EQ(std::vector<int>({6, 2, 9, 8, 10, 7, 5, 4}), schedule[1][0].second);
    EXPECT_EQ("Build 4", schedule[1][1].first);
    EXPECT_EQ(std::vector<int>({1}), schedule[1][1].second);
    
    // Wednesday, Thursday, Friday should be empty
    EXPECT_EQ(0, schedule[2].size());
    EXPECT_EQ(0, schedule[3].size());
    EXPECT_EQ(0, schedule[4].size());
    
    // Total: 5 buildings scheduled
    int totalScheduledBuildings = 0;
    for (int day = 0; day < 5; day++) {
        totalScheduledBuildings += schedule[day].size();
    }
    EXPECT_EQ(5, totalScheduledBuildings);
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
    
    auto schedule = scheduler.getSchedule();
    // With only certified installers, only single-story buildings can be scheduled
    // Monday should have 2 single-story buildings
    EXPECT_EQ(2, schedule[0].size());
    EXPECT_EQ("Build 3", schedule[0][0].first);
    EXPECT_EQ(std::vector<int>({10}), schedule[0][0].second);
    EXPECT_EQ("Build 4", schedule[0][1].first);
    EXPECT_EQ(std::vector<int>({9}), schedule[0][1].second);
    
    // Other days should be empty (no other building types can be built with only certified installers)
    EXPECT_EQ(0, schedule[1].size());
    EXPECT_EQ(0, schedule[2].size());
    EXPECT_EQ(0, schedule[3].size());
    EXPECT_EQ(0, schedule[4].size());
    
    // Total: 2 buildings scheduled
    int totalScheduledBuildings = 0;
    for (int day = 0; day < 5; day++) {
        totalScheduledBuildings += schedule[day].size();
    }
    EXPECT_EQ(2, totalScheduledBuildings);
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
    
    auto schedule = scheduler.getSchedule();
    // With limited employee availability, 2 two-story buildings scheduled on Monday
    EXPECT_EQ(2, schedule[0].size());
    EXPECT_EQ("Build 0", schedule[0][0].first);
    EXPECT_EQ(std::vector<int>({6, 7}), schedule[0][0].second);
    EXPECT_EQ("Build 2", schedule[0][1].first);
    EXPECT_EQ(std::vector<int>({2, 4}), schedule[0][1].second);
    
    // Other days should be empty (commercial building can't be scheduled with limited resources)
    EXPECT_EQ(0, schedule[1].size());
    EXPECT_EQ(0, schedule[2].size());
    EXPECT_EQ(0, schedule[3].size());
    EXPECT_EQ(0, schedule[4].size());
    
    // Total: 2 buildings scheduled
    int totalScheduledBuildings = 0;
    for (int day = 0; day < 5; day++) {
        totalScheduledBuildings += schedule[day].size();
    }
    EXPECT_EQ(2, totalScheduledBuildings);
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
    
    auto schedule = scheduler.getSchedule();
    // Verify specific schedule with limited employees
    // Monday: 3 buildings
    EXPECT_EQ(3, schedule[0].size());
    EXPECT_EQ("Build 0", schedule[0][0].first);
    EXPECT_EQ("Build 2", schedule[0][1].first);
    EXPECT_EQ("Build 3", schedule[0][2].first);
    
    // Tuesday: 1 building
    EXPECT_EQ(1, schedule[1].size());
    EXPECT_EQ("Build 5", schedule[1][0].first);
    
    // Wednesday: 3 buildings
    EXPECT_EQ(3, schedule[2].size());
    EXPECT_EQ("Build 6", schedule[2][0].first);
    EXPECT_EQ("Build 8", schedule[2][1].first);
    EXPECT_EQ("Build 9", schedule[2][2].first);
    
    // Thursday: 1 building
    EXPECT_EQ(1, schedule[3].size());
    EXPECT_EQ("Build 11", schedule[3][0].first);
    
    // Friday: 3 buildings
    EXPECT_EQ(3, schedule[4].size());
    EXPECT_EQ("Build 12", schedule[4][0].first);
    EXPECT_EQ("Build 14", schedule[4][1].first);
    EXPECT_EQ("Build 15", schedule[4][2].first);
    
    // Total: 11 buildings scheduled out of 24
    int totalScheduledBuildings = 0;
    for (int day = 0; day < 5; day++) {
        totalScheduledBuildings += schedule[day].size();
    }
    EXPECT_EQ(11, totalScheduledBuildings);
    EXPECT_LT(totalScheduledBuildings, 24);
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
    
    auto schedule = scheduler.getSchedule();
    // Monday: 2 buildings
    EXPECT_EQ(2, schedule[0].size());
    EXPECT_EQ("Build 0", schedule[0][0].first);
    EXPECT_EQ(std::vector<int>({2, 7}), schedule[0][0].second);
    EXPECT_EQ("Build 2", schedule[0][1].first);
    EXPECT_EQ(std::vector<int>({1, 5}), schedule[0][1].second);
    
    // Tuesday: 2 buildings
    EXPECT_EQ(2, schedule[1].size());
    EXPECT_EQ("Build 3", schedule[1][0].first);
    EXPECT_EQ(std::vector<int>({6}), schedule[1][0].second);
    EXPECT_EQ("Build 4", schedule[1][1].first);
    EXPECT_EQ(std::vector<int>({2}), schedule[1][1].second);
    
    // Other days should be empty
    EXPECT_EQ(0, schedule[2].size());
    EXPECT_EQ(0, schedule[3].size());
    EXPECT_EQ(0, schedule[4].size());
    
    // Verify employee 8 is not in any schedule
    for (int day = 0; day < 5; day++) {
        for (const auto& [building, employees] : schedule[day]) {
            EXPECT_EQ(std::find(employees.begin(), employees.end(), 8), employees.end());
        }
    }
    
    // Total: 4 buildings scheduled
    int totalScheduledBuildings = 0;
    for (int day = 0; day < 5; day++) {
        totalScheduledBuildings += schedule[day].size();
    }
    EXPECT_EQ(4, totalScheduledBuildings);
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
    
    auto schedule = scheduler.getSchedule();
    // Same as randomSchedule since employee 8 was reverted
    // Monday: 2 buildings
    EXPECT_EQ(2, schedule[0].size());
    EXPECT_EQ("Build 0", schedule[0][0].first);
    EXPECT_EQ(std::vector<int>({2, 8}), schedule[0][0].second);
    EXPECT_EQ("Build 2", schedule[0][1].first);
    EXPECT_EQ(std::vector<int>({1, 7}), schedule[0][1].second);
    
    // Tuesday: 2 buildings
    EXPECT_EQ(2, schedule[1].size());
    EXPECT_EQ("Build 1", schedule[1][0].first);
    EXPECT_EQ(std::vector<int>({6, 2, 10, 3, 8, 7, 5, 4}), schedule[1][0].second);
    EXPECT_EQ("Build 3", schedule[1][1].first);
    EXPECT_EQ(std::vector<int>({1}), schedule[1][1].second);
    
    // Wednesday: 1 building
    EXPECT_EQ(1, schedule[2].size());
    EXPECT_EQ("Build 4", schedule[2][0].first);
    EXPECT_EQ(std::vector<int>({6}), schedule[2][0].second);
    
    // Thursday and Friday should be empty
    EXPECT_EQ(0, schedule[3].size());
    EXPECT_EQ(0, schedule[4].size());
    
    // Total: 5 buildings scheduled
    int totalScheduledBuildings = 0;
    for (int day = 0; day < 5; day++) {
        totalScheduledBuildings += schedule[day].size();
    }
    EXPECT_EQ(5, totalScheduledBuildings);
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
    
    auto schedule = scheduler.getSchedule();
    // With all employees unavailable, no buildings should be scheduled
    int totalScheduledBuildings = 0;
    for (int day = 0; day < 5; day++) {
        totalScheduledBuildings += schedule[day].size();
    }
    EXPECT_EQ(0, totalScheduledBuildings);
}



