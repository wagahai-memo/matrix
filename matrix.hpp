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


  //------------------------------------------
  //
  // iRow行とiCokumn列を除いた成分を行列にして返す。
  //
  //------------------------------------------
  constexpr Matrix<T, N - 1> minor_matrix(int iRow, int iColumn) const {
    static_assert(N > 1, "");

    Matrix<T, N - 1> ret;
    for (int iRR = 0, i = -1; iRR < N; iRR++) {
      if (iRR == iRow) continue;
      i++;
      for (int iCC = 0, j = -1; iCC < N; iCC++) {
        if (iCC == iColumn) continue;
        j++;
        ret(i, j) = elements_[iRR][iCC];
      }
    }
    return ret;
  }


protected:
  T elements_[N][N] = {};
};  // namespace Matrix


//------------------------------------------
//
// (i, j)成分の余因子を求める。
//
//------------------------------------------
template <typename T, int N> inline
constexpr T cofactor(const Matrix<T, N>& m, int iRow, int iColumn) {
  T sign = (iRow + iColumn) % 2 == 0 ? 1 : -1;
  return sign * det(m.minor_matrix(iRow, iColumn));
}


//------------------------------------------
//
// 行列式を求めるときのヘルパー。
// 余因子展開で再帰的(detとcofactorが相互に呼ぶ)に計算する。
// 部分的特殊化で N == 1 の動きを変えるために必要。
// (関数テンプレートは部分的特殊化ができないが、クラステンプレートならできる)
//
//------------------------------------------
template <typename T, int N>
struct Det {
  inline static constexpr T det(const Matrix<T, N>& matrix) {
    T ret = 0;
    for (int iColumn = 0; iColumn < N; iColumn++) {
      ret += matrix(0, iColumn) * cofactor(matrix, 0, iColumn);
    }
    return ret;
  }
};


template<typename T>
struct Det<T, 1> {
  inline static constexpr T det(const Matrix<T, 1>& matrix) {
    return matrix(0, 0);
  }
};


template<typename T>
struct Det<T, 2> {
  inline static constexpr T det(const Matrix<T, 2>& matrix) {
    return matrix(0, 0) * matrix(1, 1) - matrix(0, 1) * matrix(1, 0);
  }
};


template<typename T>
struct Det<T, 3> {
  inline static constexpr T det(const Matrix<T, 3>& matrix) {
    T a = matrix(0, 0) * matrix(1, 1) * matrix(2, 2);
    T b = matrix(0, 0) * matrix(1, 2) * matrix(2, 1);
    T c = matrix(0, 1) * matrix(1, 0) * matrix(2, 2);
    T d = matrix(0, 1) * matrix(1, 2) * matrix(2, 0);
    T e = matrix(0, 2) * matrix(1, 0) * matrix(2, 1);
    T f = matrix(0, 2) * matrix(1, 1) * matrix(2, 0);
    return a - b - c + d + e - f;
  }
};


//------------------------------------------
//
// 行列式を求める
//
//------------------------------------------
template <typename T, int N> inline
constexpr T det(const Matrix<T, N>& matrix) {
  return Det<T, N>::det(matrix);
}


//------------------------------------------
//
// 余因子行列を求める
//
//------------------------------------------
template <typename T, int N> inline
constexpr Matrix<T, N> cofactor_matrix(const Matrix<T, N>& m) {
  Matrix<T, N> ret;
  for (int iRow = 0; iRow < N; iRow++) {
    for(int iColumn = 0; iColumn < N; iColumn++) {
      //ここで行と列を入れ替えているため、転置したことになっている。
      ret(iRow, iColumn) = cofactor(m, iColumn, iRow);
    }
  }
  return ret;
}


};  // namespace mylib
