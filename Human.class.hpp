// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Human.class.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/09 18:38:14 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/12 14:36:09 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef _HUMAN_HPP_
# define _HUMAN_HPP_

#include "Hit_box.class.hpp"
#include "Player.class.hpp"

class Human : public Player {
private:
	std::list<Hit_box*>	box;
	bool				make;
public:
	Human( void );
	Human( Human const &src );
	Human( std::string n, int np );
	Human( int np );
	~Human( void );

	void	make_hitBox( void );
	void		ft_machin_learning();
	t_pions	*put_token( Game & game );
	Human & operator=( Human const &rhs );
};

#endif
