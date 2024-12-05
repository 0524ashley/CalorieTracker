#include "MealEntryWindow.h"
#include <gtk/gtk.h>
#include <iostream>
#include <vector>

std::vector<std::pair<std::string, int>> meals;

MealEntryWindow::MealEntryWindow() {
    gtk_init(nullptr, nullptr);  // Initialize GTK

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Calorie Tracker");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create input fields
    entry_name = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_name), "Enter meal name");

    entry_calories = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_calories), "Enter calories");

    entry_category = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_category), "Enter category (e.g., Breakfast)");

    entry_date = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_date), "Enter date (YYYY-MM-DD)");

    // Add the fields to the box
    gtk_box_pack_start(GTK_BOX(vbox), entry_name, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_calories, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_category, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry_date, FALSE, FALSE, 0);

    // Add the Add Meal button
    GtkWidget* button_add_meal = gtk_button_new_with_label("Add Meal");
    g_signal_connect(button_add_meal, "clicked", G_CALLBACK(on_add_meal_button_clicked), this);
    gtk_box_pack_start(GTK_BOX(vbox), button_add_meal, FALSE, FALSE, 0);

    // Add a listbox to display meals
    listbox_meals = gtk_list_box_new();
    gtk_box_pack_start(GTK_BOX(vbox), listbox_meals, TRUE, TRUE, 0);

    // Label to show total calories
    label_total_calories = gtk_label_new("Total Calories: 0 kcal");
    gtk_box_pack_start(GTK_BOX(vbox), label_total_calories, FALSE, FALSE, 0);

    // Connect signal to handle window close
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);
}

MealEntryWindow::~MealEntryWindow() {
    gtk_widget_destroy(window);
}

void MealEntryWindow::show() {
    gtk_widget_show_all(window);
    gtk_main();
}

void MealEntryWindow::on_add_meal_button_clicked(GtkButton* button, gpointer user_data) {
    MealEntryWindow* window = static_cast<MealEntryWindow*>(user_data);

    // Get the values from the entry fields
    const char* name = gtk_entry_get_text(GTK_ENTRY(window->entry_name));
    const char* calories_text = gtk_entry_get_text(GTK_ENTRY(window->entry_calories));
    const char* category = gtk_entry_get_text(GTK_ENTRY(window->entry_category));
    const char* date = gtk_entry_get_text(GTK_ENTRY(window->entry_date));

    // Convert calories to integer
    int calories = std::stoi(calories_text);

    // Add meal to listbox and vector
    window->add_meal_to_listbox(name, calories, category, date);
    meals.push_back({name, calories});

    // Update total calories
    window->update_total_calories();
}

void MealEntryWindow::add_meal_to_listbox(const std::string& name, int calories, const std::string& category, const std::string& date) {
    std::string meal_text = name + " (" + category + ") - " + std::to_string(calories) + " kcal on " + date;
    GtkWidget* row = gtk_label_new(meal_text.c_str());
    gtk_list_box_insert(GTK_LIST_BOX(listbox_meals), row, -1);
}

void MealEntryWindow::update_total_calories() {
    int total_calories = 0;
    for (const auto& meal : meals) {
        total_calories += meal.second;
    }
    std::string total_text = "Total Calories: " + std::to_string(total_calories) + " kcal";
    gtk_label_set_text(GTK_LABEL(label_total_calories), total_text.c_str());
}
