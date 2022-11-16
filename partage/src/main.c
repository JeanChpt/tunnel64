//*******************************************//
// Fonction principale du programme tunnel64 //
//*******************************************//

// Includes
#include "iftun.h"

/**
 * Fonction principale du programme tunnel64
 * @param argc Le nombre d'arguments du programme
 * @param argv Les arguments d'appel du programme
*/
int main (int argc, char** argv){
    /*if (!argv[1]){
        printf("Utilisation : ./tunnel64 ___ <- nom de l'interface (ex. \"tun0\"\n");
    } else {*/
        int tunfd;
        printf("Création de %s\n",argv[1]);
        tunfd = tun_alloc(argv[1]);
        printf("Application de la configuration de %s contenue dans le script configure-tun.sh...\n",argv[1]);
        printf("Appuyez sur une touche pour continuer\n");
        getchar();
        system("/bin/bash ./scripts/configure-tun.sh");
        printf("Interface %s Configurée:\n",argv[1]);
        system("ip addr");
        transfert(tunfd, 1);
        printf("Appuyez sur une touche pour terminer\n");
        getchar();
    //}  

  return 0;
}