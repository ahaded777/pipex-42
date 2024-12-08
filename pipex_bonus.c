/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:14:48 by aahaded           #+#    #+#             */
/*   Updated: 2024/12/07 21:27:07 by aahaded          ###   ########.fr       */
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
	int		pipen;

	pipen = pipe(pipefd);
	pid = fork();
	pipe_fork_tcheck_err(pid, pipen);
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

void	ft_read_file1(char **argv)
{
	int	file1;

	file1 = open(argv[1], O_RDONLY);
	if (file1 < 0)
	{
		perror("Error opening file1");
		exit(EXIT_FAILURE);
	}
	dup2(file1, STDIN_FILENO);
	close(file1);
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc >= 5)
	{
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
	}
	else
	{
		// if (ft_strncmp(argv[1], "here_doc", ft_strlen((const char *)argv[1])) == 0
		// || ft_strncmp(argv[1], ".here_doc",
		// 	ft_strlen((const char *)argv[1])) == 0)
		// {
		// 	ft_putstr_fd("Error: Bad arguments\n", 2);
		// 	ft_putstr_fd("Usage: ./pipex here_doc LIMITER cmd cmd1 file\n", 2);
		// 	exit(EXIT_FAILURE);
		// }

		ft_putstr_fd("Error: Bad arguments\n", 2);
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n", 2);
		exit(EXIT_FAILURE);
	}
	
	exit(EXIT_SUCCESS);
}
