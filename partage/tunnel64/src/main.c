//*******************************************//
// Fonction principale du programme tunnel64 //
//*******************************************//

// Includes
#include "iftun.h"
#include "config.h"
#include "donnees.h"
#include "executeur.h"

#include <pthread.h>

#define CONFIG "/vagrant/tunnel64.conf"

/**
 * Fonction principale du programme tunnel64
*/
int main (void){
    printf("Début");
    int tunfd;
    pthread_t client, serveur;
    args_tunnel args_in, args_out;
    printf("Début");
    args_config conf = saisie_config(CONFIG);
    printf("Début");
    printf("Creation de %s\n",conf.tun);
    tunfd = tun_alloc(conf.tun);
    printf("Application de la configuration de %s contenue dans le script configure-tun.sh...\n",conf.tun);
    printf("Appuyez sur une touche pour continuer\n");
    getchar();
    system("/bin/bash /mnt/partage/tunnel64/scripts/configure-tun.sh");
    printf("Interface %s configuree:\n",conf.tun);
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

    return 0;
}