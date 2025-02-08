#pragma once
#include <random>

class MT {
private:
    static std::mt19937 rng; // Déclaration de la variable statique
    MT() = default;

public:
    static double rand_unif(); // Génère un nombre uniforme U(0, 1)
    static double rand_norm(); // Génère un nombre normal N(0, 1)
};
