#include "random.h"

namespace student::random {

// minimum inclusive, maximum exclusive
auto Range(int min, int max) -> int
{
  std::uniform_int_distribution<int> distribution(min, max - 1);
  return distribution(generator);
}

}  // namespace student::random