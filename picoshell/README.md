## Résumé de fonction:
Dans le child, la 1ere commande rentre dans le if 2.
Les commande middle rentrent dans le if 1 et 2.
La dernière commande rentre
## Pipe: 
- La fonction pipe()sert à connecter la sortie standard d’une commande à l’entrée standard de la suivante (ex. : ls | grep test.txt).
Ce que l’un écrit dans l’extrémité d’écriture peut être lu par l’autre depuis l’extrémité de lecture.
pipefd[0] : extrémité de lecture
pipefd[1] : extrémité d’écriture
Retourne 0 en cas de succès, -1 en cas d’erreur (errno est positionné).

## Fork:
- La fonction fork() en C (POSIX) sert à créer un nouveau processus, dit processus fils, qui est une copie presque exacte du processus père appelant.

## Exec
- Remplace le processus courant par un autre programme. Ça ne crée pas de nouveau processus (contrairement à fork()).

Variantes utiles :
execl(path, arg0, …, NULL) / execv(path, argv) : chemin exact, pas de recherche.
execlp(file, …) / execvp(file, argv) : cherche dans PATH.
execve(path, argv, envp) : version “bas niveau” où tu fournis l’environnement.

Avant exec : ton code du shell tourne.

Après exec (si ça réussit) : c’est la commande que tu as demandée (ls, grep…) qui tourne à la place de ton code.

## Close
- Ferme un descripteur de fichier (fd) dans ton processus.

## Questions
1) A quoi sert l'entrée standard de la première commande