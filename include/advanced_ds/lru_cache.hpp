
#ifndef ADVANCED_DS_LRU_CACHE_HPP
#define ADVANCED_DS_LRU_CACHE_HPP

#include <cstddef>
#include <list>
#include <optional>
#include <unordered_map>
#include <utility>

namespace advanced_ds {

template <typename Key, typename Value>
class LRUCache {
private:
    using Entry = std::pair<Key, Value>;
    using List = std::list<Entry>;
    using Iterator = typename List::iterator;

    std::size_t capacity_;
    List items_;
    std::unordered_map<Key, Iterator> index_;

    // Moves the accessed element to the front.
    void touch(Iterator it) {
        items_.splice(items_.begin(), items_, it);
    }

public:
    // Constructs an LRU Cache with the given capacity.
    explicit LRUCache(std::size_t capacity)
        : capacity_(capacity) {}

    // Returns maximum capacity.
    std::size_t capacity() const noexcept {
        return capacity_;
    }

    // Returns current number of elements.
    std::size_t size() const noexcept {
        return items_.size();
    }

    // Checks whether the cache is empty.
    bool empty() const noexcept {
        return items_.empty();
    }

    // Checks whether a key exists.
    bool contains(const Key& key) const {
        return index_.find(key) != index_.end();
    }

    // Returns the value if found and marks it as recently used.
    std::optional<Value> get(const Key& key) {
        auto it = index_.find(key);

        if (it == index_.end()) {
            return std::nullopt;
        }

        touch(it->second);

        return it->second->second;
    }

    // Inserts or updates a key-value pair.
    // Capacity zero means no elements are stored.
    void put(const Key& key, const Value& value) {
        if (capacity_ == 0) {
            return;
        }

        auto it = index_.find(key);

        // Update an existing entry.
        if (it != index_.end()) {
            it->second->second = value;
            touch(it->second);
            return;
        }

        // Insert the new entry first.
        items_.emplace_front(key, value);

        try {
            auto result = index_.emplace(
                items_.front().first,
                items_.begin()
            );

            if (!result.second) {
                items_.pop_front();
                return;
            }
        } catch (...) {
            items_.pop_front();
            throw;
        }

        // Remove the least recently used entry if necessary.
        if (items_.size() > capacity_) {
            auto last = std::prev(items_.end());

            index_.erase(last->first);
            items_.pop_back();
        }
    }

    // Removes an entry by key.
    // Returns false if the key does not exist.
    bool erase(const Key& key) {
        auto it = index_.find(key);

        if (it == index_.end()) {
            return false;
        }

        items_.erase(it->second);
        index_.erase(it);

        return true;
    }

    // Removes all entries.
    void clear() {
        items_.clear();
        index_.clear();
    }
};

} // namespace advanced_ds

#endif // ADVANCED_DS_LRU_CACHE_HPP
