/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 23:22:23 by zqadiri           #+#    #+#             */
/*   Updated: 2019/10/24 23:32:20 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	size;
	char			*tab;

	size = 0;
	if (s == 0)
		return (NULL);
	while (s[size] != '\0')
		size++;
	tab = (char *)malloc((size + 1) * sizeof(char));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		tab[i] = (*f)(i, s[i]);
		i++;
	}
	*(tab + i) = '\0';
	return (tab);
}
