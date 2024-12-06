/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:11:01 by aahaded           #+#    #+#             */
/*   Updated: 2024/12/06 12:03:28 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	find_path_child(int *pipefd, char **argv)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	execve("/usr/bin/which", argv, NULL);
	perror("Error executing cmd");
	exit(1);
}

char	*find_path_parent(char **result, int *pipefd, char **argv)
{
	int	len_buff;

	close(pipefd[1]);
	wait(NULL);
	*result = malloc(1024);
	if (!*result)
		return (free(argv), NULL);
	len_buff = read(pipefd[0], *result, 1024);
	if (len_buff <= 0)
		return (free(argv), free(*result), NULL);
	close(pipefd[0]);
	return (*result);
}

void	execute_command(char *cmd)
{
	char	**args;

	args = ft_split(cmd, ' ');
	execve(args[0], args, NULL);
	perror("Error executing command");
	exit(1);
}
