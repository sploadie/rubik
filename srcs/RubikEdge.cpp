/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RubikEdge.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 20:07:55 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/05/22 11:49:56 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RubikEdge.hpp"

RubikEdge::RubikEdge( void ) {
	this->_edge[0] = nullptr;
	this->_edge[1] = nullptr;
	this->_edge[2] = nullptr;
}

RubikEdge::RubikEdge( int* a, int* b, int* c ) { this->setEdgePointers(a, b, c); }

RubikEdge::RubikEdge( RubikEdge const & obj )  { this->setEdgePointers(obj._edge[0], obj._edge[1], obj._edge[2]); } // COPIES POINTERS, NOT VALUES

RubikEdge::~RubikEdge( void ) {}

RubikEdge & RubikEdge::operator=( RubikEdge const & rhs ) { // COPIES VALUES, NOT POINTERS
	if ( this->isReady() && rhs.isReady() ) {
		this->setEdge( *(rhs._edge[0]), *(rhs._edge[1]), *(rhs._edge[2]) );
	} else {
		throw std::exception(); // ONLY COPY IF ALL NOT NULL
	}
	return *this;
}

int*& RubikEdge::operator[]( std::size_t index ) { return this->_edge[index]; }

bool RubikEdge::isReady( void ) const {
	if ( this->_edge[0] && this->_edge[1] && this->_edge[2] )
		return true;
	return false;
}

void RubikEdge::setEdgePointers( int* a, int* b, int* c ) { // COPIES POINTERS, NOT VALUES
	this->_edge[0] = a;
	this->_edge[1] = b;
	this->_edge[2] = c;
}

void RubikEdge::setEdge( int a, int b, int c ) { // COPIES POINTERS, NOT VALUES
	*(this->_edge[0]) = a;
	*(this->_edge[1]) = b;
	*(this->_edge[2]) = c;
}
