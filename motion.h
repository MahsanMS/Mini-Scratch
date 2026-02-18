#ifndef MINI_SCRATCH_MOTION_H
#define MINI_SCRATCH_MOTION_H

#include "UI.h"

// Motion Commands

// Functions:

// Linear movement
void move(Sprite* sprite, float steps) {
    if (!sprite) {
        std::cout << "Error: Sprite not found!\n";
        return;
    }
    if (!sprite->state.visible) {
        std::cout << "Sprite is invisible!\n";
        return;
    }

    // Convert degrees to radians
    float radian = sprite->state.direction * 3.14159265f / 180.0f;
    float dx = steps * std::cos(radian); // Horizontal movement
    float dy = steps * std::sin(radian); // Vertical movement

    // New position
    sprite->state.x += dx;
    sprite->state.y += dy;

    std::cout << "Move " << steps << " steps\n";
    std::cout << "New position: (" << sprite->state.x << ", " << sprite->state.y << ")\n";
}

// Clockwise rotation
void right_turn(Sprite* sprite, float degrees) {
    if (!sprite) {
        std::cout << "Error: Sprite not found!\n";
        return;
    }

    sprite->state.direction -= degrees; // Decrease angle for right turn

    // Normalize angle to 0-360 range
    while (sprite->state.direction < 0) {
        sprite->state.direction += 360;
    }
    while (sprite->state.direction >= 360) {
        sprite->state.direction -= 360;
    }

    std::cout << "Turned right by " << degrees << " degrees\n";
    std::cout << "Current direction: " << sprite->state.direction << " degrees\n";
}

// Counter-clockwise rotation
void left_turn(Sprite* sprite, float degrees) {
    if (!sprite) {
        std::cout << "Error: Sprite not found!\n";
        return;
    }

    sprite->state.direction += degrees; // Increase angle for left turn

    // Normalize angle to 0-360 range
    while (sprite->state.direction < 0) {
        sprite->state.direction += 360;
    }
    while (sprite->state.direction >= 360) {
        sprite->state.direction -= 360;
    }

    std::cout << "Turned left by " << degrees << " degrees\n";
    std::cout << "Current direction: " << sprite->state.direction << " degrees\n";
}

// Go to specific position
void go_to(Sprite* sprite, float targetX, float targetY) {
    if (!sprite) {
        std::cout << "Error: Sprite not found!\n";
        return;
    }

    if (!sprite->state.visible) {
        std::cout << "Sprite is hidden!\n";
        return;
    }

    // New position
    sprite->state.x = targetX;
    sprite->state.y = targetY;

    std::cout << "Moved to position (" << targetX << ", " << targetY << ")\n";
}

// Set specific direction
void set_direction(Sprite* sprite, float newdirection) {
    if (!sprite) {
        std::cout << "Error: Sprite not found!\n";
        return;
    }

    // New direction
    sprite->state.direction = newdirection;

    // Normalize angle to 0-360 range
    while (sprite->state.direction < 0) {
        sprite->state.direction += 360;
    }
    while (sprite->state.direction >= 360) {
        sprite->state.direction -= 360;
    }

    std::cout << "Direction set to " << newdirection << " degrees\n";
    std::cout << "Current direction: " << sprite->state.direction << " degrees\n";
}

// Relative X change
void change_x_by(Sprite* sprite, float deltaX) {
    if (!sprite) {
        std::cout << "Error: Sprite not found!\n";
        return;
    }

    if (!sprite->state.visible) {
        std::cout << "Sprite is hidden!\n";
        return;
    }

    // Change X coordinate
    sprite->state.x += deltaX;

    std::cout << "X changed by " << deltaX << "\n";
    std::cout << "New X position: " << sprite->state.x << "\n";
}

// Relative Y change
void change_y_by(Sprite* sprite, float deltaY) {
    if (!sprite) {
        std::cout << "Error: Sprite not found!\n";
        return;
    }

    if (!sprite->state.visible) {
        std::cout << "Sprite is hidden!\n";
        return;
    }

    // Change Y coordinate
    sprite->state.y += deltaY;

    std::cout << "Y changed by " << deltaY << "\n";
    std::cout << "New Y position: " << sprite->state.y << "\n";
}

// Go to random position
void go_to_random_position(Sprite* sprite) {
    if (!sprite || !sprite->state.visible) return;

    std::srand(std::time(nullptr));

    // Screen dimensions
    int screenWidth = (int)(sprite->state.maxX - sprite->state.minX);
    int screenHeight = (int)(sprite->state.maxY - sprite->state.minY);

    // Create random position
    sprite->state.x = sprite->state.minX + std::rand() % screenWidth;
    sprite->state.y = sprite->state.minY + std::rand() % screenHeight;

    std::cout << "Moved to random position\n";
}

// Stop on edge collision
void stop_on_edge(Sprite* sprite) {
    if (!sprite) return;

    // Determine edge coordinates
    float minX = sprite->state.minX;
    float maxX = sprite->state.maxX;
    float minY = sprite->state.minY;
    float maxY = sprite->state.maxY;

    // Stop at edges
    if (sprite->state.x < minX) sprite->state.x = minX;
    if (sprite->state.x > maxX) sprite->state.x = maxX;
    if (sprite->state.y < minY) sprite->state.y = minY;
    if (sprite->state.y > maxY) sprite->state.y = maxY;
}

#endif