
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "advanced_ds/fenwick_tree.hpp"

// Test initial size and basic prefix sums.
void testPrefixSum() {
    advanced_ds::FenwickTree ft(5);

    assert(ft.size() == 5);

    ft.update(0, 2);
    ft.update(1, 4);
    ft.update(2, 1);
    ft.update(3, 7);
    ft.update(4, 3);

    assert(ft.prefixSum(0) == 2);
    assert(ft.prefixSum(1) == 6);
    assert(ft.prefixSum(2) == 7);
    assert(ft.prefixSum(3) == 14);
    assert(ft.prefixSum(4) == 17);
}

// Test range sum and point updates.
void testRangeSumAndUpdate() {
    advanced_ds::FenwickTree ft(5);

    ft.update(0, 2);
    ft.update(1, 4);
    ft.update(2, 1);
    ft.update(3, 7);
    ft.update(4, 3);

    assert(ft.rangeSum(0, 5) == 17);
    assert(ft.rangeSum(1, 4) == 12);
    assert(ft.rangeSum(2, 2) == 0);
    assert(ft.rangeSum(0, 1) == 2);
    assert(ft.rangeSum(4, 5) == 3);

    ft.update(2, 5);

    assert(ft.prefixSum(2) == 12);
    assert(ft.rangeSum(1, 4) == 17);
    assert(ft.rangeSum(0, 5) == 22);
}

// Test negative updates and negative sums.
void testNegativeUpdates() {
    advanced_ds::FenwickTree ft(4);

    ft.update(0, 10);
    ft.update(1, -5);
    ft.update(2, -3);
    ft.update(3, 2);

    assert(ft.prefixSum(0) == 10);
    assert(ft.prefixSum(1) == 5);
    assert(ft.prefixSum(2) == 2);
    assert(ft.prefixSum(3) == 4);

    assert(ft.rangeSum(1, 3) == -8);
    assert(ft.rangeSum(0, 4) == 4);

    ft.update(0, -15);

    assert(ft.prefixSum(0) == -5);
    assert(ft.rangeSum(0, 4) == -11);
}

// Test updates with zero.
void testZeroUpdate() {
    advanced_ds::FenwickTree ft(3);

    ft.update(0, 0);
    ft.update(1, 5);
    ft.update(2, 0);

    assert(ft.prefixSum(0) == 0);
    assert(ft.prefixSum(1) == 5);
    assert(ft.prefixSum(2) == 5);

    ft.update(1, 0);

    assert(ft.prefixSum(2) == 5);
}

// Test a single-element Fenwick Tree.
void testSingleElement() {
    advanced_ds::FenwickTree ft(1);

    assert(ft.size() == 1);

    ft.update(0, 10);

    assert(ft.prefixSum(0) == 10);
    assert(ft.rangeSum(0, 1) == 10);

    ft.update(0, -3);

    assert(ft.prefixSum(0) == 7);
    assert(ft.rangeSum(0, 1) == 7);
}

// Test empty Fenwick Tree.
void testEmptyTree() {
    advanced_ds::FenwickTree ft(0);

    assert(ft.size() == 0);
    assert(ft.rangeSum(0, 0) == 0);
}

// Test invalid update index.
void testInvalidIndex() {
    advanced_ds::FenwickTree ft(3);

    bool thrown = false;

    try {
        ft.update(3, 1);
    } catch (const std::out_of_range&) {
        thrown = true;
    }

    assert(thrown);
}

// Test invalid prefix sum index.
void testInvalidPrefixSum() {
    advanced_ds::FenwickTree ft(3);

    bool thrown = false;

    try {
        ft.prefixSum(3);
    } catch (const std::out_of_range&) {
        thrown = true;
    }

    assert(thrown);
}

// Test invalid range queries.
void testInvalidRange() {
    advanced_ds::FenwickTree ft(3);

    bool thrown = false;

    try {
        ft.rangeSum(0, 4);
    } catch (const std::out_of_range&) {
        thrown = true;
    }

    assert(thrown);

    thrown = false;

    try {
        ft.rangeSum(2, 1);
    } catch (const std::out_of_range&) {
        thrown = true;
    }

    assert(thrown);

    thrown = false;

    try {
        ft.rangeSum(4, 4);
    } catch (const std::out_of_range&) {
        thrown = true;
    }

    assert(thrown);
}

// Test invalid operations on an empty tree.
void testEmptyTreeInvalidOperations() {
    advanced_ds::FenwickTree ft(0);

    bool thrown = false;

    try {
        ft.update(0, 5);
    } catch (const std::out_of_range&) {
        thrown = true;
    }

    assert(thrown);

    thrown = false;

    try {
        ft.prefixSum(0);
    } catch (const std::out_of_range&) {
        thrown = true;
    }

    assert(thrown);

    thrown = false;

    try {
        ft.rangeSum(0, 1);
    } catch (const std::out_of_range&) {
        thrown = true;
    }

    assert(thrown);
}

// Compare Fenwick Tree results against a normal array.
void testAgainstNormalArray() {
    const int n = 100;

    advanced_ds::FenwickTree ft(n);
    std::vector<long long> arr(n, 0);

    for (int i = 0; i < n; i++) {
        long long value = (i % 2 == 0) ? i + 1 : -(i + 1);

        ft.update(i, value);
        arr[i] += value;
    }

    // Perform additional updates.
    for (int i = 0; i < n; i += 3) {
        ft.update(i, 5);
        arr[i] += 5;
    }

    // Verify prefix sums.
    long long prefix = 0;

    for (int i = 0; i < n; i++) {
        prefix += arr[i];

        assert(ft.prefixSum(i) == prefix);
    }

    // Verify range sums.
    for (int left = 0; left < n; left += 5) {
        int right = (left + 10 <= n) ? left + 10 : n;

        long long expected = 0;

        for (int i = left; i < right; i++) {
            expected += arr[i];
        }

        assert(ft.rangeSum(left, right) == expected);
    }
}

int main() {
    testPrefixSum();
    testRangeSumAndUpdate();
    testNegativeUpdates();
    testZeroUpdate();
    testSingleElement();
    testEmptyTree();
    testInvalidIndex();
    testInvalidPrefixSum();
    testInvalidRange();
    testEmptyTreeInvalidOperations();
    testAgainstNormalArray();

    std::cout << "All Fenwick Tree tests passed!\n";

    return 0;
}
