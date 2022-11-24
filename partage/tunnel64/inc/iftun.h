//****************************************************//
// Déclaration des fonctions de la bibliothèque iftun //
//****************************************************//

#ifndef IFTUN_H
#define IFTUN_H

// Includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h> 
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>

/**
 * Fonction qui crée une interface virtuelle dont le nom est passé en paramètres
 * @param dev Le nom de l'interface à créer
 * @return Le descripteur de fichier qui permet la lecture/écriture sur l'interface
*/
int tun_alloc(char *dev);

/**
 * Fonction qui permet le transfert de ce qui est lu sur src vers dest
 * @param src Le descripteur de fichier source
 * @param dest Le descripteur de fichier destination
*/
void transfert(int src, int dest);

#endif