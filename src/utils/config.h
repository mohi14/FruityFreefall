#pragma once

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PLAYER_SPEED = 300.0f; // Pixels per second
const float FALLING_OBJECT_INITIAL_SPEED = 150.0f; // Pixels per second
const float FALLING_OBJECT_MAX_SPEED = 600.0f;
const float DIFFICULTY_INCREASE_RATE = 0.05f; // How much speed increases per second
const int FRUIT_POINTS = 10;
const int BOMB_PENALTY_POINTS = -5;
const int BOMB_PENALTY_TIME = -3; // Seconds
const int GAME_DURATION_SECONDS = 60;
const int OBJECT_POOL_SIZE = 20; // Max number of fruits/bombs active at once
const float SPAWN_INTERVAL = 1.0f; // Initial interval between spawns in seconds
const float MIN_SPAWN_INTERVAL = 0.2f; // Minimum spawn interval
const float SPAWN_INTERVAL_DECREASE_RATE = 0.02f; // How much spawn interval decreases per second