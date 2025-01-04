cmake_minimum_required(VERSION 3.29)
project(TspSA)

set(CMAKE_CXX_STANDARD 20)

add_executable(TspSA main.cpp
        TspAlgoBase/SimulatedAnnealing/TspSimulatedAnnealing.cpp
        TspAlgoBase/SimulatedAnnealing/TspSimulatedAnnealing.h
        Graph/AsymmetricalGraph.cpp
        Graph/AsymmetricalGraph.h
        Graph/Graph.cpp
        Graph/Graph.h
        Graph/SymmetricalGraph.cpp
        Graph/SymmetricalGraph.h
        TspAlgoBase/NearestNeighbour/TspNearestNeighbour.cpp
        TspAlgoBase/NearestNeighbour/TspNearestNeighbour.h
        TspAlgoBase/TspAlgoBase.cpp
        TspAlgoBase/TspAlgoBase.h
        TspAlgoBase/SimulatedAnnealing/StateGenStrategy/StateGenStrategy.cpp
        TspAlgoBase/SimulatedAnnealing/StateGenStrategy/StateGenStrategy.h
        TspAlgoBase/SimulatedAnnealing/StateGenStrategy/SwapStateGenStrategy.cpp
        TspAlgoBase/SimulatedAnnealing/StateGenStrategy/SwapStateGenStrategy.h
        TspAlgoBase/SimulatedAnnealing/StateGenStrategy/ReverseStateGenStrategy.cpp
        TspAlgoBase/SimulatedAnnealing/StateGenStrategy/ReverseStateGenStrategy.h
        TspAlgoBase/SimulatedAnnealing/StateGenStrategy/InsertStateGenStrategy.cpp
        TspAlgoBase/SimulatedAnnealing/StateGenStrategy/InsertStateGenStrategy.h
        TspAlgoBase/SimulatedAnnealing/TemperatureCoolingStrategy/TemperatureCoolingStrategy.cpp
        TspAlgoBase/SimulatedAnnealing/TemperatureCoolingStrategy/TemperatureCoolingStrategy.h
        TspAlgoBase/SimulatedAnnealing/TemperatureCoolingStrategy/LinearCoolingStrategy.cpp
        TspAlgoBase/SimulatedAnnealing/TemperatureCoolingStrategy/LinearCoolingStrategy.h
        TspAlgoBase/SimulatedAnnealing/TemperatureCoolingStrategy/GeometricCoolingStrategy.cpp
        TspAlgoBase/SimulatedAnnealing/TemperatureCoolingStrategy/GeometricCoolingStrategy.h
)
