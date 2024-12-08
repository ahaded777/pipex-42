/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:11:01 by aahaded           #+#    #+#             */
/*   Updated: 2024/12/07 18:22:24 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	pipe_fork_tcheck_err(pid_t pid, int pipen)
{
	if (pipen < 0)
	{
		perror("Error: pipe");
		exit(EXIT_FAILURE);
	}
	if (pid < 0)
	{
		perror("Error: fork");
		exit(EXIT_FAILURE);
	}
}

char	*find_path_child(char **result, int *pipefd, char **argv)
{
	int	len_buff;

	close(pipefd[1]);
	*result = malloc(1024);
	if (!*result)
		return (free(argv), NULL);
	len_buff = read(pipefd[0], *result, 1024);
	if (len_buff <= 0)
		return (free(argv), free(*result), NULL);
	close(pipefd[0]);
	return (*result);
}

void	find_path_parent(int *pipefd, char **argv)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	execve("/usr/bin/which", argv, NULL);
	perror("Error executing cmd");
	exit(EXIT_FAILURE);
}
