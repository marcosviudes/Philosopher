/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_absatol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviudes <mviudes@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 20:25:11 by mviudes           #+#    #+#             */
/*   Updated: 2021/09/05 12:16:00 by mviudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher.h>
#define MAX_ABSTOL_LEN	20
#define ABSTOL_ERROR	-1

static size_t	absatol_len(char *string)
{
	size_t	i;

	i = 0;
	while (string[i])
		i++;
	return (i);
}

static int	is_abs_num(const char *number)
{
	int		i;

	i = 0;
	while (number[i])
	{
		if (number[i] > '9' || number[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

long	ft_absatol(const char *string)
{
	char	*ptr;
	long	ret;

	ptr = (char *)string;
	ret = 0;
	if (!string)
		return (ABSTOL_ERROR);
	while (*ptr == ' ' || *ptr == '0')
		ptr++;
	if (absatol_len(ptr) > MAX_ABSTOL_LEN || !is_abs_num(ptr))
		return (ABSTOL_ERROR);
	while (*ptr)
		ret = ret * 10 + (*ptr++ - '0');
	return (ret);
}
