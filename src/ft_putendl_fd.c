/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:53:09 by mviudes           #+#    #+#             */
/*   Updated: 2021/07/24 19:37:11 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher.h>

static void	ft_putstr_fd(char *string, int fd)
{
	int	i;

	i = 0;
	while(string[i] != '\0')
	{
		write(1, &string[i], fd);
		i++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(1, "\n", fd);
}
