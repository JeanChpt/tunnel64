//********************************************************//
// Déclaration des fonctions de la bibliothèque executeur //
//********************************************************//

#ifndef EXECUTEUR_H
#define EXECUTEUR_H

// Includes
#include "donnees.h"
#include "extremite.h"

/**
 * Pointeur de fonction qui fait appel à ext_in
*/
void *exec_in(void *args);

/**
 * Pointeur de fonction qui fait appel à ext_out
*/
void *exec_out(void *args);

#endif