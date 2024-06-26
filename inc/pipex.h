/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:41:41 by yabejani          #+#    #+#             */
/*   Updated: 2024/04/16 13:39:11 by yabejani         ###   ########.fr       */
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
# define ARGS_ERROR "Need 4 inputs, not more not less\n"
# define TEMPLATE "./pipex infile cmd1 cmd2 outfile\n"
# define ARGS_ERROR_HERE_DOC "Need at least 4 inputs with here_doc\n"
# define MERROR "Malloc Error\n"
# define OPENFAIL "No such file or directory : "
# define CMDFAIL "Command not found / Permission denied /\
 No such file or directory\n"
# define NOCMD "Command not found\n"
# define FORK "Fork error\n"

typedef struct s_pipe
{
	char	**cmds;
	char	**envp;
	char	**path;
	int		fdin;
	int		fdout;
	int		**pipes;
	int		nb_pipes;
	int		flag;
}			t_pipe;

void		ft_init(t_pipe *pipe, int argc, char **argv, char **envp);
int			wait_children(int flag, pid_t pid);
pid_t		get_cmds(t_pipe *pip, char **argv);
int			access_cmd(t_pipe *pip);
void		ft_exec(t_pipe *pip, int indcmd, pid_t *pid);
void		freeclose(t_pipe *pip);

#endif