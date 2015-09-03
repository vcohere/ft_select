/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcohere <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 14:37:18 by vcohere           #+#    #+#             */
/*   Updated: 2015/03/08 14:37:19 by vcohere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void				get_up(t_lst *list)
{
	t_lst			*browser;

	browser = list;
	while (browser->next != NULL)
	{
		if (browser->next && browser->next->slct == 1)
		{
			browser->slct = 1;
			browser->next->slct = 0;
			return ;
		}
		browser = browser->next;
	}
	list->slct = 0;
	browser->slct = 1;
}

void				get_down(t_lst *list)
{
	t_lst			*browser;

	browser = list;
	while (browser != NULL)
	{
		if (browser->slct == 1)
		{
			browser->slct = 0;
			if (!browser->next)
				list->slct = 1;
			else
				browser->next->slct = 1;
			return ;
		}
		browser = browser->next;
	}
}
