/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttang <ttang@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 00:00:00 by ttang             #+#    #+#             */
/*   Updated: 2026/09/28 00:00:00 by ttang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	magnitude;

	magnitude = (unsigned int)n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		magnitude = 0U - magnitude;
	}
	if (magnitude >= 10)
		ft_putnbr_fd((int)(magnitude / 10), fd);
	ft_putchar_fd('0' + magnitude % 10, fd);
}
