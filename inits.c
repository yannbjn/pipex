/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:28:05 by yabejani          #+#    #+#             */
/*   Updated: 2024/03/19 18:44:05 by yabejani         ###   ########.fr       */
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
	pip->limiter = NULL;
	pip->fdin = 0;
	pip->fdout = 0;
	pip->pipes = 0;
	pip->nb_pipes = argc - 4;
	ft_open(pip, argc, argv);
}

static void	ft_open(t_pipe *pip, int argc, char **argv)
{
	if (!pip->here_doc)
	{
		pip->fdin = open(argv[1], O_RDONLY);
		pip->fdout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
	if (pip->here_doc)
	{
		pip->limiter = ft_strjoin(argv[2], "\n");
		if (!pip->limiter)
			fd_printf(STDERR_FILENO, "%s\n", MERROR);
		pip->fdout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	}
	if (pip->fdin == -1)
		(fd_printf(STDERR_FILENO, OPENFAIL), fd_printf(2, "%s\n", argv[1]));
	if (pip->here_doc)
		pip->nb_pipes = argc - 5;
	ft_path(pip);
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
	ft_pipes(pip);
}

static void	ft_pipes(t_pipe *pip)
{
	int	i;

	i = -1;
	pip->pipes = ft_calloc(pip->nb_pipes + 1, sizeof(int *));
	if (!pip->pipes)
		(fd_printf(STDERR_FILENO, MERROR), exit(1));
	pip->pipes[pip->nb_pipes] = NULL;
	while(++i < pip->nb_pipes)
	{
		pip->pipes[i] = ft_calloc(3, sizeof(int));
		if (!pip->pipes[i] || pipe(pip->pipes[i]) == -1)
			(fd_printf(STDERR_FILENO, MERROR), exit(1));
	}
}
