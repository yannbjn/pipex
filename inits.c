/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:28:05 by yabejani          #+#    #+#             */
/*   Updated: 2024/04/16 17:22:14 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/pipex.h"

static void	ft_open(t_pipe *pip, int argc, char **argv);
static void	ft_path(t_pipe *pip);
static void	ft_pipes(t_pipe *pip);

void	ft_init(t_pipe *pip, int argc, char **argv, char **envp)
{
	pip->cmds = NULL;
	pip->envp = envp;
	pip->path = NULL;
	pip->fdin = 0;
	pip->fdout = 0;
	pip->pipes = 0;
	pip->nb_pipes = argc - 4;
	pip->flag = 0;
	ft_open(pip, argc, argv);
}

static void	ft_open(t_pipe *pip, int argc, char **argv)
{
	pip->fdin = open(argv[1], O_RDONLY);
	pip->fdout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pip->fdin == -1)
		(fd_printf(STDERR_FILENO, OPENFAIL), fd_printf(2, "%s\n", argv[1]));
	if (pip->fdout == -1)
		pip->flag = 1;
	(ft_path(pip), ft_pipes(pip));
}

static void	ft_path(t_pipe *pip)
{
	size_t	i;
	char	*path;

	i = 0;
	while (pip->envp[i] && !ft_strnstr(pip->envp[i], "PATH", 4))
		i++;
	if (!pip->envp[i])
		return ;
	path = ft_substr(pip->envp[i], 5, ft_strlen(pip->envp[i]) - 5);
	if (!path)
		(fd_printf(STDERR_FILENO, "%s", MERROR), exit(1));
	pip->path = ft_split(path, ':');
	free(path);
	if (!pip->path)
		(fd_printf(STDERR_FILENO, "%s", MERROR), exit(1));
}

static void	ft_pipes(t_pipe *pip)
{
	int	i;

	i = -1;
	pip->pipes = ft_calloc(pip->nb_pipes + 1, sizeof(int *));
	if (!pip->pipes)
		(fd_printf(STDERR_FILENO, MERROR), exit(1));
	pip->pipes[pip->nb_pipes] = NULL;
	while (++i < pip->nb_pipes)
	{
		pip->pipes[i] = ft_calloc(2, sizeof(int));
		if (!pip->pipes[i] || pipe(pip->pipes[i]) == -1)
		{
			if (!pip->pipes[i])
				(fd_printf(STDERR_FILENO, MERROR), exit(1));
			if (pipe(pip->pipes[i]) == -1)
				(fd_printf(STDERR_FILENO, "Pipe error\n"), exit(1));
		}
	}
}
