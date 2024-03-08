/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:10:11 by yabejani          #+#    #+#             */
/*   Updated: 2024/03/08 18:33:33 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/pipex.h"

static void	ft_check_input(t_pipe *pipe, int argc, char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		pipe->here_doc = TRUE;
	else
		pipe->here_doc = FALSE;
	if (pipe->here_doc && argc < 6)
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
	t_pipe	pipe;

	ft_check_input(&pipe, argc, argv);
	ft_init(&pipe, argc, argv, envp);
	fd_printf(1, "success");
}