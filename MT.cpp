#include "MT.h"


std::mt19937 MT::rng(std::random_device{}());

// Implémentation de rand_unif
double MT::rand_unif() {
    static std::uniform_real_distribution<> dist(0.0, 1.0);
    return dist(rng);
}

// Implémentation de rand_norm
double MT::rand_norm() {
    static std::normal_distribution<> dist(0.0, 1.0);
    return dist(rng);
}
