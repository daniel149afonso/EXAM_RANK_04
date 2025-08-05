/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:19:15 by daniel149af       #+#    #+#             */
/*   Updated: 2025/08/04 23:38:16 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> //exit()
#include <stdio.h> 
#include <sys/wait.h> //pid_t
#include <unistd.h> //pipe(), fork(), execvp()

int	main()
{
	int	pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (1);
	
	pid = fork(); //création nouveau processus
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execlp("ls", "ls", NULL);
		exit(1);
	}
	pid_t pid1 = fork(); 
	if (pid1 == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		execlp("grep", "grep", "foo", NULL);
		exit(1);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	printf("Dark Vador: Je suis ton père\n");
	waitpid(pid, NULL, 0);
    waitpid(pid1, NULL, 0);
	printf("Dark Vador: La vérité est dans ton coeur\n");
	return (0);
}

// int main(void) {
//     pid_t pid = fork();
//     if (pid < 0) {
//         perror("fork");
//         exit(1);
//     }
//     else if (pid == 0) {
//         // Code exécuté par le fils
//         printf("Je suis le fils (PID = %d)\n", getpid());
//         exit(1);
//     }
//     else {
//         // Code exécuté par le père
//         printf("Je suis le père (PID = %d), mon fils a PID = %d\n",
//                getpid(), pid);
//         wait(NULL);  // attend la fin du fils
//         printf("Fils terminé.\n");
//     }
//     return 0;
// }