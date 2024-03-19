/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:10:11 by yabejani          #+#    #+#             */
/*   Updated: 2024/03/19 16:57:14 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/pipex.h"

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

	ft_check_input(&pip, argc, argv);
	ft_init(&pip, argc, argv, envp);
	if (pip.here_doc)
		return (wait_children(get_cmds(&pip, argv + 2)));
	else
		return (wait_children(get_cmds(&pip, argv + 1)));
}
