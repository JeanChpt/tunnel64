//*****************************************************//
// Définition des fonctions de configuration du tunnel //
//*****************************************************//

// Includes
#include "config.h"


/**
 * Fonction de lecture des paramètres du tunnel dans le fichier tunnel64.conf
*/
args_config saisie_config(char* conf) {
    args_config args;
    FILE* f;
    char c;

    // Patterns à reconnaître dans le fichier
    char* patterns[] = {
        "tun=%s\n",
        "inport=%s\n",
        "options=%s\n",
        "outip=%s\n",
        "outport=%s\n",
    };

    // Valeurs récupérées dans le fichier
    char* valeurs[] = {
        args.tun,
        args.inport,
        args.options,
        args.outip,
        args.outport
    };
    
    f = fopen(conf, "r");
    if (f == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier de configuration");
        exit(-1);
    } else {
        do {
            while ((c = fgetc(f)) != '\n') {
                fscanf(conf, patterns, valeurs);
            }
        } while (c != EOF);
    }

    return args;
}