/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Screen.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 17:50:04 by sraccah           #+#    #+#             */
/*   Updated: 2016/05/12 19:35:41 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <locale.h>
#include "Screen.hpp"

Screen::Screen(void) {
	setlocale(LC_ALL,"");
	// Initialisation
	initscr();
	// Clear screen
  	clear();
  	// User input not displayed
  	noecho();
  	// User input does not require newline
  	cbreak();
  	// Special user input does not generate a signal and is passed to program instead
  	raw();
  	// getch does not wait for user input
  	nodelay(stdscr, TRUE);
  	// Preparing the keypad and cursor
  	keypad(stdscr, TRUE);
  	curs_set(0);
  	// Initialising colors we will use
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	// init_pair(2, COLOR_RED, COLOR_BLACK);
	// init_pair(3, COLOR_BLUE, COLOR_BLACK);
	// init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	// init_pair(5, COLOR_BLACK, COLOR_BLACK);
	init_pair(50, COLOR_BLACK, COLOR_YELLOW);
	init_pair(51, COLOR_BLACK, COLOR_WHITE);
	init_pair(52, COLOR_WHITE, COLOR_RED);
	init_pair(53, COLOR_WHITE, COLOR_CYAN);
	init_pair(54, COLOR_WHITE, COLOR_BLUE);
	init_pair(55, COLOR_WHITE, COLOR_GREEN);

	attron(COLOR_PAIR(1));
	attron(A_BOLD);
	printw("Screen created...\n");
	attroff(A_BOLD);
	attroff(COLOR_PAIR(1));
	return ;
}

Screen::Screen(Screen const & src) { *this = src; }

Screen& Screen::operator=(Screen const & rhs) { static_cast<void>(rhs);	return *this; }

Screen::~Screen(void) { endwin(); }

void		Screen::hello() {
	move((LINES/2) - 1, (COLS/2) - 2);
	attron(COLOR_PAIR(1));
	attron(A_BOLD);
	printw("RUBIK");
	attroff(A_BOLD);
	attroff(COLOR_PAIR(1));

	move((LINES/2), (COLS/2) - 11);
	attron(COLOR_PAIR(1));
	attron(A_BOLD);
	printw("Press any key to start");
	attroff(A_BOLD);
	attroff(COLOR_PAIR(1));

	move((LINES/2) + 1, (COLS/2) - 8);
	attron(COLOR_PAIR(1));
	attron(A_BOLD);
	printw("Press Q to Quit");
	attroff(A_BOLD);
	attroff(COLOR_PAIR(1));
}
