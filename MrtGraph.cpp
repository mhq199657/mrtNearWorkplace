#include <MrtGraph.h>
void MrtGraph::addToAdjList(const Line line, const std::vector<std::string>& stationNames) {
  Index prevIndex = -1;
  for (const auto& stationName: stationNames) {
    auto it = std::find_if (stations_.begin(),
                            stations_.end(), [&stationName](const MrtStation& s) {
                              return s.StationName == stationName; 
                            });
    Index index;
    if (it != stations_.end()) {
      index = it - stations_.begin();
      MrtStation& curr = *it;
      curr.Lines.push_back(line);
      curr.IsTransit = true;
    } else {
      index = stations_.size();
      MrtStation newStation {
        .IsTransit = false,
        .StationName = stationName,
        .Lines = {line},
      };
      stations_.push_back(newStation);
      adjList_.push_back({});
    }
    if (prevIndex != -1) {
      adjList_[prevIndex].push_back(index);
      adjList_[index].push_back(prevIndex);
    }
    prevIndex = index;
  }
}
std::vector<MrtResult> MrtGraph::getFeasibleStations(const std::string& stationName, int tolerance) {
  auto it = std::find_if (stations_.begin(),
                          stations_.end(), [&stationName](const MrtStation& s) {
                            return s.StationName == stationName; 
                          });
  assert(it != stations_.end());
  Index src = it - stations_.begin();
  std::vector<MrtResult> ret;
  dfs(src, ret, tolerance);
  return ret;
}
void MrtGraph::dfs(const Index curr, std::vector<MrtResult>& result, int tolerance) {
  for (const auto line: stations_[curr].Lines) {
    dfs(curr, result, tolerance, 1, line);
  }
}
void MrtGraph::dfs(const Index curr, std::vector<MrtResult>& result, int tolerance, unsigned transitSoFar, Line currLine) {
  if (tolerance < 0) {
    return;
  }
  if (visited_.find(curr) != visited_.end()) {
    if (visited_.at(curr).find(currLine) != visited_.at(curr).end()) {
      return;
    } else {
      visited_.at(curr).insert(currLine);
    }
  } else {
    result.push_back({stations_[curr].StationName, transitSoFar});
    visited_.insert({curr, {currLine}});
  }
  for (const auto dest: adjList_[curr]) {
    const auto& destLines = stations_[dest].Lines;
    if (std::find(destLines.begin(), destLines.end(), currLine) != destLines.end()) {
      // we should not change line
      dfs(dest, result, tolerance - 1, transitSoFar, currLine);
    }else { 
      for (const auto& destLine: destLines) {
        dfs(dest, result, tolerance - 1, transitSoFar + 1, destLine);
      }
    }
  }
}
