//*******************************************************//
// Définition des fonctions de la bibliothèque executeur //
//*******************************************************//

// Include
#include "executeur.h"

/**
 * Pointeur de fonction qui fait appel à ext_in
*/
void *exec_in(void *args) {
    args_tunnel *donnees = (args_tunnel*)args;

    ext_in(donnees->tunfd, donnees->hote, donnees->port);

    return NULL;
}

/**
 * Pointeur de fonction qui fait appel à ext_out
*/
void *exec_out(void *args) {
    args_tunnel *donnees = (args_tunnel*)args;

    ext_out(donnees->tunfd, donnees->port);

    return NULL;
}