#include "commands.h"

using namespace std::placeholders;

void berdyanskij::area(const std::vector<Polygon>& data)
{
  auto accumalateArea_if = [](double ac, const berdyanskij::Polygon& poly, std::size_t mod2, std::size_t vertices)
    {
      if ((poly.points.size() % 2 == mod2) || (mod2 == 2 && poly.points.size() == vertices) || (mod2 == 3))
      {
        ac += poly.getArea();
      }
      return ac;
    };

  std::string it;
  std::cin >> it;
  if (it == "EVEN")
  {
    std::cout << std::accumulate(data.begin(), data.end(), 0.0,
      std::bind(accumalateArea_if, _1, _2, 0, 0)) << '\n';
  }
  else if (it == "ODD")
  {
    std::cout << std::accumulate(data.begin(), data.end(), 0.0,
      std::bind(accumalateArea_if, _1, _2, 1, 0)) << '\n';
  }
  else if (it == "MEAN" && data.size() != 0)
  {
    std::cout << std::accumulate(data.begin(), data.end(), 0.0,
      std::bind(accumalateArea_if, _1, _2, 3, 0)) / data.size() << std::endl;
  }
  else if (std::all_of(it.begin(), it.end(), isdigit) && stoi(it) > 2)
  {
    std::cout << std::accumulate(data.begin(), data.end(), 0.0,
      std::bind(accumalateArea_if, _1, _2, 2, stoi(it))) << '\n';
  }
  else
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
}

void berdyanskij::min(const std::vector<Polygon>& data)
{
  if (data.empty())
      throw std::runtime_error("<INVALID COMMAND>");

  std::string it;
  std::cin >> it;

  if (it == "AREA")
  {
    std::cout << std::min_element(data.begin(), data.end())->getArea() << '\n';
  }
  else if (it == "VERTEXES")
  {
    std::vector<std::size_t> sizes(data.size());

    std::cout << std::accumulate(
      data.begin() + 1,
      data.end(),
      data[0].points.size(),
      [](std::size_t min, const Polygon& poly)
      {
        return (poly.points.size() < min ? poly.points.size() : min);
      }
    ) << '\n';
  }
  else
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
}

void berdyanskij::max(const std::vector<Polygon>& data)
{
  if (data.empty())
    throw std::runtime_error("<INVALID COMMAND>");

  std::string it;
  std::cin >> it;

  if (it == "AREA")
  {
    std::cout << std::max_element(data.begin(), data.end())->getArea() << '\n';
  }
  else if (it == "VERTEXES")
  {
    std::vector<std::size_t> sizes(data.size());

    std::cout << std::accumulate(
      data.begin() + 1,
      data.end(),
      data[0].points.size(),
      [](std::size_t max, const Polygon& poly)
      {
        return (poly.points.size() > max ? poly.points.size() : max);
      }
    ) << '\n';
  }
  else
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
}

void berdyanskij::count(const std::vector<Polygon>& data)
{
  auto countPolygons_if = [](const berdyanskij::Polygon& poly, std::size_t mod2, std::size_t vertices)
    {
      return ((poly.points.size() % 2 == mod2) || (mod2 == 2 && poly.points.size() == vertices));
    };

  std::string it;
  std::cin >> it;
  if (it == "EVEN")
  {
    std::cout << std::count_if(data.begin(), data.end(),
      std::bind(countPolygons_if, _1, 0, 0)) << '\n';
  }
  else if (it == "ODD")
  {
    std::cout << std::count_if(data.begin(), data.end(),
      std::bind(countPolygons_if, _1, 1, 0)) << '\n';
  }
  else if (std::all_of(it.begin(), it.end(), isdigit) && stoi(it) > 2)
  {
    std::cout << std::count_if(data.begin(), data.end(),
      std::bind(countPolygons_if, _1, 2, stoi(it))) << '\n';
  }
  else
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
}

void berdyanskij::rmecho(std::vector<Polygon>& data)
{
  berdyanskij::Polygon targetPoly;
  std::cin >> targetPoly;
  if (std::cin.fail() || std::cin.get() != '\n')
    throw std::runtime_error("<INVALID COMMAND>");

  int removedCount = 0;
  auto it = data.begin();

  while (it != data.end())
  {
    if (*it == targetPoly)
    {
      auto nextIt = std::next(it);
      bool hasDuplicates = false;
      while (nextIt != data.end() && *nextIt == targetPoly)
      {
        nextIt = data.erase(nextIt);
        ++removedCount;
        hasDuplicates = true;
      }
      if (hasDuplicates)
      {
        ++removedCount;
        it = data.erase(it);
      }
      else
      {
        ++it;
      }
    }
    else
    {
      ++it;
    }
  }
  std::cout << removedCount << '\n';
}

void berdyanskij::inframe(const std::vector<Polygon>& data)
{
  berdyanskij::Polygon poly;
  std::cin >> poly;
  if (std::cin.fail() || std::cin.get() != '\n')
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
  berdyanskij::Frame frame = getFrame(data);
  std::cout << (frame.containsPolygon(poly) ? "<TRUE>" : "<FALSE>") << '\n';
}
