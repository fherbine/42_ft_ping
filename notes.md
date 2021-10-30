## Fonctions autorisées

### Informations processus:

#### getpid

```c
#include <unistd.h>
#include <sys/types.h>

pid_t getpid(void);
```

**Retour:**

`getpid` renvoie le [PID](https://fr.wikipedia.org/wiki/Identifiant_de_processus),
du  processus.

- un PID sur 32 bits pour les CPU 32bits.
- un PID sur 64 bits pour les CPU 64bits.

#### getuid

```c
#include <unistd.h>
#include <sys/types.h>

uid_t getuid(void);
```

**Retour:**

`getuid` renvoie l'UID du processus.


### reverse DNS

#### fonction `getaddrinfo`

```c
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int getaddrinfo(char *hostname, char *service, struct addrinfo *hints, struct addrinfo **res);
```

**Arguments:**

- <ins>hostname</ins>: Nom d'hote du serveur cible.
- <ins>service</ins>: Service utilisé (_ex: http, ..._). Voir `/etc/services`
- <ins>hints</ins>: Il s'agit d'une structure `addrinfo` type pour configurer ce qui va être reçu en résultat.
- <ins>res</ins>: Il s'agit de l'adresse du pointeur sur structure `addrinfo`, qui va recevoir, le résultat du DNS lookup.

**Retour:**

- Cette fonction retourne un entier, qui correspond au statut de la requête. Voir **getaddrinfo(3)**.

```c
struct addrinfo {
    int              ai_flags;
    int              ai_family;
    int              ai_socktype;
    int              ai_protocol;
    socklen_t        ai_addrlen;
    struct sockaddr *ai_addr;
    char            *ai_canonname;
    struct addrinfo *ai_next;
};
```

**Contenu:**
- <ins>ai_flags</ins>: 

_To describe..._


