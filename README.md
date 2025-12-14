# Schedule dynamic employees for some buildings for the upcoming week



## Running the code and the output
Pre-requisite and tested machine:
- Linux (ubuntu based, should be fine on any OS supporting devcontainers)
- Docker installed
- Internet connection


## To run the code:
First open in devcontainer, then run:
```bash
bazel build //...
bazel test //... 
```

## To generate code coverage report:
Run the coverage command and generate HTML report:
```bash
bazel coverage --combined_report=lcov //...
genhtml bazel-out/_coverage/_coverage_report.dat --output-directory coverage_html
```

Then open `coverage_html/index.html` in a browser to view the detailed coverage report.

## Sample test output

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