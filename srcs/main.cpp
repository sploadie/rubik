/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/06 20:50:12 by sraccah           #+#    #+#             */
/*   Updated: 2016/05/12 19:52:52 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <curses.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <signal.h>
#include "Screen.hpp"

// static void		print_data(int row, int col, int hp, int frame_count, int loop_remaining_time)
// {
// 	int 		i;

// 	i = 0;
// 	// Draw a limit for data display
// 	move(LINES-2, 0);
// 	while (i++ < COLS)
// 		printw("-");
// 	// Moving just above the end of the screen
// 	move(LINES-1, 0);
// 	attron(COLOR_PAIR(1));
// 	attron(A_BOLD);
// 	// Display player position just above the bottom of the screen
// 	printw("Player pos = ");
// 	attron(COLOR_PAIR(4));
// 	printw("%d", row);
// 	attron(COLOR_PAIR(1));
// 	printw(" - ");
// 	attron(COLOR_PAIR(4));
// 	printw("%d", col);
// 	// Display the score just above the end of the screen in the middle of COLS
// 	move(LINES-1, (COLS/2)-5);
// 	attron(COLOR_PAIR(3));
// 	printw("Health = %d", hp);
// 	move(LINES-1, COLS-12);
// 	attron(COLOR_PAIR(2));
// 	printw("Score = %d", g_score);
// 	attroff(A_BOLD);
// 	attroff(COLOR_PAIR(2));
// 	// Display frames
// 	move(0, 0);
// 	attron(COLOR_PAIR(4));
// 	printw("Frame %d", frame_count);
// 	attroff(COLOR_PAIR(4));
// 	// Display remaining milliseconds
// 	move(0, 20);
// 	attron(COLOR_PAIR(4));
// 	printw("Remaining Useconds: %d", loop_remaining_time);
// 	attroff(COLOR_PAIR(4));
// }

// static void		print_gameover()
// {
// 	move((LINES/2) - 1, (COLS/2) - 5);
// 	attron(COLOR_PAIR(1));
// 	attron(A_BOLD);
// 	printw("GAME OVER");
// 	attroff(A_BOLD);
// 	attroff(COLOR_PAIR(1));

// 	move((LINES/2) + 1, (COLS/2) - 8);
// 	attron(COLOR_PAIR(1));
// 	attron(A_BOLD);
// 	printw("Press Q to Quit");
// 	attroff(A_BOLD);
// 	attroff(COLOR_PAIR(1));
// }

int	 clockToMilliseconds(clock_t ticks) {
	return (ticks * 1000)/CLOCKS_PER_SEC;
}

int	 clockToUseconds(clock_t ticks) {
	return (ticks * 1000000)/CLOCKS_PER_SEC;
}

static void		print_debug_data(unsigned int frame_count, clock_t loop_remaining_time) {
	// Display frames
	move(0, 0);
	attron(COLOR_PAIR(1));
	printw("Frame %d", frame_count);
	attroff(COLOR_PAIR(1));
	// Display remaining milliseconds
	move(0, 20);
	attron(COLOR_PAIR(1));
	printw("Useconds: %d", loop_remaining_time);
	attroff(COLOR_PAIR(1));
}

static void		game_loop(void) {
	int ch;
	unsigned int frame_count = 0;
	clock_t loop_time;
	clock_t loop_start_time = 0;

	// Command History
	std::string history;

	// Main loop
	while (42) {
		frame_count++;
		loop_time = clockToUseconds(clock()) - clockToUseconds(loop_start_time);
		loop_start_time = clock();

		// Read Input (Also calls refresh)
		ch = getch();
		clear();
		print_debug_data(frame_count, loop_time);
		// if (ch == KEY_LEFT) {
		if (ch == 'q' || ch == 'Q') {
			break;
		} else if (ch == 'w') { // UP C
		} else if (ch == 'e') { // UP CC
		} else if (ch == 'r') { // UP 180
		} else if (ch == 'a') { // FRONT C
		} else if (ch == 's') { // FRONT CC
		} else if (ch == 'd') { // FRONT 180
		} else if (ch == 'z') { // RIGHT C
		} else if (ch == 'x') { // RIGHT CC
		} else if (ch == 'c') { // RIGHT 180
		} else if (ch == 't') { // BACK C
		} else if (ch == 'y') { // BACK CC
		} else if (ch == 'u') { // BACK 180
		} else if (ch == 'g') { // LEFT C
		} else if (ch == 'h') { // LEFT CC
		} else if (ch == 'j') { // LEFT 180
		} else if (ch == 'v') { // DOWN C
		} else if (ch == 'b') { // DOWN CC
		} else if (ch == 'n') { // DOWN 180
		}
		// Draw here
		// ...
	}
}

void resizeHandler(int sig) {
	(void)sig;
	if (LINES < Screen::Height || COLS < Screen::Width) {
		endwin();
		std::cerr << "Error: Screen became too small" << std::endl;
		exit(1);
	}
}

int	main( void ) {
	// Start ncurses
	Screen 		scr;
	// Handle Screen Size
	if (LINES < Screen::Height || COLS < Screen::Width) {
		endwin();
		std::cerr << "Error: Screen too small" << std::endl;
		return 0;
	}
	signal(SIGWINCH, &resizeHandler);

	// Display an intro message
	scr.hello();
	// Wait until the user press a key
	nodelay(stdscr, FALSE);
	if (getch() == 'q') { return 0; }
	nodelay(stdscr, TRUE);
	// Clear the screen before game loop
	clear();

	// GAME LOOP
	game_loop();
	
	return 0;
}
