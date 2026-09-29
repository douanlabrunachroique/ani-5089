#include <iostream>

int main()
{
    std::cout << "Programme de test lance." << std::endl;

    int* pointeur = nullptr;

    // Plantage volontaire
    int valeur = *pointeur;

    std::cout << "Valeur : " << valeur << std::endl;

    return 0;
}
