/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bpipex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:10:11 by yabejani          #+#    #+#             */
/*   Updated: 2024/04/16 18:10:50 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/pipex.h"

static int	get_heredoc(t_pipe *pip)
{
	int		fd;
	int		i;
	char	*file;

	i = 2;
	file = ft_calloc(i, sizeof(char));
	if (!file)
		(fd_printf(2, MERROR), freeclose(pip), exit(1));
	ft_memset(file, 'a', i - 1);
	while (access(file, F_OK) == 0 && errno != ENOENT)
	{
		(free(file), file = ft_calloc(++i, sizeof(char)));
		if (!file && fd_printf(2, MERROR))
			(freeclose(pip), exit(1));
		ft_memset(file, 'a', i - 1);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	pip->fdin = open(file, O_RDONLY);
	(unlink(file), free(file));
	if (pip->fdin == -1 || fd == -1)
		perror("open");
	return (fd);
}

static void	heredoc(t_pipe *pip)
{
	int		fd;
	char	*line;

	fd = get_heredoc(pip);
	while (ft_printf("here_doc> "))
	{
		line = ft_get_next_line(0);
		if (!line)
			(fd_printf(2, MERROR), freeclose(pip), exit(1));
		if (!ft_strncmp(line, pip->limiter, ft_strlen(pip->limiter)))
			break ;
		(fd_printf(fd, "%s", line), free(line));
	}
	(free(line), close(fd));
}

static void	ft_check_input(t_pipe *pip, int argc, char **argv)
{
	if (argc < 2)
		(fd_printf(1, "No args\n"), exit(1));
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		pip->here_doc = TRUE;
	else
		pip->here_doc = FALSE;
	if (pip->here_doc && argc < 6)
	{
		fd_printf(STDERR_FILENO, ARGS_ERROR_HERE_DOC);
		fd_printf(STDERR_FILENO, HERE_TEMPLATE);
		exit(1);
	}
	if (argc < 5)
	{
		fd_printf(STDERR_FILENO, ARGS_ERROR);
		fd_printf(STDERR_FILENO, TEMPLATE);
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pip;
	int		flag;

	ft_check_input(&pip, argc, argv);
	ft_init(&pip, argc, argv, envp);
	if (pip.here_doc)
		heredoc(&pip);
	flag = pip.flag;
	if (pip.here_doc)
		return (wait_children(flag, get_cmds(&pip, argv + 2)));
	else
		return (wait_children(flag, get_cmds(&pip, argv + 1)));
}
