#ifndef MEAL_H
#define MEAL_H

#include <string>

class Meal {
public:
    std::string name;
    int calories;
    std::string category; // e.g., "Breakfast", "Lunch"
    std::string date;     // e.g., "YYYY-MM-DD"

    Meal(const std::string& name, int calories, const std::string& category, const std::string& date);
};

#endif
