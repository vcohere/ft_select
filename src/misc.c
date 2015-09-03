/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcohere <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 15:11:52 by vcohere           #+#    #+#             */
/*   Updated: 2015/03/08 15:11:53 by vcohere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int					ft_outc(int c)
{
	ft_putchar(c);
	return (0);
}

void				ft_puterror(char *str)
{
	clear_my_screen();
	tputs(tgetstr("ve", NULL), 0, ft_outc);
	ft_putendl_fd(str, 2);
	exit(-1);
}

void				quit_me(void)
{
	clear_my_screen();
	tputs(tgetstr("ve", NULL), 0, ft_outc);
	exit(0);
}

static void			delete_me(t_lst *list, t_lst *browser)
{
	if (browser->next && browser->next->slct)
	{
		if (browser->next->next)
		{
			browser->next->next->slct = 1;
			free(browser->next->str);
			free(browser->next);
			browser->next = browser->next->next;
		}
		else
		{
			list->slct = 1;
			free(browser->next->str);
			free(browser->next);
			browser->next = NULL;
		}
	}
}

t_lst				*delete_item(t_lst *list)
{
	t_lst			*browser;

	browser = list;
	if (!list->next)
		quit_me();
	if (browser->slct)
	{
		list->next->slct = 1;
		return (list->next);
	}
	while (browser != NULL)
	{
		delete_me(list, browser);
		browser = browser->next;
	}
	return (list);
}
