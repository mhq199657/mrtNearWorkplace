#pragma once
#include <MrtStation.h>
#include <algorithm>
#include <optional>
#include <unordered_map>
#include <vector>
#include <MrtUtils.h>
#include <MrtDataReader.h>
#include <MrtResult.h>
#include <unordered_set>
#include <unordered_map>
class MrtGraph {
  public:
  using Index = unsigned;
    std::optional<MrtStation> getStation(const std::string& stationName) {
      auto it = std::find_if(stations_.cbegin(), 
                            stations_.cend(),
                            [&stationName](const MrtStation& s) {
                              return stationName == s.StationName;
                            });
      if (it != stations_.cend()) {
        return {*it};
      } else {
        return {};
      }
    }
    static MrtGraph fromFile(const std::string& file) {
      MrtDataReader reader(file);
      MrtGraph ret;
      while(reader.hasNext()) {
        Line line = MrtLineToEnumMapper::map(reader.getLine());
        std::vector<std::string> stationNames = reader.getStationNames();
        ret.addToAdjList(line, stationNames);
      }
      return ret;
    }
    std::vector<MrtResult> getFeasibleStations(const std::string& stationName, int tolerance);
  private:
    void addToAdjList(const Line, const std::vector<std::string>& stationNames);
    void dfs(const Index curr, std::vector<MrtResult>& result, int tolerance);
    void dfs(const Index curr, std::vector<MrtResult>& result, int tolerance, unsigned transitSoFar, Line currLine);
    std::vector<MrtStation> stations_; 

    std::vector<std::vector<Index>> adjList_;
    std::unordered_map<Index, std::unordered_set<Line>> visited_;
};