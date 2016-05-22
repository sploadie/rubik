/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RubikFace.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 20:07:55 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/05/22 12:00:53 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RubikFace.hpp"

RubikFace::RubikFace( void ) { this->reset('X'); }

RubikFace::RubikFace( char c ) { this->reset(c); }

RubikFace::RubikFace( RubikFace const & obj ) { *this = obj; }

RubikFace::~RubikFace( void ) {}

RubikFace & RubikFace::operator=( RubikFace const & rhs ) {
	for (int i=0; i<9; ++i) { this->face[i] = rhs.face[i]; }
	return *this;
}

int & RubikFace::operator[]( std::size_t index ) { return this->face[index]; }

void RubikFace::reset( char c ) {
	int val = static_cast<int>(c);
	val = val << 8;
	for (int i=0; i<9; ++i) { this->face[i] = val + i; }
}

void RubikFace::rotate_c( void ) {
	int tmp_face[9];
	int tmp_edge[3];
	int i;
	// Rotate edges
	for (i=0; i<3; ++i) { tmp_edge[i] = *(this->edges[3][i]); } // Save last edge (West)
	for (i=3; i>0; --i) { this->edges[i] = this->edges[i-1]; }
	this->edges[0].setEdge(tmp_edge[0], tmp_edge[1], tmp_edge[2]); // First edge now equal to last edge (North = West)
	// Rotate face
	for (i=0; i<9; ++i) { tmp_face[i] = this->face[i]; }
	this->face[0] = tmp_face[6];
	this->face[1] = tmp_face[3];
	this->face[2] = tmp_face[0];
	this->face[3] = tmp_face[7];
	// this->face[4] = tmp_face[4]; // Center tile does not rotate
	this->face[5] = tmp_face[1];
	this->face[6] = tmp_face[8];
	this->face[7] = tmp_face[5];
	this->face[8] = tmp_face[2];
}

void RubikFace::rotate_2( void )  { this->rotate_c(); this->rotate_c(); }

void RubikFace::rotate_cc( void ) {
	int tmp_face[9];
	int tmp_edge[3];
	int i;
	// Rotate edges
	for (i=0; i<3; ++i) { tmp_edge[i] = *(this->edges[0][i]); } // Save last edge (West)
	for (i=0; i<3; ++i) { this->edges[i] = this->edges[i+1]; }
	this->edges[3].setEdge(tmp_edge[0], tmp_edge[1], tmp_edge[2]); // First edge now equal to last edge (North = West)
	// Rotate face
	for (i=0; i<9; ++i) { tmp_face[i] = this->face[i]; }
	this->face[0] = tmp_face[2];
	this->face[1] = tmp_face[5];
	this->face[2] = tmp_face[8];
	this->face[3] = tmp_face[1];
	// this->face[4] = tmp_face[4]; // Center tile does not rotate
	this->face[5] = tmp_face[7];
	this->face[6] = tmp_face[0];
	this->face[7] = tmp_face[3];
	this->face[8] = tmp_face[6];
}
