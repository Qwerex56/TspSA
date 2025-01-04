//
// Created by qwere on 11.12.2024.
//

#include <cmath>
#include <numeric>
#include <random>
#include <iostream>
#include <fstream>

#include "TspSimulatedAnnealing.h"
#include "StateGenStrategy/SwapStateGenStrategy.h"
#include "TemperatureCoolingStrategy/GeometricCoolingStrategy.h"
#include "TemperatureCoolingStrategy/LinearCoolingStrategy.h"
#include "StateGenStrategy/ReverseStateGenStrategy.h"
#include "StateGenStrategy/InsertStateGenStrategy.h"

namespace pea_tsp::algo {

TspSimulatedAnnealing::TspSimulatedAnnealing(const std::string &conf_path, const std::string &graph_conf_path)
    : TspAlgoBase(conf_path, graph_conf_path) {
  auto file = std::fstream{conf_path};

  if (!file.is_open()) {
    std::cout << "Could not open config file\n";
  } else {
    std::string line;
    std::string graph_config;

    while (!file.eof()) {
      std::getline(file, line);

      std::stringstream str_stream{line};
      std::string token;
      std::vector<std::string> tokens;

      while (std::getline(str_stream, token, '=')) {
        tokens.emplace_back(token);
      }

      if (tokens[0] == "acceptance_probability") {
        acceptance_probability_ = std::stof(tokens[1]);
      } else if (tokens[0] == "cooling_rate") {
        cooling_rate_ = std::stof(tokens[1]);
      } else if (tokens[0] == "end_temperature") {
        end_temperature_ = std::stof(tokens[1]);
      } else if (tokens[0] == "iterations_per_temperature") {
        iterations_per_temperature_ = std::stoi(tokens[1]);
      } else if (tokens[0] == "temp_strategy") {
        switch (std::stoi(tokens[1])) {
          case 0:
            temperature_cooling_strategy_ = new sa_helpers::LinearCoolingStrategy(cooling_rate_);
            std::cout << "Linear cooling\n";
            break;
          case 1:
          default:
            temperature_cooling_strategy_ = new sa_helpers::GeometricCoolingStrategy(cooling_rate_);
            std::cout << "Geometric cooling\n";
            break;
        }
      } else if (tokens[0] == "gen_strategy") {
        switch (std::stoi(tokens[1])) {
          case 0:
            state_gen_strategy_ = new sa_helpers::SwapStateGenStrategy();
            std::cout << "Swap gen\n";
            break;
          case 1:
            state_gen_strategy_ = new sa_helpers::ReverseStateGenStrategy();
            std::cout << "Reverse gen\n";

            break;
          case 2:
            state_gen_strategy_ = new sa_helpers::InsertStateGenStrategy();
            std::cout << "Insert gen\n";

            break;
          default:
            state_gen_strategy_ = new sa_helpers::SwapStateGenStrategy();
            std::cout << "Swap gen\n";

            break;
        }
      } else if (tokens[0] == "use_nn_as_bound") {
        auto do_use_nn = std::stoi(tokens[1]);
        if (do_use_nn == 1) {
          nn_algorithm = new TspNearestNeighbour(conf_path, false, graph_conf_path);
          std::cout << "Use nn\n";
        } else {
          nn_algorithm = nullptr;
          std::cout << "Use random\n";
        }
      }
    }
  }
}

std::vector<int> TspSimulatedAnnealing::FindSolution() const {
  const auto initial_temperature = CalcFirstTemperature(acceptance_probability_, 100);
  auto temperature = initial_temperature;
  auto current_state = GetFirstState();
  current_state.pop_back();

  auto best_found_state = current_state;
  best_found_state.emplace_back(best_found_state.front());

  auto current_time{std::chrono::steady_clock::now()};
  const auto start_time{std::chrono::steady_clock::now()};

  auto rand_float = []() -> float {
    auto random_device = std::random_device{};
    auto gen = std::mt19937(random_device());
    auto r_dist = std::uniform_real_distribution<>(0.0f, 1.0f);

    return (float) r_dist(gen);
  };

  while (temperature > end_temperature_) {
    auto max_iterations = CalcIterationsPerTemperature(temperature, initial_temperature);

    for (auto iteration = 1; iteration <= max_iterations; ++iteration) {
      auto next_state = (*state_gen_strategy_)(current_state);

      current_state.emplace_back(current_state.front());
      next_state.emplace_back(next_state.front());

      auto current_fit = CalcStateFit(current_state);
      auto next_fit = CalcStateFit(next_state);

      auto distance_delta = next_fit - current_fit;
      auto acceptance_factor = CalcAcceptanceProbability(current_state, next_state, temperature);

      if (distance_delta < 0 || acceptance_factor >= rand_float()) {
        current_state = next_state;

        if (next_fit < CalcStateFit(best_found_state)) {
          best_found_state = current_state;
        }
      }

      current_state.pop_back();

      if (do_show_progress_) {
        std::cout << "Current weight: " << current_fit << "\tTemperature: " << temperature << "\tAcceptance factor: "
                  << acceptance_factor << "\n\t";
        for (const auto vert : current_state) {
          std::cout << vert << " ";
        }

        std::cout << "\nBest found:\n\t";
        for (const auto vert : best_found_state) {
          std::cout << vert << " ";
        }

        std::cout << current_state.front() << "\n\n";
      }

      current_time = std::chrono::steady_clock::now();

      if (std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count()
          >= max_time.count()) {
        std::cout << "Current weight: " << current_fit << "\tTemperature: " << temperature << "\tAcceptance factor: "
                  << acceptance_factor << "\n";
        goto END_ALGO;
      }
    }
    temperature = (*temperature_cooling_strategy_)(temperature);
  }

  END_ALGO:
  std::cout << "\tTemperature: " << temperature << "\n\t";
  std::cout << "\nCurrent found:\n\t";

  current_state.emplace_back(current_state.front());

  for (const auto vert : current_state) {
    std::cout << vert << " ";
  }
  std::cout << "\nPath weight: " << CalcStateFit(current_state);

  std::cout << "\nBest found:\n\t";
  for (const auto vert : best_found_state) {
    std::cout << vert << " ";
  }
  std::cout << "\nPath weight: " << CalcStateFit(best_found_state);

  std::cout << "\nCurrent result delta: " << GetResultDeviation(CalcStateFit(current_state))
            << "\n Percent diff: " << GetPercentDeviation(CalcStateFit(current_state)) << "%";
  std::cout << "\nBest result delta: " << GetResultDeviation(CalcStateFit(best_found_state))
            << "\n Percent diff: " << GetPercentDeviation(CalcStateFit(best_found_state)) << "%";

  return current_state;
}

std::vector<int> TspSimulatedAnnealing::GetFirstState() const {
  if (nn_algorithm != nullptr) {
    return nn_algorithm->FindSolution();
  }

  std::random_device rd;
  std::mt19937 g(rd());

  auto state = std::vector<int>(graph_->GetDimension());
  std::iota(state.begin(), state.end(), 1);
  std::shuffle(state.begin(), state.end(), g);

  return state;
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

      auto next_state = (*state_gen_strategy_)(state);

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

int TspSimulatedAnnealing::CalcIterationsPerTemperature(float current_temperature, float initial_temperature) const {
  auto base_iterations = graph_->GetDimension() * iterations_per_temperature_;
  auto adjusted_iterations = (float) base_iterations * (current_temperature / initial_temperature);

  if (adjusted_iterations < 1.0f) {
    adjusted_iterations = 1.0f;
  }

  return (int) adjusted_iterations;
}

} // algo
// pea_tsp