
#ifndef ADVANCED_DS_FENWICK_TREE_HPP
#define ADVANCED_DS_FENWICK_TREE_HPP

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace advanced_ds {

class FenwickTree {
private:
    std::size_t n_;
    std::vector<long long> tree_;

public:
    // Constructs a Fenwick Tree of size n.
    explicit FenwickTree(std::size_t n)
        : n_(n), tree_(n + 1, 0) {}

    // Adds delta to the element at zero-based index.
    void update(std::size_t index, long long delta) {
        if (index >= n_) {
            throw std::out_of_range("FenwickTree index out of range");
        }

        // Move through Fenwick Tree nodes using the lowest set bit.
        for (std::size_t i = index + 1; i <= n_; i += i & -i) {
            tree_[i] += delta;
        }
    }

    // Returns the prefix sum over [0, index].
    long long prefixSum(std::size_t index) const {
        if (index >= n_) {
            throw std::out_of_range("FenwickTree index out of range");
        }

        long long result = 0;

        // Move backwards through Fenwick Tree nodes.
        for (std::size_t i = index + 1; i > 0; i -= i & -i) {
            result += tree_[i];
        }

        return result;
    }

    // Returns the sum over the half-open range [left, right).
    long long rangeSum(std::size_t left, std::size_t right) const {
        if (left > right || right > n_) {
            throw std::out_of_range("Invalid FenwickTree range");
        }

        if (left == right) {
            return 0;
        }

        long long result = prefixSum(right - 1);

        if (left > 0) {
            result -= prefixSum(left - 1);
        }

        return result;
    }

    // Returns the number of elements.
    std::size_t size() const noexcept {
        return n_;
    }
};

} // namespace advanced_ds

#endif // ADVANCED_DS_FENWICK_TREE_HPP
