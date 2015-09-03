/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcohere <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 12:01:07 by vcohere           #+#    #+#             */
/*   Updated: 2015/03/07 12:01:08 by vcohere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_termios				term_init(struct termios term)
{
	char				*term_name;

	if ((term_name = getenv("TERM")) == NULL)
		ft_puterror("fatal error: env missing");
	if (tgetent(NULL, term_name) == ERR)
		ft_puterror("fatal error: cant initiate termcap");
	if (tcgetattr(0, &term) == -1)
		ft_puterror("fatal error: cant initiate termcap");
	return (term);
}

static t_lst			*get_args(char **av, t_lst *list)
{
	int					i;

	i = 0;
	while (av[++i])
		list = push_list(ft_strtrim(av[i]), list);
	return (list);
}

static void				much_signal(void)
{
	signal(SIGWINCH, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGCONT, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGKILL, signal_handler);
	signal(SIGQUIT, signal_handler);
}

t_lst					*push_list(char *str, t_lst *lst)
{
	t_lst				*nw;
	t_lst				*browser;

	if ((nw = (t_lst *)malloc(sizeof(t_lst))) == NULL)
		ft_puterror("fatal error: cant malloc");
	nw->str = str;
	nw->chck = 0;
	nw->next = NULL;
	if (lst == NULL)
	{
		nw->slct = 1;
		return (nw);
	}
	nw->slct = 0;
	browser = lst;
	while (browser->next != NULL)
		browser = browser->next;
	browser->next = nw;
	return (lst);
}

int						main(int ac, char **av)
{
	struct termios		term;
	t_lst				*list;

	list = NULL;
	if (ac < 2)
		ft_puterror("need moar arguments!");
	much_signal();
	term = term_init(term);
	list = get_args(av, list);
	tputs(tgetstr("cl", NULL), 0, ft_outc);
	g_list = list;
	some_caps(term, list);
	term.c_lflag = (ICANON | ECHO);
	tcsetattr(0, 0, &term);
	return (0);
}
