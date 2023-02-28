/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:17:27 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/02/28 16:03:39 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>

# include "./libft/libft.h"

# define PATH_SEP ':'

int		you_fucked_up(char *msg);

void	free_array(char	**ptr);

char	*ft_strtok(char *str, char sep);

char	*get_path(char *cmd, char **envp);

char	*get_path_token(char *cmd, char *path_env, int cmd_len);

void	here_doc(char **argv);

void	here_doc_exec(char **argv, int *pid_fd);

void	pipex(char *cmd, char **envp);

void	execute(char *cmd, char **envp);

char	*ft_strcat(char *dest, char *src);

#endif