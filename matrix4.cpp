#include <iostream>
#include "matrix.hpp"


int main()
{
  //static_assert((mylib::Matrix<int, 3>{{1,2,3},{4,5,6},{7,8,9}} += y)(1, 1) == 6, "");
  //static_assert((mylib::Matrix<int, 3>{{1,2,3},{4,5,6},{7,8,9}} -= y))(1, 1) == 4, "");
  //static_assert((mylib::Matrix<int, 3>{{1,2,3},{4,5,6},{7,8,9}} *= 2)(1, 1) == 10, "");
  //static_assert((mylib::Matrix<int, 3>{{1,2,3},{4,5,6},{7,8,9}} *= y))(1, 1) == 5, "");

  constexpr const mylib::Matrix<int, 3> x{{1,2,3},{4,5,6},{7,8,9}};
  constexpr const mylib::Matrix<int, 3> y{{1,0,0},{0,1,0},{0,0,1}};

  constexpr mylib::Matrix<int, 3> a = x + y;
  std::cout << a << std::endl;

  constexpr mylib::Matrix<int, 3> b = x - y;
  std::cout << b << std::endl;

  constexpr mylib::Matrix<int, 3> c = x * 2;
  std::cout << c << std::endl;

  mylib::Matrix<int, 3> d = x * y;
  std::cout << d << std::endl;

  static_assert(x == x, "");

  return 0;
}
