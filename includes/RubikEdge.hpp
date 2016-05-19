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

class RubikEdge {

public:

	RubikEdge( void );
	RubikEdge( int* a, int* b, int* c );
	RubikEdge( RubikEdge const & obj );

	~RubikEdge( void );

	RubikEdge & operator=( RubikEdge const & rhs );
	char operator[]( std::size_t index );

	bool isReady( void );

	void setEdgePointers( int* a, int* b, int* c );
	void setEdge( int a, int b, int c );

private:
	char*	_edge[3];
};

#endif
