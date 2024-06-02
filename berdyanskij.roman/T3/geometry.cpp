#include "geometry.h"

berdyanskij::Triangle::Triangle(const Point &a, const Point &b, const Point &c)
{
  this->a = a;
  this->b = b;
  this->c = c;
}

double berdyanskij::getDistance(const berdyanskij::Point &p1, const berdyanskij::Point &p2)
{
  int dx = p1.x - p2.x;
  int dy = p1.y - p2.y;
  return std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
}

double berdyanskij::Triangle::getArea() const
{
  double x = getDistance(a, b);
  double y = getDistance(a, c);
  double z = getDistance(b, c);
  double p = (x + y + z) / 2;
  return std::sqrt(p * (p - x) * (p - y) * (p - z));
}

double berdyanskij::Polygon::getArea() const
{
  berdyanskij::Point fixed = points[0], first = points[1];

  double square = std::accumulate(
      points.begin() + 2,
      points.end(),
      0.0,
      [fixed, &first](double accumulator, berdyanskij::Point second)
      {
        accumulator += Triangle(fixed, first, second).getArea();
        first = second;
        return accumulator;
      }
  );
  return square;
}

bool berdyanskij::Polygon::operator<(const Polygon &other) const
{
  return getArea() < other.getArea();
}

bool berdyanskij::Polygon::operator==(const Polygon &otherEl) const
{
  if (points.size() != otherEl.points.size())
  {
    return false;
  }
  for (size_t i = 0; i < this->points.size(); i++)
  {
    if (points[i] != otherEl.points[i])
    {
      return false;
    }
  }
  return true;
}

bool berdyanskij::Polygon::operator!=(const Polygon &other) const
{
  return !(*this == other);
}

bool berdyanskij::Point::operator==(const Point &other) const
{
  return x == other.x && y == other.y;
}

bool berdyanskij::Point::operator!=(const Point &other) const
{
  return !(*this == other);
}
