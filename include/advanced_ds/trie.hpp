
#ifndef ADVANCED_DS_TRIE_HPP
#define ADVANCED_DS_TRIE_HPP

#include <cstddef>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace advanced_ds {

class Trie {
private:
    struct Node {
        std::map<char, std::unique_ptr<Node>> children;
        bool isEndOfWord = false;
    };

    Node root_;
    std::size_t wordCount_ = 0;

    // Collects words in lexicographical order.
    static void collectWords(
        const Node& node,
        std::string& current,
        std::vector<std::string>& result,
        std::size_t limit
    ) {
        if (result.size() >= limit) {
            return;
        }

        if (node.isEndOfWord) {
            result.push_back(current);
        }

        for (const auto& entry : node.children) {
            if (result.size() >= limit) {
                break;
            }

            current.push_back(entry.first);

            collectWords(
                *entry.second,
                current,
                result,
                limit
            );

            current.pop_back();
        }
    }

    // Recursive helper for deleting a word.
    static bool eraseHelper(
        Node& node,
        const std::string& word,
        std::size_t index,
        bool& erased
    ) {
        // End of the word reached.
        if (index == word.size()) {
            if (!node.isEndOfWord) {
                return false;
            }

            node.isEndOfWord = false;
            erased = true;

            return node.children.empty();
        }

        auto it = node.children.find(word[index]);

        if (it == node.children.end()) {
            return false;
        }

        bool canDelete = eraseHelper(
            *it->second,
            word,
            index + 1,
            erased
        );

        // Remove unnecessary nodes.
        if (erased && canDelete) {
            node.children.erase(it);
        }

        return !node.isEndOfWord && node.children.empty();
    }

public:
    Trie() = default;

    // Inserts a word into the Trie.
    void insert(const std::string& word) {
        Node* current = &root_;

        for (char ch : word) {
            auto it = current->children.find(ch);

            if (it == current->children.end()) {
                auto child = std::make_unique<Node>();

                it = current->children.emplace(
                    ch,
                    std::move(child)
                ).first;
            }

            current = it->second.get();
        }

        // Avoid counting duplicate words.
        if (!current->isEndOfWord) {
            current->isEndOfWord = true;
            ++wordCount_;
        }
    }

    // Checks whether a complete word exists.
    bool search(const std::string& word) const {
        const Node* current = &root_;

        for (char ch : word) {
            auto it = current->children.find(ch);

            if (it == current->children.end()) {
                return false;
            }

            current = it->second.get();
        }

        return current->isEndOfWord;
    }

    // Checks whether any word starts with the prefix.
    bool startsWith(const std::string& prefix) const {
        const Node* current = &root_;

        for (char ch : prefix) {
            auto it = current->children.find(ch);

            if (it == current->children.end()) {
                return false;
            }

            current = it->second.get();
        }

        return true;
    }

    // Returns autocomplete suggestions in lexicographical order.
    std::vector<std::string> autocomplete(
        const std::string& prefix,
        std::size_t limit = 10
    ) const {
        std::vector<std::string> result;

        if (limit == 0) {
            return result;
        }

        const Node* current = &root_;

        // Find the prefix node.
        for (char ch : prefix) {
            auto it = current->children.find(ch);

            if (it == current->children.end()) {
                return result;
            }

            current = it->second.get();
        }

        std::string currentWord = prefix;

        collectWords(
            *current,
            currentWord,
            result,
            limit
        );

        return result;
    }

    // Deletes a word from the Trie.
    bool erase(const std::string& word) {
        bool erased = false;

        eraseHelper(root_, word, 0, erased);

        if (erased) {
            --wordCount_;
        }

        return erased;
    }

    // Checks whether the Trie is empty.
    bool empty() const noexcept {
        return wordCount_ == 0;
    }

    // Returns the number of stored words.
    std::size_t size() const noexcept {
        return wordCount_;
    }

    // Removes all words.
    void clear() {
        root_ = Node{};
        wordCount_ = 0;
    }
};

} // namespace advanced_ds

#endif // ADVANCED_DS_TRIE_HPP
