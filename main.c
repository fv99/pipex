/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:06:16 by fvonsovs          #+#    #+#             */
/*   Updated: 2023/02/28 16:07:48 by fvonsovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	in;
	int	out;
	int	i;

	if (argc < 5)
		you_fucked_up(argv[0]);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
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
	while (i < (argc - 2))
		pipex(argv[i++], envp);
	dup2(out, 1);
	execute(argv[argc - 2], envp);
}
