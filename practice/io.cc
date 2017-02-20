#include "io.h"

using namespace std;

istream &Problem::Read(istream &is) {
  is >> num_rows_ >> num_cols_ >> min_num_ingridients_ >> max_num_cells_;
  m_pizza.resize(num_rows_);
  for (int i = 0; i < num_rows_; ++i)
    is >> m_pizza[i];
  return is;
}
