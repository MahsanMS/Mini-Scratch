// Variables.h
#ifndef VARIABLES_H
#define VARIABLES_H

#include <iostream>
#include <string>
#include <map>

// ===================================
// Variable Management Functions

// Create new variable
void make_variable(Sprite* sprite, const std::string& name, float initval = 0) {
    // Check if sprite exists
    if (!sprite) {
        std::cout << "Error: Sprite not found!\n";
        return;
    }

    // Check if variable already exists
    if (sprite->var.find(name) != sprite->var.end()) {
        std::cout << "Error: Variable '" << name << "' already exists!\n";
        return;
    }

    // Add new variable
    sprite->var[name] = initval;
    std::cout << "Variable '" << name << "' created with value " << initval << "\n";
}

// Get variable value
float get_value(Sprite* sprite, const std::string& name) {
    // Check if sprite exists
    if (!sprite) {
        std::cout << "Error: Sprite not found!\n";
        return 0;
    }

    // Check if variable exists
    if (sprite->var.find(name) == sprite->var.end()) {
        std::cout << "Error: Variable '" << name << "' not found!\n";
        return 0;
    }

    // Return value
    return sprite->var[name];
}

// Set variable value
void set_value(Sprite* sprite, const std::string& name, float value) {
    // Check if sprite exists
    if (!sprite) {
        std::cout << "Error: Sprite not found!\n";
        return;
    }

    // Check if variable exists
    if (sprite->var.find(name) == sprite->var.end()) {
        std::cout << "Error: Variable '" << name << "' not found! Use make_variable first.\n";
        return;
    }

    // Set new value
    sprite->var[name] = value;
    std::cout << "Variable '" << name << "' set to " << value << "\n";
}

// Change variable value
void change_value(Sprite* sprite, const std::string& name, float delta) {
    // Check if sprite exists
    if (!sprite) {
        std::cout << "Error: Sprite not found!\n";
        return;
    }

    // Check if variable exists
    if (sprite->var.find(name) == sprite->var.end()) {
        std::cout << "Error: Variable '" << name << "' not found!\n";
        return;
    }

    // Add delta to current value
    sprite->var[name] += delta;
    std::cout << "Variable '" << name << "' changed by " << delta
              << ", new value: " << sprite->var[name] << "\n";
}

// Show all variables
void show_variables(Sprite* sprite) {
    // Check if sprite exists
    if (!sprite) {
        std::cout << "Error: Sprite not found!\n";
        return;
    }

    // Check if any variables exist
    if (sprite->var.empty()) {
        std::cout << "No variables for '" << sprite->name << "'\n";
        return;
    }

    // Show sprite name
    std::cout << "\nVariables for '" << sprite->name << "':\n";

    // Loop through all variables
    for (const auto& pair : sprite->var) {
        std::cout << pair.first << " = " << pair.second << "\n";
    }
}

// Hide variables
void hide_variables(Sprite* sprite) {
    // Check if sprite exists
    if (!sprite) {
        std::cout << "Error: Sprite not found!\n";
        return;
    }

    // Later with SDL we will actually hide variables from screen
    std::cout << "Hide variables for '" << sprite->name << "' (SDL version later)\n";
}

#endif