#ifndef SINGULARITY_RESOURCEID_HPP
#define SINGULARITY_RESOURCEID_HPP

#include <functional>

template<typename T>
class ResourceID {
public:
    unsigned long long id = 0;
    bool isValid() const { return id != 0; }
    bool operator==(const ResourceID& other) const { return other.id == id; }
};

namespace std {
    template<typename T>
    struct hash<ResourceID<T>> {
        std::size_t operator()(const ResourceID<T>& rid) const noexcept {
            // use id as a hash
            return std::hash<std::size_t>{}(rid.id);
        }
    };
}

#endif // SINGULARITY_RESOURCEID_HPP