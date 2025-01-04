//
// Created by qwere on 26.12.2024.
//

#ifndef TSPSA_TSPALGOBASE_SIMULATEDANNEALING_TEMPERATURECOOLINGSTRATEGY_LINEARCOOLINGSTRATEGY_H_
#define TSPSA_TSPALGOBASE_SIMULATEDANNEALING_TEMPERATURECOOLINGSTRATEGY_LINEARCOOLINGSTRATEGY_H_

#include "TemperatureCoolingStrategy.h"
namespace pea_tsp::algo::sa_helpers {

class LinearCoolingStrategy : public TemperatureCoolingStrategy {
 public:
  LinearCoolingStrategy() = default;
  explicit LinearCoolingStrategy(float cooling_factor);

  float operator()(float current_temperature) final;
};

} // sa_helpers
// algo
// pea_tsp

#endif //TSPSA_TSPALGOBASE_SIMULATEDANNEALING_TEMPERATURECOOLINGSTRATEGY_LINEARCOOLINGSTRATEGY_H_
