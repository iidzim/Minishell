/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 11:41:45 by zqadiri           #+#    #+#             */
/*   Updated: 2021/01/08 09:29:59 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*new;

	new = (char *)malloc(n + 1);
	if (new == NULL)
		return (NULL);
	new[n] = '\0';
	return ((char *)ft_memcpy(new, s, n));
}
