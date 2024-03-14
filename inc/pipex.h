/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:41:41 by yabejani          #+#    #+#             */
/*   Updated: 2024/03/14 13:52:57 by yabejani         ###   ########.fr       */
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
# include <unistd.h>

# define TRUE 1
# define FALSE 0
# define ARGS_ERROR "Need at least 4 inputs\n"
# define TEMPLATE "./pipex infile cmd1 cmd2 outfile\n"
# define ARGS_ERROR_HERE_DOC "Need at least 4 inputs with here_doc\n"
# define HERE_TEMPLATE "./pipex here_doc LIMITER cmd1 cmd2 file\n"
# define MERROR "Malloc Error"
# define OPENFAIL "No such file or directory / permission denied: "

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
}			t_pipe;

void		ft_init(t_pipe *pipe, int argc, char **argv, char **envp);

#endif