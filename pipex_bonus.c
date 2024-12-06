/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:14:48 by aahaded           #+#    #+#             */
/*   Updated: 2024/12/06 11:59:20 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex_bonus.h"

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
		find_path_child(pipefd, argv);
	else
		find_path_parent(&result, pipefd, argv);
	result[ft_serch_newline(result, '\n')] = '\0';
	return (result);
}

int	ft_tcheck_path(char *cmd)
{
	char	**words;
	char	*path;

	words = ft_split(cmd, ' ');
	path = ft_find_path(words[0]);
	if (!path || access(path, X_OK) == -1)
		return (0);
	free(path);
	return (1);
}

void	ft_read_file1(char **argv)
{
	int	file1;

	file1 = open(argv[1], O_RDONLY);
	if (file1 < 0)
	{
		perror("Error opening file1");
		exit(1);
	}
	dup2(file1, STDIN_FILENO);
	close(file1);
}

// 3andak leaks 📣
// 3andak leaks 📣
// 3andak leaks 📣
int	main(int argc, char **argv)
{
	int	i;

	if (argc < 3)
	{
		write(2, "Error: Bad arguments\n", 22);
		exit(1);
	}
	if (ft_strncmp(argv[1], "here_doc", ft_strlen((const char *)argv[1])) == 0
		|| ft_strncmp(argv[1], ".here_doc",
			ft_strlen((const char *)argv[1])) == 0)
		check_commands_and_here_doc(argc, argv);
	else
		ft_read_file1(argv);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen((const char *)argv[1])) == 0
		|| ft_strncmp(argv[1], ".here_doc",
			ft_strlen((const char *)argv[1])) == 0)
		i = 3;
	else
		i = 2;
	setup_pipeline_fork(argc, argv, i);
	return (0);
}
