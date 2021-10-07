/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:24:03 by zqadiri           #+#    #+#             */
/*   Updated: 2021/04/27 14:53:21 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t		i;
	char		*ptr;
	char		*find;
	size_t		size;

	i = 0;
	ptr = (char *)str;
	find = (char *)to_find;
	if (*to_find == '\0' || to_find == NULL)
		return (ptr);
	size = ft_strlen(find);
	while (ptr[i] != '\0' && len >= i + size)
	{
		if (ft_strncmp(ptr + i, find, size) == 0)
			return (ptr + i);
		i++;
	}
	return (NULL);
}
