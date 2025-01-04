//
// Created by qwere on 25.12.2024.
//

#include "SwapStateGenStrategy.h"

namespace pea_tsp::algo::sa_helpers {

std::vector<int> SwapStateGenStrategy::operator()(const std::vector<int> &current_state) const {
  auto next_state = std::vector<int>(current_state.size());

  std::copy(current_state.begin(), current_state.end(), next_state.begin());

  auto n_one = RandNumber((int)current_state.size() - 1);
  auto n_two = RandNumber((int)current_state.size() - 1);

  while (n_one == n_two) {
    n_two = RandNumber((int)current_state.size() - 1);
  }

  if (n_one > n_two) {
    auto temp = n_one;
    n_one = n_two;
    n_two = temp;
  }

  std::iter_swap(next_state.begin() + n_one, next_state.begin() + n_two);

  return next_state;
}

} // sa_helpers
// algo
// pea_tsp