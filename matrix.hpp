#include <ostream>
#include <initializer_list>


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


public:
  //------------------------------------------
  //
  //  Constructor, Destructor, Copy, Move
  //
  //------------------------------------------
  constexpr Matrix() noexcept(noexcept(T())) {}

  constexpr Matrix(const T& a) {
    for (int i = 0; i < N; i++)
      elements_[i][i] = a;
  }

  constexpr Matrix(std::initializer_list<std::initializer_list<T>> ll) {
    auto itRow = ll.begin();
    for (int iRow = 0; iRow < N && itRow != ll.end(); iRow++, ++itRow) {
      auto l = *itRow;
      auto itColumn = l.begin();
      for (int iColumn = 0; iColumn < N && itColumn != l.end(); iColumn++, ++itColumn) {
        elements_[iRow][iColumn] = *itColumn;
      }
    }
  }

  constexpr Matrix(const Matrix& other) noexcept = default;
  constexpr Matrix(Matrix&&) noexcept = default;
  ~Matrix() = default;

  constexpr Matrix& operator =(const Matrix&) & noexcept = default;
  constexpr Matrix& operator =(Matrix&&) & noexcept = default;

  constexpr Matrix&& operator =(const Matrix&) && noexcept = delete;
  constexpr Matrix&& operator =(Matrix&&) && noexcept = delete;


protected:
  T elements_[N][N] = {};
};  // namespace Matrix

};  // namespace mylib
