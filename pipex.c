/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:10:11 by yabejani          #+#    #+#             */
/*   Updated: 2024/04/16 17:17:06 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pip;
	int		flag;

	if (argc != 5)
	{
		fd_printf(STDERR_FILENO, ARGS_ERROR);
		fd_printf(STDERR_FILENO, TEMPLATE);
		exit(1);
	}
	ft_init(&pip, argc, argv, envp);
	flag = pip.flag;
	return (wait_children(flag, get_cmds(&pip, argv + 1)));
}
