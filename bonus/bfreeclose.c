/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeclose.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:28:23 by yabejani          #+#    #+#             */
/*   Updated: 2024/03/20 13:02:08 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/pipex.h"

void	freeclose(t_pipe *pip)
{
	int	i;

	i = -1;
	if (pip->path)
		free_tab(pip->path);
	if (pip->cmds)
		free_tab(pip->cmds);
	if (pip->pipes)
	{
		while (pip->pipes[++i])
			(close(pip->pipes[i][0]), close(pip->pipes[i][1]), \
			free(pip->pipes[i]));
		free(pip->pipes);
	}
	if (pip->limiter)
		free(pip->limiter);
	if (pip->fdin >= 0)
		close(pip->fdin);
	if (pip->fdout >= 0)
		close(pip->fdout);
}
