// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Game.class.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/09 17:03:53 by mmoumini          #+#    #+#             //
//   Updated: 2016/03/16 21:06:52 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef _GAME_HPP_
# define _GAME_HPP_

#include "Gomoku.hpp"
#include "Node.hpp"
class Player;
class Game {

private:
	Timer					*time;
 	std::unordered_map<std::string, int> pions;
	std::unordered_map<std::string, int> fake;
	std::unordered_map<std::string, int> trace;
	sf::Texture				noir;
	sf::Texture				blanc;
	sf::Texture				woodTex;
	sf::Texture				fond;
	sf::Music				music[3];
	sf::Sound				victory;
	sf::Sound				forbi;
	sf::Sound				captur;
	sf::Sound				cbreaker;
	sf::SoundBuffer			*buffer1;
	sf::SoundBuffer			*buffer2;
	sf::SoundBuffer			*buffer3;
	sf::SoundBuffer			*buffer4;
	sf::Font				osaka;
	sf::Font				madeinc;
	sf::Font 				digi;
	Player					*p1;
	Player					*p2;
	std::stringstream		stm1;
	std::stringstream		stm2;
	bool					w;
	bool					tmpwin;
	int						c;
	int						cap1;
	int						cap2;
	int						breakstat;
	bool					linebreak;
	t_pions					save;
	int						advance;
	int						tracer;

public:

	int 		turn;
	int 		nwin;
	int 		decal;
	int 		len;

	std::pair<int, Node &> 	State;
	sf::RenderWindow        *app;

	Game(  int h, Node & n );
	~Game( void );
	Game & operator=( Game const &rhs );

	int  		ft_check_is_catchable(Node & node);
	void 		ft_display_map(std::array<std::array<char, 19>, 19> map);
	bool		ft_is_finished_for(std::array<std::array<char, 19>, 19> map, char c);
	bool 		ft_check_if_win(std::array<std::array<char, 19>, 19> const map);
	void		check_event( void );
	void		init( sf::RenderWindow *win );
	void		add_token( t_pions *token ); //ajoute un pion definitif
	void		add_token( int x, int y, int player );
	void		drawGrid( void );
	void		drawScore( void );
	void		drawToken( void );
	int			whoisHere( t_pions *wp );	//---fonctiont pour savoir qui est a la
	int			whoisHere( int x, int y );	//position (x, y) renvoie zero si personne..
	bool		isWin( t_pions *token );
	void		Winner( int p );
	bool		hori( t_pions *token );
	bool		vert( t_pions *token );
	bool		diag1( t_pions *token );
	bool		diag2( t_pions *token );
	void		clear_all( void );
	void		draw_choice( void );
	int			gameMenu( void );
	void		quit( void );
	void		Play( void );
	void		DrawGame( void );
	bool		CaptureW( t_pions * ntoken );
	bool		CaptureB( t_pions * ntoken );
	void 		Slashme();
	void		remove_token( int x, int y );
	bool		forbidden( t_pions * token );
	int			freeThreeHor( t_pions *token );
	bool		checkfreeHori(int xa, int xb, int y, int player);
	int			freeThreeVer( t_pions *token );
	bool		checkfreeVer(int x, int ya, int yb, int player);
	int			freeThreeDiag1( t_pions *token );
	bool		checkfreeDiag1(int xa, int xb, int ya, int yb, int player);
	int			freeThreeDiag2( t_pions *token );
	bool		checkfreeDiag2(int xa, int xb, int ya, int yb, int player);
	void		unbreakable1( t_pions * token );
	void		unbreakable2( t_pions * token );
	void		drawBreakevent( void );
	void		breakcapture1( void );
	void		breakcapture2( void );
	bool		checkEvryLineBreak( int x, int  y, int player);
	void		horiLineBreaker(int x, int y, int player, int incr);
	void		vertLineBreaker(int x, int y, int player, int incr);
	void		diagLineBreaker(int x, int y, int player, int incrx, int incry);
	void		add_virtualtoken( t_pions *token ); //ajoute un pions vituel
	void		add_virtualtoken( int x, int y, int player );
	void		clear_all_virtual( void ); //efface tout les pions virtuel.. -- a rapeler tout le temp...
	void		removeVirtualToken( int x, int y );
	bool		CaptureVirtualB( t_pions * ntoken );
	bool		CaptureVirtualW( t_pions * ntoken );
};
#endif
