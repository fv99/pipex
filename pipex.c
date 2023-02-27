/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:09:18 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/02/27 15:49:42 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// Parse the command-line arguments. 
// Open file1 for reading and file2 for writing.
// Use the pipe function to create a pipe between the two commands. 
// This allows the output of cmd1 to be fed as input to cmd2.
// Fork the process. This creates a child process that will execute cmd1.
// In the child process, use dup2 to redirect the standard output 
// to the write end of the pipe. 
// This allows the output of cmd1 to be written to the pipe.
// In the parent process, fork again to 
// create a second child process that will execute cmd2.
// In the second child process, use dup2 to redirect 
// the standard input to the read end of the pipe.
// This allows the input to cmd2 to come from the pipe.
// Use execve to execute cmd1 in the first 
// child process and cmd2 in the second child process.
// Use wait or waitpid to wait for both 
// child processes to finish executing.
// Close any open file descriptors and 
// free any allocated memory to avoid memory leaks.
// Handle any errors that may occur, using the 
// external functions listed in the project requirements as necessary.


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



	
}