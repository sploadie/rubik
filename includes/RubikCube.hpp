/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RubikCube.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 20:08:20 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/05/20 19:30:53 by tgauvrit         ###   ########.fr       */
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

private:
	RubikFace	_faces[6];

	void reset( void );
	void draw_block( int x, int y, int color, char c );
};

#endif
