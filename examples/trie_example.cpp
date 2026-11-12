#include <iostream>
#include <string>
#include "advanced_ds/trie.hpp"

int main() {
    advanced_ds::Trie trie;

    trie.insert("apple");
    trie.insert("app");
    trie.insert("application");
    trie.insert("apt");
    trie.insert("banana");

    std::cout << std::boolalpha;

    std::cout << "Search app: " << trie.search("app") << '\n';
    std::cout << "Search ap: " << trie.search("ap") << '\n';
    std::cout << "Prefix ap: " << trie.startsWith("ap") << '\n';

    std::cout << "\nAutocomplete for app:\n";
    for (const std::string& word : trie.autocomplete("app", 5)) {
        std::cout << word << '\n';
    }

    std::cout << "\nTotal words: " << trie.size() << '\n';

    trie.erase("app");

    std::cout << "Search app after deletion: "
              << trie.search("app") << '\n';
    std::cout << "Total words after deletion: "
              << trie.size() << '\n';

    return 0;
}
