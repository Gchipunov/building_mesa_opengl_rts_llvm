#include <iostream>
#include <vector>
#include <bitset>

// 1. Define Entity as a simple ID
using Entity = uint32_t;
const uint32_t MAX_ENTITIES = 5000;

// 2. Define Components (Pure Data Structs)
struct Position {
    float x, y;
};

struct Velocity {
    float dx, dy;
};

// Component Masks to identify types
enum ComponentType {
    COMP_POSITION = 0,
    COMP_VELOCITY = 1,
    MAX_COMPONENTS = 32
};

using ComponentMask = std::bitset<MAX_COMPONENTS>;

// 3. The ECS Registry/Manager
struct MovementSystem {
    // Systems are pure logic loops
    void Update(std::vector<Position>& positions, 
                const std::vector<Velocity>& velocities, 
                const std::vector<ComponentMask>& entityMasks, 
                float dt) 
    {
        for (Entity e = 0; e < MAX_ENTITIES; ++e) {
            // Only update entities that have BOTH Position and Velocity
            if (entityMasks[e].test(COMP_POSITION) && entityMasks[e].test(COMP_VELOCITY)) {
                positions[e].x += velocities[e].dx * dt;
                positions[e].y += velocities[e].dy * dt;
            }
        }
    }
};
