/*	************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RubikEdge.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 20:07:26 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/05/16 20:11:35 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUBIKEDGE_H
# define RUBIKEDGE_H

# include <cstddef>
# include <exception>

class RubikEdge {

public:

	RubikEdge( void );
	RubikEdge( char* a, char* b, char* c );
	RubikEdge( RubikEdge const & obj );

	~RubikEdge( void );

	RubikEdge & operator=( RubikEdge const & rhs );
	char*& operator[]( std::size_t index );

	bool isReady( void ) const;

	void setEdgePointers( char* a, char* b, char* c );
	void setEdge( char a, char b, char c );

private:
	char*	_edge[3];
};

#endif
