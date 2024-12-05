#include "CalorieTracker.h"

void CalorieTracker::addMeal(const Meal& meal) {
    meals.push_back(meal);
}

int CalorieTracker::getTotalCalories(const std::string& date) {
    int total = 0;
    for (const auto& meal : meals) {
        if (meal.date == date) {
            total += meal.calories;
        }
    }
    return total;
}

std::vector<int> CalorieTracker::getWeeklySummary() {
    std::vector<int> summary(7, 0);
    // Mock implementation for simplicity
    for (size_t i = 0; i < meals.size() && i < 7; ++i) {
        summary[i] += meals[i].calories;
    }
    return summary;
}
