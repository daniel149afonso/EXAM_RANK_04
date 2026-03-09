/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:35:18 by daniel149af       #+#    #+#             */
/*   Updated: 2025/09/18 14:15:54 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Mode 'r' → read : le parent veut lire la sortie du fils
// → dup2(fd[1], STDOUT_FILENO) dans l’enfant → parent retourne fd[0].

// Mode 'w' → write : le parent veut écrire dans l’entrée du fils
// → dup2(fd[0], STDIN_FILENO) dans l’enfant → parent retourne fd[1].

#include <stdlib.h> //exit()
#include <sys/wait.h> //pid_t
#include <unistd.h> //pipe(), fork(), execvp()
#include <string.h>

int	ft_popen(const char *file, char *const argv[], char type)
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
			if (dup2(pipefd[1], STDOUT_FILENO) < 0) // le parent veut lire la sortie du fils
				exit(-1); //ferme aussi automatiquement les fds
		}
		else
		{
			if (dup2(pipefd[0], STDIN_FILENO) < 0) //le parent veut écrire dans l'entrée du fils.
				exit(-1); //ferme aussi automatiquement les fds
		}
		close(pipefd[0]);
		close(pipefd[1]);
		execvp(file, argv);
		exit(-1);
	}
	if (type == 'r')
	{
		close(pipefd[1]);
		return (pipefd[0]); // permet de lire la sortie du fils
	}
	else
	{
		close(pipefd[0]);
		return (pipefd[1]); // permet d'écrire dans l'entrée du fils
	}
}

//TESTING READING THE OUTPUT FILE
// int main(void)
// {
// 	int fd = ft_popen("ls", (char *const[]){"ls", "-1", NULL}, 'r');
// 	if (fd < 0)
// 		return 1;

// 	char buffer[128];
// 	ssize_t n;
// 	while ((n = read(fd, buffer, sizeof(buffer) - 1)) > 0)
// 	{
// 		buffer[n] = '\0';
// 		write(STDOUT_FILENO, buffer, n); // afficher sur le terminal
// 	}
// 	close(fd);
// 	return (0);
//}

//TESTING WRITTING IN INPUT FILE
// int	main(void)
// {
// 	int fd = ft_popen("wc", (char *const[]){"wc", "-l", NULL}, 'w');
// 	if (fd < 0)
// 		return 1;

// 	const char *text = "salut\ncomment\nça va\n";
// 	write(fd, text, strlen(text));
// 	close(fd);
// 	return (0);
// }
