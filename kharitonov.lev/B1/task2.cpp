#include <fstream>
#include <memory>
#include <stdexcept>
#include <vector>

#include "auxiliary.hpp"
#include "access.hpp"

void task2(const char* fileName) 
{
  if (fileName == nullptr)
  {
    throw std::runtime_error("Empty file name");
  }
  std::ifstream inFile(fileName);
  if (!inFile) 
  {
    throw std::runtime_error("File unavaliable");
  }

  size_t arraySize = 1;
  size_t elementsCount = 0;
  std::unique_ptr<char[], decltype(&free)> array(static_cast<char*>(malloc(arraySize)), &free);

  if (!array) 
  {
    throw std::bad_alloc();
  }
  while (inFile) {
    inFile.read(&array[elementsCount], arraySize - elementsCount);
    elementsCount += inFile.gcount();

    if (elementsCount >= arraySize)
    {
      arraySize *= 2;
      std::unique_ptr<char[], decltype(&free)> newArray(static_cast<char*>(realloc(array.get(), arraySize)), &free);
      if (!newArray)
      {
        throw std::bad_alloc();
      }
      array.swap(newArray);
      newArray.release();
    }
  }

  if (elementsCount)
  {
    std::vector<char> vector(array.get(), array.get() + elementsCount);

    print(vector, "");
  }
}
