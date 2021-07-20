/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 22:10:30 by mviudes           #+#    #+#             */
/*   Updated: 2021/07/13 22:16:24 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher.h>

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isnum(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '-' && i == 0)
			i++;
		if (!ft_isdigit(string[i]))
			return (0);
		i++;
	}
	return (1);
}
