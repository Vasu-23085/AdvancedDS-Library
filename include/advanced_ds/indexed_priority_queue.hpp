
#ifndef ADVANCED_DS_INDEXED_PRIORITY_QUEUE_HPP
#define ADVANCED_DS_INDEXED_PRIORITY_QUEUE_HPP

#include <cstddef>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

namespace advanced_ds {

template <typename Priority>
class IndexedPriorityQueue {
public:
    using Index = std::size_t;
    using Entry = std::pair<Index, Priority>;

    // Returns true if the queue is empty.
    bool empty() const noexcept {
        return heap_.empty();
    }

    // Returns the number of elements.
    std::size_t size() const noexcept {
        return heap_.size();
    }

    // Checks whether an index exists.
    bool contains(Index index) const {
        return position_.find(index) != position_.end();
    }

    // Inserts a new index with the given priority.
    void insert(Index index, const Priority& priority) {
        if (contains(index)) {
            throw std::invalid_argument("Index already exists");
        }

        heap_.push_back(index);

        try {
            priorities_.emplace(index, priority);

            try {
                position_.emplace(index, heap_.size() - 1);
            } catch (...) {
                priorities_.erase(index);
                throw;
            }
        } catch (...) {
            heap_.pop_back();
            throw;
        }

        siftUp(heap_.size() - 1);
    }

    // Returns the index with minimum priority.
    Index minIndex() const {
        ensureNotEmpty();
        return heap_.front();
    }

    // Returns the minimum priority.
    const Priority& minPriority() const {
        ensureNotEmpty();
        return priorities_.at(heap_.front());
    }

    // Removes and returns the minimum index-priority pair.
    Entry extractMin() {
        ensureNotEmpty();

        Index index = heap_.front();
        Priority priority = priorities_.at(index);

        swapPositions(0, heap_.size() - 1);

        heap_.pop_back();
        position_.erase(index);
        priorities_.erase(index);

        if (!heap_.empty()) {
            siftDown(0);
        }

        return {index, std::move(priority)};
    }

    // Updates the priority of an existing index.
    void changePriority(Index index, const Priority& newPriority) {
        auto it = priorities_.find(index);

        if (it == priorities_.end()) {
            throw std::out_of_range("Index does not exist");
        }

        bool shouldMoveUp = newPriority < it->second;

        it->second = newPriority;

        std::size_t position = position_.at(index);

        if (shouldMoveUp) {
            siftUp(position);
        } else {
            siftDown(position);
        }
    }

    // Removes an index from the queue.
    // Returns false if the index does not exist.
    bool erase(Index index) {
        auto it = position_.find(index);

        if (it == position_.end()) {
            return false;
        }

        std::size_t position = it->second;
        std::size_t lastPosition = heap_.size() - 1;

        if (position != lastPosition) {
            swapPositions(position, lastPosition);
        }

        heap_.pop_back();
        position_.erase(index);
        priorities_.erase(index);

        if (position < heap_.size()) {
            if (position > 0 &&
                priorities_.at(heap_[position]) <
                    priorities_.at(heap_[(position - 1) / 2])) {
                siftUp(position);
            } else {
                siftDown(position);
            }
        }

        return true;
    }

    // Removes all elements.
    void clear() noexcept {
        heap_.clear();
        position_.clear();
        priorities_.clear();
    }

private:
    // Binary min-heap storing indices.
    std::vector<Index> heap_;

    // Maps index to its heap position.
    std::unordered_map<Index, std::size_t> position_;

    // Maps index to its priority.
    std::unordered_map<Index, Priority> priorities_;

    // Throws if the queue is empty.
    void ensureNotEmpty() const {
        if (empty()) {
            throw std::out_of_range("Priority queue is empty");
        }
    }

    // Swaps two heap positions and updates their mappings.
    void swapPositions(std::size_t first, std::size_t second) {
        if (first == second) {
            return;
        }

        std::swap(heap_[first], heap_[second]);

        position_.at(heap_[first]) = first;
        position_.at(heap_[second]) = second;
    }

    // Restores heap property upwards.
    void siftUp(std::size_t position) {
        while (position > 0) {
            std::size_t parent = (position - 1) / 2;

            if (!(priorities_.at(heap_[position]) <
                  priorities_.at(heap_[parent]))) {
                break;
            }

            swapPositions(position, parent);
            position = parent;
        }
    }

    // Restores heap property downwards.
    void siftDown(std::size_t position) {
        while (true) {
            std::size_t smallest = position;
            std::size_t left = 2 * position + 1;
            std::size_t right = 2 * position + 2;

            if (left < heap_.size() &&
                priorities_.at(heap_[left]) <
                    priorities_.at(heap_[smallest])) {
                smallest = left;
            }

            if (right < heap_.size() &&
                priorities_.at(heap_[right]) <
                    priorities_.at(heap_[smallest])) {
                smallest = right;
            }

            if (smallest == position) {
                break;
            }

            swapPositions(position, smallest);
            position = smallest;
        }
    }
};

} // namespace advanced_ds

#endif // ADVANCED_DS_INDEXED_PRIORITY_QUEUE_HPP
