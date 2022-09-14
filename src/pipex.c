/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:57:40 by cmorales          #+#    #+#             */
/*   Updated: 2022/09/14 16:55:05 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main()
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return(1);
	if (pid == 0)
	{
		printf("Child: I'm the child, my internal pid is %d.\n", pid);
        printf("Child: Done!\n");
	}
	else if (pid > 0)
    {
        printf("Parent: I'm the parent, my child's pid is %d.\n", pid);
        while (1) // Infinite loop, the parent will never end !
            usleep(1);
    }
    return (0);
}