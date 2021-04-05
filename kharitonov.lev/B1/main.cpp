#include <iostream>
#include <stdexcept>
#include <ctime>
#include <sstream>
#include <cstring>
#include "auxiliary.hpp"

void task1(std::function<bool(const int&, const int&)> comparator);
void task2(const char* fileName);
void task3();
void task4(std::function<bool(const double&, const double&)> comparator, const size_t size);


int main(int argc, char* argv[])
{
  try
  {
    if (argc <= 1) {
      std::cerr << "Wrong number of arguments";
      return 1;
    }
    std::srand(std::time(0));
    std::istringstream taskNumberStream(argv[1]);
    size_t task = 0;
    taskNumberStream >> task;
    if (taskNumberStream.fail()) {
      std::cerr << "Wrong task number";
      return 1;
    }

    switch (task) {
    case 1: {
      if (argc != 3) {
        std::cerr << "Wrong number of arguments";
        return 1;
      }
      try
      {
        auto comparator = orderComparator<int>(argv[2]);
        task1(comparator);
      }
      catch (const std::runtime_error& error) {
        std::cerr << error.what() << "\n";
        return 2;
      }
      catch (const std::invalid_argument& error) {
        std::cerr << error.what() << "\n";
        return 1;
      }
      break;
    }

    case 2: {
      if (argc != 3) {
        std::cerr << "Wrong number of arguments";
        return 1;
      }

      if (strlen(argv[2]) == 0) {
        std::cerr << "Wrong file name";
        return 1;
      }
      try
      {
        task2(argv[2]);
      }
      catch (const std::bad_alloc& error) {
        std::cerr << "Allocation error: " << error.what() << "\n";
        return 2;
      }
      catch (const std::runtime_error& error) {
        std::cerr << error.what() << "\n";
        return 2;
      }
      break;
    }

    case 3: {
      if (argc != 2) {
        std::cerr << "Wrong number of arguments";
        return 1;
      }
      try
      {
        task3();
      }
      catch (const std::runtime_error& error) {
        std::cerr << error.what() << "\n";
        return 2;
      }
      break;
    }

    case 4: {
      if (argc != 4) {
        std::cerr << "Wrong number of arguments";
        return 1;
      }
      std::istringstream arraySizeStream(argv[3]);
      size_t size = 0;
      arraySizeStream >> size;
      if (arraySizeStream.fail()) {
        std::cerr << "Wrong task number";
        return 1;
      }
      try
      {
        auto comparator = orderComparator<double>(argv[2]);
        task4(comparator, size);
      }
      catch (const std::invalid_argument& error) {
        std::cerr << error.what() << "\n";
        return 1;
      }
      break;
    }
    default: {
      std::cerr << "Wrong task number";
      return 1;
    }
    }
  }
  catch (const std::exception& error) {
    std::cerr << "Unexpected error" << error.what() << "\n";
    return -1;
  }
  return 0;
}
