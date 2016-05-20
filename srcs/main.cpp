/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/06 20:50:12 by sraccah           #+#    #+#             */
/*   Updated: 2016/05/20 20:02:07 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <curses.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <string>
#include <algorithm>
#include <signal.h>
#include "Screen.hpp"
#include "RubikCube.hpp"

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

// static int clockToMilliseconds(clock_t ticks) {
// 	return (ticks * 1000)/CLOCKS_PER_SEC;
// }

static int clockToUseconds(clock_t ticks) {
	return (ticks * 1000000)/CLOCKS_PER_SEC;
}

static void print_debug_data( unsigned int frame_count, clock_t loop_remaining_time ) {
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

static std::string game_loop( RubikCube cube ) {
	int ch;
	unsigned int frame_count = 0;
	clock_t loop_time;
	clock_t loop_start_time = 0;

	// Command History
	std::string history;

	// To solve or not to solve
	bool solve = false;

	// Main loop
	while (42) {
		frame_count++;
		loop_time = clockToUseconds(clock()) - clockToUseconds(loop_start_time);
		loop_start_time = clock();

		// Read Input (Also calls refresh)
		// refresh();
		ch = getch();
		// clear();
		print_debug_data(frame_count, loop_time);
		// if (ch == KEY_LEFT) {
		if (ch == 'q' || ch == 'Q') {
			break;
		} else if (ch == 'w') { cube[0].rotate_cc(); history.append(" U");  // UP C
		} else if (ch == 'e') { cube[0].rotate_c();  history.append(" U'"); // UP CC
		} else if (ch == 'r') { cube[0].rotate_2();  history.append(" U2"); // UP 180
		} else if (ch == 'a') { cube[4].rotate_cc(); history.append(" F");  // FRONT C
		} else if (ch == 's') { cube[4].rotate_c();  history.append(" F'"); // FRONT CC
		} else if (ch == 'd') { cube[4].rotate_2();  history.append(" F2"); // FRONT 180
		} else if (ch == 'z') { cube[3].rotate_cc(); history.append(" R");  // RIGHT C
		} else if (ch == 'x') { cube[3].rotate_c();  history.append(" R'"); // RIGHT CC
		} else if (ch == 'c') { cube[3].rotate_2();  history.append(" R2"); // RIGHT 180
		} else if (ch == 't') { cube[5].rotate_cc(); history.append(" B");  // BACK C
		} else if (ch == 'y') { cube[5].rotate_c();  history.append(" B'"); // BACK CC
		} else if (ch == 'u') { cube[5].rotate_2();  history.append(" B2"); // BACK 180
		} else if (ch == 'g') { cube[2].rotate_cc(); history.append(" L");  // LEFT C
		} else if (ch == 'h') { cube[2].rotate_c();  history.append(" L'"); // LEFT CC
		} else if (ch == 'j') { cube[2].rotate_2();  history.append(" L2"); // LEFT 180
		} else if (ch == 'v') { cube[1].rotate_cc(); history.append(" D");  // DOWN C
		} else if (ch == 'b') { cube[1].rotate_c();  history.append(" D'"); // DOWN CC
		} else if (ch == 'n') { cube[1].rotate_2();  history.append(" D2"); // DOWN 180
		} else if (ch == KEY_ENTER) {
			solve = true; break;
		}
		// Draw here
		cube.draw();
		move(11, 0);
		attron(COLOR_PAIR(1));
		printw("History:");
		printw(history.c_str());
		attroff(COLOR_PAIR(1));
	}

	if (solve) {
		// Solve
	}

	return history;
}

void resizeHandler( int sig ) {
	(void)sig;
	if (LINES < Screen::Height || COLS < Screen::Width) {
		endwin();
		std::cerr << "Error: Screen became too small" << std::endl;
		exit(1);
	}
}

char upcase(char c) { return std::toupper(c); }

int	main( int argc, char* argv[] ) {
	// Rubiks Cube
	RubikCube cube;

	// Combine arguments and pass to cube
	std::string args;
	if (argc > 1) {
		int i;
		for (i=1; i<argc; ++i) {
			if (args.size() != 0) args.append(" ");
			args.append(argv[i]);
		}
		std::transform(args.begin(), args.end(), args.begin(), upcase);
	}
	if (args.size() > 0) cube.apply(args);

	// Start ncurses
	Screen * 	scr = new Screen();

	// Handle Screen Size
	if (LINES < Screen::Height || COLS < Screen::Width) {
		endwin();
		std::cerr << "Error: Screen too small" << std::endl;
		return 0;
	}
	signal(SIGWINCH, &resizeHandler);

	// Display an intro message
	scr->hello();
	// Wait until the user press a key
	nodelay(stdscr, FALSE);
	if (getch() == 'q') { return 0; }
	nodelay(stdscr, TRUE);
	// Clear the screen before game loop
	clear();

	// Create history
	std::string history;

	// GAME LOOP
	history = game_loop(cube);
	history.erase(0,1);

	delete scr;
	// std::cout << "Input: " << history << std::endl;
	// std::cout << "History:" << history << std::endl;
	std::cout << history << std::endl;
	return 0;
}
