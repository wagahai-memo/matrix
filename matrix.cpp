#include <iostream>
#include <complex>
#include "matrix.hpp"


int main()
{
  mylib::Matrix<int, 3> x;
  std::cout << x << std::endl;

  using C = std::complex<double>;
  mylib::Matrix<C, 3> y;
  std::cout << y << std::endl;

  return 0;
}
