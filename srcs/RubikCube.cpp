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

// UF UR UB UL DF DR DB DL FR FL BR BL UFR URB UBL ULF DRF DFL DLB DBR
std::string * RubikCube::getMikeFormat( void ) {
	int i;
	for (i = 0; i < 20; ++i) {
		this->_mike[i] = "";
	}
	// First color of edges
	this->_mike[ 0] += static_cast<char>( this->_faces[0][7] >> 8 ); // UF
	this->_mike[ 1] += static_cast<char>( this->_faces[0][5] >> 8 ); // UR
	this->_mike[ 2] += static_cast<char>( this->_faces[0][1] >> 8 ); // UB
	this->_mike[ 3] += static_cast<char>( this->_faces[0][3] >> 8 ); // UL

	this->_mike[ 4] += static_cast<char>( this->_faces[1][5] >> 8 ); // DF
	this->_mike[ 5] += static_cast<char>( this->_faces[1][7] >> 8 ); // DR
	this->_mike[ 6] += static_cast<char>( this->_faces[1][3] >> 8 ); // DB
	this->_mike[ 7] += static_cast<char>( this->_faces[1][1] >> 8 ); // DL

	this->_mike[ 8] += static_cast<char>( this->_faces[4][5] >> 8 ); // FR
	this->_mike[ 9] += static_cast<char>( this->_faces[4][3] >> 8 ); // FL

	this->_mike[10] += static_cast<char>( this->_faces[5][3] >> 8 ); // BR
	this->_mike[11] += static_cast<char>( this->_faces[5][5] >> 8 ); // BL

	// Second color of edges
	this->_mike[ 0] += static_cast<char>( this->_faces[0].edges[2][1][0] >> 8 ); // UF
	this->_mike[ 1] += static_cast<char>( this->_faces[0].edges[1][1][0] >> 8 ); // UR
	this->_mike[ 2] += static_cast<char>( this->_faces[0].edges[0][1][0] >> 8 ); // UB
	this->_mike[ 3] += static_cast<char>( this->_faces[0].edges[3][1][0] >> 8 ); // UL

	this->_mike[ 4] += static_cast<char>( this->_faces[1].edges[1][1][0] >> 8 ); // DF
	this->_mike[ 5] += static_cast<char>( this->_faces[1].edges[2][1][0] >> 8 ); // DR
	this->_mike[ 6] += static_cast<char>( this->_faces[1].edges[3][1][0] >> 8 ); // DB
	this->_mike[ 7] += static_cast<char>( this->_faces[1].edges[0][1][0] >> 8 ); // DL

	this->_mike[ 8] += static_cast<char>( this->_faces[4].edges[1][1][0] >> 8 ); // FR
	this->_mike[ 9] += static_cast<char>( this->_faces[4].edges[3][1][0] >> 8 ); // FL

	this->_mike[10] += static_cast<char>( this->_faces[5].edges[3][1][0] >> 8 ); // BR
	this->_mike[11] += static_cast<char>( this->_faces[5].edges[1][1][0] >> 8 ); // BL

	// First color of corners
	this->_mike[12] += static_cast<char>( this->_faces[0][8] >> 8 );
	this->_mike[13] += static_cast<char>( this->_faces[0][2] >> 8 );
	this->_mike[14] += static_cast<char>( this->_faces[0][0] >> 8 );
	this->_mike[15] += static_cast<char>( this->_faces[0][6] >> 8 );
	this->_mike[16] += static_cast<char>( this->_faces[1][8] >> 8 );
	this->_mike[17] += static_cast<char>( this->_faces[1][2] >> 8 );
	this->_mike[18] += static_cast<char>( this->_faces[1][0] >> 8 );
	this->_mike[19] += static_cast<char>( this->_faces[1][6] >> 8 );

	// Second color of corners
	this->_mike[12] += static_cast<char>( this->_faces[0].edges[2][0][0] >> 8 );
	this->_mike[13] += static_cast<char>( this->_faces[0].edges[1][0][0] >> 8 );
	this->_mike[14] += static_cast<char>( this->_faces[0].edges[0][0][0] >> 8 );
	this->_mike[15] += static_cast<char>( this->_faces[0].edges[3][0][0] >> 8 );
	this->_mike[16] += static_cast<char>( this->_faces[1].edges[2][0][0] >> 8 );
	this->_mike[17] += static_cast<char>( this->_faces[1].edges[1][0][0] >> 8 );
	this->_mike[18] += static_cast<char>( this->_faces[1].edges[0][0][0] >> 8 );
	this->_mike[19] += static_cast<char>( this->_faces[1].edges[3][0][0] >> 8 );
	
	// Third color of corners
	this->_mike[12] += static_cast<char>( this->_faces[0].edges[1][2][0] >> 8 );
	this->_mike[13] += static_cast<char>( this->_faces[0].edges[0][2][0] >> 8 );
	this->_mike[14] += static_cast<char>( this->_faces[0].edges[3][2][0] >> 8 );
	this->_mike[15] += static_cast<char>( this->_faces[0].edges[2][2][0] >> 8 );
	this->_mike[16] += static_cast<char>( this->_faces[1].edges[1][2][0] >> 8 );
	this->_mike[17] += static_cast<char>( this->_faces[1].edges[0][2][0] >> 8 );
	this->_mike[18] += static_cast<char>( this->_faces[1].edges[3][2][0] >> 8 );
	this->_mike[19] += static_cast<char>( this->_faces[1].edges[2][2][0] >> 8 );

	return this->_mike;
}

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
	//			North (Back)
	this->_faces[0].edges[0][0] = this->_faces[5].face + 2;
	this->_faces[0].edges[0][1] = this->_faces[5].face + 1;
	this->_faces[0].edges[0][2] = this->_faces[5].face + 0;
	//			East (Right)
	this->_faces[0].edges[1][0] = this->_faces[3].face + 2;
	this->_faces[0].edges[1][1] = this->_faces[3].face + 1;
	this->_faces[0].edges[1][2] = this->_faces[3].face + 0;
	//			South (Front)
	this->_faces[0].edges[2][0] = this->_faces[4].face + 2;
	this->_faces[0].edges[2][1] = this->_faces[4].face + 1;
	this->_faces[0].edges[2][2] = this->_faces[4].face + 0;
	//			West (Left)
	this->_faces[0].edges[3][0] = this->_faces[2].face + 2;
	this->_faces[0].edges[3][1] = this->_faces[2].face + 1;
	this->_faces[0].edges[3][2] = this->_faces[2].face + 0;
	// Down
	//			North (Left)
	this->_faces[1].edges[0][0] = this->_faces[2].face + 6;
	this->_faces[1].edges[0][1] = this->_faces[2].face + 7;
	this->_faces[1].edges[0][2] = this->_faces[2].face + 8;
	//			East (Front)
	this->_faces[1].edges[1][0] = this->_faces[4].face + 6;
	this->_faces[1].edges[1][1] = this->_faces[4].face + 7;
	this->_faces[1].edges[1][2] = this->_faces[4].face + 8;
	//			South (Right)
	this->_faces[1].edges[2][0] = this->_faces[3].face + 6;
	this->_faces[1].edges[2][1] = this->_faces[3].face + 7;
	this->_faces[1].edges[2][2] = this->_faces[3].face + 8;
	//			West (Back)
	this->_faces[1].edges[3][0] = this->_faces[5].face + 6;
	this->_faces[1].edges[3][1] = this->_faces[5].face + 7;
	this->_faces[1].edges[3][2] = this->_faces[5].face + 8;
	// Left
	//			North (Up)
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
	//			North (Up)
	this->_faces[4].edges[0][0] = this->_faces[0].face + 6;
	this->_faces[4].edges[0][1] = this->_faces[0].face + 7;
	this->_faces[4].edges[0][2] = this->_faces[0].face + 8;
	//			East (Right)
	this->_faces[4].edges[1][0] = this->_faces[3].face + 0;
	this->_faces[4].edges[1][1] = this->_faces[3].face + 3;
	this->_faces[4].edges[1][2] = this->_faces[3].face + 6;
	//			South (Down)
	this->_faces[4].edges[2][0] = this->_faces[1].face + 8;
	this->_faces[4].edges[2][1] = this->_faces[1].face + 5;
	this->_faces[4].edges[2][2] = this->_faces[1].face + 2;
	//			West (Left)
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

	// Mike Format
	this->getMikeFormat();
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
		} else if (cmd == "U'")	{ this->_faces[0].rotate_cc(); // UP C
		} else if (cmd == "U")	{ this->_faces[0].rotate_c();  // UP CC
		} else if (cmd == "U2")	{ this->_faces[0].rotate_2();  // UP 180
		} else if (cmd == "F'")	{ this->_faces[4].rotate_cc(); // FRONT C
		} else if (cmd == "F")	{ this->_faces[4].rotate_c();  // FRONT CC
		} else if (cmd == "F2")	{ this->_faces[4].rotate_2();  // FRONT 180
		} else if (cmd == "R'")	{ this->_faces[3].rotate_cc(); // RIGHT C
		} else if (cmd == "R")	{ this->_faces[3].rotate_c();  // RIGHT CC
		} else if (cmd == "R2")	{ this->_faces[3].rotate_2();  // RIGHT 180
		} else if (cmd == "B'")	{ this->_faces[5].rotate_cc(); // BACK C
		} else if (cmd == "B")	{ this->_faces[5].rotate_c();  // BACK CC
		} else if (cmd == "B2")	{ this->_faces[5].rotate_2();  // BACK 180
		} else if (cmd == "L'")	{ this->_faces[2].rotate_cc(); // LEFT C
		} else if (cmd == "L")	{ this->_faces[2].rotate_c();  // LEFT CC
		} else if (cmd == "L2")	{ this->_faces[2].rotate_2();  // LEFT 180
		} else if (cmd == "D'")	{ this->_faces[1].rotate_cc(); // DOWN C
		} else if (cmd == "D")	{ this->_faces[1].rotate_c();  // DOWN CC
		} else if (cmd == "D2")	{ this->_faces[1].rotate_2();  // DOWN 180
		} else { throw std::exception(); }
	}
}

void RubikCube::draw_block( int x, int y, int c ) {
	attron(COLOR_PAIR(c >> 8));
	// mvaddch(x, y, ((c << 8) >> 8) + '0');
	mvaddch(x, y, ' ');
	attroff(COLOR_PAIR(c >> 8));
}

void RubikCube::draw() {
	this->draw(0, 0);
}


void RubikCube::draw( int x, int y ) {
	// Up
	this->draw_block( x + 2, y +  7, this->_faces[0].face[0]);//, '0');
	this->draw_block( x + 3, y +  9, this->_faces[0].face[1]);//, '1');
	this->draw_block( x + 4, y + 11, this->_faces[0].face[2]);//, '2');
	this->draw_block( x + 3, y +  5, this->_faces[0].face[3]);//, '3');
	this->draw_block( x + 4, y +  7, this->_faces[0].face[4]);//, '4');
	this->draw_block( x + 5, y +  9, this->_faces[0].face[5]);//, '5');
	this->draw_block( x + 4, y +  3, this->_faces[0].face[6]);//, '6');
	this->draw_block( x + 5, y +  5, this->_faces[0].face[7]);//, '7');
	this->draw_block( x + 6, y +  7, this->_faces[0].face[8]);//, '8');
	// Down
	this->draw_block( x + 5, y + 19, this->_faces[1].face[0]);//, '0');
	this->draw_block( x + 6, y + 21, this->_faces[1].face[1]);//, '1');
	this->draw_block( x + 7, y + 23, this->_faces[1].face[2]);//, '2');
	this->draw_block( x + 6, y + 17, this->_faces[1].face[3]);//, '3');
	this->draw_block( x + 7, y + 19, this->_faces[1].face[4]);//, '4');
	this->draw_block( x + 8, y + 21, this->_faces[1].face[5]);//, '5');
	this->draw_block( x + 7, y + 15, this->_faces[1].face[6]);//, '6');
	this->draw_block( x + 8, y + 17, this->_faces[1].face[7]);//, '7');
	this->draw_block( x + 9, y + 19, this->_faces[1].face[8]);//, '8');
	// Left
	this->draw_block( x + 2, y + 20, this->_faces[2].face[0]);//, '0');
	this->draw_block( x + 3, y + 22, this->_faces[2].face[1]);//, '1');
	this->draw_block( x + 4, y + 24, this->_faces[2].face[2]);//, '2');
	this->draw_block( x + 3, y + 20, this->_faces[2].face[3]);//, '3');
	this->draw_block( x + 4, y + 22, this->_faces[2].face[4]);//, '4');
	this->draw_block( x + 5, y + 24, this->_faces[2].face[5]);//, '5');
	this->draw_block( x + 4, y + 20, this->_faces[2].face[6]);//, '6');
	this->draw_block( x + 5, y + 22, this->_faces[2].face[7]);//, '7');
	this->draw_block( x + 6, y + 24, this->_faces[2].face[8]);//, '8');
	// Right
	this->draw_block( x + 7, y +  8, this->_faces[3].face[0]);//, '0');
	this->draw_block( x + 6, y + 10, this->_faces[3].face[1]);//, '1');
	this->draw_block( x + 5, y + 12, this->_faces[3].face[2]);//, '2');
	this->draw_block( x + 8, y +  8, this->_faces[3].face[3]);//, '3');
	this->draw_block( x + 7, y + 10, this->_faces[3].face[4]);//, '4');
	this->draw_block( x + 6, y + 12, this->_faces[3].face[5]);//, '5');
	this->draw_block( x + 9, y +  8, this->_faces[3].face[6]);//, '6');
	this->draw_block( x + 8, y + 10, this->_faces[3].face[7]);//, '7');
	this->draw_block( x + 7, y + 12, this->_faces[3].face[8]);//, '8');
	// Front
	this->draw_block( x + 5, y +  2, this->_faces[4].face[0]);//, '0');
	this->draw_block( x + 6, y +  4, this->_faces[4].face[1]);//, '1');
	this->draw_block( x + 7, y +  6, this->_faces[4].face[2]);//, '2');
	this->draw_block( x + 6, y +  2, this->_faces[4].face[3]);//, '3');
	this->draw_block( x + 7, y +  4, this->_faces[4].face[4]);//, '4');
	this->draw_block( x + 8, y +  6, this->_faces[4].face[5]);//, '5');
	this->draw_block( x + 7, y +  2, this->_faces[4].face[6]);//, '6');
	this->draw_block( x + 8, y +  4, this->_faces[4].face[7]);//, '7');
	this->draw_block( x + 9, y +  6, this->_faces[4].face[8]);//, '8');
	// Back
	this->draw_block( x + 4, y + 14, this->_faces[5].face[0]);//, '0');
	this->draw_block( x + 3, y + 16, this->_faces[5].face[1]);//, '1');
	this->draw_block( x + 2, y + 18, this->_faces[5].face[2]);//, '2');
	this->draw_block( x + 5, y + 14, this->_faces[5].face[3]);//, '3');
	this->draw_block( x + 4, y + 16, this->_faces[5].face[4]);//, '4');
	this->draw_block( x + 3, y + 18, this->_faces[5].face[5]);//, '5');
	this->draw_block( x + 6, y + 14, this->_faces[5].face[6]);//, '6');
	this->draw_block( x + 5, y + 16, this->_faces[5].face[7]);//, '7');
	this->draw_block( x + 4, y + 18, this->_faces[5].face[8]);//, '8');
}
