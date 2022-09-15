/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:53:56 by cmorales          #+#    #+#             */
/*   Updated: 2022/09/15 21:07:18 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../42-library/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void	ft_check_fd(int fd);
void	ft_free_paths(char **paths);
char	**ft_all_the_paths(char **envp);
char	*ft_get_the_path(char *cmd, char **envp);
void	ft_cmd_not_found(char **cmd, char *path);
#endif