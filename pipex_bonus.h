/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahaded <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:15:13 by aahaded           #+#    #+#             */
/*   Updated: 2024/12/06 12:09:04 by aahaded          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>

void	find_path_child(int *pipefd, char **argv);
char	*find_path_parent(char **result, int *pipefd, char **argv);
void	execute_command(char *cmd);
char	*ft_find_path(char *cmd);
void	setup_pipeline_fork(int argc, char **argv, int i);
void	check_commands_and_here_doc(int argc, char **argv);
void	setup_here_doc_input(char **argv);

#endif
