#include <iostream>
#include <stdexcept>
#include <sstream>

void task(std::istream&, std::ostream&);

int main()
{
  try
  {
    task(std::cin, std::cout);
  }
  catch (const std::runtime_error& error) {
    std::cerr << error.what() << "\n";
    return 2;
  }
  catch (const std::exception& error) 
  {
    std::cerr << "Unexpected error" << error.what() << "\n";
    return -1;
  }
  return 0;
}
