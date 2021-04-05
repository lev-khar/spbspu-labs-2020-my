#include <iostream>
#include <stdexcept>
#include <sstream>

void task1(std::istream&, std::ostream&);
void task2(std::istream&, std::ostream&);

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Wrong number of arguments";
      return 1;
    }
    std::istringstream taskNumberStream(argv[1]);
    size_t task = 0;
    taskNumberStream >> task;
    if (taskNumberStream.fail())
    {
      std::cerr << "Wrong task number";
      return 1;
    }

    switch (task)
    {
    case 1:
    {
      try
      {
        task1(std::cin, std::cout);
      }
      catch (const std::runtime_error& error)
      {
        std::cerr << error.what() << "\n";
        return 2;
      }
      break;
    }
    case 2:
    {
      try
      {
        task2(std::cin, std::cout);
      }
      catch (const std::runtime_error& error)
      {
        std::cerr << error.what() << "\n";
        return 2;
      }
      break;
    }
    default:
    {
      std::cerr << "Wrong task number";
      return 1;
    }
    }
  }
  catch (const std::exception& error)
  {
    std::cerr << "Unexpected error " << error.what() << "\n";
    return -1;
  }
  return 0;
}
