#ifndef _COMMANDS_H
#define _COMMANDS_H

#include <algorithm>
#include <string>
#include <functional>
#include <numeric>
#include <vector>
#include <iostream>

#include "geometry.h"
#include "io.h"

namespace berdyanskij
{
  void area(const std::vector<Polygon> &data);
  void min(const std::vector<Polygon> &data);
  void max(const std::vector<Polygon> &data);
  void count(const std::vector<Polygon> &data);
  void rmecho(std::vector<Polygon> &data);
  void inframe(std::vector<Polygon> &value);
}
#endif
