//
// Created by qwere on 25.12.2024.
//

#ifndef TSPSA_TSPALGOBASE_SIMULATEDANNEALING_STATEGENSTRATEGY_STATEGENSTRATEGY_H_
#define TSPSA_TSPALGOBASE_SIMULATEDANNEALING_STATEGENSTRATEGY_STATEGENSTRATEGY_H_

#include <vector>
namespace pea_tsp::algo::sa_helpers {

class StateGenStrategy {
 public:
  StateGenStrategy() = default;

  virtual std::vector<int> operator()(const std::vector<int> &current_state) const = 0;

 protected:
  [[nodiscard]] static int RandNumber(int min, int max);
  [[nodiscard]] static inline int RandNumber(int max) {
    return RandNumber(0, max);
  }
};

} // sa_helpers
// algo
// pea_tsp

#endif //TSPSA_TSPALGOBASE_SIMULATEDANNEALING_STATEGENSTRATEGY_STATEGENSTRATEGY_H_
