/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RubikFace.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 20:07:22 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/05/22 11:53:54 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUBIKFACE_H
# define RUBIKFACE_H

# include "RubikEdge.hpp"

class RubikFace {

public:

	RubikFace( void );
	RubikFace( char c );
	RubikFace( RubikFace const & obj );

	~RubikFace( void );

	RubikFace & operator=( RubikFace const & rhs );
	int & operator[]( std::size_t index );

	void reset( char c );

	void rotate_c( void );
	void rotate_2( void );
	void rotate_cc( void );

	int			face[9];
	RubikEdge	edges[4];

private:
};

#endif
