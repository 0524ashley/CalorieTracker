#ifndef CALORIE_TRACKER_H
#define CALORIE_TRACKER_H

#include "Meal.h"
#include <vector>
#include <string>

class CalorieTracker {
private:
    std::vector<Meal> meals;

public:
    void addMeal(const Meal& meal);
    int getTotalCalories(const std::string& date);
    std::vector<int> getWeeklySummary();
};

#endif
