// Protection contre les inclusions multiples du fichier d'en-tête
#ifndef CLIMAT_H // Si CLIMAT_H n'est pas défini
#define CLIMAT_H // Définir CLIMAT_H

// Inclusion du fichier d'en-tête contenant les définitions des structures utilisées
#include "structures.h" // Inclure le fichier structures.h

// Déclaration des fonctions pour gérer le climat
void avancerJour(Climat *climat); // Déclaration de la fonction avancerJour qui prend un pointeur sur Climat

void afficherClimat(const Climat *climat); // Déclaration de la fonction afficherClimat qui prend un pointeur constant sur Climat

// Fin de la protection contre les inclusions multiples
#endif // CLIMAT_H // Fin de la condition si CLIMAT_H n'est pas défini
