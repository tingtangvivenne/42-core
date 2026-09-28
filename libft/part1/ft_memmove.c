/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttang <ttang@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 00:00:00 by ttang             #+#    #+#             */
/*   Updated: 2026/09/23 00:00:00 by ttang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*dest;
	const unsigned char	*source;

	if (dst == src || n == 0)
		return (dst);
	dest = (unsigned char *)dst;
	source = (const unsigned char *)src;
	if ((uintptr_t)dst < (uintptr_t)src)
		return (ft_memcpy(dst, src, n));
	while (n > 0)
	{
		n--;
		dest[n] = source[n];
	}
	return (dst);
}
