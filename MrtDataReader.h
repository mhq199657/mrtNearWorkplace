#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
class MrtDataReader {
  public:
  MrtDataReader(const std::string& fileName) : fileName_(fileName), file_(fileName_.c_str()) {
  }
  bool hasNext() const {
    return !file_.eof();
  }
  std::string getLine() {
    std::string ret;
    std::getline(file_, ret);
    return ret;
  }
  std::vector<std::string> getStationNames() {
    std::string curr;
    std::vector<std::string> ret;
    while(true) {
      std::getline(file_, curr);
      if (curr == "~") {
        break;
      }
      ret.push_back(curr);
    }
    return ret;
  }
  private:
  std::string fileName_;
  std::ifstream file_;
};