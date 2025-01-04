//
// Created by qwere on 26.12.2024.
//

#ifndef TSPSA_TSPALGOBASE_SIMULATEDANNEALING_TEMPERATURECOOLINGSTRATEGY_TEMPERATURECOOLINGSTRATEGY_H_
#define TSPSA_TSPALGOBASE_SIMULATEDANNEALING_TEMPERATURECOOLINGSTRATEGY_TEMPERATURECOOLINGSTRATEGY_H_

namespace pea_tsp::algo::sa_helpers {

class TemperatureCoolingStrategy {
 public:
  TemperatureCoolingStrategy() = default;
  explicit TemperatureCoolingStrategy(float cooling_factor);

  virtual float operator()(float current_temperature) = 0;

 protected:
  float cooling_factor_ = 0.0f;
};

} // sa_helpers
// algo
// pea_tsp

#endif //TSPSA_TSPALGOBASE_SIMULATEDANNEALING_TEMPERATURECOOLINGSTRATEGY_TEMPERATURECOOLINGSTRATEGY_H_
