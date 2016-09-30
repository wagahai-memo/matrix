#include <iostream>
#include "matrix.hpp"


int main()
{
  constexpr mylib::Matrix<int, 3> x{{1,2,3},{4,5,6},{7,8,9}};
  constexpr mylib::Matrix<int, 3> y = x;

  //y = x;

  //mylib::Matrix<int, 3>() = x;
  //mylib::Matrix<int, 3>() = mylib::Matrix<int, 3>();

  std::cout << x << std::endl;
  std::cout << y << std::endl;

  std::cout << noexcept(mylib::Matrix<int, 2>()) << std::endl;

  return 0;
}
