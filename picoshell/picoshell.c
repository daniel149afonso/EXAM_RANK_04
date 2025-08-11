/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:19:15 by daniel149af       #+#    #+#             */
/*   Updated: 2025/08/11 00:40:49 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> //exit()
#include <stdio.h> 
#include <sys/wait.h> //pid_t
#include <unistd.h> //pipe(), fork(), execvp()

int	main()
{
	int		pipefd[2];
	int		prev_fd = -1;
	pid_t	pid;
	int		i = 0;
	char *cmds[][3] = {
		{"ls", "-l", NULL},
		{"grep", "subject", NULL},
		{NULL}
	};

	while (cmds[i])
	{
		if (cmds[i + 1])
		{
			if (pipe(pipefd) == -1)
			return (1);
		}
		else
		{
			pipefd[0] = -1;
			pipefd[1] = -1;
		}
		pid = fork(); //création nouveau processus
		if (pid < 0)
			return (1);
		if (pid == 0)
		{
			if (prev_fd != 0)//Applique stdin
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (pipefd[1] != -1)//Applique stdout si pas derniere commande
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		else
		{
			close(pipefd[0]);
			close(pipefd[1]);
			close(prev_fd);
			prev_fd = pipefd[0];
			i++;
		}
	}
	waitpid(pid, NULL, 0);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	int	cmds_size = 1;
// 	for (int i = 0; i < argc; i++)
// 	{
// 		if (!strcmp(argv[i], "|"))
// 			cmds_size++;
		
// 	}
// 	char ***cmds = calloc(cmds_size + 1, sizeof(char **));
// 	if (!cmds)
// 	{
// 		dprintf(2, "Malloc error: %m\n");
// 		return (1);
// 	}
// 	cmds[0] = argv + 1;
// 	int	cmds_i = 1;
// 	for (int i = 0; i < argc; i++)
// 	{
// 		if (!strcmp(argv[i], "|"))
// 		{
// 			cmds[cmds_i] = argv + i + 1;
// 			argv[i] = NULL;
// 			cmds_i++;
// 		}
// 	}
// 	int	ret = picoshell(cmds);
// 	if (ret)
// 		perror("picoshell");
// 	free(cmds);
// 	return (ret);
// }

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