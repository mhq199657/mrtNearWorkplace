#pragma once
#include <vector>
#include <MrtResult.h>
#include <iostream>
class MrtResultDisplayer {
  public:
  static void displayPossibleStations(const std::vector<MrtResult>& results) {
    for (const auto& result : results) {
      std::cout << result << '\n';
    }
  }
};