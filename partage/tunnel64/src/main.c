//*******************************************//
// Fonction principale du programme tunnel64 //
//*******************************************//

// Includes
#include "iftun.h"
#include "config.h"
#include "donnees.h"
#include "executeur.h"

#include <pthread.h>

/**
 * Fonction principale du programme tunnel64
 * @param argc Le nombre d'arguments du programme
 * @param argv Les arguments d'appel du programme
*/
int main (int argc, char** argv){
    /*if (argc != 4){
        printf("Utilisation : ./tunnel64 nom_interface ip_extremite port\n");
    } else {
        if (!argv[1]) {
            printf("Merci de definir un nom pour l'interface virtuelle TUN. (ex. tun0)\n");
        } else {*/
            int tunfd;
            pthread_t client, serveur;
            args_tunnel args_in, args_out;
            args_config conf = saisie_config("/vagrant/tunnel64.conf");
            printf("Creation de %s\n",argv[1]);
            tunfd = tun_alloc(argv[1]);
            printf("Application de la configuration de %s contenue dans le script configure-tun.sh...\n",argv[1]);
            printf("Appuyez sur une touche pour continuer\n");
            getchar();
            system("/bin/bash ./scripts/configure-tun.sh");
            printf("Interface %s configuree:\n",argv[1]);
            system("ip addr");

            args_in.tunfd = tunfd;
            args_in.port = conf.inport;
            pthread_create(&serveur, NULL, exec_in, (void *)&args_in);
            printf("Appuyez sur une touche pour connecter le client\n");
            getchar();

            args_out.tunfd = tunfd;
            args_out.hote = conf.outip;
            args_out.port = conf.outport;
            pthread_create(&client, NULL, exec_out, (void *)&args_out);
            printf("Appuyez sur une touche pour arreter le client\n");
            getchar();
            
            pthread_join(client, NULL);
            printf("Appuyez sur une touche pour arreter le serveur\n");
            getchar();
            pthread_join(serveur, NULL);
    //     } 
    // }

    return 0;
}