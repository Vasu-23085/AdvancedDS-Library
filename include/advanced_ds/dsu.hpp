
#ifndef ADVANCED_DS_DSU_HPP
#define ADVANCED_DS_DSU_HPP

#include <cstddef>
#include <numeric>
#include <stdexcept>
#include <utility>
#include <vector>

namespace advanced_ds {

class DSU {
private:
    std::vector<std::size_t> parent_;
    std::vector<std::size_t> size_;
    std::size_t components_;

    void checkIndex(std::size_t x) const {
        if (x >= parent_.size()) {
            throw std::out_of_range("DSU index out of range");
        }
    }

public:
    explicit DSU(std::size_t n)
        : parent_(n), size_(n, 1), components_(n) {
        std::iota(parent_.begin(), parent_.end(), 0);
    }

    std::size_t find(std::size_t x) {
        checkIndex(x);

        if (parent_[x] != x) {
            parent_[x] = find(parent_[x]);
        }

        return parent_[x];
    }

    bool unite(std::size_t a, std::size_t b) {
        a = find(a);
        b = find(b);

        if (a == b) return false;

        if (size_[a] < size_[b]) {
            std::swap(a, b);
        }

        parent_[b] = a;
        size_[a] += size_[b];
        --components_;

        return true;
    }

    bool connected(std::size_t a, std::size_t b) {
        return find(a) == find(b);
    }

    std::size_t size(std::size_t x) {
        return size_[find(x)];
    }

    std::size_t count() const {
        return components_;
    }

    std::size_t capacity() const {
        return parent_.size();
    }
};

} // namespace advanced_ds

#endif
