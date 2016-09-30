#include <ostream>


namespace mylib {

template <typename T, int N>
class Matrix {
  static_assert(N > 0, "");

public:
  //------------------------------------------
  //
  //  Insertion operator
  //
  //------------------------------------------
  friend std::ostream& operator <<(std::ostream& os, const Matrix& x) {
    os << "[";
    for (int iRow = 0; iRow < N; iRow++) {
      os << "[";
      for (int iColumn = 0; iColumn < N; iColumn++) {
        os << x.elements_[iRow][iColumn];
        if (iColumn != N - 1)
          os << ",";
      }
      os << "]";
      if (iRow != N - 1)
        os << ",";
    }
    os << "]";
    return os;
  }

protected:
  T elements_[N][N] = {};
};  // namespace Matrix

};  // namespace mylib
