/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:09:18 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/03/01 16:32:49 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Yeah you did))
int	you_fucked_up(char *msg)
{
	ft_printf("Usage: %s <option> <file1> <cmd1> <cmd2> ... <file2>\n", msg);
	exit(0);
}

// Creates pipe storing its fd in pid_fd
// Forks a new process, storing pid in pid
// Calls here_doc_exec 
void	here_doc(char **argv)
{
	int		pid_fd[2];
	pid_t	pid;

	if (pipe(pid_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
		here_doc_exec(argv, pid_fd);
	else
	{
		close(pid_fd[1]);
		dup2(pid_fd[0], 0);
		wait(NULL);
	}
}

void	here_doc_exec(char **argv, int *pid_fd)
{
	char	*line;

	close(pid_fd[0]);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
		{
			free(line);
			exit(0);
		}
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(line);
			exit(0);
		}
		ft_printf("%s", line);
		free(line);
	}
}

void	pipex(char *cmd, char **envp)
{
	pid_t	pid;
	int		pid_fd[2];

	if (pipe(pid_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
	{
		close(pid_fd[0]);
		dup2(pid_fd[1], 1);
		execute(cmd, envp);
	}
	else
	{
		close(pid_fd[1]);
		dup2(pid_fd[0], 0);
	}
}

void	execute(char *cmd, char **envp)
{
	char	**command;
	char	*path;

	command = ft_split(cmd, ' ');
	path = get_path(command[0], envp);
	if (execve(path, command, envp) == -1)
	{
		ft_printf("Command not found: %s \n", command[0]);
		free_array(command);
		exit(0);
	}
}
