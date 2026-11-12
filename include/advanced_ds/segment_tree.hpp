
#ifndef ADVANCED_DS_SEGMENT_TREE_HPP
#define ADVANCED_DS_SEGMENT_TREE_HPP

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace advanced_ds {

class SegmentTree {
private:
    std::size_t n_;
    std::vector<long long> tree_;

    // Builds the segment tree recursively.
    void build(const std::vector<long long>& values,
               std::size_t node,
               std::size_t start,
               std::size_t end) {

        // Leaf node.
        if (end - start == 1) {
            tree_[node] = values[start];
            return;
        }

        std::size_t mid = start + (end - start) / 2;

        build(values, node * 2, start, mid);
        build(values, node * 2 + 1, mid, end);

        // Merge child sums.
        tree_[node] = tree_[node * 2] + tree_[node * 2 + 1];
    }

    // Updates a single element.
    void update(std::size_t node,
                std::size_t start,
                std::size_t end,
                std::size_t index,
                long long value) {

        if (end - start == 1) {
            tree_[node] = value;
            return;
        }

        std::size_t mid = start + (end - start) / 2;

        if (index < mid) {
            update(node * 2, start, mid, index, value);
        } else {
            update(node * 2 + 1, mid, end, index, value);
        }

        // Recalculate the current node.
        tree_[node] = tree_[node * 2] + tree_[node * 2 + 1];
    }

    // Returns the sum over the requested range.
    long long query(std::size_t node,
                    std::size_t start,
                    std::size_t end,
                    std::size_t left,
                    std::size_t right) const {

        // No overlap.
        if (right <= start || end <= left) {
            return 0;
        }

        // Complete overlap.
        if (left <= start && end <= right) {
            return tree_[node];
        }

        // Partial overlap.
        std::size_t mid = start + (end - start) / 2;

        return query(node * 2, start, mid, left, right)
             + query(node * 2 + 1, mid, end, left, right);
    }

public:
    // Constructs a segment tree from an input vector.
    explicit SegmentTree(const std::vector<long long>& values)
        : n_(values.size()), tree_(4 * values.size() + 1, 0) {

        if (n_ > 0) {
            build(values, 1, 0, n_);
        }
    }

    // Returns the number of elements.
    std::size_t size() const noexcept {
        return n_;
    }

    // Assigns a new value at a zero-based index.
    void update(std::size_t index, long long value) {
        if (index >= n_) {
            throw std::out_of_range("SegmentTree index out of range");
        }

        update(1, 0, n_, index, value);
    }

    // Returns the sum over the half-open range [left, right).
    long long rangeSum(std::size_t left, std::size_t right) const {
        if (left > right || right > n_) {
            throw std::out_of_range("Invalid SegmentTree range");
        }

        if (left == right) {
            return 0;
        }

        return query(1, 0, n_, left, right);
    }
};

} // namespace advanced_ds

#endif // ADVANCED_DS_SEGMENT_TREE_HPP
