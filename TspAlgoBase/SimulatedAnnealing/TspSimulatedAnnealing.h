//
// Created by qwere on 11.12.2024.
//

#ifndef TSPSA_TSPALGOBASE_SIMULATEDANNEALING_TSPSIMULATEDANNEALING_H_
#define TSPSA_TSPALGOBASE_SIMULATEDANNEALING_TSPSIMULATEDANNEALING_H_

#include "../TspAlgoBase.h"
#include "../NearestNeighbour/TspNearestNeighbour.h"
#include "./StateGenStrategy/StateGenStrategy.h"
#include "TemperatureCoolingStrategy/TemperatureCoolingStrategy.h"

namespace pea_tsp::algo {

class TspSimulatedAnnealing : public TspAlgoBase {
 public:
  TspSimulatedAnnealing() = default;
  [[maybe_unused]] explicit TspSimulatedAnnealing(const std::string &conf_path,
                                         const std::string &graph_conf_path = "");

  [[nodiscard]] std::vector<int> FindSolution() const override;

 private:
//--- From conf ---//
  TspNearestNeighbour *nn_algorithm = nullptr;

  float acceptance_probability_ = 0.0f;
  float cooling_rate_ = 0.0f;
  float end_temperature_ = 0.0f;
  int iterations_per_temperature_ = 0;

  sa_helpers::TemperatureCoolingStrategy *temperature_cooling_strategy_ = nullptr;
  sa_helpers::StateGenStrategy *state_gen_strategy_ = nullptr;
//-----------------//

  [[nodiscard]] int CalcIterationsPerTemperature(float current_temperature, float initial_temperature) const;
  [[nodiscard]] std::vector<int> GetFirstState() const;
  [[nodiscard]] float CalcFirstTemperature(float desired_acceptance, int max_iterations) const;
  [[nodiscard]] int CalcStateFit(const std::vector<int>& state) const;
  [[nodiscard]] float CalcAcceptanceProbability(const std::vector<int> &current_state,
                                  const std::vector<int> &proposed_state,
                                  float temperature) const;
};

} // algo
// pea_tsp

#endif //TSPSA_TSPALGOBASE_SIMULATEDANNEALING_TSPSIMULATEDANNEALING_H_
