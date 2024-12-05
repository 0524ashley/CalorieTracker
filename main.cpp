#include "CalorieTracker.h"
#include "Database.h"
#include <iostream>

int main() {
    Database db("calories.db");

    // Adding example meals
    db.insertMeal(Meal("Eggs", 150, "Breakfast", "2024-12-05"));
    db.insertMeal(Meal("Burger", 500, "Lunch", "2024-12-05"));

    CalorieTracker tracker;

    auto meals = db.getMeals();
    for (const auto& meal : meals) {
        tracker.addMeal(meal);
    }

    std::cout << "Total Calories for Today: " << tracker.getTotalCalories("2024-12-05") << " kcal" << std::endl;

    auto summary = tracker.getWeeklySummary();
    for (size_t i = 0; i < summary.size(); ++i) {
        std::cout << "Day " << i + 1 << ": " << summary[i] << " kcal" << std::endl;
    }

    return 0;
}
