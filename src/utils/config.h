#pragma once

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PLAYER_SPEED 300.0f // Pixels per second
#define FALLING_OBJECT_INITIAL_SPEED 150.0f // Pixels per second
#define FALLING_OBJECT_MAX_SPEED 600.0f
#define DIFFICULTY_INCREASE_RATE 0.05f // How much speed increases per second
#define FRUIT_POINTS 10
#define BOMB_PENALTY_POINTS -5
#define BOMB_PENALTY_TIME -3 // Seconds
#define GAME_DURATION_SECONDS 60
#define BJECT_POOL_SIZE 20 // Max number of fruits/bombs active at once
#define SPAWN_INTERVAL 1.0f // Initial interval between spawns in seconds
#define MIN_SPAWN_INTERVAL 0.2f // Minimum spawn interval
#define SPAWN_INTERVAL_DECREASE_RATE 0.02f // How much spawn interval decreases per second