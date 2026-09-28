/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttang <ttang@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 00:00:00 by ttang             #+#    #+#             */
/*   Updated: 2026/09/28 00:00:00 by ttang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	number_length(int n)
{
	size_t	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10 != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t			len;
	unsigned int	magnitude;
	char			*result;

	len = number_length(n);
	result = malloc(len + 1);
	if (result == NULL)
		return (NULL);
	result[len] = '\0';
	magnitude = (unsigned int)n;
	if (n < 0)
		magnitude = 0U - magnitude;
	while (len > 0)
	{
		result[--len] = '0' + magnitude % 10;
		magnitude /= 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}
