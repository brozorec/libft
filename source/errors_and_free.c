/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_and_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 19:16:23 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/10 19:51:04 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_ls_prototypes.h"

void
	handle_err_eacces(char *s1, char *s2, t_option *option)
{
	(option->my_errno)++;
	if (errno == 13)
	{
		if (s1)
			write(2, s1, ft_strlen(s1));
		if (s2 != 0)
			perror(s2);
	}
}

void
	handle_err(char *s1, char *s2, t_option *option)
{
	(option->my_errno)++;
	if (s1)
		write(2, s1, ft_strlen(s1));
	if (s2 != 0)
		perror(s2);
}

void
	free_cont(t_cont *list, t_option option)
{
	t_cont		*copy;

	copy = list;
	while (copy)
	{
		copy = list->next;
		free(list->name);
		free(list->path);
		if (option.t == 0)
			free(list->val);
		free(list);
		list = copy;
	}
	free(copy);
}

void
	free_cont_err(t_cont *list)
{
	t_cont		*copy;

	copy = list;
	while (copy)
	{
		copy = list->next;
		free(list->name);
		free(list->val);
		free(list);
		list = copy;
	}
	free(copy);
}

void
	free_param(t_param *lst, t_option option)
{
	free_cont_err(lst->err);
	free_cont(lst->file, option);
	free_cont(lst->dir, option);
	free(lst);
}
