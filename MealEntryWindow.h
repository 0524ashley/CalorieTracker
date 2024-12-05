#ifndef MEAL_ENTRY_WINDOW_H
#define MEAL_ENTRY_WINDOW_H

#include <gtk/gtk.h>
#include <string>

class MealEntryWindow {
private:
    GtkWidget* window;
    GtkWidget* entry_name;
    GtkWidget* entry_calories;
    GtkWidget* entry_category;
    GtkWidget* entry_date;
    GtkWidget* listbox_meals;
    GtkWidget* label_total_calories;

public:
    MealEntryWindow();
    ~MealEntryWindow();

    void show();
    static void on_add_meal_button_clicked(GtkButton* button, gpointer user_data);
    void add_meal_to_listbox(const std::string& name, int calories, const std::string& category, const std::string& date);
    void update_total_calories();
};

#endif
