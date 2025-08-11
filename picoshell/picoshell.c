/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:19:15 by daniel149af       #+#    #+#             */
/*   Updated: 2025/08/11 04:02:57 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h> //exit()
#include <sys/wait.h> //pid_t
#include <unistd.h> //pipe(), fork(), execvp()

int	picoshell(char **cmds[])
{
	int		pipefd[2];
	int		prev_fd = -1;
	pid_t	pid;
	int		i = 0;

	while (cmds[i] != NULL)
	{
		if (cmds[i + 1])
		{
			if (pipe(pipefd) == -1)
				return (1);
		}
		else//si c'est la dernière commande
		{
			pipefd[0] = -1;
			pipefd[1] = -1;
		}
		pid = fork(); //création processus enfant
		if (pid < 0)
			return (1);
		if (pid == 0)
		{
			if (prev_fd != -1)//redirige stdin si il y a eu un pipe avant la commande
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (pipefd[1] != -1)//Redirige stdout si ce n'est pas la derniere commande
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		else//processus parent
		{
			if (pipefd[1] != -1) 
				close(pipefd[1]);
			if (prev_fd != -1) 
				close(prev_fd);
			prev_fd = pipefd[0];//sauvegarde stdin pour la prochaine commande
			i++;
		}
	}
	for (int j = 0; j < i; j++)
		wait(NULL);
	return (0);
}

//Main seulement pour tester!!!
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
