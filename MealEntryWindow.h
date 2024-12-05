#ifndef MEAL_ENTRY_WINDOW_H
#define MEAL_ENTRY_WINDOW_H

#include <gtk/gtk.h>

class MealEntryWindow {
private:
    GtkWidget *window;
    GtkWidget *mealNameEntry;
    GtkWidget *caloriesEntry;
    GtkWidget *mealTypeComboBox;
    GtkWidget *addButton;

public:
    MealEntryWindow();
    void show();

    static void on_add_button_clicked(GtkWidget *widget, gpointer data);
};

#endif

