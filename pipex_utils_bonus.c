/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:15:34 by aahaded           #+#    #+#             */
/*   Updated: 2024/12/06 12:08:04 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex_bonus.h"

void	find_path_child(int *pipefd, char **argv)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	execve("/usr/bin/which", argv, NULL);
	perror("Error executing command");
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
	char	**words;

	words = ft_split(cmd, ' ');
	execve(ft_find_path(words[0]), words, NULL);
	perror("Error executing command");
	exit(1);
}

static void	setup_pipeline_fork_(int argc, char **argv)
{
	int	file2;

	file2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC);
	if (file2 < 0)
	{
		perror("Error opening file2");
		exit(-1);
	}
	dup2(file2, STDOUT_FILENO);
	close(file2);
	execute_command(argv[argc - 2]);
}

void	setup_pipeline_fork(int argc, char **argv, int i)
{
	int	pipefd[2];

	while (i < argc - 2)
	{
		pipe(pipefd);
		if (fork() == 0)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			execute_command(argv[i]);
		}
		else
		{
			wait(NULL);
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
		}
		i++;
	}
	setup_pipeline_fork_(argc, argv);
}
