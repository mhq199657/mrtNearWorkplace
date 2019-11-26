#pragma once
#include <MrtStation.h>
#include <algorithm>
#include <cassert>
#include <iostream>
class MrtLineToEnumMapper {
  public:
    static Line map(const std::string& line) {
      auto it = std::find(lines.begin(), lines.end(), line);
      assert(it != lines.end());
      return static_cast<Line>(it - lines.begin());
    }
  private:
    static const std::vector<std::string> lines;
};