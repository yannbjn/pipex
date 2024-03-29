/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:41:41 by yabejani          #+#    #+#             */
/*   Updated: 2024/03/28 13:59:05 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0
# define ARGS_ERROR "Need at least 4 inputs\n"
# define TEMPLATE "./pipex infile cmd1 cmd2 outfile\n"
# define ARGS_ERROR_HERE_DOC "Need at least 4 inputs with here_doc\n"
# define HERE_TEMPLATE "./pipex here_doc LIMITER cmd1 cmd2 file\n"
# define MERROR "Malloc Error\n"
# define OPENFAIL "No such file or directory / permission denied: "
# define CMDFAIL "Command not found / Permission denied\n"
# define NOCMD "Command not found\n"
# define FORK "Fork error\n"

typedef struct s_pipe
{
	char	**cmds;
	char	**envp;
	char	**path;
	bool	here_doc;
	char	*limiter;
	int		fdin;
	int		fdout;
	int		**pipes;
	int		nb_pipes;
	int		flag;
}			t_pipe;

void		ft_init(t_pipe *pipe, int argc, char **argv, char **envp);
int			wait_children(pid_t pid);
pid_t		get_cmds(t_pipe *pip, char **argv);
int			access_cmd(t_pipe *pip);
void		ft_exec(t_pipe *pip, int indcmd, pid_t *pid);
void		freeclose(t_pipe *pip);

#endif