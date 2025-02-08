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
    T _U;                              // Facteur de mont�e
    T _D;                              // Facteur de descente
    bool _parametersSet;               // Indicateur si les param�tres sont d�finis
    // Calcule automatiquement les valeurs si les param�tres sont d�finis
    void compute();

public:
    // Constructeur de la classe 
    BinaryTree();

    // Impl�mentation des m�thodes de la classe BinaryTree
    // D�finit la profondeur de l'arbre et initialise les n�uds
    void setDepth(int depth);

    // D�finit les param�tres pour les calculs automatiques
    void setParameters(T S0, T U, T D);

    // D�finit une valeur manuelle dans un n�ud
    void setNode(int level, int index, const T& value);

    // R�cup�re une valeur d'un n�ud
    T getNode(int level, int index) const;

    // Affiche l'arbre
    void display() const;
};

// === Impl�mentation des m�thodes ===

// Constructeur
template <typename T>
BinaryTree<T>::BinaryTree() : _depth(0), _S0(0), _U(1.0), _D(1.0), _parametersSet(false) {}

// D�finit la profondeur et initialise les niveaux
template <typename T>
void BinaryTree<T>::setDepth(int depth) {
    if (depth < 0) {
        throw std::invalid_argument("Depth must be non-negative.");
    }
    _depth = depth;
    _tree.resize(_depth + 1); // Redimensionne pour contenir `_depth` niveaux
    for (int i = 0; i <= _depth; ++i) {
        _tree[i].resize(i + 1, T{}); // Chaque niveau contient `i + 1` �l�ments
    }

    // Si les param�tres sont d�finis, calculer automatiquement
    if (_parametersSet) {
        compute();
    }
}

// D�finit les param�tres pour les calculs automatiques
template <typename T>
void BinaryTree<T>::setParameters(T S0, T U, T D) {
    if (S0 <= 0 || D >= U || D <= 0 || U <= 0) {
        throw std::invalid_argument("Invalid parameters: Ensure S0 > 0, U > D > 0.");
    }
    _S0 = S0;
    _U = U;
    _D = D;
    _parametersSet = true; // Les param�tres sont maintenant d�finis

    // Recalculer les valeurs si la profondeur a d�j� �t� d�finie
    if (_depth > 0) {
        compute();
    }
}

// D�finit une valeur manuelle dans un n�ud
template <typename T>
void BinaryTree<T>::setNode(int level, int index, const T& value) {
    if (level < 0 || level > _depth || index < 0 || index > level) {
        throw std::out_of_range("Index out of range in setNode.");
    }
    _tree[level][index] = value;
}

// R�cup�re une valeur d'un n�ud
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
        spacing -= 4; // R�duire l'espacement pour le niveau suivant
    }
}

// Calcule les valeurs des n�uds selon le mod�le CRR
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
