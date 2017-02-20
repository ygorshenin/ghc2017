#pragma once

#include <cassert>
#include <vector>

struct Fenwick {
  Fenwick(int size) : data_(size), size_(size) {}

  static int F(int i) { return i & (i + 1); }
  static int G(int i) { return i | (i + 1); }

  void Add(int i, int v) {
    assert(i >= 0);

    while (i < size_) {
      data_[i] += v;
      i = G(i);
    }
  }

  // Returns the sum of elements in the range [0, j].
  int Sum(int j) const {
    assert(j < size_);

    int sum = 0;
    for (; j >= 0; j = F(j) - 1)
      sum += data_[j];
    return sum;
  }

  // Returns the sum of elements in the range [i, j].
  int Sum(int i, int j) const {
    assert(i <= j);
    return Sum(j) - Sum(i - 1);
  }

  std::vector<int> data_;
  int size_;
};

struct Fenwick2D {
  Fenwick2D(int num_rows, int num_cols)
      : fenwicks_(num_rows, Fenwick(num_cols)), num_rows_(num_rows),
        num_cols_(num_cols) {}

  void Add(int r, int c, int v) {
    assert(r >= 0);

    for (; r < num_rows_; r = Fenwick::G(r))
      fenwicks_[r].Add(c, v);
  }

  // Returns the sum of elements in the square (0, 0) - (r, c) (inclusively).
  int Sum(int r, int c) const {
    assert(r < num_rows_);

    int sum = 0;
    for (; r >= 0; r = Fenwick::F(r) - 1)
      sum += fenwicks_[r].Sum(c);
    return sum;
  }

  // Returns the sum of elements in the square (r1, c1) - (r2, c2)
  // (inclusively).
  int Sum(int r1, int c1, int r2, int c2) const {
    assert(r1 <= r2);
    assert(c1 <= c2);
    return Sum(r2, c2) - Sum(r2, c1 - 1) - Sum(r1 - 1, c2) +
           Sum(r1 - 1, c1 - 1);
  }

  std::vector<Fenwick> fenwicks_;
  int num_rows_;
  int num_cols_;
};
