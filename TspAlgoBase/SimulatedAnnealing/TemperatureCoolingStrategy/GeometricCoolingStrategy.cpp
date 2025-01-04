//
// Created by qwere on 26.12.2024.
//

#include "GeometricCoolingStrategy.h"

namespace pea_tsp::algo::sa_helpers {

GeometricCoolingStrategy::GeometricCoolingStrategy(float cooling_factor) : TemperatureCoolingStrategy(cooling_factor) {
  if (cooling_factor_ > 1.0f) {
    cooling_factor_ = 1.0f;
  } else if (cooling_factor_ < 0.0f) {
    cooling_factor_ = 0.0f;
  }
}

float GeometricCoolingStrategy::operator()(float current_temperature) {
  return current_temperature * cooling_factor_;
}

} // sa_helpers
// algo
// pea_tsp