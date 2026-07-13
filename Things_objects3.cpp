#include <iostream>
#include <vector>
#include <cstdint>
#include <limits>

// Define our index type and our absolute 'Null' sentinel
using Idx = uint32_t;
constexpr Idx INVALID_INDEX = std::numeric_limits<Idx>::max();

// A real-world example: A structural grid or physics node pool
struct TransformNode {
    float x, y, z;
    Idx parentNode; // Can be 0 (the root node!), or INVALID_INDEX if it has no parent
};

class NodePool {
private:
    std::vector<TransformNode> m_nodes;
    std::vector<Idx> m_freeSlots; // Tracks recycled indices for reuse

public:
    // Create an item and return its index (which can absolutely be 0)
    Idx CreateNode(float x, float y, float z, Idx parent = INVALID_INDEX) {
        if (!m_freeSlots.empty()) {
            Idx recycledIdx = m_freeSlots.back();
            m_freeSlots.pop_back();
            m_nodes[recycledIdx] = {x, y, z, parent};
            return recycledIdx;
        }

        m_nodes.push_back({x, y, z, parent});
        return static_cast<Idx>(m_nodes.size() - 1);
    }

    void DestroyNode(Idx index) {
        if (index >= m_nodes.size()) return;
        
        // Mark this slot as a tombstone
        m_nodes[index].parentNode = INVALID_INDEX; 
        m_freeSlots.push_back(index);
    }

    TransformNode* Get(Idx index) {
        if (index >= m_nodes.size()) return nullptr;
        return &m_nodes[index];
    }
    
    size_t TotalCapacity() const { return m_nodes.size(); }
};
