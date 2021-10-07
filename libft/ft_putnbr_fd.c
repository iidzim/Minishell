/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 19:19:35 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/04 17:55:54 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_putnbr_fd(int nb, int fd)
// {
// 	unsigned int	i;

// 	i = 0;
// 	if (nb >= 0)
// 		i = nb;
// 	if (nb < 0)
// 	{
// 		ft_putchar_fd('-', fd);
// 		i = nb * -1;
// 	}
// 	if (i >= 10)
// 		ft_putnbr_fd(i / 10, fd);
// 	ft_putchar_fd(i % 10 + 48, fd);
// }

void	ft_putnbr_fd(long long nb, int fd)
{
	unsigned int	i;

	i = 0;
	if (nb >= 0)
		i = nb;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		i = nb * -1;
	}
	if (i >= 10)
		ft_putnbr_fd(i / 10, fd);
	ft_putchar_fd(i % 10 + 48, fd);
}
