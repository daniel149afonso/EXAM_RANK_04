/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:19:15 by daniel149af       #+#    #+#             */
/*   Updated: 2025/08/04 20:48:01 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h> //pipe

int	picoshell(char *cmds[])
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		
	return (0);
}

int	main(void)
{
	picoshell();
	return (0);
}