/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RubikCube.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 20:08:20 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/05/22 11:57:13 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUBIKCUBE_H
# define RUBIKCUBE_H

# include "RubikEdge.hpp"
# include "RubikFace.hpp"
# include <iostream>
# include <string>
# include <exception>
# include <curses.h>

class RubikCube {

public:
	RubikCube( void );
	RubikCube( RubikCube const & obj );

	~RubikCube( void );

	RubikCube & operator=( RubikCube const & rhs );
	RubikFace & operator[]( std::size_t index );

	void apply( std::string cmd );

	void draw( void );
	void draw( int x, int y );

	std::string * getMikeFormat( void );

private:
	RubikFace	_faces[6];
	std::string	_mike[20];

	void reset( void );
	void draw_block( int x, int y, int c );
};

void solve( std::string * mikeFormat );

#endif
