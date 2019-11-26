#pragma once
#include <string>
#include <vector>
enum class Line : unsigned {
    CC,
    NE,
    NS,
    DT,
    EW,
    CG,
    CE,
};

struct MrtStation {
  bool IsTransit;
  std::string StationName;
  std::vector<Line> Lines;
  friend bool operator==(const MrtStation& here, const MrtStation& there) {
      return here.StationName == there.StationName;
  }
};

namespace std
{
    template <>
    struct hash<MrtStation>
    {
        size_t operator()(const MrtStation& obj) const
        {
            // Compute individual hash values for two data members and combine them using XOR and bit shifting
            return hash<std::string>()(obj.StationName);
        }
    };
}