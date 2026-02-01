// Motion Commands
#ifndef MOTION_H
#define MOTION_H

#include <iostream>
#include <cmath>
#include <ctime>
#include <random>
#include <cstdlib>

// Character movement
struct motion_data {
    float x, y;                 // Character coordinates
    float minX, maxX, minY, maxY; // Screen edges
    float direction;            // Direction in degrees
    bool visible;               // Whether to display or not

    // Program defaults
    motion_data() {
        x = 0.0f;
        y = 0.0f;
        direction = 90.0f;      // Facing right
        visible = true;

        // Scratch screen dimensions
        minX = -240.0f;
        maxX = 240.0f;
        minY = -180.0f;
        maxY = 180.0f;
    }
};

// Functions:

// Linear movement
void move(motion_data* sprite, float steps) {
    if (!sprite) {
        std::cout << "Error: Sprite not found!\n";
        return;
    }
    if (!sprite->visible) {
        std::cout << "Sprite is invisible!\n";
        return;
    }

    // Convert degrees to radians
    float radian = sprite->direction * 3.14159265f / 180.0f;
    float dx = steps * std::cos(radian); // Horizontal movement
    float dy = steps * std::sin(radian); // Vertical movement

    // New position
    sprite->x += dx;
    sprite->y += dy;

    std::cout << "Move " << steps << " steps\n";
    std::cout << "New position: (" << sprite->x << ", " << sprite->y << ")\n";
}

// Clockwise rotation
void right_turn(motion_data* sprite, float degrees) {
    if (!sprite) {
        std::cout << "Error: Sprite not found!\n";
        return;
    }

    sprite->direction -= degrees; // Decrease angle for right turn

    // Normalize angle to 0-360 range
    while (sprite->direction < 0) {
        sprite->direction += 360;
    }
    while (sprite->direction >= 360) {
        sprite->direction -= 360;
    }

    std::cout << "Turned right by " << degrees << " degrees\n";
    std::cout << "Current direction: " << sprite->direction << " degrees\n";
}

// Counter-clockwise rotation
void left_turn(motion_data* sprite, float degrees) {
    if (!sprite) {
        std::cout << "Error: Sprite not found!\n";
        return;
    }

    sprite->direction += degrees; // Increase angle for left turn

    // Normalize angle to 0-360 range
    while (sprite->direction < 0) {
        sprite->direction += 360;
    }
    while (sprite->direction >= 360) {
        sprite->direction -= 360;
    }

    std::cout << "Turned left by " << degrees << " degrees\n";
    std::cout << "Current direction: " << sprite->direction << " degrees\n";
}

// Go to specific position
void go_to(motion_data* sprite, float targetX, float targetY) {
    if (!sprite) {
        std::cout << "Error: Sprite not found!\n";
        return;
    }

    if (!sprite->visible) {
        std::cout << "Sprite is hidden!\n";
        return;
    }

    // New position
    sprite->x = targetX;
    sprite->y = targetY;

    std::cout << "Moved to position (" << targetX << ", " << targetY << ")\n";
}

// Set specific direction
void set_direction(motion_data* sprite, float newdirection) {
    if (!sprite) {
        std::cout << "Error: Sprite not found!\n";
        return;
    }

    // New direction
    sprite->direction = newdirection;

    // Normalize angle to 0-360 range
    while (sprite->direction < 0) {
        sprite->direction += 360;
    }
    while (sprite->direction >= 360) {
        sprite->direction -= 360;
    }

    std::cout << "Direction set to " << newdirection << " degrees\n";
    std::cout << "Current direction: " << sprite->direction << " degrees\n";
}

// Relative X change
void change_x_by(motion_data* sprite, float deltaX) {
    if (!sprite) {
        std::cout << "Error: Sprite not found!\n";
        return;
    }

    if (!sprite->visible) {
        std::cout << "Sprite is hidden!\n";
        return;
    }

    // Change X coordinate
    sprite->x += deltaX;

    std::cout << "X changed by " << deltaX << "\n";
    std::cout << "New X position: " << sprite->x << "\n";
}

// Relative Y change
void change_y_by(motion_data* sprite, float deltaY) {
    if (!sprite) {
        std::cout << "Error: Sprite not found!\n";
        return;
    }

    if (!sprite->visible) {
        std::cout << "Sprite is hidden!\n";
        return;
    }

    // Change Y coordinate
    sprite->y += deltaY;

    std::cout << "Y changed by " << deltaY << "\n";
    std::cout << "New Y position: " << sprite->y << "\n";
}

// Go to random position
void go_to_random_position(motion_data* sprite) {
    if (!sprite || !sprite->visible) return;

    std::srand(std::time(nullptr));

    // Screen dimensions
    int screenWidth = (int)(sprite->maxX - sprite->minX);
    int screenHeight = (int)(sprite->maxY - sprite->minY);

    // Create random position
    sprite->x = sprite->minX + std::rand() % screenWidth;
    sprite->y = sprite->minY + std::rand() % screenHeight;

    std::cout << "Moved to random position\n";
}

// Stop on edge collision
void stop_on_edge(motion_data* sprite) {
    if (!sprite) return;

    // Determine edge coordinates
    float minX = sprite->minX;
    float maxX = sprite->maxX;
    float minY = sprite->minY;
    float maxY = sprite->maxY;

    // Stop at edges
    if (sprite->x < minX) sprite->x = minX;
    if (sprite->x > maxX) sprite->x = maxX;
    if (sprite->y < minY) sprite->y = minY;
    if (sprite->y > maxY) sprite->y = maxY;
}

#endif 