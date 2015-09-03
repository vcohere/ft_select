/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcohere <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 12:26:28 by vcohere           #+#    #+#             */
/*   Updated: 2015/03/08 12:26:29 by vcohere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void				print_da_list(t_lst *list)
{
	t_lst			*browser;

	browser = list;
	clear_my_screen();
	if (!check_size(list))
	{
		ft_putstr("TOO SMALL !");
		return ;
	}
	while (browser != NULL)
	{
		if (browser->slct == 1)
			tputs(tgetstr("us", NULL), 0, ft_outc);
		if (browser->chck == 1)
			tputs(tgetstr("so", NULL), 0, ft_outc);
		ft_putendl(browser->str);
		tputs(tgetstr("ue", NULL), 0, ft_outc);
		tputs(tgetstr("se", NULL), 0, ft_outc);
		browser = browser->next;
	}
}

static void			select_me(t_lst *list)
{
	t_lst			*browser;

	browser = list;
	while (browser != NULL)
	{
		if (browser->slct == 1)
		{
			browser->chck = !browser->chck;
			get_down(list);
			return ;
		}
		browser = browser->next;
	}
}

static void			return_things(t_lst *list)
{
	t_lst			*browser;
	int				i;

	browser = list;
	i = 0;
	clear_my_screen();
	while (browser != NULL)
	{
		if (browser->chck)
		{
			if (i > 0)
				ft_putchar(' ');
			ft_putstr(browser->str);
			i++;
		}
		browser = browser->next;
	}
	tputs(tgetstr("ve", NULL), 0, ft_outc);
	exit(0);
}

void				good_while(t_lst *list)
{
	char			buf[4];

	print_da_list(list);
	while (1337)
	{
		ft_bzero(buf, 4);
		read(0, buf, sizeof(buf));
		if (buf[0] == 27 && buf[1] == 0)
			quit_me();
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
			get_up(list);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
			get_down(list);
		else if (buf[0] == ' ')
			select_me(list);
		else if (buf[0] == '\n')
			return_things(list);
		else if ((buf[0] == '\033' && buf[2] == '3' && buf[3] == '~')
				|| (buf[0] == 8 || buf[0] == 127))
			list = delete_item(list);
		if (list == NULL)
			quit_me();
		print_da_list(list);
	}
}

void				some_caps(struct termios term, t_lst *list)
{
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		ft_puterror("fatal error: tcsetattr");
	tputs(tgetstr("vi", NULL), 0, ft_outc);
	good_while(list);
}
