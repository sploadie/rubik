/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RubikCube.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 20:07:55 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/05/22 12:01:38 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RubikCube.hpp"

RubikCube::RubikCube( void ) { this->reset(); }

RubikCube::RubikCube( RubikCube const & obj ) { this->reset(); *this = obj; }

RubikCube::~RubikCube( void ) {}

RubikCube & RubikCube::operator=( RubikCube const & rhs ) {
	for (int i=0;i<6;++i) {
		for (int j=0;j<9;++j) {
			this->_faces[i].face[j] = rhs._faces[i].face[j];
		}
	}
	return *this;
}

RubikFace & RubikCube::operator[]( std::size_t index ) { return this->_faces[index]; }

void RubikCube::reset( void ) {
	// Set initial colors
	this->_faces[0].reset('U');
	this->_faces[1].reset('D');
	this->_faces[2].reset('L');
	this->_faces[3].reset('R');
	this->_faces[4].reset('F');
	this->_faces[5].reset('B');
	// Assign edges
	// Up
	//			North
	this->_faces[0].edges[0][0] = this->_faces[5].face + 2;
	this->_faces[0].edges[0][1] = this->_faces[5].face + 1;
	this->_faces[0].edges[0][2] = this->_faces[5].face + 0;
	//			East
	this->_faces[0].edges[1][0] = this->_faces[3].face + 2;
	this->_faces[0].edges[1][1] = this->_faces[3].face + 1;
	this->_faces[0].edges[1][2] = this->_faces[3].face + 0;
	//			South
	this->_faces[0].edges[2][0] = this->_faces[4].face + 2;
	this->_faces[0].edges[2][1] = this->_faces[4].face + 1;
	this->_faces[0].edges[2][2] = this->_faces[4].face + 0;
	//			West
	this->_faces[0].edges[3][0] = this->_faces[2].face + 2;
	this->_faces[0].edges[3][1] = this->_faces[2].face + 1;
	this->_faces[0].edges[3][2] = this->_faces[2].face + 0;
	// Down
	//			North
	this->_faces[1].edges[0][0] = this->_faces[2].face + 6;
	this->_faces[1].edges[0][1] = this->_faces[2].face + 7;
	this->_faces[1].edges[0][2] = this->_faces[2].face + 8;
	//			East
	this->_faces[1].edges[1][0] = this->_faces[4].face + 6;
	this->_faces[1].edges[1][1] = this->_faces[4].face + 7;
	this->_faces[1].edges[1][2] = this->_faces[4].face + 8;
	//			South
	this->_faces[1].edges[2][0] = this->_faces[3].face + 6;
	this->_faces[1].edges[2][1] = this->_faces[3].face + 7;
	this->_faces[1].edges[2][2] = this->_faces[3].face + 8;
	//			West
	this->_faces[1].edges[3][0] = this->_faces[5].face + 6;
	this->_faces[1].edges[3][1] = this->_faces[5].face + 7;
	this->_faces[1].edges[3][2] = this->_faces[5].face + 8;
	// Left
	//			North
	this->_faces[2].edges[0][0] = this->_faces[0].face + 0;
	this->_faces[2].edges[0][1] = this->_faces[0].face + 3;
	this->_faces[2].edges[0][2] = this->_faces[0].face + 6;
	//			East
	this->_faces[2].edges[1][0] = this->_faces[4].face + 0;
	this->_faces[2].edges[1][1] = this->_faces[4].face + 3;
	this->_faces[2].edges[1][2] = this->_faces[4].face + 6;
	//			South
	this->_faces[2].edges[2][0] = this->_faces[1].face + 2;
	this->_faces[2].edges[2][1] = this->_faces[1].face + 1;
	this->_faces[2].edges[2][2] = this->_faces[1].face + 0;
	//			West
	this->_faces[2].edges[3][0] = this->_faces[5].face + 8;
	this->_faces[2].edges[3][1] = this->_faces[5].face + 5;
	this->_faces[2].edges[3][2] = this->_faces[5].face + 2;
	// Right
	//			North
	this->_faces[3].edges[0][0] = this->_faces[0].face + 8;
	this->_faces[3].edges[0][1] = this->_faces[0].face + 5;
	this->_faces[3].edges[0][2] = this->_faces[0].face + 2;
	//			East
	this->_faces[3].edges[1][0] = this->_faces[5].face + 0;
	this->_faces[3].edges[1][1] = this->_faces[5].face + 3;
	this->_faces[3].edges[1][2] = this->_faces[5].face + 6;
	//			South
	this->_faces[3].edges[2][0] = this->_faces[1].face + 6;
	this->_faces[3].edges[2][1] = this->_faces[1].face + 7;
	this->_faces[3].edges[2][2] = this->_faces[1].face + 8;
	//			West
	this->_faces[3].edges[3][0] = this->_faces[4].face + 8;
	this->_faces[3].edges[3][1] = this->_faces[4].face + 5;
	this->_faces[3].edges[3][2] = this->_faces[4].face + 2;
	// Front
	//			North
	this->_faces[4].edges[0][0] = this->_faces[0].face + 6;
	this->_faces[4].edges[0][1] = this->_faces[0].face + 7;
	this->_faces[4].edges[0][2] = this->_faces[0].face + 8;
	//			East
	this->_faces[4].edges[1][0] = this->_faces[3].face + 0;
	this->_faces[4].edges[1][1] = this->_faces[3].face + 3;
	this->_faces[4].edges[1][2] = this->_faces[3].face + 6;
	//			South
	this->_faces[4].edges[2][0] = this->_faces[1].face + 8;
	this->_faces[4].edges[2][1] = this->_faces[1].face + 5;
	this->_faces[4].edges[2][2] = this->_faces[1].face + 2;
	//			West
	this->_faces[4].edges[3][0] = this->_faces[2].face + 8;
	this->_faces[4].edges[3][1] = this->_faces[2].face + 5;
	this->_faces[4].edges[3][2] = this->_faces[2].face + 2;
	// Back
	//			North
	this->_faces[5].edges[0][0] = this->_faces[0].face + 2;
	this->_faces[5].edges[0][1] = this->_faces[0].face + 1;
	this->_faces[5].edges[0][2] = this->_faces[0].face + 0;
	//			East
	this->_faces[5].edges[1][0] = this->_faces[2].face + 0;
	this->_faces[5].edges[1][1] = this->_faces[2].face + 3;
	this->_faces[5].edges[1][2] = this->_faces[2].face + 6;
	//			South
	this->_faces[5].edges[2][0] = this->_faces[1].face + 0;
	this->_faces[5].edges[2][1] = this->_faces[1].face + 3;
	this->_faces[5].edges[2][2] = this->_faces[1].face + 6;
	//			West
	this->_faces[5].edges[3][0] = this->_faces[3].face + 8;
	this->_faces[5].edges[3][1] = this->_faces[3].face + 5;
	this->_faces[5].edges[3][2] = this->_faces[3].face + 2;
}

void RubikCube::apply( std::string commands ) {
	std::string list(commands);
	std::string cmd;
	std::size_t pos;

	while (list.size() > 0) {
		// std::cout << list << std::endl;
		pos = list.find_first_of(" \n");
		cmd = list.substr(0, pos);
		if (pos != std::string::npos) ++pos;
		list.erase(0, pos);
		if (cmd == "") {
			// Skip
		} else if (cmd == "U")	{ this->_faces[0].rotate_cc(); // UP C
		} else if (cmd == "U'")	{ this->_faces[0].rotate_c();  // UP CC
		} else if (cmd == "U2")	{ this->_faces[0].rotate_2();  // UP 180
		} else if (cmd == "F")	{ this->_faces[4].rotate_cc(); // FRONT C
		} else if (cmd == "F'")	{ this->_faces[4].rotate_c();  // FRONT CC
		} else if (cmd == "F2")	{ this->_faces[4].rotate_2();  // FRONT 180
		} else if (cmd == "R")	{ this->_faces[3].rotate_cc(); // RIGHT C
		} else if (cmd == "R'")	{ this->_faces[3].rotate_c();  // RIGHT CC
		} else if (cmd == "R2")	{ this->_faces[3].rotate_2();  // RIGHT 180
		} else if (cmd == "B")	{ this->_faces[5].rotate_cc(); // BACK C
		} else if (cmd == "B'")	{ this->_faces[5].rotate_c();  // BACK CC
		} else if (cmd == "B2")	{ this->_faces[5].rotate_2();  // BACK 180
		} else if (cmd == "L")	{ this->_faces[2].rotate_cc(); // LEFT C
		} else if (cmd == "L'")	{ this->_faces[2].rotate_c();  // LEFT CC
		} else if (cmd == "L2")	{ this->_faces[2].rotate_2();  // LEFT 180
		} else if (cmd == "D")	{ this->_faces[1].rotate_cc(); // DOWN C
		} else if (cmd == "D'")	{ this->_faces[1].rotate_c();  // DOWN CC
		} else if (cmd == "D2")	{ this->_faces[1].rotate_2();  // DOWN 180
		} else { throw std::exception(); }
	}
}

void RubikCube::draw_block( int x, int y, int c ) {
	attron(COLOR_PAIR(c >> 8));
	mvaddch(x, y, ((c << 8) >> 8) + '0');
	attroff(COLOR_PAIR(c >> 8));
}

void RubikCube::draw( void ) {
	// Up
	this->draw_block( 2,  7, this->_faces[0].face[0]);//, '0');
	this->draw_block( 3,  9, this->_faces[0].face[1]);//, '1');
	this->draw_block( 4, 11, this->_faces[0].face[2]);//, '2');
	this->draw_block( 3,  5, this->_faces[0].face[3]);//, '3');
	this->draw_block( 4,  7, this->_faces[0].face[4]);//, '4');
	this->draw_block( 5,  9, this->_faces[0].face[5]);//, '5');
	this->draw_block( 4,  3, this->_faces[0].face[6]);//, '6');
	this->draw_block( 5,  5, this->_faces[0].face[7]);//, '7');
	this->draw_block( 6,  7, this->_faces[0].face[8]);//, '8');
	// Down
	this->draw_block( 5, 19, this->_faces[1].face[0]);//, '0');
	this->draw_block( 6, 21, this->_faces[1].face[1]);//, '1');
	this->draw_block( 7, 23, this->_faces[1].face[2]);//, '2');
	this->draw_block( 6, 17, this->_faces[1].face[3]);//, '3');
	this->draw_block( 7, 19, this->_faces[1].face[4]);//, '4');
	this->draw_block( 8, 21, this->_faces[1].face[5]);//, '5');
	this->draw_block( 7, 15, this->_faces[1].face[6]);//, '6');
	this->draw_block( 8, 17, this->_faces[1].face[7]);//, '7');
	this->draw_block( 9, 19, this->_faces[1].face[8]);//, '8');
	// Left
	this->draw_block( 2, 20, this->_faces[2].face[0]);//, '0');
	this->draw_block( 3, 22, this->_faces[2].face[1]);//, '1');
	this->draw_block( 4, 24, this->_faces[2].face[2]);//, '2');
	this->draw_block( 3, 20, this->_faces[2].face[3]);//, '3');
	this->draw_block( 4, 22, this->_faces[2].face[4]);//, '4');
	this->draw_block( 5, 24, this->_faces[2].face[5]);//, '5');
	this->draw_block( 4, 20, this->_faces[2].face[6]);//, '6');
	this->draw_block( 5, 22, this->_faces[2].face[7]);//, '7');
	this->draw_block( 6, 24, this->_faces[2].face[8]);//, '8');
	// Right
	this->draw_block( 7,  8, this->_faces[3].face[0]);//, '0');
	this->draw_block( 6, 10, this->_faces[3].face[1]);//, '1');
	this->draw_block( 5, 12, this->_faces[3].face[2]);//, '2');
	this->draw_block( 8,  8, this->_faces[3].face[3]);//, '3');
	this->draw_block( 7, 10, this->_faces[3].face[4]);//, '4');
	this->draw_block( 6, 12, this->_faces[3].face[5]);//, '5');
	this->draw_block( 9,  8, this->_faces[3].face[6]);//, '6');
	this->draw_block( 8, 10, this->_faces[3].face[7]);//, '7');
	this->draw_block( 7, 12, this->_faces[3].face[8]);//, '8');
	// Front
	this->draw_block( 5,  2, this->_faces[4].face[0]);//, '0');
	this->draw_block( 6,  4, this->_faces[4].face[1]);//, '1');
	this->draw_block( 7,  6, this->_faces[4].face[2]);//, '2');
	this->draw_block( 6,  2, this->_faces[4].face[3]);//, '3');
	this->draw_block( 7,  4, this->_faces[4].face[4]);//, '4');
	this->draw_block( 8,  6, this->_faces[4].face[5]);//, '5');
	this->draw_block( 7,  2, this->_faces[4].face[6]);//, '6');
	this->draw_block( 8,  4, this->_faces[4].face[7]);//, '7');
	this->draw_block( 9,  6, this->_faces[4].face[8]);//, '8');
	// Back
	this->draw_block( 4, 14, this->_faces[5].face[0]);//, '0');
	this->draw_block( 3, 16, this->_faces[5].face[1]);//, '1');
	this->draw_block( 2, 18, this->_faces[5].face[2]);//, '2');
	this->draw_block( 5, 14, this->_faces[5].face[3]);//, '3');
	this->draw_block( 4, 16, this->_faces[5].face[4]);//, '4');
	this->draw_block( 3, 18, this->_faces[5].face[5]);//, '5');
	this->draw_block( 6, 14, this->_faces[5].face[6]);//, '6');
	this->draw_block( 5, 16, this->_faces[5].face[7]);//, '7');
	this->draw_block( 4, 18, this->_faces[5].face[8]);//, '8');
}
