//*************************************************************//
// Déclaration des structures de données nécessaires au tunnel //
//*************************************************************//

#ifndef DONNEES_H
#define DONNEES_H

/**
 * Pointeur de fonction qui fait appel à ext_in
*/
typedef struct {
    int tunfd;  // Descripteur de fichier de l'interface TUN
    char *hote; // Nom d'hôte de la machine ou se trouve la sortie du tunnel
    char *port; // Port d'écoute du serveur et port de connexion à la sortie du tunnel
} args_tunnel;

/**
 * Structure de donnée pour stocker les paramètres issus du fichier
*/
typedef struct {
    char* tun;
    char* inport;
    char* options;
    char* outip;
    char* outport;
} args_config;

#endif