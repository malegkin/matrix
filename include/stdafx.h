#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <array>
#include <stdexcept>
#include <tuple>


//simple blunt solution for output only in debug build
#ifdef DEBUG
#define dout std::cout
#else
#define dout 0 && std::cout
#endif
