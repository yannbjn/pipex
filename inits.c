/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:28:05 by yabejani          #+#    #+#             */
/*   Updated: 2024/03/08 19:24:54 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/pipex.h"

static void	ft_open(t_pipe *pipe, int argc, char **argv, char **envp);
static void	ft_path(t_pipe *pipe);

void	ft_init(t_pipe *pipe, int argc, char **argv, char **envp)
{
	pipe->cmds = NULL;
	pipe->envp = envp;
	pipe->path = NULL;
	pipe->limiter = NULL;
	pipe->fdin = 0;
	pipe->fdout = 0;
	pipe->pipes = 0;
	pipe->nb_pipes = 0;
	ft_open(pipe, argc, argv, envp);
}

static void	ft_open(t_pipe *pipe, int argc, char **argv, char **envp)
{
	if (!pipe->here_doc)
	{
		pipe->fdin = open(argv[1], O_RDONLY);
		pipe->fdout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (pipe->here_doc)
	{
		pipe->limiter = ft_strjoin(argv[2], "\n");
		if (!pipe->limiter)
			fd_printf(STDERR_FILENO, "%s\n", MERROR);
		pipe->fdout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (pipe->fdin == -1)
		(fd_printf(STDERR_FILENO, OPENFAIL), fd_printf(2, "%s\n", argv[1]));
	// fd_printf(1, "%s\n", pipe->limiter);
	// fd_printf(STDOUT_FILENO, "SUCCES OPENING INFILE\n");
	ft_path(pipe);
}

static void	ft_path(t_pipe *pipe)
{
	size_t	i;
	char	*path;

	i = 0;
	while (pipe->envp[i] && !ft_strnstr(pipe->envp[i], "PATH", 4))
		i++;
	if (!pipe->envp[i])
		return ;
	path = ft_substr(pipe->envp[i], 5, ft_strlen(pipe->envp[i]) - 5);
	if (!path)
		(fd_printf(STDERR_FILENO, "%s", MERROR), exit(1));
	pipe->path = ft_split(path, ':');
	free(path);
	if (!pipe->path)
		(fd_printf(STDERR_FILENO, "%s", MERROR), exit(1));
	fd_printf(1, "%s\n", pipe->path);
}

static void	ft_pipes(t_pipe *pipe)
{
	int	i;
	
}

// static void	init_pipes(t_pipe *pipex)
// {
// 	int	i;

// 	i = -1;
// 	pipex->pipes = ft_calloc(pipex->nb_pipes + 1, sizeof(int *));
// 	if (!pipex->pipes)
// 		(ft_dprintf(2, "%s", ERR_MEM), free_all(pipex), exit(1));
// 	pipex->pipes[pipex->nb_pipes] = NULL;
// 	while (++i < pipex->nb_pipes)
// 	{
// 		pipex->pipes[i] = ft_calloc(3, sizeof(int));
// 		if (!pipex->pipes[i] || pipe(pipex->pipes[i]) == -1)
// 			(ft_dprintf(2, "%s", ERR_MEM), free_all(pipex), exit(1));
// 	}
// }
