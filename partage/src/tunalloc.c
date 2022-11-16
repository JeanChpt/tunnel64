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

int tun_alloc(char *dev)
{
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

int main (int argc, char** argv){
  int tunfd;
  printf("Création de %s\n",argv[1]);
  tunfd = tun_alloc(argv[1]);
  printf("Faire la configuration de %s...\n",argv[1]);
  printf("Appuyez sur une touche pour continuer\n");
  getchar();
  system("/bin/bash ../scripts/configure-tun.sh");
  printf("Interface %s Configurée:\n",argv[1]);
  system("ip addr");
/*
  FILE* interface = fdopen(tunfd,"r");
  if (interface == NULL){
    perror("Erreur de lecture sur l'interface : tun0");
    exit(-1);
  } else {
    char buffer[1000];
    char c;
    int i = 0;
    do {
      c = fgetc(interface);
      buffer[i] = c;
      i++;
    } while (c != EOF);
    fclose(interface);
    printf("Ce qui est récupéré de l'interface tun0 : \n%s\n",buffer);
  }
*/
  printf("Appuyez sur une touche pour terminer\n");
  getchar();

  return 0;
}
