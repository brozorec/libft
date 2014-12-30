/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 17:02:53 by bbarakov          #+#    #+#             */
/*   Updated: 2014/12/22 17:39:09 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void
	cont_init(t_cont **new, struct stat *buf)
{
	(*new)->mode = buf->st_mode;
	(*new)->nlink = buf->st_nlink;
	(*new)->uid = buf->st_uid;
	(*new)->gid = buf->st_gid;
	(*new)->rdev = buf->st_rdev;
	(*new)->size = buf->st_size;
	(*new)->blocks = buf->st_blocks;
	(*new)->mtime = buf->st_mtime;
}

t_cont
	*create_new(char *name, t_cont *new, struct stat *buf, t_option option)
{
	if ((new = (t_cont *)malloc(sizeof(t_cont))) == 0)
		return (0);
	if (buf != 0)
		cont_init(&new, buf);
	new->name = ft_strdup(name);
	new->next = 0;
	if (option.t == 0 || buf == 0)
	{
		new->val = (char *)malloc(ft_strlen(name) + 1);
		ft_memcpy(new->val, name, ft_strlen(name) + 1);
	}
	else
	{
		new->val = (long *)malloc(sizeof(long *));
		new->val = (void *)new->mtime;
	}
	return (new);
}

int
	detect_type(char *name, char *path, t_cont **new, t_option option)
{
	struct stat			buf;
	int					i;

	if (option.l == 0)
		i = stat(path, &buf);
	else
		i = lstat(path, &buf);
	if (i == -1)
	{
		*new = create_new(name, *new, 0, option);
		return (-1);
	}
	*new = create_new(name, *new, &buf, option);
	(*new)->path = ft_strdup(path);
	if (S_ISDIR(buf.st_mode))
		return (2);
	else
		return (1);
/*
 *	other types
 */
	return (0);
}

int
	fill_list(t_cont **lst, t_cont *new, t_option option)
{
	if (option.emp_tr == 1)
		add(lst, new, option, &ft_strcmp);
	else if (option.t == 1 && option.r == 1)
		add(lst, new, option, &ft_numcmp);
	else if (option.t == 1 && option.r == 0)
		add(lst, new, option, &ft_numcmp_rev);
	else if (option.t == 0 && option.r == 1)
		add(lst, new, option, &ft_strcmp_rev);
	return (0);
}

void
	collect_params(char *name, t_option option, t_param *lst)
{
	t_cont				*new;
	int					i;

	new = 0;
	i = detect_type(name, name, &new, option);
	if (i == -1)
		add(&(lst->err), new, option, &ft_strcmp);
	else if (i == 1)
		fill_list(&(lst->file), new, option);
	else if (i == 2)
	{
		fill_list(&(lst->dir), new, option);
		lst->dir_num++;
		lst->counter++;
	}
}
