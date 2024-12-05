#include "MealEntryWindow.h"
#include <gtk/gtk.h>
#include <iostream>

// Constructor: Initializes the window and widgets
MealEntryWindow::MealEntryWindow() {
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Meal Entry");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    mealNameEntry = gtk_entry_new();
    caloriesEntry = gtk_entry_new();
    mealTypeComboBox = gtk_combo_box_text_new();

    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(mealTypeComboBox), "Breakfast");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(mealTypeComboBox), "Lunch");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(mealTypeComboBox), "Dinner");

    addButton = gtk_button_new_with_label("Add Meal");

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), mealNameEntry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), caloriesEntry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), mealTypeComboBox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), addButton, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Connect the "Add Meal" button click to the signal handler
    g_signal_connect(addButton, "clicked", G_CALLBACK(MealEntryWindow::on_add_button_clicked), this);

    // Quit the GTK application when the window is closed
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

// Signal handler for when the "Add Meal" button is clicked
void MealEntryWindow::on_add_button_clicked(GtkWidget *widget, gpointer data) {
    MealEntryWindow *window = static_cast<MealEntryWindow*>(data);
    
    const gchar *mealName = gtk_entry_get_text(GTK_ENTRY(window->mealNameEntry));
    const gchar *calories = gtk_entry_get_text(GTK_ENTRY(window->caloriesEntry));
    const gchar *mealType = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(window->mealTypeComboBox));

    std::cout << "Meal: " << mealName << ", Calories: " << calories << ", Type: " << mealType << std::endl;
}

// Show the window
void MealEntryWindow::show() {
    gtk_widget_show_all(window);
    gtk_main();  // Starts GTK main loop
}
