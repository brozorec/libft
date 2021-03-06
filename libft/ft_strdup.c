/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 18:24:05 by bbarakov          #+#    #+#             */
/*   Updated: 2014/11/05 19:53:08 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*copy;

	len = ft_strlen(s1) + 1;
	copy = (char *)malloc(len * sizeof(*copy));
	if (copy == 0)
		return (0);
	ft_memcpy(copy, s1, len);
	return (copy);
}
