/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:53:56 by cmorales          #+#    #+#             */
/*   Updated: 2022/09/19 20:00:47 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../42-library/libft.h"
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

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
#endif