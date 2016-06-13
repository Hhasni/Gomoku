// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Player.class.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/09 17:56:39 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/12 14:34:06 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef _PLAYER_HPP_
# define _PLAYER_HPP_

#include "Gomoku.hpp"
#include "Game.class.hpp"

class Player{
protected:
	std::string		name;
	int				player;
public:
	Player( void );
	Player( Player const &src );
	Player( std::string n, int np );
	Player( int np );
	~Player( void );
	Player & operator=( Player const &rhs );

	void			ChangePlayer( void );
	virtual void	ft_machin_learning( void ) = 0;
	int				GetPlayerN( void );
	std::string		GetPlayerName( void );
	virtual t_pions *put_token( Game & game ) = 0;
	bool			human;
};

#endif
