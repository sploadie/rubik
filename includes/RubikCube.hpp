/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RubikCube.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 20:08:20 by tgauvrit          #+#    #+#             */
/*   Updated: 2016/05/16 20:30:51 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUBIKCUBE_H
# define RUBIKCUBE_H

# include "RubikEdge.hpp"
# include "RubikFace.hpp"

class RubikCube {

public:

	RubikCube( void );
	RubikCube( RubikCube const & obj );

	~RubikCube( void );

	RubikCube & operator=( RubikCube const & rhs );

private:
	RubikFace	_faces[6];
};

#endif
