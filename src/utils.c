/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:51:07 by cmorales          #+#    #+#             */
/*   Updated: 2023/02/13 12:14:28 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error(char *text)
{
	if (errno == 0)
	{
		printf("Entra aqui\n");
		write(2, "Error\n", 6);
	}
	else
	{
		printf("Entra aqui\n");
		perror(text);
	}
	exit(EXIT_FAILURE);
}

void	ft_cmd_not_found(char **cmd)
{
	printf("Entra aqui\n"); 
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": command not found\n", 20);
	ft_free_paths(cmd);
	exit(EXIT_FAILURE);
}

void	ft_free_paths(char **paths)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (paths[len])
		len++;
	while (i < len)
		free(paths[i++]);
	free(paths);
}


