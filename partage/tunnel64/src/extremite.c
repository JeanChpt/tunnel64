//*******************************************************//
// Définition des fonctions de la bibliothèque extremite //
//*******************************************************//

// Include
#include "extremite.h"
#include "iftun.h"

/**
 * Fonction qui permet de rediriger le flux de tun0 vers la socket
 * @param t Descripteur de fichier de l'interface tun0
 */
void ext_out(int t, char* hote, char* port)
{
    char ip[NI_MAXHOST];         // Adresse IPv4 en notation pointée
    struct addrinfo *resol;      // Structure pour la résolution de nom
    int s;                       // Descripteur de socket

    // Résolution de l'hôte
    if (getaddrinfo(hote, port, NULL, &resol) < 0)
    {
        perror("Résolution adresse");
        exit(2);
    }

    // On extrait l'adresse IP et on la stocke dans ip
    sprintf(ip, "%s", inet_ntoa(((struct sockaddr_in *)resol->ai_addr)->sin_addr));

    // Création de la socket, de type TCP / IPv4
    if ((s = socket(resol->ai_family, resol->ai_socktype, resol->ai_protocol)) < 0)
    {
        perror("Allocation de socket");
        exit(3);
    }
    fprintf(stderr, "Le numero de la socket est : %i\n", s);

    // Connexion au serveur
    // fprintf(stderr, "Essai de connexion à %s (%s) sur le port %s\n\n", hote, ip, port);
    while (connect(s, resol->ai_addr, sizeof(struct sockaddr_in)) < 0)
    {
        sleep(1);
        printf(".");
    }
    // Libération mémoire
    freeaddrinfo(resol);

    transfert(t, s);

    // Destruction de la socket
    close(s);

    // fprintf(stderr, "Fin de la session.\n");
}

/**
 * Fonction qui permet de rediriger le flux de la socket vers tun0
 */
void ext_in(int t, char* port)
{
    int s, n;                                         // Descripteurs de socket
    int len, on;                                      // Utilitaires divers
    struct addrinfo *resol;                           // Résolution
    struct addrinfo indic = {AI_PASSIVE,              // Toute interface
                             PF_INET, SOCK_STREAM, 0, // IP mode connecté
                             0, NULL, NULL, NULL};
    struct sockaddr_in client; // Adresse de socket du client
    int err;                   // Code d'erreur

    fprintf(stderr, "Ecoute sur le port %s\n", port);
    err = getaddrinfo(NULL, port, &indic, &resol);
    if (err < 0)
    {
        fprintf(stderr, "Résolution: %s\n", gai_strerror(err));
        exit(2);
    }

    // Création de la socket, de type TCP / IPv4
    if ((s = socket(resol->ai_family, resol->ai_socktype, resol->ai_protocol)) < 0)
    {
        perror("Allocation de socket");
        exit(3);
    }
    fprintf(stderr, "Le n° de la socket est : %i\n", s);

    // On rend le port réutilisable rapidement
    on = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    {
        perror("Option socket");
        exit(4);
    }
    // fprintf(stderr, "Option(s) OK!\n");

    // Association de la socket s à l'adresse obtenue par résolution
    if (bind(s, resol->ai_addr, sizeof(struct sockaddr_in)) < 0)
    {
        perror("bind");
        exit(5);
    }

    // Libération mémoire
    freeaddrinfo(resol);
    // fprintf(stderr, "bind!\n");

    // la socket est prête à recevoir
    if (listen(s, SOMAXCONN) < 0)
    {
        perror("Listen");
        exit(6);
    }
    // fprintf(stderr, "Listen !\n");

    // Attendre et gérer indéfiniment les connexions entrantes
    len = sizeof(struct sockaddr_in);
    if ((n = accept(s, (struct sockaddr *)&client, (socklen_t *)&len)) < 0)
    {
        perror("Accept");
        exit(7);
    }

    // Nom réseau du client
    char hotec[NI_MAXHOST];
    char portc[NI_MAXSERV];
    err = getnameinfo((struct sockaddr *)&client, len, hotec, NI_MAXHOST, portc, NI_MAXSERV, 0);
    if (err < 0)
    {
        fprintf(stderr, "Résolution client (%i): %s\n", n, gai_strerror(err));
    }
    else
    {
        fprintf(stderr, "Accept ! (%i) ip=%s port=%s\n", n, hotec, portc);
    }

    // Redirection vers l'interface virtuelle TUN
    transfert(n, t);
}