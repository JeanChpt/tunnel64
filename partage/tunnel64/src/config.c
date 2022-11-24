//*****************************************************//
// Définition des fonctions de configuration du tunnel //
//*****************************************************//

// Includes
#include "config.h"


/**
 * Fonction de lecture des paramètres du tunnel dans le fichier tunnel64.conf
*/
args_config saisie_config(char* conf) {
    printf("Debut");
    args_config args;
    char c = EOF;
    FILE* f;

    // Patterns à reconnaître dans le fichier
    char* patterns[] = {
        "tun=%s\n",
        "inport=%s\n",
        "outip=%s\n",
        "outport=%s\n",
    };

    // Valeurs récupérées dans le fichier
    char* valeurs[] = {
        args.tun,
        args.inport,
        args.outip,
        args.outport
    };
    
    // Ouverture du fichier en lecture
    f = fopen(conf, "r");
    if (f == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier de configuration\n");
        exit(-1);
    } else {
        for(int i = 0; i < 4; i++){
          while(fscanf(f, patterns[i], valeurs[i]) != 1) {
            do {
                c = fgetc(f);
            } while (c != EOF && c != '\n');  
          }
        }
    }

   

    // Fermeture du fichier
    fclose(f);
    printf("Fin");
    return args;
}