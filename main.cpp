#include <iostream>
#include "TspAlgoBase/SimulatedAnnealing/TspSimulatedAnnealing.h"

int main() {
  auto solution = pea_tsp::algo::TspSimulatedAnnealing("./conf.txt", "./fm11_0.atsp").FindSolution();
  return 0;
}
