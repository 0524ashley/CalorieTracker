#include "Database.h"
#include "Meal.h"
#include <sqlite3.h>
#include <iostream>

Database::Database(const std::string& dbFile) {
    if (sqlite3_open(dbFile.c_str(), &db)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    }
}

Database::~Database() {
    sqlite3_close(db);
}

bool Database::insertMeal(const Meal& meal) {
    const char* sql = "INSERT INTO MEALS (NAME, CALORIES, CATEGORY, DATE) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return false;  // Return false if there is an error
    }

    sqlite3_bind_text(stmt, 1, meal.name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, meal.calories);
    sqlite3_bind_text(stmt, 3, meal.category.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, meal.date.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "SQL execution error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;  // Return false if the SQL step fails
    }

    sqlite3_finalize(stmt);
    return true;  // Return true if the insert is successful
}

std::vector<Meal> Database::getMeals() {
    std::vector<Meal> meals;
    const char* sql = "SELECT NAME, CALORIES, CATEGORY, DATE FROM MEALS;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return meals;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        int calories = sqlite3_column_int(stmt, 1);
        std::string category = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        std::string date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

        meals.push_back(Meal(name, calories, category, date));
    }

    sqlite3_finalize(stmt);
    return meals;
}
