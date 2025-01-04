//
// Created by qwere on 25.12.2024.
//

#include <random>
#include "StateGenStrategy.h"

namespace pea_tsp::algo::sa_helpers {

int StateGenStrategy::RandNumber(int min, int max) {
  if (min > max) {
    auto temp = min;
    min = max;
    max = temp;
  }

  auto random_device = std::random_device{};
  auto gen = std::mt19937(random_device());
  auto r_dist = std::uniform_int_distribution<>(min, max);

  return r_dist(gen);
}
} // sa_helpers
// algo
// pea_tsp