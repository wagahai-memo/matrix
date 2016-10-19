#include <iostream>
#include <utility>
#include "matrix.hpp"


// constでない一時オブジェクトの状態を、コンパイル時に変更できるかテストする関数。
constexpr mylib::Matrix<int, 3>&& test(mylib::Matrix<int, 3>&& x) {
  x(1, 2) = 37;
  return std::move(x);
}


int main()
{
  // 上述のtest()関数を使って、constexpr T& operator ()(int row, int column) のテスト。
  static_assert((test(mylib::Matrix<int, 3>{{1,2,3},{4,5,6},{7,8,9}}))(1, 2) == 37, "");

  constexpr const mylib::Matrix<int, 3> x{{1,2,3},{4,5,6},{7,8,9}};

  // constなら状態の変更ができないことのテスト。
  //x(1, 2) = 13;

  // constexpr const T& operator ()(int row, int column) const のテスト。
  static_assert(x(1, 2) == 6, "");

  // constexpr Matrix operator +() const のテスト。
  static_assert((-x)(1, 2) == -6, "");

  // constexpr Matrix operator -() const のテスト。
  static_assert((+x)(1, 2) == 6, "");

  return 0;
}
