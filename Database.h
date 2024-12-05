#ifndef DATABASE_H
#define DATABASE_H

#include "Meal.h"
#include <sqlite3.h>
#include <vector>
#include <string>

class Database {
private:
    sqlite3* db;

public:
    Database(const std::string& dbName);
    ~Database();
    bool insertMeal(const Meal& meal);
    std::vector<Meal> getMeals();
};

#endif // DATABASE_H
