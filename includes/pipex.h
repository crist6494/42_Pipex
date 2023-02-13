/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:53:56 by cmorales          #+#    #+#             */
/*   Updated: 2023/02/13 01:07:03 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../42-library/libft.h"
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

/*Struct*/

typedef struct s_data
{
	char	**env;
	char	**argv;
	int		argc;
	int		heredoc;
	int		fd_input;
	int		fd_output;
	int		num_cmds;
	int		*pipe;
	int		*pids;
	int		child;
	char	*cmd_path;
	char	**cmds;
} t_data;


/*Pipex*/

void	child1_process(int *fd_file, int *fd, char **av, char **envp);
void	child2_process(int *fd_file, int *fd, char **av, char **envp);
int		main(int argc, char **argv, char **envp);

/*Utils*/
void	ft_error(char *text);
void	ft_cmd_not_found(char **cmd);
void	ft_free_paths(char **paths);
char	**ft_all_the_paths(char **envp);
char	*ft_get_path(char *cmd, char **envp);

void	ft_get_fd_input(t_data *data);
void	ft_get_fd_output(t_data *data);
t_data init(int argc, char **argv, char **envp);
void	ft_close_pipes(t_data *data);

#endif