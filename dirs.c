/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/13 15:30:11 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/04 11:26:10 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int
	collect_content_dir(char *name, char *path, t_cont **list, t_option option)
{
	t_cont				*new;
	char				*path_new;

	new = 0;
	path_new = 0;
	if (ft_strcmp(path, "/") == 0)
		path_new = ft_strdup("/");
	else
		path_new = ft_strjoin(path, "/");
	path_new = ft_realloc(path_new, ft_strlen(name) + ft_strlen(path_new) + 10);
	path_new = ft_strcat(path_new, name);
	if (detect_type(name, path_new, &new, option) == -1)
	{
		free(path_new);
		return (-1);
	}
	fill_list(list, new, option);
	free(path_new);
	return (0);
}

int
	dir_tree(t_cont *list, t_param *lst, t_option option)
{
	struct stat			buf;

	while (list)
	{
		lstat(list->path, &buf);
		if (!ft_strcmp(list->name, ".") || !ft_strcmp(list->name, "..") ||
			S_ISLNK(buf.st_mode))
		{
			list = list->next;
			continue;
		}
		if (S_ISDIR(list->mode))
		{
			free(lst->dir_name);
			lst->dir_name = ft_strdup(list->name);
			lst->flag = 0;
			content_dir(list->path, lst, option);
		}
		list = list->next;
	}
	return (0);
}

void
	read_dir_loop(DIR *dirp, char *path, t_cont **list, t_option option)
{
	struct dirent		*entry;

	while (1)
	{
		errno = 0;
		if ((entry = readdir(dirp)) != 0)
			collect_content_dir(entry->d_name, path, list, option);
		if (entry == 0 && errno == 0)
			break ;
	}
}

void
	content_dir(char *path, t_param *lst, t_option option)
{
	DIR					*dirp;
	t_cont				*list;

	list = 0;
	errno = 0;
	if ((dirp = opendir(path)) != 0)
	{
		read_dir_loop(dirp, path, &list, option);
		if (list && (lst->flag == 1 || option.a == 1 ||
			(lst->dir_name[0] != '.' && option.a == 0)))
			print_dir_content(path, list, lst, option);
		closedir(dirp);
		if (option.recursive == 1)
			dir_tree(list, lst, option);
		free_cont(list, option);
	}
	else
	{
		if (errno != 14)
			handle_err_eacces("ft_ls: ", ft_strrchr(path, '/') + 1);
	}
}
