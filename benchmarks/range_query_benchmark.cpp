#include <chrono>
#include <cstddef>
#include <iostream>
#include <vector>

#include "advanced_ds/advanced_ds.hpp"

using Clock = std::chrono::steady_clock;

template <typename Function>
double measureMilliseconds(Function operation) {
    const auto start = Clock::now();
    operation();
    const auto finish = Clock::now();

    return std::chrono::duration<double, std::milli>(
        finish - start
    ).count();
}

int main() {
    constexpr std::size_t N = 100000;
    constexpr std::size_t OPERATIONS = 200000;

    std::vector<long long> values(N);

    for (std::size_t i = 0; i < N; ++i) {
        values[i] = static_cast<long long>(i % 100);
    }

    advanced_ds::FenwickTree fenwick(N);

    for (std::size_t i = 0; i < N; ++i) {
        fenwick.update(i, values[i]);
    }

    advanced_ds::SegmentTree segmentTree(values);

    long long fenwickChecksum = 0;
    long long segmentChecksum = 0;

    const double fenwickUpdateMs = measureMilliseconds([&]() {
        for (std::size_t i = 0; i < OPERATIONS; ++i) {
            fenwick.update(i % N, 1);
        }
    });

    const double segmentUpdateMs = measureMilliseconds([&]() {
        for (std::size_t i = 0; i < OPERATIONS; ++i) {
            segmentTree.update(i % N, static_cast<long long>(i));
        }
    });

    const double fenwickQueryMs = measureMilliseconds([&]() {
        for (std::size_t i = 0; i < OPERATIONS; ++i) {
            const std::size_t left = i % (N / 2);
            const std::size_t right = left + N / 2;

            fenwickChecksum += fenwick.rangeSum(left, right);
        }
    });

    const double segmentQueryMs = measureMilliseconds([&]() {
        for (std::size_t i = 0; i < OPERATIONS; ++i) {
            const std::size_t left = i % (N / 2);
            const std::size_t right = left + N / 2;

            segmentChecksum += segmentTree.rangeSum(left, right);
        }
    });

    std::cout << "AdvancedDS Range Query Benchmark\n";
    std::cout << "Elements: " << N << '\n';
    std::cout << "Operations per test: " << OPERATIONS << "\n\n";

    std::cout << "Fenwick Tree updates: "
              << fenwickUpdateMs << " ms\n";
    std::cout << "Segment Tree updates: "
              << segmentUpdateMs << " ms\n\n";

    std::cout << "Fenwick Tree range queries: "
              << fenwickQueryMs << " ms\n";
    std::cout << "Segment Tree range queries: "
              << segmentQueryMs << " ms\n\n";

    std::cout << "Checksums: "
              << fenwickChecksum << ", "
              << segmentChecksum << '\n';

    return 0;
}
