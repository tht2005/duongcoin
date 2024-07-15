#ifndef RABIN_MILLER_HPP
#define RABIN_MILLER_HPP

#include <cstdint>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>

#include "modint.hpp"

namespace rabin_miller {

bool primality_test(uint64_t n);

}

#endif
