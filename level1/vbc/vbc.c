/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel149afonso <daniel149afonso@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 00:47:31 by daniel149af       #+#    #+#             */
/*   Updated: 2025/11/12 00:06:33 by daniel149af      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>    // MOD: on utilise <stdlib.h> pour calloc/free au lieu de <malloc.h>
#include <ctype.h>

char *input;
int  error = 0;

int sum();
int product();
int primary();

void    handle_error(char c) {
	if (c == '\0')
		printf("Unexpected end of input\n");
	else
		printf("Unexpected token '%c\n", c);
	error = 1;
}

int primary() {
	if (error)
		return 0;
	if (*input == '(') {
		input++;
		int result = sum();
		if (error)
			return 0;
		if (*input != ')')
			return (handle_error(*input), 0);
		input++;
		return result;
	}
	if (isdigit(*input)) {
		int num = *input - '0';
		input++;
		return num;
	}
	return (handle_error(*input), 0);
}

int product() {
	int left = primary();
	if (error)
		return 0;
	while(*input == '*') {
		input++;
		int right = primary();
		if (error)
			return 0;
		left *= right;
	}
	return left;
}

int sum() {
	int left = product();
	if (error)
		return 0;
	while (*input == '+') {
		input++;
		int right = product();
		if (error)
			return 0;
		left += right;
	}
	return left;
}

int main(int ac, char **av) {
	if (ac != 2)
		return 1;
	input = av[1];
	int result = sum();
	if (error)
		return 1;
	if (*input != '\0')
		return 1;
	printf("%d\n", result);
	return 0;
}