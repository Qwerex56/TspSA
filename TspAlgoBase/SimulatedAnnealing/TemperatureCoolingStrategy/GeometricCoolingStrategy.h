//
// Created by qwere on 26.12.2024.
//

#ifndef TSPSA_TSPALGOBASE_SIMULATEDANNEALING_TEMPERATURECOOLINGSTRATEGY_GEOMETRICCOOLINGSTRATEGY_H_
#define TSPSA_TSPALGOBASE_SIMULATEDANNEALING_TEMPERATURECOOLINGSTRATEGY_GEOMETRICCOOLINGSTRATEGY_H_

#include "TemperatureCoolingStrategy.h"

namespace pea_tsp::algo::sa_helpers {

class GeometricCoolingStrategy : public TemperatureCoolingStrategy {
 public:
  GeometricCoolingStrategy() = default;
  explicit GeometricCoolingStrategy(float cooling_factor);

  float operator()(float current_temperature) final;
};

} // sa_helpers
// algo
// pea_tsp

#endif //TSPSA_TSPALGOBASE_SIMULATEDANNEALING_TEMPERATURECOOLINGSTRATEGY_GEOMETRICCOOLINGSTRATEGY_H_
