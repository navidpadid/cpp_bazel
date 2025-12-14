#pragma once
#include <unordered_map>
#include <string>

constexpr int WORK_DAYS=5;

enum class DayOfWeek {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY
}; //could use WORK_DAYS at the end of the DayOfWeek as well

inline const std::unordered_map<DayOfWeek, std::string> dayToStr  = {
    {DayOfWeek::MONDAY, "Monday"},
    {DayOfWeek::TUESDAY, "Tuesday"},
    {DayOfWeek::WEDNESDAY, "Wednesday"},
    {DayOfWeek::THURSDAY, "Thursday"},
    {DayOfWeek::FRIDAY, "Friday"}
};

inline DayOfWeek& operator++(DayOfWeek& day) {
    day = static_cast<DayOfWeek>(static_cast<int>(day) + 1);
    return day;
}
