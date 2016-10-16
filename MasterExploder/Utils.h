#pragma once

#define TERRAIN_WIDTH 40
#define TERRAIN_HEIGHT 30

#define TILE_WIDTH 20
#define TILE_HEIGHT 20

#define MS_PER_UPDATE 50

#define MAX_MOVEMENT_SPEED (1000 / MS_PER_UPDATE)

#define CALCULATE_X(key) ((key) / TERRAIN_HEIGHT)
#define CALCULATE_Y(key) ((key) % TERRAIN_HEIGHT)
#define CALCULATE_KEY(x, y) ((x) * TERRAIN_HEIGHT + (y))