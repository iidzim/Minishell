/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 10:02:53 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/08 17:16:01 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchar(char *save, char c)
{
	size_t	i;

	i = 0;
	while (save[i] != c)
	{
		if (save[i] == '\0')
			return (NULL);
		i++;
	}
	return (save);
}
