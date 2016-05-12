/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Screen.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 17:49:12 by sraccah           #+#    #+#             */
/*   Updated: 2016/05/12 19:41:25 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCREEN_HPP
# define SCREEN_HPP

# include <iostream>
# include <curses.h>

class Screen {
public:
	Screen(void);
	Screen(Screen const & src);
	Screen& operator=(Screen const & rhs);
	~Screen(void);
	void	hello();

	static int const	Width  = 100;
	static int const	Height = 10;

};

#endif
