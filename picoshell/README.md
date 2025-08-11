## Pipe: 
- La fonction pipe()sert à connecter la sortie standard d’une commande à l’entrée standard de la suivante (ex. : ls | grep foo).
Ce que l’un écrit dans l’extrémité d’écriture peut être lu par l’autre depuis l’extrémité de lecture.
pipefd[0] : extrémité de lecture
pipefd[1] : extrémité d’écriture
Retourne 0 en cas de succès, -1 en cas d’erreur (errno est positionné).

## Fork:
La fonction fork() en C (POSIX) sert à créer un nouveau processus, dit processus fils, qui est une copie presque exacte du processus père appelant.

## Exec

## Close

## Questions
1) A quoi sert l'entrée standard de la première commande