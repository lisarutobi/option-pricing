#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED

#include <vector>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>

template <typename T>
class BinaryTree {
private:
    int _depth;                        // Profondeur de l'arbre
    std::vector<std::vector<T>> _tree; // Structure de l'arbre
    T _S0;                             // Prix initial
    T _U;                              // Facteur de montée
    T _D;                              // Facteur de descente
    bool _parametersSet;               // Indicateur si les paramètres sont définis
    // Calcule automatiquement les valeurs si les paramètres sont définis
    void compute();

public:
    // Constructeur de la classe 
    BinaryTree();

    // Implémentation des méthodes de la classe BinaryTree
    // Définit la profondeur de l'arbre et initialise les nœuds
    void setDepth(int depth);

    // Définit les paramètres pour les calculs automatiques
    void setParameters(T S0, T U, T D);

    // Définit une valeur manuelle dans un nœud
    void setNode(int level, int index, const T& value);

    // Récupère une valeur d'un nœud
    T getNode(int level, int index) const;

    // Affiche l'arbre
    void display() const;
};

// === Implémentation des méthodes ===

// Constructeur
template <typename T>
BinaryTree<T>::BinaryTree() : _depth(0), _S0(0), _U(1.0), _D(1.0), _parametersSet(false) {}

// Définit la profondeur et initialise les niveaux
template <typename T>
void BinaryTree<T>::setDepth(int depth) {
    if (depth < 0) {
        throw std::invalid_argument("Depth must be non-negative.");
    }
    _depth = depth;
    _tree.resize(_depth + 1); // Redimensionne pour contenir `_depth` niveaux
    for (int i = 0; i <= _depth; ++i) {
        _tree[i].resize(i + 1, T{}); // Chaque niveau contient `i + 1` éléments
    }

    // Si les paramètres sont définis, calculer automatiquement
    if (_parametersSet) {
        compute();
    }
}

// Définit les paramètres pour les calculs automatiques
template <typename T>
void BinaryTree<T>::setParameters(T S0, T U, T D) {
    if (S0 <= 0 || D >= U || D <= 0 || U <= 0) {
        throw std::invalid_argument("Invalid parameters: Ensure S0 > 0, U > D > 0.");
    }
    _S0 = S0;
    _U = U;
    _D = D;
    _parametersSet = true; // Les paramètres sont maintenant définis

    // Recalculer les valeurs si la profondeur a déjà été définie
    if (_depth > 0) {
        compute();
    }
}

// Définit une valeur manuelle dans un nœud
template <typename T>
void BinaryTree<T>::setNode(int level, int index, const T& value) {
    if (level < 0 || level > _depth || index < 0 || index > level) {
        throw std::out_of_range("Index out of range in setNode.");
    }
    _tree[level][index] = value;
}

// Récupère une valeur d'un nœud
template <typename T>
T BinaryTree<T>::getNode(int level, int index) const {
    if (level < 0 || level > _depth || index < 0 || index > level) {
        throw std::out_of_range("Index out of range in getNode.");
    }
    return _tree[level][index];
}

// Affiche l'arbre
template <typename T>
void BinaryTree<T>::display() const {
    if (_depth == 0) {
        std::cout << "BinaryTree is empty." << std::endl;
        return;
    }

    int spacing = 4 * (_depth); // Espacement initial pour aligner les niveaux
    for (int level = 0; level <= _depth; ++level) {
        std::cout << std::string(spacing, ' '); // Espacement initial
        for (int index = 0; index <= level; ++index) {
            std::cout << std::setw(8) << _tree[level][index] << " ";
        }
        std::cout << std::endl;
        spacing -= 4; // Réduire l'espacement pour le niveau suivant
    }
}

// Calcule les valeurs des nœuds selon le modèle CRR
template <typename T>
void BinaryTree<T>::compute() {
    if (!_parametersSet) {
        throw std::logic_error("Parameters must be set before computing the tree.");
    }

    for (int n = 0; n <= _depth; ++n) {
        for (int i = 0; i <= n; ++i) {
            T up_factor = std::pow(_U, i);
            T down_factor = std::pow(_D, n - i);
            _tree[n][i] = _S0 * up_factor * down_factor;

            // Debugging output
            std::cout << "Node (" << n << ", " << i << "): " << _tree[n][i] << std::endl;
        }
    }
}

#endif // BINARYTREE_H_INCLUDED
