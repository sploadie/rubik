/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/06 20:50:12 by sraccah           #+#    #+#             */
/*   Updated: 2016/05/22 11:36:21 by tgauvrit         ###   ########.fr       */
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

// static int clockToMilliseconds(clock_t ticks) {
// 	return (ticks * 1000)/CLOCKS_PER_SEC;
// }

static int clockToUseconds(clock_t ticks) {
	return (ticks * 1000000) / CLOCKS_PER_SEC;
}

static void print_debug_data( unsigned int frame_count, clock_t loop_remaining_time ) {
	// Display frames
	move(0, 0);
	attron(COLOR_PAIR(1));
	printw("Frame %d     ", frame_count);
	attroff(COLOR_PAIR(1));
	// Display remaining milliseconds
	move(0, 20);
	attron(COLOR_PAIR(1));
	printw("Useconds: %d     ", loop_remaining_time);
	attroff(COLOR_PAIR(1));
}

void draw_screen( std::string args, RubikCube cube, std::string solution ) {
	static unsigned int frame_count = 0;
	clock_t loop_time;
	static clock_t loop_start_time = 0;

	// Debugging
	frame_count++;
	loop_time = clockToUseconds(clock()) - clockToUseconds(loop_start_time);
	loop_start_time = clock();
	print_debug_data(frame_count, loop_time);

	// Drawing
	cube.draw();
	// Arguments
	move(11, 0);
	attron(COLOR_PAIR(1));
	printw("Arguments:");
	printw(args.c_str());
	attroff(COLOR_PAIR(1));
	// Mike
	attron(COLOR_PAIR(1));
	std::string *mike = cube.getMikeFormat();
	printw("\nMike Reid's Format:");
	for (int i = 0; i < 20; ++i) {
		printw(" ");
		printw(mike[i].c_str());
	}
	attroff(COLOR_PAIR(1));
	// Solution
	if (solution != "") {
		attron(COLOR_PAIR(1));
		printw("\nSolution:");
		printw(solution.c_str());
		attroff(COLOR_PAIR(1));
	}
}

void game_loop( RubikCube & cube, std::string & args ) {
	int ch;
	bool doSolve = false;

	// Main loop
	while (42) {
		// Read Input (Also calls refresh)
		// refresh();
		ch = getch();
		// clear();

		// if (ch == KEY_LEFT) {
		if (ch == 'q' || ch == 'Q') {
			break;
		} else if (ch == 'w') { cube[0].rotate_c();  args.append(" U");  // UP C
		} else if (ch == 'e') { cube[0].rotate_cc(); args.append(" U'"); // UP CC
		} else if (ch == 'r') { cube[0].rotate_2();  args.append(" U2"); // UP 180
		} else if (ch == 'a') { cube[4].rotate_c();  args.append(" F");  // FRONT C
		} else if (ch == 's') { cube[4].rotate_cc(); args.append(" F'"); // FRONT CC
		} else if (ch == 'd') { cube[4].rotate_2();  args.append(" F2"); // FRONT 180
		} else if (ch == 'z') { cube[3].rotate_c();  args.append(" R");  // RIGHT C
		} else if (ch == 'x') { cube[3].rotate_cc(); args.append(" R'"); // RIGHT CC
		} else if (ch == 'c') { cube[3].rotate_2();  args.append(" R2"); // RIGHT 180
		} else if (ch == 't') { cube[5].rotate_c();  args.append(" B");  // BACK C
		} else if (ch == 'y') { cube[5].rotate_cc(); args.append(" B'"); // BACK CC
		} else if (ch == 'u') { cube[5].rotate_2();  args.append(" B2"); // BACK 180
		} else if (ch == 'g') { cube[2].rotate_c();  args.append(" L");  // LEFT C
		} else if (ch == 'h') { cube[2].rotate_cc(); args.append(" L'"); // LEFT CC
		} else if (ch == 'j') { cube[2].rotate_2();  args.append(" L2"); // LEFT 180
		} else if (ch == 'v') { cube[1].rotate_c();  args.append(" D");  // DOWN C
		} else if (ch == 'b') { cube[1].rotate_cc(); args.append(" D'"); // DOWN CC
		} else if (ch == 'n') { cube[1].rotate_2();  args.append(" D2"); // DOWN 180
		} else if (ch == ' ') {
			doSolve = true;
			break;
		}
		draw_screen(args, cube, "");
	}
	if (doSolve) {
		clock_t loop_time = 400000;
		clock_t loop_start_time = clockToUseconds(clock());
		std::string solution = solve(cube.getMikeFormat());
		std::string solution_buffer;
		std::string cmd;
		std::size_t pos;
		while (42) {
			ch = getch();
			if (ch == 'q' || ch == 'Q')
				break;
			// Timing
			if (clockToUseconds(clock()) - loop_start_time < loop_time)
				continue;
			loop_start_time = clockToUseconds(clock());
			// Solution
			pos = solution.find_first_of(" \n");
			cmd = solution.substr(0, pos);
			cube.apply(cmd);
			solution_buffer += ' ';
			solution_buffer += cmd;
			if (pos != std::string::npos) ++pos;
			solution.erase(0, pos);
			draw_screen(args, cube, solution_buffer);
			if (solution.size() == 0)
				break;
		}
		attron(COLOR_PAIR(1));
		attron(A_BOLD);
		printw("\nPress Q to Quit");
		attroff(A_BOLD);
		attroff(COLOR_PAIR(1));
		while (42) {
			nodelay(stdscr, FALSE);
			ch = getch();
			if (ch == 'q' || ch == 'Q')
				break;
		}
	}
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
	RubikCube cube;
	bool verbose = false;
	bool interactive = false;
	std::string args;
	std::string *mike;
	std::string solution;

	while (true) {
		if (argc > 1) {
			if (std::string(argv[1]) == "-i") {
				// Interactive
				interactive = true;
			} else if (std::string(argv[1]) == "-v") {
				// Verbose
				verbose = true;
			} else if (std::string(argv[1]) == "-vi" || std::string(argv[1]) == "-iv") {
				// Both
				interactive = true;
				verbose = true;
			} else {
				break;
			}
			--argc;
			++argv;
			continue;
		}
		break;
	}

	// Combine arguments and pass to cube
	if (argc > 1) {
		for (int i = 1; i < argc; ++i) {
			args.append(" ");
			args.append(argv[i]);
		}
		std::transform(args.begin(), args.end(), args.begin(), upcase);
	}
	if (args.size() > 0) cube.apply(args);

	if (interactive) {
		// Start ncurses
		Screen * 	scr = new Screen();
		// Handle Screen Size
		if (LINES < Screen::Height || COLS < Screen::Width) {
			endwin();
			std::cerr << "Error: Screen too small" << std::endl;
			return 0;
		}
		signal(SIGWINCH, &resizeHandler);
		// // Display an intro message
		// scr->hello();
		// // Wait until the user press a key
		// nodelay(stdscr, FALSE);
		// if (getch() == 'q') { return 0; }
		nodelay(stdscr, TRUE);
		// Clear the screen before game loop
		clear();
		// GAME LOOP
		game_loop(cube, args);
		delete scr;
	}
	mike = cube.getMikeFormat();
	solution = solve(mike);
	if (verbose) {
		std::cerr << "Arguments:" << args << std::endl;
		std::cerr << "Mike Reid's Format:";
		for (int i = 0; i < 20; ++i) {
			std::cerr << ' ' << mike[i];
		}
		std::cerr << std::endl << "Solution: " << solution << std::endl;
	} else {
		std::cout << solution << std::endl;
	}
	return 0;
}
