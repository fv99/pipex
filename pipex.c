/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:09:18 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/02/27 18:20:58 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The char *envp[] argument is a pointer to an 
// array of strings that represent the environment
// variables for the current process. In C, environment variables
// are stored as a list of key-value pairs, where the keys and values are strings.
// The char *envp[] argument is a way to access the environment variables 
// in a more flexible way. It is typically used in programs
// that need to modify the environment variables or pass
// a modified set of environment variables to a child process.
int	main(int argc, char *argv[], char *envp[])
{
	int	in;
	int	out;
	int	i;

 	if (argc != 5)
 		you_fucked_up(argv[0]);
	else if (argv[1] == "here_doc")
	{
		if (argc < 6)
			you_fucked_up(argv[0]);
		i = 3;
		out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		here_doc(argv);
	}
	else
	{
		i = 2;
		in = open(argv[1], O_RDONLY, 0777);
		out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(in, 0);
	}
	while (i < (ac - 2))
		pipex(av[i++], envp);
	dup2(out, 1);
	exec(argv[argc - 2], envp);
}

int	you_fucked_up(char msg)
{
	ft_printf("Usage: %s <option> <file1> <cmd1> <cmd2> ... <file2>\n", msg));
	exit(0);
}

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
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(ret);
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
	path = get_path(command[0], env);
	if (execve(path, command, envp) == -1)
	{
		ft_printf("Command not found: %s \n", command[0]);
		free_double_pointer(command);
		exit(0);
	}
}

void	free_double_pointer(char	**ptr)
{
	size_t	i;

	i = 0;
	while(ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

char	*getenv(char *name, char **envp)
{
	int		i;
	int		j;
	char	*sub;


}

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	*exec;
	char	*path;
	char	**fullpath;
	char	**command;

	i = -1;
	fullpath = ft_split(getenv)

}