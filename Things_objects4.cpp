#include <iostream>
#include <vector>
#include <cstdint>

using Idx = uint32_t;
constexpr Idx INVALID_INDEX = 0; // 0 means empty/null!

struct Component {
    float value;
    Idx nextThing; // Initialized to 0 (meaning none)
};

class IntrusivePool {
private:
    std::vector<Component> m_pool;
    std::vector<Idx> m_freeSlots;

public:
    IntrusivePool() {
        // Reserve index 0 as a permanent 'Null Object' boundary
        m_pool.push_back({0.0f, INVALID_INDEX}); 
    }

    Idx Allocate(float value) {
        // Reuse an index if available
        if (!m_freeSlots.empty()) {
            Idx recycledIdx = m_freeSlots.back();
            m_freeSlots.pop_back();
            m_pool[recycledIdx] = {value, INVALID_INDEX};
            return recycledIdx;
        }

        // Otherwise, push to back. Real IDs will be 1, 2, 3...
        m_pool.push_back({value, INVALID_INDEX});
        return static_cast<Idx>(m_pool.size() - 1);
    }

    void Free(Idx index) {
        // Guard against freeing index 0 or out of bounds
        if (index == INVALID_INDEX || index >= m_pool.size()) return;

        // Clear the data and push back to free list
        m_pool[index] = {0.0f, INVALID_INDEX};
        m_freeSlots.push_back(index);
    }

    // Completely safe lookup: returns the harmless null-object at index 0 
    // if given an invalid index, preventing crashes.
    Component& Get(Idx index) {
        if (index >= m_pool.size()) return m_pool[INVALID_INDEX];
        return m_pool[index];
    }
};

// test
IntrusivePool pool;
Idx brokenId = 0; // Left uninitialized, so it defaults to 0

// This will NOT crash the engine! It safely returns a reference to 
// the dead data at index 0, keeping your program alive.
pool.Get(brokenId).value = 42.0f;


