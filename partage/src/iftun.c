//***************************************************//
// Définition des fonctions de la bibliothèque iftun //
//***************************************************//

// Include
#include "iftun.h"

/**
 * Fonction qui crée une interface virtuelle dont le nom est passé en paramètres
 * @param dev Le nom de l'interface à créer
 * @return Le descripteur de fichier qui permet la lecture/écriture sur l'interface
*/
int tun_alloc(char *dev){
  struct ifreq ifr;
  int fd, err;

  if( (fd = open("/dev/net/tun", O_RDWR)) < 0 ){
    perror("alloc tun");
    exit(-1);
  }

  memset(&ifr, 0, sizeof(ifr));

  /* Flags: IFF_TUN   - TUN device (no Ethernet headers) 
   *        IFF_TAP   - TAP device  
   *
   *        IFF_NO_PI - Do not provide packet information  
   */ 
  ifr.ifr_flags = IFF_TUN; 
  if( *dev )
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);

  if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ){
    close(fd);
    return err;
  }
  strcpy(dev, ifr.ifr_name);
  return fd;
}

/**
 * Fonction qui permet le transfert de ce qui est lu sur src vers dest
 * @param src Le descripteur de fichier source
 * @param dest Le descripteur de fichier destination
*/
void transfert(int src, int dest){
    char r[1000];
    while (1){
        read(src, r, 1000);
        write(dest, r, 1000);
    }
}