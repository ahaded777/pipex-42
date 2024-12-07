/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:46:23 by aahaded           #+#    #+#             */
/*   Updated: 2024/12/07 18:23:34 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	ft_serch_newline(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}

char	*ft_find_path(char *cmd)
{
	char	*result;
	char	**argv;
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (NULL);
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return (NULL);
	argv[0] = "which";
	argv[1] = cmd;
	argv[2] = NULL;
	if (pid == 0)
		find_path_child(&result, pipefd, argv);
	else
		find_path_parent(pipefd, argv);
	result[ft_serch_newline(result, '\n')] = '\0';
	return (result);
}

void	child_process(char **argv, int *pipefd)
{
	int		file2;
	char	**words;

	file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file2 == -1)
	{
		perror("Error opening file2");
		exit(1);
	}
	dup2(file2, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(file2);
	close(pipefd[0]);
	close(pipefd[1]);
	words = ft_split(argv[3], ' ');
	execve(ft_find_path(words[0]), words, NULL);
	perror("Error executing cmd2");
	exit(1);
}

void	parent_process(char **argv, int *pipefd)
{
	int		file1;
	char	**words;

	file1 = open(argv[1], O_RDONLY);
	if (file1 == -1)
	{
		perror("Error opening file1");
		exit(1);
	}
	dup2(file1, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(file1);
	close(pipefd[0]);
	close(pipefd[1]);
	words = ft_split(argv[2], ' ');
	execve(ft_find_path(words[0]), words, NULL);
	perror("Error executing cmd1");
	exit(1);
}

int	main(int argc, char **argv)
{
	int		pipefd[2];
	pid_t	pid;
	int		pipen;

	if (argc != 5)
	{
		write(2, "Error: Bad arguments\n", 22);
		exit(1);
	}
	pipen = pipe(pipefd);
	pid = fork();
	if (pid < 0 || pipen == -1)
	{
		perror("Error: fork and pipe");
		exit(1);
	}
	if (pid == 0)
		child_process(argv, pipefd);
	else
		parent_process(argv, pipefd);
	exit(0);
}
