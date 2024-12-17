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
)
