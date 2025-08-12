/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:35:18 by daniel149af       #+#    #+#             */
/*   Updated: 2025/08/11 23:48:00 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> //exit()
#include <sys/wait.h> //pid_t
#include <unistd.h> //pipe(), fork(), execvp()

int	ft_popen(const char file, char const argv[], char type)
{
	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);
	
	int	pipefd[2];
	if (pipe(pipefd) < 0)
		return (-1);
	pid_t pid = fork();
	if (pid < 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		if (type == 'r')
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
		else
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
		}
		execvp(file, argv);
		exit(-1);
	}
	if (type == 'r')
	{
		close(pipefd[0]);
		return (pipefd[1]);
	}
	else
	{
		close(pipefd[1]);
		return (pipefd[0]);
	}
}