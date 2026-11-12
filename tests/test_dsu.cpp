
#include <cassert>
#include <iostream>
#include <stdexcept>
#include "advanced_ds/dsu.hpp"

void testUnionAndFind() {
    advanced_ds::DSU dsu(5);

    assert(dsu.count() == 5);
    assert(dsu.capacity() == 5);
    assert(!dsu.connected(0, 1));

    assert(dsu.unite(0, 1));
    assert(dsu.connected(0, 1));
    assert(dsu.count() == 4);

    assert(dsu.unite(1, 2));
    assert(dsu.connected(0, 2));
    assert(dsu.count() == 3);

    assert(!dsu.unite(0, 2));
    assert(dsu.count() == 3);
}

void testSetSize() {
    advanced_ds::DSU dsu(6);

    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);

    assert(dsu.size(0) == 3);
    assert(dsu.size(2) == 3);
    assert(dsu.size(3) == 2);
    assert(dsu.size(5) == 1);
}

void testSelfUnion() {
    advanced_ds::DSU dsu(3);

    assert(!dsu.unite(1, 1));
    assert(dsu.count() == 3);
    assert(dsu.size(1) == 1);
}

void testSingleElement() {
    advanced_ds::DSU dsu(1);

    assert(dsu.count() == 1);
    assert(dsu.capacity() == 1);
    assert(dsu.find(0) == 0);
    assert(dsu.size(0) == 1);
    assert(dsu.connected(0, 0));

    assert(!dsu.unite(0, 0));
    assert(dsu.count() == 1);
}

void testIndependentComponents() {
    advanced_ds::DSU dsu(7);

    dsu.unite(0, 1);
    dsu.unite(1, 2);

    dsu.unite(3, 4);
    dsu.unite(4, 5);

    assert(dsu.connected(0, 2));
    assert(dsu.connected(3, 5));

    assert(!dsu.connected(0, 3));
    assert(!dsu.connected(2, 6));

    assert(dsu.count() == 3);
}

void testEmptyDSU() {
    advanced_ds::DSU dsu(0);

    assert(dsu.count() == 0);
    assert(dsu.capacity() == 0);
}

void testInvalidIndex() {
    advanced_ds::DSU dsu(3);

    bool thrown = false;

    try {
        dsu.find(3);
    } catch (const std::out_of_range&) {
        thrown = true;
    }

    assert(thrown);

    thrown = false;

    try {
        dsu.size(3);
    } catch (const std::out_of_range&) {
        thrown = true;
    }

    assert(thrown);

    thrown = false;

    try {
        dsu.connected(0, 3);
    } catch (const std::out_of_range&) {
        thrown = true;
    }

    assert(thrown);

    thrown = false;

    try {
        dsu.unite(0, 3);
    } catch (const std::out_of_range&) {
        thrown = true;
    }

    assert(thrown);
}

void testInvalidIndexInEmptyDSU() {
    advanced_ds::DSU dsu(0);

    bool thrown = false;

    try {
        dsu.find(0);
    } catch (const std::out_of_range&) {
        thrown = true;
    }

    assert(thrown);
}

int main() {
    testUnionAndFind();
    testSetSize();
    testSelfUnion();
    testSingleElement();
    testIndependentComponents();
    testEmptyDSU();
    testInvalidIndex();
    testInvalidIndexInEmptyDSU();

    std::cout << "All DSU tests passed!\n";

    return 0;
}
