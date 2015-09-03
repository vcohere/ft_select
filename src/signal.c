/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcohere <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 16:22:31 by vcohere           #+#    #+#             */
/*   Updated: 2015/03/08 16:22:32 by vcohere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void					clear_my_screen(void)
{
	tputs(tgetstr("ho", NULL), 0, ft_outc);
	tputs(tgetstr("cd", NULL), 0, ft_outc);
}

void					signal_handler(int sig)
{
	struct termios		term;

	term = term_init(term);
	if (sig == SIGCONT)
	{
		term.c_lflag &= ~(ICANON);
		term.c_lflag &= ~(ECHO);
		term.c_cc[VMIN] = 1;
		term.c_cc[VTIME] = 0;
		if (tcsetattr(0, TCSADRAIN, &term) == -1)
			ft_puterror("fatal error: tcsetattr");
		tputs(tgetstr("vi", NULL), 0, ft_outc);
	}
	if (sig == SIGWINCH)
		print_da_list(g_list);
}

int						check_size(t_lst *list)
{
	struct winsize		w;
	int					i;
	t_lst				*browser;

	ioctl(STDOUT_FILENO, TIOCGSIZE, &w);
	i = 0;
	browser = list;
	while (browser != NULL)
	{
		if (ft_strlen(browser->str) > w.ws_col)
			return (0);
		i++;
		browser = browser->next;
	}
	if (i >= w.ws_row)
		return (0);
	return (1);
}
