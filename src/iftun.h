/**
 * Bibliothèque de fonctions iftun
 */

#ifndef IFTUN_H
#define IFTUN_H

/**
 * Includes
 */
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
 * Déclaration des fonctions de l bibliothèque
 */

/**
 * Fonction permettant la création de l'interface virtuelle dont le nom est passé en paramètres
 * @param dev Nom de l'interface à créer (par exemple tun0)
 * @return Le descripteur de fichier permettantla lecture sur cette interface
 */
int tun_alloc(char* dev);

/**
 * Fonction permettant le transfert des bits lus sur src vers dest
 * @param src Le descripteur de fichier en lecture
 * @param dest Le descripteur de fichier en écriture
 */
void transfert(int src, int dest);

#endif