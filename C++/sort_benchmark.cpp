#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using Values = std::vector<double>;

void bubble(Values& a) {
    for (std::size_t end = a.size(); end > 1; --end) {
        bool changed = false;
        for (std::size_t i = 1; i < end; ++i) if (a[i - 1] > a[i]) { std::swap(a[i - 1], a[i]); changed = true; }
        if (!changed) break;
    }
}

void mergeRange(Values& a, Values& tmp, std::size_t lo, std::size_t hi) {
    if (hi - lo < 2) return;
    std::size_t mid = lo + (hi - lo) / 2;
    mergeRange(a, tmp, lo, mid); mergeRange(a, tmp, mid, hi);
    std::size_t i = lo, j = mid, k = lo;
    while (i < mid && j < hi) tmp[k++] = a[i] <= a[j] ? a[i++] : a[j++];
    while (i < mid) tmp[k++] = a[i++];
    while (j < hi) tmp[k++] = a[j++];
    std::copy(tmp.begin() + lo, tmp.begin() + hi, a.begin() + lo);
}
void mergeSort(Values& a) { Values tmp(a.size()); mergeRange(a, tmp, 0, a.size()); }

struct Node { double value; Node* left = nullptr; Node* right = nullptr; explicit Node(double v) : value(v) {} };
void insert(Node*& n, double v) { if (!n) n = new Node(v); else if (v < n->value) insert(n->left, v); else insert(n->right, v); }
void inOrder(Node* n, Values& a, std::size_t& i) { if (!n) return; inOrder(n->left, a, i); a[i++] = n->value; inOrder(n->right, a, i); }
void release(Node* n) { if (!n) return; release(n->left); release(n->right); delete n; }
void treeSort(Values& a) { Node* root = nullptr; for (double v : a) insert(root, v); std::size_t i = 0; inOrder(root, a, i); release(root); }

void sift(Values& a, std::size_t n, std::size_t root) {
    while (2 * root + 1 < n) {
        std::size_t child = 2 * root + 1;
        if (child + 1 < n && a[child + 1] > a[child]) ++child;
        if (a[root] >= a[child]) return;
        std::swap(a[root], a[child]); root = child;
    }
}
void heapSort(Values& a) {
    for (std::size_t i = a.size() / 2; i > 0; --i) sift(a, a.size(), i - 1);
    for (std::size_t end = a.size(); end > 1; --end) { std::swap(a[0], a[end - 1]); sift(a, end - 1, 0); }
}

void countingSort(Values& a) {
    Values keys = a; std::sort(keys.begin(), keys.end());
    keys.erase(std::unique(keys.begin(), keys.end()), keys.end());
    std::vector<std::size_t> counts(keys.size(), 0);
    for (double v : a) ++counts[std::lower_bound(keys.begin(), keys.end(), v) - keys.begin()];
    std::size_t k = 0;
    for (std::size_t i = 0; i < keys.size(); ++i) while (counts[i]--) a[k++] = keys[i];
}

Values data(std::size_t n, std::uint32_t seed) {
    std::mt19937 rng(seed); std::uniform_real_distribution<double> dist(-1000000.0, 1000000.0);
    Values a(n); for (double& v : a) v = dist(rng); return a;
}
template<class Function> void measure(const std::string& name, Function sort, std::size_t n) {
    Values a = data(n, 42);
    auto start = std::chrono::steady_clock::now(); sort(a); auto end = std::chrono::steady_clock::now();
    double ms = std::chrono::duration<double, std::milli>(end - start).count();
    std::uint64_t extra = name == "Merge" ? 8ULL * n : name == "Tree" ? 24ULL * n : name == "Counting" ? 12ULL * n : 0;
    std::cout << name << ',' << n << ',' << ms << ',' << extra << '\n';
}
int main(int argc, char** argv) {
    std::vector<std::size_t> sizes;
    if (argc == 1) sizes = {100000, 1000000, 10000000, 100000000, 1000000000};
    else for (int i = 1; i < argc; ++i) sizes.push_back(std::stoull(argv[i]));
    std::cout << "algoritmo,n,tiempo_ms,memoria_delta_bytes\n";
    for (std::size_t n : sizes) {
        measure("Bubble", bubble, n); measure("Merge", mergeSort, n); measure("Tree", treeSort, n); measure("Heap", heapSort, n); measure("Counting", countingSort, n);
    }
}
