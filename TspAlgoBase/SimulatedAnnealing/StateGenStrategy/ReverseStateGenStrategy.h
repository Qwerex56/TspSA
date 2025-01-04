//
// Created by qwere on 25.12.2024.
//

#ifndef TSPSA_TSPALGOBASE_SIMULATEDANNEALING_STATEGENSTRATEGY_REVERSESTATEGENSTRATEGY_H_
#define TSPSA_TSPALGOBASE_SIMULATEDANNEALING_STATEGENSTRATEGY_REVERSESTATEGENSTRATEGY_H_

#include "StateGenStrategy.h"

namespace pea_tsp::algo::sa_helpers {

class ReverseStateGenStrategy : public StateGenStrategy {
 public:
  ReverseStateGenStrategy() = default;

  std::vector<int> operator()(const std::vector<int> &current_state) const final;
};

} // sa_helpers
// algo
// pea_tsp

#endif //TSPSA_TSPALGOBASE_SIMULATEDANNEALING_STATEGENSTRATEGY_REVERSESTATEGENSTRATEGY_H_
