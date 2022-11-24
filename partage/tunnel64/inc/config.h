//******************************************************//
// Déclaration des fonctions de configuration du tunnel //
//******************************************************//

#ifndef CONFIG_H
#define CONFIG_H

// Includes
#include <stdlib.h>
#include <stdio.h>
#include "donnees.h"

/**
 * Fonction de lecture des paramètres du tunnel dans le fichier tunnel64.conf
*/
args_config saisie_config(char* conf);

#endif