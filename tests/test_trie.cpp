
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "advanced_ds/trie.hpp"

// Test insertion and searching.
void testInsertAndSearch() {
    advanced_ds::Trie trie;

    assert(trie.empty());

    trie.insert("apple");
    trie.insert("app");

    assert(trie.search("apple"));
    assert(trie.search("app"));
    assert(!trie.search("ap"));
    assert(!trie.search("banana"));

    assert(trie.size() == 2);

    // Duplicate insertion should not increase size.
    trie.insert("apple");
    assert(trie.size() == 2);
}

// Test prefix searching.
void testPrefixSearch() {
    advanced_ds::Trie trie;

    trie.insert("apple");
    trie.insert("application");

    assert(trie.startsWith("app"));
    assert(trie.startsWith("apple"));
    assert(trie.startsWith(""));
    assert(!trie.startsWith("banana"));
    assert(!trie.startsWith("xyz"));
}

// Test autocomplete functionality.
void testAutocomplete() {
    advanced_ds::Trie trie;

    trie.insert("application");
    trie.insert("apple");
    trie.insert("app");
    trie.insert("apt");
    trie.insert("banana");

    std::vector<std::string> expected = {
        "app", "apple", "application"
    };

    assert(trie.autocomplete("app", 10) == expected);
    assert(trie.autocomplete("app", 2).size() == 2);
    assert(trie.autocomplete("xyz").empty());
    assert(trie.autocomplete("app", 0).empty());
}

// Test deleting words.
void testErase() {
    advanced_ds::Trie trie;

    trie.insert("app");
    trie.insert("apple");
    trie.insert("application");

    assert(trie.erase("app"));

    assert(!trie.search("app"));
    assert(trie.search("apple"));
    assert(trie.search("application"));
    assert(trie.startsWith("app"));

    // Deleting an already deleted word.
    assert(!trie.erase("app"));

    assert(trie.size() == 2);

    assert(trie.erase("apple"));
    assert(trie.erase("application"));

    assert(trie.empty());
}

// Test empty string handling.
void testEmptyWord() {
    advanced_ds::Trie trie;

    trie.insert("");

    assert(trie.search(""));
    assert(trie.startsWith(""));
    assert(trie.size() == 1);

    assert(trie.erase(""));

    assert(!trie.search(""));
    assert(trie.empty());
}

// Test clearing the Trie.
void testClear() {
    advanced_ds::Trie trie;

    trie.insert("hello");
    trie.insert("world");

    trie.clear();

    assert(trie.empty());
    assert(trie.size() == 0);
    assert(!trie.search("hello"));
    assert(!trie.search("world"));

    // Trie should work after clearing.
    trie.insert("again");

    assert(trie.search("again"));
    assert(trie.size() == 1);
}

// Test case sensitivity.
void testCaseSensitivity() {
    advanced_ds::Trie trie;

    trie.insert("Apple");
    trie.insert("apple");

    assert(trie.search("Apple"));
    assert(trie.search("apple"));
    assert(!trie.search("APPLE"));

    assert(trie.size() == 2);
}

// Test deleting a prefix without deleting longer words.
void testDeletePrefixWord() {
    advanced_ds::Trie trie;

    trie.insert("car");
    trie.insert("card");
    trie.insert("care");
    trie.insert("careful");

    assert(trie.erase("car"));

    assert(!trie.search("car"));
    assert(trie.search("card"));
    assert(trie.search("care"));
    assert(trie.search("careful"));

    assert(trie.size() == 3);
}

// Test deleting nonexistent words.
void testDeleteNonexistentWord() {
    advanced_ds::Trie trie;

    trie.insert("hello");
    trie.insert("help");

    assert(!trie.erase("he"));
    assert(!trie.erase("world"));

    assert(trie.search("hello"));
    assert(trie.search("help"));

    assert(trie.size() == 2);
}

// Test autocomplete with an empty prefix.
void testAutocompleteEmptyPrefix() {
    advanced_ds::Trie trie;

    trie.insert("banana");
    trie.insert("apple");
    trie.insert("application");
    trie.insert("app");
    trie.insert("apt");

    std::vector<std::string> expected = {
        "app",
        "apple",
        "application",
        "apt",
        "banana"
    };

    assert(trie.autocomplete("") == expected);
}

// Test autocomplete ordering and limits.
void testAutocompleteOrdering() {
    advanced_ds::Trie trie;

    trie.insert("dog");
    trie.insert("dot");
    trie.insert("door");
    trie.insert("dove");
    trie.insert("duck");

    std::vector<std::string> expected = {
        "dog", "door", "dot", "dove", "duck"
    };

    assert(trie.autocomplete("d") == expected);

    std::vector<std::string> limited = {
        "dog", "door"
    };

    assert(trie.autocomplete("d", 2) == limited);
}

// Test inserting and deleting multiple words.
void testMultipleInsertionsAndDeletions() {
    advanced_ds::Trie trie;

    for (int i = 0; i < 100; i++) {
        trie.insert("word" + std::to_string(i));
    }

    assert(trie.size() == 100);

    for (int i = 0; i < 50; i++) {
        assert(trie.erase("word" + std::to_string(i)));
    }

    assert(trie.size() == 50);

    for (int i = 0; i < 50; i++) {
        assert(!trie.search("word" + std::to_string(i)));
    }

    for (int i = 50; i < 100; i++) {
        assert(trie.search("word" + std::to_string(i)));
    }
}

int main() {
    testInsertAndSearch();
    testPrefixSearch();
    testAutocomplete();
    testErase();
    testEmptyWord();
    testClear();

    testCaseSensitivity();
    testDeletePrefixWord();
    testDeleteNonexistentWord();
    testAutocompleteEmptyPrefix();
    testAutocompleteOrdering();
    testMultipleInsertionsAndDeletions();

    std::cout << "All Trie tests passed!\n";

    return 0;
}
