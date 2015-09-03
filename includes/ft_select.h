/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcohere <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 12:02:25 by vcohere           #+#    #+#             */
/*   Updated: 2015/03/07 12:02:26 by vcohere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H
# include "../libft/includes/libft.h"
# include <unistd.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <stdio.h>

typedef struct			s_lst
{
	char				*str;
	int					chck;
	int					slct;
	struct s_lst		*next;
}						t_lst;
typedef struct termios	t_termios;

t_lst					*g_list;

void					clear_my_screen(void);
void					ft_puterror(char *str);
t_lst					*push_list(char *str, t_lst *lst);
void					some_caps(struct termios term, t_lst *list);
void					good_while(t_lst *list);
void					get_up(t_lst *list);
void					get_down(t_lst *list);
void					quit_me(void);
int						ft_outc(int c);
void					signal_handler(int sig);
t_termios				term_init(struct termios term);
t_lst					*delete_item(t_lst *list);
int						check_size(t_lst *list);
void					print_da_list(t_lst *list);

#endif
