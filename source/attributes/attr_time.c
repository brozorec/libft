/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attr_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 11:53:15 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/19 16:46:31 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_ls_prototypes.h"

void		put_month_day(char *month, char *day)
{
	ft_putstr(month);
	ft_putstr(" ");
	if (ft_strlen(day) == 1)
		ft_putstr(" ");
	ft_putstr(day);
	ft_putstr(" ");
}

void		put_hour(char *h, char *min)
{
	ft_putstr(h);
	ft_putstr(":");
	ft_putstr(min);
}

void		file_time(long mtime)
{
	char	**tab;
	char	**tab_h;
	long	now;

	tab = 0;
	tab_h = 0;
	now = time(0);
	tab = ft_strsplit(ctime(&mtime), ' ');
	tab_h = ft_strsplit(tab[3], ':');
	put_month_day(tab[1], tab[2]);
	if (now - 15724763 > mtime || mtime > now)
	{
		ft_putstr(" ");
		tab[4][4] = '\0';
		ft_putstr(tab[4]);
	}
	else
		put_hour(tab_h[0], tab_h[1]);
	ft_putstr(" ");
	ft_strdel(tab);
	ft_strdel(tab_h);
}
