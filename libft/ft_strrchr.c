/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:38:42 by zqadiri           #+#    #+#             */
/*   Updated: 2019/10/24 21:48:16 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t		len;
	char		*str;
	char		val;

	val = (char)c;
	str = (char *)s;
	len = ft_strlen(str);
	if (c == 0)
		return ((char *)(str + len));
	while (len > 0)
	{
		if (str[len - 1] == c)
			return (str + len - 1);
		else
			len--;
	}
	return (NULL);
}
