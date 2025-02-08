#pragma once
#include <random>

class MT {
private:
    static std::mt19937 rng; // D�claration de la variable statique
    MT() = default;

public:
    static double rand_unif(); // G�n�re un nombre uniforme U(0, 1)
    static double rand_norm(); // G�n�re un nombre normal N(0, 1)
};
