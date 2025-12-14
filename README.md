# Employee Scheduler

[![CI](https://img.shields.io/github/actions/workflow/status/navidpadid/cpp_bazel/ci.yml?branch=main&style=for-the-badge&logo=github&logoColor=white&label=Build)](https://github.com/navidpadid/cpp_bazel/actions/workflows/ci.yml)
[![Last Commit](https://img.shields.io/github/last-commit/navidpadid/cpp_bazel?style=for-the-badge&logo=git&logoColor=white)](https://github.com/navidpadid/cpp_bazel/commits/main)
[![Commit Activity](https://img.shields.io/github/commit-activity/m/navidpadid/cpp_bazel?style=for-the-badge&logo=github)](https://github.com/navidpadid/cpp_bazel/graphs/commit-activity)

> A C++23 application for dynamically scheduling employees across multiple buildings for the work week.

## 📋 Overview

This project implements an intelligent employee scheduling system that assigns workers to buildings based on various constraints and requirements. Built with modern C++23 and Bazel, it demonstrates object-oriented design, testing best practices, and CI/CD integration.

## ✨ Features

- **Dynamic Scheduling**: Automatically assigns employees to buildings across a 5-day work week
- **Multiple Building Types**: Support for single-story, two-story, and commercial buildings
- **Flexible Employee Management**: Handle varying employee counts and availability
- **Comprehensive Testing**: Full test coverage with Google Test framework
- **Modern C++23**: Leverages latest C++ features including `constexpr`, `inline` variables, and enum classes

## 🏗️ Project Structure

```
src/
├── building.h/cpp       # Building class and types
├── employee.h/cpp       # Employee management
├── scheduler.h/cpp      # Core scheduling logic
├── days.h              # Day-of-week utilities and constants
├── main.cpp            # Application entry point
└── scheduler_test.cpp  # Comprehensive unit tests
```

## 🚀 Prerequisites

- **Linux** (Ubuntu-based recommended, works on any OS supporting dev containers)
- **Docker** installed and running
- **Internet connection** for initial setup

## 🛠️ Building and Running

### Setup

1. Open the project in a dev container (VS Code will prompt automatically)
2. Wait for the container to build and initialize

### Build the Project

```bash
bazel build //...
```

### Run Tests

```bash
bazel test //...
```

### Run the Application

```bash
bazel run //src:scheduler_main
```

## 📊 Code Coverage

Generate a detailed code coverage report:

```bash
# Run coverage analysis
bazel coverage --combined_report=lcov //...

# Generate HTML report
genhtml bazel-out/_coverage/_coverage_report.dat --output-directory coverage_html
```

Open `coverage_html/index.html` in your browser to view the interactive coverage report.

## 🧪 Sample Test Output

```bash
[       OK ] SchedulerTest.lessThanWorkDayBuildings (0 ms)
[ RUN      ] SchedulerTest.buildingsMoreThanCanHandle
************ SCHEDULE ***************
Monday: Building -> Build 0: | Employees -> [6] [7] 
Monday: Building -> Build 2: | Employees -> [2] [4] 
Monday: Building -> Build 3: | Employees -> [1] [8] 
Tuesday: Building -> Build 5: | Employees -> [1] [4] 
Wednesday: Building -> Build 6: | Employees -> [6] [7] 
Wednesday: Building -> Build 8: | Employees -> [2] [4] 
Wednesday: Building -> Build 9: | Employees -> [1] [8] 
Thursday: Building -> Build 11: | Employees -> [1] [5] 
Friday: Building -> Build 12: | Employees -> [6] [7] 
Friday: Building -> Build 14: | Employees -> [2] [5] 
Friday: Building -> Build 15: | Employees -> [1] [8] 
*************************************
[       OK ] SchedulerTest.buildingsMoreThanCanHandle (0 ms)
[ RUN      ] SchedulerTest.randomSchedulerUpdateAvail
************ SCHEDULE ***************
Monday: Building -> Build 0: | Employees -> [2] [7] 
Monday: Building -> Build 2: | Employees -> [1] [5] 
Tuesday: Building -> Build 3: | Employees -> [6] 
Tuesday: Building -> Build 4: | Employees -> [2] 
*************************************
```