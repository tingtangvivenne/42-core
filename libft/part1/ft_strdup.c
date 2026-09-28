/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttang <ttang@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 00:00:00 by ttang             #+#    #+#             */
/*   Updated: 2026/09/23 00:00:00 by ttang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	length;

	length = ft_strlen(s);
	copy = malloc(length + 1);
	if (copy == NULL)
		return (NULL);
	ft_memcpy(copy, s, length + 1);
	return (copy);
}
