//
// Created by qwere on 11.12.2024.
//

#include <cmath>
#include <numeric>
#include <cmath>
#include <random>
#include <iostream>

#include "TspSimulatedAnnealing.h"

namespace pea_tsp::algo {

TspSimulatedAnnealing::TspSimulatedAnnealing(const std::string &conf_path, const std::string &graph_conf_path)
    : TspAlgoBase(conf_path, graph_conf_path) {
  nn_algorithm = TspNearestNeighbour(conf_path, false, graph_conf_path);
}

std::vector<int> TspSimulatedAnnealing::FindSolution() const {
  auto temperature = CalcFirstTemperature(0.8f, 25);
  auto current_state = GetFirstState();
  current_state.pop_back();

  auto rand_float = []() -> float {
    auto random_device = std::random_device{};
    auto gen = std::mt19937(random_device());
    auto r_dist = std::uniform_real_distribution<>(0.0f, 1.0f);

    return (float) r_dist(gen);
  };

  while (temperature > 0.1f) {
    auto next_state = GetNextState(current_state);

    current_state.emplace_back(current_state.front());
    next_state.emplace_back(next_state.front());

    auto current_fit = CalcStateFit(current_state);
    auto next_fit = CalcStateFit(next_state);

    auto distance_delta = next_fit - current_fit;
    auto acceptance_factor = CalcAcceptanceProbability(current_state, next_state, temperature);

    if (distance_delta < 0 || acceptance_factor >= rand_float()) {
      current_state = next_state;
    }

    current_state.pop_back();
    temperature *= cooling_rate;

    if (do_show_progress_) {
      std::cout << "Current weight: " << current_fit << "\tTemperature: " << temperature << "\tAcceptance factor: "
                << acceptance_factor << "\n\t";
      for (const auto vert : current_state) {
        std::cout << vert << " ";
      }
      std::cout << current_state.front() << "\n\n";
    }
  }

  return current_state;
}

std::vector<int> TspSimulatedAnnealing::GetFirstState() const {
  return nn_algorithm.FindSolution();
}

float TspSimulatedAnnealing::CalcFirstTemperature(float desired_acceptance, int max_iterations) const {
  auto predicted_temperature = 1000.f;
  auto total_acceptance = 0.0f;
  auto mean_acceptance = 0.0f;

  std::random_device rd;
  std::mt19937 g(rd());

  do {
    total_acceptance = 0.0f;

    for (auto i = 0; i < max_iterations; ++i) {
      auto state = std::vector<int>(graph_->GetDimension());
      std::iota(state.begin(), state.end(), 1);
      std::shuffle(state.begin(), state.end(), g);

      auto next_state = GetNextState(state);

      state.emplace_back(state.front());
      next_state.emplace_back(next_state.front());

      auto state_fit = (float) CalcStateFit(state);
      auto next_state_fit = (float) CalcStateFit(next_state);

      total_acceptance += (float) std::exp(-std::abs(next_state_fit - state_fit) / predicted_temperature);
    }

    mean_acceptance = total_acceptance / (float) max_iterations;

    if ((desired_acceptance - mean_acceptance) > 0.005f) {
      auto accept_delta = std::max(1.0f + std::abs(desired_acceptance - mean_acceptance), 1.1f);
      predicted_temperature *= accept_delta;
    } else if ((desired_acceptance - mean_acceptance) < -0.005f) {
      auto accept_delta = std::max(1.0f + std::abs(desired_acceptance - mean_acceptance), 1.01f);
      predicted_temperature /= accept_delta;
    }

  } while (std::abs(desired_acceptance - mean_acceptance) > 0.01f);

  return predicted_temperature;
}

int TspSimulatedAnnealing::CalcStateFit(const std::vector<int> &state) const {
  return GetPathWeight(state);
}

float TspSimulatedAnnealing::CalcAcceptanceProbability(const std::vector<int> &current_state,
                                                       const std::vector<int> &proposed_state,
                                                       float temperature) const {
  auto current_state_fit = CalcStateFit(current_state);
  auto proposed_state_fit = CalcStateFit(proposed_state);

  auto delta = (float) std::abs(current_state_fit - proposed_state_fit);

  return std::exp(-delta / temperature);
}

std::vector<int> TspSimulatedAnnealing::GetNextState(const std::vector<int> &current_state) {
  auto random_device = std::random_device{};
  auto gen = std::mt19937(random_device());
  auto r_dist = std::uniform_int_distribution<>(0, (int) current_state.size() - 1);

  auto next_state = std::vector<int>(current_state.size());
  std::move(current_state.begin(), current_state.end(), next_state.begin());

  std::iter_swap(next_state.begin() + r_dist(gen), next_state.begin() + r_dist(gen));

  return next_state;
}

} // algo
// pea_tsp