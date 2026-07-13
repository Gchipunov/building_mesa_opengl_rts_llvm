// part 1 

#include <iostream>
#include <vector>
#include <optional>
#include <cstdint>

// A 32-bit Entity ID split into 20 bits for Index, 12 bits for Generation
struct Entity {
    uint32_t id;

    uint32_t index() const { return id & 0xFFFFF; }
    uint32_t generation() const { return (id >> 20) & 0xFFF; }
};

// part 2

template<typename T, size_t MaxEntities = 10000>
class ComponentPool {
private:
    // The dense array stores actual components contiguously for system iteration
    std::vector<T> m_denseComponents;
    std::vector<Entity> m_denseToEntity; // Maps dense index back to Entity

    // The intrusive lookup array: Entity Index -> Index in the dense array
    // We use an invalid marker (like -1) to signify "no component"
    std::vector<int32_t> m_entityToDense;

public:
    ComponentPool() {
        m_entityToDense.resize(MaxEntities, -1);
    }

    // Assign a component to an entity
    template<typename... Args>
    T& Assign(Entity entity, Args&&... args) {
        uint32_t idx = entity.index();
        
        // If it already exists, overwrite it
        if (Has(entity)) {
            size_t denseIdx = m_entityToDense[idx];
            m_denseComponents[denseIdx] = T(std::forward<Args>(args)...);
            return m_denseComponents[denseIdx];
        }

        // Otherwise, push back to the dense layout
        m_entityToDense[idx] = static_cast<int32_t>(m_denseComponents.size());
        m_denseToEntity.push_back(entity);
        m_denseComponents.emplace_back(std::forward<Args>(args)...);

        return m_denseComponents.back();
    }

    // O(1) Check
    bool Has(Entity entity) const {
        uint32_t idx = entity.index();
        return idx < m_entityToDense.size() && m_entityToDense[idx] != -1;
    }

    // O(1) Lookup
    T* Get(Entity entity) {
        if (!Has(entity)) return nullptr;
        return &m_denseComponents[m_entityToDense[entity.index()]];
    }

    // Remove component while maintaining a packed dense array (Swap-and-Pop)
    void Remove(Entity entity) {
        if (!Has(entity)) return;

        uint32_t entIdx = entity.index();
        size_t indexToRemove = m_entityToDense[entIdx];
        size_t lastIndex = m_denseComponents.size() - 1;

        // Swap the elements in the dense vectors
        if (indexToRemove != lastIndex) {
            m_denseComponents[indexToRemove] = std::move(m_denseComponents[lastIndex]);
            
            Entity lastEntity = m_denseToEntity[lastIndex];
            m_denseToEntity[indexToRemove] = lastEntity;
            m_entityToDense[lastEntity.index()] = static_cast<int32_t>(indexToRemove);
        }

        // Shrink the dense arrays
        m_denseComponents.pop_back();
        m_denseToEntity.pop_back();
        m_entityToDense[entIdx] = -1;
    }

    // Exposed for System Iteration (Pure Cache Locality)
    T* data() { return m_denseComponents.data(); }
    size_t size() const { return m_denseComponents.size(); }
};

