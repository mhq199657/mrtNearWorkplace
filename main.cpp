#include <MrtGraph.h>
#include <string>
#include <iostream>
#include <MrtResultDisplayer.h>
static const std::string MRT_DATA = "./mrt";
const std::vector<std::string> MrtLineToEnumMapper::lines {"CC", "NE", "NS", "DT", "EW", "CG", "CE"};
int main()
{
  auto mrtGraph = MrtGraph::fromFile(MRT_DATA);
  std::string mrtStation;
  int stops;
  while (true) {
    std::cout << "Enter MRT Station as src: ";
    std::cin >> mrtStation;
    std::cout << "How many stops can you tolerate? Enter a positive integer: ";
    std::cin >> stops;
    auto possibleStations = mrtGraph.getFeasibleStations(mrtStation, stops);
    MrtResultDisplayer::displayPossibleStations(possibleStations);
  }
}