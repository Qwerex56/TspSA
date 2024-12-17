//
// Created by qwere on 11.12.2024.
//

#ifndef TSPSA_TSPALGOBASE_SIMULATEDANNEALING_TSPSIMULATEDANNEALING_H_
#define TSPSA_TSPALGOBASE_SIMULATEDANNEALING_TSPSIMULATEDANNEALING_H_

#import "../TspAlgoBase.h"
#include "../NearestNeighbour/TspNearestNeighbour.h"

namespace pea_tsp::algo {

class TspSimulatedAnnealing : public TspAlgoBase {
 public:
  TspSimulatedAnnealing() = default;
  [[maybe_unused]] explicit TspSimulatedAnnealing(const std::string &conf_path,
                                         const std::string &graph_conf_path = "");

  [[nodiscard]] std::vector<int> FindSolution() const override;

 private:
  TspNearestNeighbour nn_algorithm;

  float acceptance_probability = 0.8f;
  float cooling_rate = 0.99f;
  int reheat_rate = 25;

  [[nodiscard]] std::vector<int> GetFirstState() const;
  [[nodiscard]] float CalcFirstTemperature(float desired_acceptance, int max_iterations) const;
  [[nodiscard]] int CalcStateFit(const std::vector<int>& state) const;
  [[nodiscard]] float CalcAcceptanceProbability(const std::vector<int> &current_state,
                                  const std::vector<int> &proposed_state,
                                  float temperature) const;

  [[nodiscard]] static std::vector<int> GetNextState(const std::vector<int> &current_state) ;
};

} // algo
// pea_tsp

#endif //TSPSA_TSPALGOBASE_SIMULATEDANNEALING_TSPSIMULATEDANNEALING_H_
