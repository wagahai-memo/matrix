#include <time.h>
#include <iostream>
#include "matrix.hpp"


int main()
{
  /*
  constexpr mylib::Matrix<int, 3> x{{1,2,3},{4,5,6},{7,8,9}};
  constexpr mylib::Matrix<int, 3> y = cofactor_matrix(x);
  std::cout << y << std::endl;
  std::cout << x * y << std::endl;
  */

  clock_t start, end;
  //mylib::Matrix<int, 3> m{{1,3,2},{4,5,6},{7,8,9}};
  mylib::Matrix<int, 4> m{{1,2,4,3},{3,4,5,7},{6,7,8,9},{10,11,12,13}};
  //mylib::Matrix<int, 5> m{{1,2,4,3,5},{3,4,5,7,9},{6,7,8,9,7},{10,11,12,13,14},{0,3,6,9,2}};
  //mylib::Matrix<int, 6> m{{1,2,4,3,5,6},{3,4,5,7,9,3},{6,7,8,9,7,4},{10,11,12,13,14,2},{0,3,6,9,2,8},{0,5,6,2,1,6}};
  //mylib::Matrix<int, 7> m{{1,2,4,3,5,6,5},{3,4,5,7,9,3,2},{6,7,8,9,7,4,4},{10,11,12,13,14,2,0},{0,3,6,9,2,8,8},{0,5,6,2,1,6,9},{4,3,7,2,9,6,9}};

  int z = 0;
  start = clock();
  for (int i = 0; i < 5000; i++)
    z = mylib::det(m);
  end = clock();
  std::cout << (end - start) << std::endl;

  start = clock();
  for (int i = 0; i < 10000; i++)
    z = mylib::det(m);
  end = clock();
  std::cout << (end - start) << std::endl;

  start = clock();
  for (int i = 0; i < 15000; i++)
    z = mylib::det(m);
  end = clock();
  std::cout << (end - start) << std::endl;

  start = clock();
  for (int i = 0; i < 20000; i++)
    z = mylib::det(m);
  end = clock();
  std::cout << (end - start) << std::endl;

  start = clock();
  for (int i = 0; i < 25000; i++)
    z = mylib::det(m);
  end = clock();
  std::cout << (end - start) << std::endl;

  start = clock();
  for (int i = 0; i < 30000; i++)
    z = mylib::det(m);
  end = clock();
  std::cout << (end - start) << std::endl;

  start = clock();
  for (int i = 0; i < 35000; i++)
    z = mylib::det(m);
  end = clock();
  std::cout << (end - start) << std::endl;

  start = clock();
  for (int i = 0; i < 40000; i++)
    z = mylib::det(m);
  end = clock();
  std::cout << (end - start) << std::endl;

  return 0;
}
