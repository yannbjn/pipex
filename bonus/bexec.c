/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bexec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:04:59 by yabejani          #+#    #+#             */
/*   Updated: 2024/04/18 12:37:06 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/pipex.h"

static void	ft_closefdinandout(t_pipe *pip)
{
	if (pip->fdin != -1)
		close(pip->fdin);
	if (pip->fdout != -1)
		close(pip->fdout);
}

void	ft_exec(t_pipe *pip, int indcmd, pid_t *pid)
{
	size_t	i;
	int		fd[2];

	i = -1;
	if (!indcmd)
		fd[0] = pip->fdin;
	else
		fd[0] = pip->pipes[indcmd - 1][0];
	if (indcmd == pip->nb_pipes)
		fd[1] = pip->fdout;
	else
		fd[1] = pip->pipes[indcmd][1];
	*pid = fork();
	if (*pid == -1)
		(fd_printf(STDERR_FILENO, FORK), freeclose(pip), exit(1));
	if (*pid == 0)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1)
			(fd_printf(2, "Permission denied\n"), freeclose(pip), exit(1));
		while (pip->pipes[++i])
			(close(pip->pipes[i][0]), close (pip->pipes[i][1]));
		ft_closefdinandout(pip);
		execve(pip->cmds[0], pip->cmds, pip->envp);
		(perror("execve "), freeclose(pip), exit(1));
	}
}

int	access_cmd(t_pipe *pip)
{
	int		i;
	char	*cmd;
	char	*tmp;

	i = -1;
	cmd = pip->cmds[0];
	if (ft_strchr(cmd, '/') != NULL && access(cmd, F_OK | X_OK) != 0)
		return (42);
	else if (ft_strchr(cmd, '/') != NULL && access(cmd, F_OK | X_OK) == 0)
		return (0);
	while (pip->path && pip->path[++i])
	{
		tmp = ft_strjoinfree(ft_strjoin(pip->path[i], "/"), cmd);
		if (!tmp)
			return (-1);
		if (!access(tmp, X_OK))
		{
			(free(pip->cmds[0]), pip->cmds[0] = tmp);
			return (0);
		}
		free(tmp);
	}
	return (42);
}

pid_t	get_cmds(t_pipe *pip, char **argv)
{
	pid_t	pid;
	int		i;
	int		code;

	i = -1;
	while (++i <= pip->nb_pipes && ++argv)
	{
		(free_tab(pip->cmds), pip->cmds = ft_split(*(argv), ' '));
		if (!pip->cmds || !pip->cmds[0])
		{
			(fd_printf(STDERR_FILENO, NOCMD), pid = -1);
			continue ;
		}
		code = access_cmd(pip);
		if (code == -1)
			(fd_printf(2, MERROR), freeclose(pip), exit(1));
		else if (code == 42)
			(fd_printf(2, "%s: %s", pip->cmds[0], CMDFAIL), pid = -1);
		else
			ft_exec(pip, i, &pid);
	}
	return (freeclose(pip), pid);
}

int	wait_children(int flag, pid_t pid)
{
	int	status;
	int	code;

	code = 1;
	status = -1;
	while (errno != ECHILD)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			code = WEXITSTATUS(status);
		if (errno == EACCES)
			return (126);
		if (pid == -1)
			code = 127;
	}
	if (flag)
		return (1);
	return (code);
}
