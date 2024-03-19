/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:04:59 by yabejani          #+#    #+#             */
/*   Updated: 2024/03/19 17:03:31 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/pipex.h"

pid_t	get_cmds(t_pipe *pip, char **argv)
{
	pid_t			pid;
	unsigned int	i;
	int				code;

	i = -1;
	while (++i <= pip->nb_pipes)
	{
		
	}
}

int	wait_children(pid_t pid)
{
	int	status;
	int	code;

	code = EXIT_FAILURE;
	while (errno != ECHILD)
	{
		WIFEXITED(status);
		if (wait(&status) == pid)
			code = WEXITSTATUS(status);
		if (pid == -1)
			return (127);
	}
	return (code);
}
