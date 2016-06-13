// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Game.class.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/09 17:15:37 by mmoumini          #+#    #+#             //
//   Updated: 2016/03/17 17:29:09 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Game.class.hpp"
#include "Human.class.hpp"
#include "AI.class.hpp"

#define DIM 10
#define SQUARE_H 200
#define SQUARE_L 550
#define SPACE 70

void			Game::removeVirtualToken( int x, int y ){
	std::unordered_map<std::string,int>::iterator it;
	std::ostringstream os;

    os << x << " " << y;
    it = fake.find(os.str());
    if (it != fake.end())
    {
		fake.erase(it);
		this->clear_all_virtual();
		return ;
    }
}

bool			Game::CaptureVirtualB( t_pions * ntoken ){
	int			v;

	v = this->c;
	if ( (this->whoisHere(ntoken->x + 1, ntoken->y) == 1) 
		 && (this->whoisHere(ntoken->x + 2, ntoken->y) == 1) 
		 && (this->whoisHere(ntoken->x + 3, ntoken->y) == 2) )
	{
		this->removeVirtualToken(ntoken->x + 1, ntoken->y);
		this->removeVirtualToken(ntoken->x + 2, ntoken->y);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x - 1, ntoken->y) == 1) 
		 && (this->whoisHere(ntoken->x - 2, ntoken->y) == 1) 
		 && (this->whoisHere(ntoken->x - 3, ntoken->y) == 2) )
	{
		this->removeVirtualToken(ntoken->x - 1, ntoken->y);
		this->removeVirtualToken(ntoken->x - 2, ntoken->y);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x, ntoken->y + 1) == 1) 
		 && (this->whoisHere(ntoken->x, ntoken->y + 2) == 1) 
		 && (this->whoisHere(ntoken->x, ntoken->y + 3) == 2) )
	{
		this->removeVirtualToken(ntoken->x, ntoken->y + 1);
		this->removeVirtualToken(ntoken->x, ntoken->y + 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x, ntoken->y - 1) == 1) 
		 && (this->whoisHere(ntoken->x, ntoken->y - 2) == 1) 
		 && (this->whoisHere(ntoken->x, ntoken->y - 3) == 2) )
	{
		this->removeVirtualToken(ntoken->x, ntoken->y - 1);
		this->removeVirtualToken(ntoken->x, ntoken->y - 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x + 1, ntoken->y + 1) == 1) 
		 && (this->whoisHere(ntoken->x + 2, ntoken->y + 2) == 1) 
		 && (this->whoisHere(ntoken->x + 3, ntoken->y + 3) == 2) )
	{
		this->removeVirtualToken(ntoken->x + 1, ntoken->y + 1);
		this->removeVirtualToken(ntoken->x + 2, ntoken->y + 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x - 1, ntoken->y - 1) == 1)
		 && (this->whoisHere(ntoken->x - 2, ntoken->y - 2) == 1) 
		 && (this->whoisHere(ntoken->x - 3, ntoken->y - 3) == 2) )
	{
		this->removeVirtualToken(ntoken->x - 1, ntoken->y - 1);
		this->removeVirtualToken(ntoken->x - 2, ntoken->y - 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x + 1, ntoken->y - 1) == 1)
		 && (this->whoisHere(ntoken->x + 2, ntoken->y - 2) == 1) 
		 && (this->whoisHere(ntoken->x + 3, ntoken->y - 3) == 2) )
	{
		this->removeVirtualToken(ntoken->x + 1, ntoken->y - 1);
		this->removeVirtualToken(ntoken->x + 2, ntoken->y - 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x - 1, ntoken->y + 1) == 1) 
		 && (this->whoisHere(ntoken->x - 2, ntoken->y + 2) == 1) 
		 && (this->whoisHere(ntoken->x - 3, ntoken->y + 3) == 2) )
	{
		this->removeVirtualToken(ntoken->x - 1, ntoken->y + 1);
		this->removeVirtualToken(ntoken->x - 2, ntoken->y + 2);
		this->c = this->c - 2;
	}
	if (v != this->c)
	{
		this->c = v;
		return (true);
	}
	return (false);
}

bool			Game::CaptureVirtualW( t_pions * ntoken ){
	int			v;

	v = this->c;
	if ( (this->whoisHere(ntoken->x + 1, ntoken->y) == 2) 
		 && (this->whoisHere(ntoken->x + 2, ntoken->y) == 2) 
		 && (this->whoisHere(ntoken->x + 3, ntoken->y) == 1) )
	{
		this->removeVirtualToken(ntoken->x + 1, ntoken->y);
		this->removeVirtualToken(ntoken->x + 2, ntoken->y);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x - 1, ntoken->y) == 2) 
		 && (this->whoisHere(ntoken->x - 2, ntoken->y) == 2) 
		 && (this->whoisHere(ntoken->x - 3, ntoken->y) == 1) )
	{
		this->removeVirtualToken(ntoken->x - 1, ntoken->y);
		this->removeVirtualToken(ntoken->x - 2, ntoken->y);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x, ntoken->y + 1) == 2) 
		 && (this->whoisHere(ntoken->x, ntoken->y + 2) == 2) 
		 && (this->whoisHere(ntoken->x, ntoken->y + 3) == 1) )
	{
		this->removeVirtualToken(ntoken->x, ntoken->y + 1);
		this->removeVirtualToken(ntoken->x, ntoken->y + 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x, ntoken->y - 1) == 2) 
		 && (this->whoisHere(ntoken->x, ntoken->y - 2) == 2) 
		 && (this->whoisHere(ntoken->x, ntoken->y - 3) == 1) )
	{
		this->removeVirtualToken(ntoken->x, ntoken->y - 1);
		this->removeVirtualToken(ntoken->x, ntoken->y - 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x + 1, ntoken->y + 1) == 2) 
		 && (this->whoisHere(ntoken->x + 2, ntoken->y + 2) == 2) 
		 && (this->whoisHere(ntoken->x + 3, ntoken->y + 3) == 1) )
	{
		this->removeVirtualToken(ntoken->x + 1, ntoken->y + 1);
		this->removeVirtualToken(ntoken->x + 2, ntoken->y + 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x - 1, ntoken->y - 1) == 2) 
		 && (this->whoisHere(ntoken->x - 2, ntoken->y - 2) == 2) 
		 && (this->whoisHere(ntoken->x - 3, ntoken->y - 3) == 1) )
	{
		this->removeVirtualToken(ntoken->x - 1, ntoken->y - 1);
		this->removeVirtualToken(ntoken->x - 2, ntoken->y - 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x + 1, ntoken->y - 1) == 2) 
		 && (this->whoisHere(ntoken->x + 2, ntoken->y - 2) == 2) 
		 && (this->whoisHere(ntoken->x + 3, ntoken->y - 3) == 1) )
	{
		this->removeVirtualToken(ntoken->x + 1, ntoken->y - 1);
		this->removeVirtualToken(ntoken->x + 2, ntoken->y - 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x - 1, ntoken->y + 1) == 2) 
		 && (this->whoisHere(ntoken->x - 2, ntoken->y + 2) == 2) 
		 && (this->whoisHere(ntoken->x - 3, ntoken->y + 3) == 1) )
	{
		this->removeVirtualToken(ntoken->x - 1, ntoken->y + 1);
		this->removeVirtualToken(ntoken->x - 2, ntoken->y + 2);
		this->c = this->c - 2;
	}
	if (v != this->c)
	{
		this->c = v;
		return (true);
	}
	return (false);
}

void			Game::add_virtualtoken( t_pions * token ){
	token->player = token->player + 5;

	std::stringstream   os;
    os << token->x << " " << token->y;
    fake[os.str()] = token->player;

	if (token->player - 5 == 1)
		this->CaptureVirtualW(token);
	else if (token->player - 5 == 2)
		this->CaptureVirtualB(token);
}

void			Game::add_virtualtoken( int x, int y, int player ){

	t_pions		*ntoken = new t_pions;
	std::stringstream   os;
	player = player + 5;

    os << x << " " << y;
    fake[os.str()] = player;

	ntoken->x = x;
	ntoken->y = y;
	ntoken->player = player;
	if (player - 5 == 1)
		this->CaptureVirtualW(ntoken);
	else if (player - 5 == 2)
		this->CaptureVirtualB(ntoken);
}

void		Game::clear_all_virtual( void ){
	std::unordered_map<std::string, int>::iterator		it;

	for (it = fake.begin(); it != fake.end(); it++)
	{
		if (it->second > 5)
			pions.erase(it);
	}
	fake.clear();
	for (it = pions.begin(); it != pions.end(); it++)
		fake[it->first] = it->second;
}
