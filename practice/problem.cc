#include "problem.h"

using namespace std;

istream &Problem::Read(istream &is) {
  is >> num_rows_ >> num_cols_ >> min_num_ingridients_ >> max_num_cells_;
  pizza_.resize(num_rows_);
  for (int i = 0; i < num_rows_; ++i)
    is >> pizza_[i];
  return is;
}
