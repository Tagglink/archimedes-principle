#ifndef STUDENT_RANDOM_H
#define STUDENT_RANDOM_H

#include <random>

namespace student::random {

extern std::default_random_engine generator;

extern auto Range(int min, int max) -> int;

}

#endif