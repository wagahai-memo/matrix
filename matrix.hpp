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


public:
  //------------------------------------------
  //
  //  Element access
  //
  //------------------------------------------
  constexpr T& operator ()(int row, int column) {
    return elements_[row][column];
  }

  constexpr const T& operator ()(int row, int column) const {
    return elements_[row][column];
  }


public:
  //------------------------------------------
  //
  //  Arithmetic unary operator
  //
  //------------------------------------------
  constexpr Matrix operator +() const {
    return Matrix(*this);
  }

  constexpr Matrix operator -() const {
    Matrix ret;
    for (int iRow = 0; iRow < N; iRow++) {
      for (int iColumn = 0; iColumn < N; iColumn++) {
        ret.elements_[iRow][iColumn] = -elements_[iRow][iColumn];
      }
    }
    return ret;
  }


public:
  //------------------------------------------
  //
  //  Arithmetic assignment operator
  //
  //------------------------------------------
  constexpr Matrix& operator +=(const Matrix& other) & {
    for (int iRow = 0; iRow < N; iRow++) {
      for (int iColumn = 0; iColumn < N; iColumn++) {
        elements_[iRow][iColumn] += other.elements_[iRow][iColumn];
      }
    }
    return *this;
  }

  constexpr Matrix& operator -=(const Matrix& other) & {
    for (int iRow = 0; iRow < N; iRow++) {
      for (int iColumn = 0; iColumn < N; iColumn++) {
        elements_[iRow][iColumn] -= other.elements_[iRow][iColumn];
      }
    }
    return *this;
  }

  constexpr Matrix& operator *=(const T& a) & {
    for (int iRow = 0; iRow < N; iRow++) {
      for (int iColumn = 0; iColumn < N; iColumn++) {
        elements_[iRow][iColumn] *= a;
      }
    }
    return *this;
  }

  constexpr Matrix& operator *=(const Matrix& other) & {
    Matrix tmp = *this * other;
    *this = tmp;
    return *this;
  }

  constexpr Matrix&& operator +=(const Matrix& other) && = delete;
  constexpr Matrix&& operator -=(const Matrix& other) && = delete;
  constexpr Matrix&& operator *=(const T& a) && = delete;
  constexpr Matrix&& operator *=(const Matrix& other) && = delete;


public:
  //------------------------------------------
  //
  //  Arithmetic binary operator
  //
  //------------------------------------------
  friend constexpr Matrix operator +(const Matrix& lhs, const Matrix& rhs) {
    Matrix ret(lhs);
    return ret += rhs;
  }

  friend constexpr Matrix operator -(const Matrix& lhs, const Matrix& rhs) {
    Matrix ret(lhs);
    return ret -= rhs;
  }

  friend constexpr Matrix operator *(const Matrix& lhs, const T& rhs) {
    Matrix ret(lhs);
    return ret *= rhs;
  }

  friend constexpr Matrix operator *(const T& lhs, const Matrix& rhs) {
    return rhs *= lhs;
  }

  // constexpr にするとgcc5.3のバグにより、コンパイルできない。
  friend Matrix operator *(const Matrix& lhs, const Matrix& rhs) {
    Matrix ret;
    for (int iRow = 0; iRow < N; iRow++) {
      for (int iColumn = 0; iColumn < N; iColumn++) {
        for (int i = 0; i < N; i++) {
          ret.elements_[iRow][iColumn] += lhs.elements_[iRow][i] * rhs.elements_[i][iColumn];
        }
      }
    }
    return ret;
  }


public:
  //------------------------------------------
  //
  //  Logical operator
  //
  //------------------------------------------
  friend constexpr bool operator ==(const Matrix& lhs, const Matrix& rhs) {
    for (int iRow = 0; iRow < N; iRow++) {
      for (int iColumn = 0; iColumn < N; iColumn++) {
        if (lhs.elements_[iRow][iColumn] != rhs.elements_[iRow][iColumn])
          return false;
      }
    }
    return true;
  }

  friend constexpr bool operator !=(const Matrix& lhs, const Matrix& rhs) {
    return !(lhs == rhs);
  }


protected:
  T elements_[N][N] = {};
};  // namespace Matrix

};  // namespace mylib
