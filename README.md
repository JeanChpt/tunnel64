# Tunnel IPv6 sur IPv4

> Il s'agit du projet final de l'UE Réseaux du M1 Informatique AMU. Il s'agit d'un programme permettant l'interconnexion de deux réseaux IPv6 par le biais d'un réseau IPv4. Projet en cours de développement, la version la plus à jour se trouve donc sur la branche dev.

## Compilation

Pour récupérer le code source du projet :

```sh
git clone https://github.com/JeanChpt/tunnel64.git
```

Pour se rendre sur la bonne branche (la plus à jour) :

```sh
cd tunnel64
git checkout dev
```

Et enfin pour compiler :

```sh
cd partage
make
```

## Exécution

Dans le répertoire du projet se trouve un répertoire pour chaque VM. Ici seulement deux VMs nous intéresseront pour le tunnel. Il s'agit de VM1 et de VM3. Pour lancer VM1 et démarrer le tunnel vers VM3, faire depuis le répertoire de VM1 :

```sh
vagrant up
cd /mnt/partage
./bin/tunnel64 tun0 "172.16.2.163" "123"
```

Pour lancer VM3  et démarrer le tunnel vers VM1, faire depuis le répertoire de VM3 :

```sh
vagrant up
cd /mnt/partage
./bin/tunnel64 tun0 "172.16.2.131" "123"
```

> Attention, lorsque le tunnel se lance, le serveur démarre en premier. Il faut ensuite appuyer sur une touche pour y connecter le client. Faites donc attention à lancer le serveur sur les deux machines avant de connecter les clients. Sinon la connexion sera impossible.

## Explications

Pour avoir plus d'informations sur le projet, le rapport PDF est disponible dans le répertoire docs avec les captures de test Wireshark (pas encore complet pour le moment)