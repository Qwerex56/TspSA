//
// Created by qwere on 26.12.2024.
//

#include "LinearCoolingStrategy.h"

namespace pea_tsp::algo::sa_helpers {

LinearCoolingStrategy::LinearCoolingStrategy(float cooling_factor) : TemperatureCoolingStrategy(cooling_factor) { }

float LinearCoolingStrategy::operator()(float current_temperature) {
  return current_temperature - cooling_factor_;
}

} // sa_helpers
// algo
// pea_tsp