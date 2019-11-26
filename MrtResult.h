#pragma once
#pragma once
#include <string>
#include <iostream>
struct MrtResult {
  std::string StationName;
  int NumTransitsRequired;
};

std::ostream& operator<<(std::ostream& os, const MrtResult& res);