/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumini <mmoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/09 17:15:37 by mmoumini          #+#    #+#             */
//   Updated: 2016/03/17 17:30:33 by mmoumini         ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "Game.class.hpp"
#include "Human.class.hpp"
#include "AI.class.hpp"

#define DIM 10
#define SQUARE_H 200
#define SQUARE_L 550
#define SPACE 70

Game::Game( int h, Node & n ): State(h, n){
	turn = 0;
	nwin = 5;
	len = (int)(n.getMap()).size();
	decal = len - 4;//len - 5 (ou 4)
	tmpwin = false;
}

Game::~Game( void ){
}

void		Game::quit( void ){
    this->clear_all();
	this->app->close();
	exit(0);
}

void		Game::init( sf::RenderWindow *win ){

	sf::Text		text;
	int				choice;

//	this->tracer = 0;
	srand(std::time(NULL));
	this->time = new Timer;
	this->app = win;
	this->w = false;
	this->linebreak = false;
	this->breakstat = 0;
	this->c = 0;
	this->cap1 = 0;
	this->cap2 = 0;
	this->advance = 0;;
	this->app->clear(sf::Color::White);
	this->buffer1 = new sf::SoundBuffer;
	this->buffer2 = new sf::SoundBuffer;
	this->buffer3 = new sf::SoundBuffer;
	this->buffer4 = new sf::SoundBuffer;
	if (!this->digi.loadFromFile("src/DS-DIGI.TTF"))
	std::cout << "can't load <DS-DIGI.TTF>!" << std::endl;
	if (!this->woodTex.loadFromFile("src/bois.jpg"))
		std::cout << "can't load <bois.jpg>!" << std::endl;
	if (!this->fond.loadFromFile("src/fond.jpg"))
		std::cout << "can't load <fond.jpg>" << std::endl;
	if (!this->noir.loadFromFile("src/noir.jpg"))
		std::cout << "can't load <noir.jpg>!" << std::endl;
	if (!this->blanc.loadFromFile("src/blanc.jpg"))
		std::cout << "can't load <blanc.jpg>!" << std::endl;
	if (!this->osaka.loadFromFile("src/osaka-re.ttf"))
		std::cout << "can't load <osaka-re.ttf>!" << std::endl;
	if (!this->madeinc.loadFromFile("src/MADEC.ttf"))
		std::cout << "can't load <MADEC.ttf>!" << std::endl;
	if (!this->music[0].openFromFile("src/haomaru.ogg"))
		std::cout << "can't load <haomaru.ogg>!" << std::endl;
	if (!this->music[1].openFromFile("src/Forest.ogg"))
		std::cout << "can't load <Forest.ogg>!" << std::endl;
	if (!this->buffer1->loadFromFile("src/Yooo.ogg"))
		std::cout << "can't load <Yooo.ogg>!" << std::endl;
	if (!this->buffer2->loadFromFile("src/Woosh.ogg"))
		std::cout << "can't load <Woosh.ogg>!" << std::endl;
	if (!this->buffer3->loadFromFile("src/ninja.ogg"))
		std::cout << "can't load <ninja.ogg>!" << std::endl;
	if (!this->buffer4->loadFromFile("src/breaker.ogg"))
		std::cout << "can't load <breaker.ogg>!" << std::endl;
	this->victory.setBuffer( *this->buffer1 );
	this->forbi.setBuffer( *this->buffer2 );
	this->captur.setBuffer( *this->buffer3 );
	this->cbreaker.setBuffer( *this->buffer4 );
	this->captur.setVolume(50);
	this->music[rand() % 2].play();
	this->music[0].setLoop(true);
	this->music[1].setLoop(true);
	text.setFont(this->madeinc);
	text.setString("Gomoku42");
	text.setCharacterSize(120);
	text.setColor(sf::Color::Black);
	text.setPosition(ORIGIN_X, (WIN_HEIGHT / 2) - 120);
	this->app->draw(text);
	this->app->display();
	this->time->Start();
	sleep(3);
	this->fond.setRepeated(true);
	this->woodTex.setRepeated(true);
	this->app->clear(sf::Color::White);
	choice = this->gameMenu();
	if (choice == 0)
		this->quit();
	else if (choice == 1)
	{
		p1 = new Human("mous", 1);
		p2 = new AI(2, this);
		State.second.setMap_char_at_XY(len/2, len/2, 'O');
	}
	else
	{
		p1 = new Human("mous", 1);
		p2 = new Human("mous", 2);
	}
	this->drawGrid();
	this->drawToken();
	this->app->display();
	this->Play();
}

void			Game::Play( void ){

	while(42){
	while (this->w == false)
	{
		if (this->advance == 0)
		{
			this->time->Reinitialize();
			this->time->Start();
			this->add_token(p1->put_token(*this));
			 if ( this->w )
				p2->ft_machin_learning();
		}
		else
			this->advance--;
		if (this->advance == 0 && this->w == false)
		{
			
			this->time->Reinitialize();
			this->time->Start();
			this->add_token(p2->put_token(*this));
		}
		else if(this->w == false)
			this->advance--;
	}
	this->w = false;
	State.second.setMap_char_at_XY(len/2, len/2, 'O');
	this->drawGrid();
	this->drawToken();
	this->app->display();

//	add_token(len/2, len/2, 2);
	this->advance = 0;
	}
	std::cout << "QUIT " << std::endl;
}

void			Game::draw_choice( void ){

	sf::RectangleShape				one;
	sf::RectangleShape				two;
	sf::Text						text1;
	sf::Text						text2;

	this->app->clear(sf::Color::White);

	text1.setFont(osaka);
	text1.setString("1 player");
	text1.setCharacterSize(40);
	text1.setColor(sf::Color::Black);
	text1.setPosition(ORIGIN_X + 200, SPACE + (SQUARE_H / 3));

	text2.setFont(osaka);
	text2.setString("2 players");
	text2.setCharacterSize(40);
	text2.setColor(sf::Color::Black);
	text2.setPosition(ORIGIN_X + 180, ((SPACE * 2) + SQUARE_H) +  (SQUARE_H / 3));

	one.setSize(sf::Vector2f(SQUARE_L, SQUARE_H));
	two.setSize(sf::Vector2f(SQUARE_L, SQUARE_H));
	one.setPosition( ORIGIN_X, SPACE);
	two.setPosition( ORIGIN_X, (SPACE * 2) + SQUARE_H);
	one.setOutlineThickness(2);
	two.setOutlineThickness(2);
	one.setFillColor(sf::Color(26, 188, 156));
	two.setFillColor(sf::Color(26, 188, 156));
	one.setOutlineColor(sf::Color(22, 160, 133));
	two.setOutlineColor(sf::Color(22, 160, 133));
    this->app->draw(one);
	this->app->draw(two);
	this->app->draw(text1);
	this->app->draw(text2);

	this->app->display();
}

int			Game::gameMenu( void ){

	sf::Event       appevent;
	sf::Keyboard    key;
	bool            continuer;
	int				choice;

	choice = 0;
	continuer = true;
	this->draw_choice();
	while (continuer)
	{
		this->app->pollEvent(appevent);
		switch ( appevent.type )
		{
		case sf::Event::Closed :
			continuer = false;
			break;
		case sf::Event::KeyPressed :
			if (key.isKeyPressed( sf::Keyboard::Escape )){
				continuer = false;
			}
		case sf::Event::MouseButtonPressed:
			if (appevent.mouseButton.x >= ORIGIN_X
				&& appevent.mouseButton.x <= ORIGIN_X + SQUARE_L)
			{
				if (appevent.mouseButton.y >= SPACE
					&& appevent.mouseButton.y <= SPACE + SQUARE_H)
				{
					choice = 1;
					continuer = false;
				}
				if (appevent.mouseButton.y >= (SPACE * 2) + SQUARE_H
					&& appevent.mouseButton.y <= (SPACE * 2) + (SQUARE_H * 2))
				{
					choice = 2;
					continuer = false;
				}
			}
		default:
			break;
		}
	}
	return (choice);
}

void			Game::Winner( int p ){
	sf::Text			text;
	std::stringstream   stream;

	this->linebreak = false;
	stream << "Player " << p << " Win! ";
	if (this->breakstat && p != this->breakstat)
	{
		stream << " by break !!!" << std::endl;
		this->cbreaker.play();
	}
	else if ( this->breakstat )
		stream << "Player "<< this->breakstat << " can't break it!!"<< std::endl;
	this->breakstat = 0;
	this->victory.play();
	text.setFont(osaka);
	text.setString(stream.str());

	text.setCharacterSize(40);

    this->app->clear(sf::Color::White);
    this->drawGrid();
    this->drawToken();
    this->drawScore();

	if (p == 1)
		text.setColor(sf::Color::White);
	else
		text.setColor(sf::Color::Black);
	text.setPosition(0, 0);
	app->draw(text);
	app->display();
	clear_all();
	sleep(3);
	this->app->clear(sf::Color::White);
	this->drawGrid();
	this->w = true;
	this->c = 0;
	this->cap1 = 0;
	this->cap2 = 0;
}

void			Game::check_event( void ){

	sf::Event		appevent;
	sf::Keyboard	key;
	bool			quit;

	quit = false;
	this->app->pollEvent(appevent);
	switch ( appevent.type )
	{
	case sf::Event::Closed :
		quit = true;
		break;
	case sf::Event::KeyPressed :
		if (key.isKeyPressed( sf::Keyboard::Escape )){
			quit = true;
		}
	default:
		break;
	}
	if (quit == true)
	{
		this->app->close();
		exit(0);
	}
}

void			Game::DrawGame( void ){
	sf::Text			text;
	std::stringstream   stream;

	stream << "Draw Game!!" << std::endl;
	this->victory.play();
	text.setFont(osaka);
	text.setString(stream.str());

	text.setCharacterSize(40);
	text.setColor(sf::Color(211, 84, 0));
	text.setPosition(0, 0);
	app->draw(text);
	app->display();
	clear_all();
	sf::sleep(sf::seconds(3));
	this->app->clear(sf::Color::White);
	this->drawGrid();
	this->c = 0;
}

bool			Game::checkEvryLineBreak( int x, int  y, int player){
	int			v;

	if ( ((v = this->whoisHere(x - 1, y)) != player && v)
         && (this->whoisHere(x + 1, y) == player)
         && (this->whoisHere(x + 2, y) == 0) )
{
		this->linebreak = true;
		// std::cout << "piece capturable : "<< x << ", "<< y << " & " << x + 1 << ", "<< y << std::endl;
}
	if ( ((v = this->whoisHere(x - 1, y - 1)) != player && v)
         && (this->whoisHere(x + 1, y + 1) == player)
         && (this->whoisHere(x + 2, y + 2) == 0) )
{
		this->linebreak = true;
		// std::cout << "piece capturable : "<< x << ", "<< y << " & " << x + 1 << ", "<< y + 1 << std::endl;
}
	if ( ((v = this->whoisHere(x, y - 1)) != player && v)
         && (this->whoisHere(x, y + 1) == player)
         && (this->whoisHere(x, y + 2) == 0) )
{
		this->linebreak = true;
		// std::cout << "piece capturable : "<< x << ", "<< y << " & " << x << ", "<< y + 1<< std::endl;
}
	if ( ((v = this->whoisHere(x + 1, y - 1)) != player && v)
         && (this->whoisHere(x - 1, y + 1) == player)
         && (this->whoisHere(x - 2, y + 2) == 0) )
{
		this->linebreak = true;
		// std::cout << "piece capturable : "<< x << ", "<< y << " & " << x - 1<< ", "<< y + 1 << std::endl;
}
	if ( ((v = this->whoisHere(x + 1, y)) != player && v)
         && (this->whoisHere(x - 1, y) == player)
         && (this->whoisHere(x - 2, y) == 0) )
{
		this->linebreak = true;
		// std::cout << "piece capturable : "<< x << ", "<< y << " & " << x - 1 << ", "<< y << std::endl;
}
	if ( ((v = this->whoisHere(x + 1, y + 1)) != player && v)
         && (this->whoisHere(x - 1, y - 1) == player)
         && (this->whoisHere(x - 2, y - 2) == 0) )
{
		this->linebreak = true;
		// std::cout << "piece capturable : "<< x << ", "<< y << " & " << x - 1 << ", "<< y - 1  << std::endl;
}
	if ( ((v = this->whoisHere(x, y + 1)) != player && v)
         && (this->whoisHere(x, y - 1) == player)
         && (this->whoisHere(x, y - 2) == 0) )
{
		this->linebreak = true;
		// std::cout << "piece capturable : "<< x << ", "<< y << " & " << x << ", "<< y - 1<< std::endl;
}
	if ( ((v = this->whoisHere(x - 1, y + 1)) != player && v)
         && (this->whoisHere(x + 1, y - 1) == player)
         && (this->whoisHere(x + 2, y - 2) == 0) )
{
		this->linebreak = true;
		// std::cout << "piece capturable : "<< x << ", "<< y << " & " << x + 1<< ", "<< y - 1<< std::endl;
}


	if ( (this->whoisHere(x - 1, y) == 0 )
         && (this->whoisHere(x + 1, y) == player)
         && (( v = this->whoisHere(x + 2, y)) != player && v) )
{
		this->linebreak = true;
		// std::cout << "piece capturable : "<< x << ", "<< y << " & " << x + 1 << ", "<< y << std::endl;
}
	if ( (this->whoisHere(x - 1, y - 1) == 0)
         && (this->whoisHere(x + 1, y + 1) == player)
         && (( v = this->whoisHere(x + 2, y + 2)) != player && v) )
{
		this->linebreak = true;
		// std::cout << "piece capturable : "<< x << ", "<< y << " & " << x + 1 << ", "<< y + 1<< std::endl;
}
	if ( (this->whoisHere(x, y - 1) == 0)
         && (this->whoisHere(x, y + 1) == player)
         && ((v = this->whoisHere(x, y + 2)) != player && v) )
{
		this->linebreak = true;
		// std::cout << "piece capturable : "<< x << ", "<< y << " & " << x << ", "<< y + 1<< std::endl;
}
	if ( (this->whoisHere(x + 1, y - 1) == 0)
         && (this->whoisHere(x - 1, y + 1) == player)
         && ( (v = this->whoisHere(x - 2, y + 2)) != player && v) )
{
		this->linebreak = true;
		// std::cout << "piece capturable : "<< x << ", "<< y << " & " << x - 1<< ", "<< y + 1<< std::endl;
}
	if ( (this->whoisHere(x + 1, y) == 0)
         && (this->whoisHere(x - 1, y) == player)
         && (( v = this->whoisHere(x - 2, y)) != player && v) )
{
		this->linebreak = true;
		// std::cout << "piece capturable : "<< x << ", "<< y << " & " << x - 1<< ", "<< y << std::endl;
}
	if ( (this->whoisHere(x + 1, y + 1) == 0)
         && (this->whoisHere(x - 1, y - 1) == player)
         && ((v = this->whoisHere(x - 2, y - 2)) != player && v) )
{
		this->linebreak = true;
		// std::cout << "piece capturable : "<< x << ", "<< y << " & " << x - 1<< ", "<< y - 1<< std::endl;
}
	if ( (this->whoisHere(x, y + 1) == 0)
         && (this->whoisHere(x, y - 1) == player)
         && ((v = this->whoisHere(x, y - 2)) != player && v) )
{
		this->linebreak = true;
		// std::cout << "piece capturable : "<< x << ", "<< y << " & " << x << ", "<< y - 1<< std::endl;
}
	if ( (this->whoisHere(x - 1, y + 1) == 0)
         && (this->whoisHere(x + 1, y - 1) == player)
         && ((v = this->whoisHere(x + 2, y - 2)) != player && v) )
{
		this->linebreak = true;
		// std::cout << "piece capturable : "<< x << ", "<< y << " & " << x + 1<< ", "<< y - 1<< std::endl;
}
	return (false);
}

void			Game::horiLineBreaker(int x, int y, int player, int incr){

	while (whoisHere(x, y) == player)
	{
		checkEvryLineBreak(x, y, player);
		x = x + incr;
	}
}

void			Game::vertLineBreaker(int x, int y, int player, int incr){

	while (whoisHere(x, y) == player)
	{
		checkEvryLineBreak(x, y, player);
		y = y + incr;
	}
}

void			Game::diagLineBreaker(int x, int y, int player, int incrx, int incry){

	while (whoisHere(x, y) == player)
	{
		checkEvryLineBreak(x, y, player);
		x = x + incrx;
		y = y + incry;
	}
}

bool			Game::hori( t_pions * token ){
	int				tx;
	int				ty;
	int				v;

	v = 0;
	tx = token->x + 1;
	ty = token->y;
	while ( whoisHere(tx, ty) == token->player )
	{
		tx++;
		v++;
		if (v == 4)
		{
			this->horiLineBreaker(tx - 1, ty, token->player, -1);
			return (true);
		}
	}
	tx = token->x - 1;
	while ( whoisHere(tx, ty) == token->player )
	{
		tx--;
		v++;
		if (v == 4)
		{
			this->horiLineBreaker(tx + 1, ty, token->player, 1);
			return (true);
		}
	}
	return (false);
}

bool			Game::vert( t_pions *token ){
	int				tx;
	int				ty;
	int				v;

	v = 0;

	tx = token->x;
	ty = token->y + 1;
	while ( whoisHere(tx, ty) == token->player )
	{
		ty++;
		v++;
		if (v == 4)
		{
			this->vertLineBreaker(tx, ty - 1, token->player, -1);
			return (true);
		}
	}
	ty = token->y - 1;
	while ( whoisHere(tx, ty) == token->player )
	{
		ty--;
		v++;
		if (v == 4)
		{
			this->vertLineBreaker(tx, ty + 1, token->player, 1);
			return (true);
		}
	}
	return (false);
}

bool			Game::diag1( t_pions *token ){
	int				tx;
	int				ty;
	int				v;

	v = 0;
	tx = token->x + 1;
	ty = token->y + 1;
	while ( whoisHere(tx, ty) == token->player )
	{
		ty++;
		tx++;
		v++;
		if (v == 4)
		{
			this->diagLineBreaker(tx - 1, ty - 1, token->player, -1, -1);
			return (true);
		}
	}
	ty = token->y - 1;
	tx = token->x - 1;
	while ( whoisHere(tx, ty) == token->player )
	{
		ty--;
		tx--;
		v++;
		if (v == 4)
		{
			this->diagLineBreaker(tx + 1, ty + 1, token->player, 1, 1);
			return (true);
		}
	}
	return (false);
}

bool			Game::diag2( t_pions *token ){
	int				tx;
	int				ty;
	int				v;

	v = 0;
	tx = token->x + 1;
	ty = token->y - 1;
	while ( whoisHere(tx, ty) == token->player )
	{
		ty--;
		tx++;
		v++;
		if (v == 4)
		{
			this->diagLineBreaker(tx - 1, ty + 1, token->player, -1, 1);
			return (true);
		}
	}
	ty = token->y + 1;
	tx = token->x - 1;
	while ( whoisHere(tx, ty) == token->player )
	{
		ty++;
		tx--;
		v++;
		if (v == 4)
		{
			this->diagLineBreaker(tx + 1, ty - 1, token->player, 1, -1);
			return (true);
		}
	}
	return (false);
}


bool	Game::ft_is_finished_for(std::array<std::array<char, 19>, 19> map, char c){
	int count = 0;
	int p = 0;
	for (int i = 0; i < len; ++i){ //verti
		count = 0;
		for (int j = 0; j < len; ++j){
			if (map[j][i] == c){
				count++;
				if (count == nwin){
					return (true);
				}
			}
			else
				count = 0;
		}
	}
	count = 0;
	for (int i = 0; i < len; ++i){ //hori
		count = 0;
		for (int j = 0; j < len; ++j){
			if (map[i][j] == c){
				count++;
				if (count == nwin){
					return (true);
				}
			}
			else
				count = 0;
		}
	}
	count = 0;
	for (int k = 0; k < decal; ++k){ 
		count = 0;
		for (int i = 0; i < len - k; ++i){ //start up left -> down right toward up right
			if (map[i][i+k] == c){
				count++;
				if (count == nwin){
					return (true);
				}
			}
			else
				count = 0;
		}
		count = 0;
		p = 0;
		for (int i = len - 1 - k; i >= 0; --i){
			if (map[p][i] == c){
				count++;
				if (count == nwin){
					return (true);
				}
			}
			else
				count = 0;
			p++;
		}
		if (k == 0)
			continue;
		count = 0;
		for (int i = 0; i < len - k; ++i){  //start up left -> down right toward down left
			if (map[i+k][i] == c){
				count++;
				if (count == nwin){
					return (true);
				}
			}
			else
				count = 0;
		}
		p = 0;
		count = 0;
		for (int i = len - 1; i >= k; --i){//start up right -> down left toward down right //PRETY SPACE
			if (map[p+k][i] == c){
				count++;
				if (count == nwin){
					return (true);
				}
			}
			else
				count = 0;
			p++;
		}
	}
	return (false);

}

int     Game::ft_check_is_catchable(Node & node){
  int x = node.x;
  int y = node.y;
  bool  isok;
  char  c;
  int   count;
  std::array<std::array<char, 19>, 19> map = node.getMap();

  count = 0;
  isok = false;
  c = map[y][x];
  if (x > 2){
    for (int i = 1; i < 4; ++i) //H to left
    {
      if (c == map[y][x-i]){
        if (count == 2)
          isok = true;
        else
          break;
      }
      else if (map[y][x-i] != 0 && c != map[y][x-i])
        count++;
    }
    if (isok){
    	// std::cout << "SLASH H1" << std::endl;
      map[y][x-1] = 0;
      map[y][x-2] = 0;
      node.setMap(map);
      if (map[y][x] == 'X')
        node.nbTakenBlack += 2;
      else        
        node.nbTakenWhite += 2;
      // std::cout << "CATCHABLE IN H 1" << std::endl;
      return (1);
    }
  }
  if (x < len - 3){
    count = 0;
    isok = false;
    c = map[y][x];
    for (int i = 1; i < 4; ++i)  //H to right
    {
      if (c == map[y][x+i]){
        if (count == 2)
          isok = true;
        else
          break;
      }
      else if (map[y][x+i] != 0 && c != map[y][x+i])
        count++;
    }
    if (isok){
    	// std::cout << "SLASH H2" << std::endl;
      map[y][x+1] = 0;
      map[y][x+2] = 0;
      node.setMap(map);
      if (map[y][x] == 'X')
        node.nbTakenBlack += 2;
      else        
        node.nbTakenWhite += 2;
      // std::cout << "CATCHABLE IN H 2" << std::endl;
      return (1);
    }
  }
  if (y > 2){
    count = 0;
    isok = false;
    c = map[y][x];
    for (int i = 1; i < 4; ++i)  //V to up
    {
      if (c == map[y-i][x]){
        if (count == 2)
          isok = true;
        else
          break;
      }
      else if (map[y-i][x] != 0 && c != map[y-i][x])
        count++;
    }
    if (isok){
    	// std::cout << "SLASH V1" << std::endl;
      map[y-1][x] = 0;
      map[y-2][x] = 0;
      node.setMap(map);
      if (map[y][x] == 'X')
        node.nbTakenBlack += 2;
      else        
        node.nbTakenWhite += 2;
      // std::cout << "CATCHABLE IN V 1" << std::endl;
      return (1);
    }

  }
  if (y < len - 3){
    count = 0;
    isok = false;
    c = map[y][x];
    for (int i = 1; i < 4; ++i)  //V to down
    {
      if (c == map[y+i][x]){
        if (count == 2)
          isok = true;
        else
          break;
      }
      else if (map[y+i][x] != 0 && c != map[y+i][x])
        count++;
    }
    if (isok){
    	// std::cout << "SLASH V2" << std::endl;
      map[y+1][x] = 0;
      map[y+2][x] = 0;
      node.setMap(map);
      if (map[y][x] == 'X')
        node.nbTakenBlack += 2;
      else        
        node.nbTakenWhite += 2;
      // std::cout << "CATCHABLE IN V 2" << std::endl;
      return (1);
    }
  }
  //DIIAGGG
  if (x < len - 3 && y < len - 3){
    count = 0;
    isok = false;
    c = map[y][x];
    for (int i = 1; i < 4; ++i)  //D to down-right
    {
      if (c == map[y+i][x+i]){
        if (count == 2)
          isok = true;
        else
          break;
      }
      else if (map[y+i][x+i] != 0 && c != map[y+i][x+i])
        count++;
    }
    if (isok){
    	// std::cout << "SLASH D1" << std::endl;
      map[y+1][x+1] = 0;
      map[y+2][x+2] = 0;
      node.setMap(map);
      if (map[y][x] == 'X')
        node.nbTakenBlack += 2;
      else        
        node.nbTakenWhite += 2;
      return (1);
    }
  }
  if (y > 2 && x > 2){
    count = 0;
    isok = false;
    c = map[y][x];
    for (int i = 1; i < 4; ++i)  //D to top-left
    {
      if (c == map[y-i][x-i]){
        if (count == 2)
          isok = true;
        else
          break;
      }
      else if (map[y-i][x-i] != 0 && c != map[y-i][x-i])
        count++;
    }
    if (isok){
    	// std::cout << "SLASH D2" << std::endl;
      map[y-1][x-1] = 0;
      map[y-2][x-2] = 0;
      node.setMap(map);
      if (map[y][x] == 'X')
        node.nbTakenBlack += 2;
      else        
        node.nbTakenWhite += 2;
      return (1);
    }
  }
  if (x > 2 && y < len - 3){
    count = 0;
    isok = false;
    c = map[y][x];
    for (int i = 1; i < 4; ++i)  //D to down-left
    {
      if (c == map[y+i][x-i]){
        if (count == 2)
          isok = true;
        else
          break;
      }
      else if (map[y+i][x-i] != 0 && c != map[y+i][x-i])
        count++;
    }
    if (isok){
    	// std::cout << "SLASH D3" << std::endl;
      map[y+1][x-1] = 0;
      map[y+2][x-2] = 0;
      node.setMap(map);
      if (map[y][x] == 'X')
        node.nbTakenBlack += 2;
      else        
        node.nbTakenWhite += 2;
      return (1);
    }
  }
  if (y > 2 && x < len - 3){
    count = 0;
    isok = false;
    c = map[y][x];
    for (int i = 1; i < 4; ++i)  //D to top-right
    {
      if (c == map[y-i][x+i]){
        if (count == 2)
          isok = true;
        else
          break;
      }
      else if (map[y-i][x+i] != 0 && c != map[y-i][x+i])
        count++;
    }
    if (isok){
    	// std::cout << "SLASH D4" << std::endl;
      map[y-1][x+1] = 0;
      map[y-2][x+2] = 0;
      node.setMap(map);
      if (map[y][x] == 'X')
        node.nbTakenBlack += 2;
      else        
        node.nbTakenWhite += 2;
      return (1);
    }
  }
  return (0);
}


void 		Game::ft_display_map(std::array<std::array<char, 19>, 19> map){
	char	c = 'A';

	std::cout << "  1 2 3 4 5 6 7 8 910111213141516171819" << std::endl << c << ' ';
	for (int i = 0; i < len; ++i){
		for (int j = 0; j < len; ++j){
			if (!map[i][j])
				std::cout << ' ';
			else
				std::cout << map[i][j];
			if (j < (len - 1))
				std::cout << '|';
		}
		std::cout << std::endl;
		if ((int)(c - 64) < len)
			std::cout << " ---------------------------------------" << std::endl << ++c << ' ';
	}
	std::cout << std::endl;
}

bool 		Game::ft_check_if_win(std::array<std::array<char, 19>, 19> const map){

	if (ft_is_finished_for(map, 'O'))
		return (true);
	if (ft_is_finished_for(map, 'X'))
		return (true);
	return (false);
}

bool			Game::isWin( t_pions *token ){
	(void)token;
	
	if (this->cap1 > 9 || this->cap2 > 9 )
		return (true);
	if ( this->hori(token) ){
		if (!p2->human && token->player == 1 && !State.second.istmpwin)
			State.second.istmpwin = true;
		return (true);
	}
	if ( this->vert(token) ){
		if (!p2->human && token->player == 1 && !State.second.istmpwin)
			State.second.istmpwin = true;
		return (true);
	}
	if ( this->diag1(token) ){
		if (!p2->human && token->player == 1 && !State.second.istmpwin)
			State.second.istmpwin = true;
		return (true);
	}
	if ( this->diag2(token) ){
		if (!p2->human && token->player == 1 && !State.second.istmpwin)
			State.second.istmpwin = true;
		return (true);
	}
	if (ft_check_if_win(State.second.getMap())){
		if (!p2->human && token->player == 1 && !State.second.istmpwin)
			State.second.istmpwin = true;
		return(true);
	}
	return (false);
}

void			Game::remove_token( int x, int y )
{
	if (x < 19 && y < 19)
		State.second.setMap_char_at_XY(x, y, 0);
}

bool			Game::CaptureB( t_pions * ntoken ){
	int			v;

	v = this->c;
	this->save.x = ntoken->x;
	this->save.y = ntoken->y;
	this->save.player = ntoken->player;
	if ( (this->whoisHere(ntoken->x + 1, ntoken->y) == 1)
		 && (this->whoisHere(ntoken->x + 2, ntoken->y) == 1)
		 && (this->whoisHere(ntoken->x + 3, ntoken->y) == 2) )
	{
		this->remove_token(ntoken->x + 1, ntoken->y);
		this->remove_token(ntoken->x + 2, ntoken->y);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x - 1, ntoken->y) == 1)
		 && (this->whoisHere(ntoken->x - 2, ntoken->y) == 1)
		 && (this->whoisHere(ntoken->x - 3, ntoken->y) == 2) )
	{
		this->remove_token(ntoken->x - 1, ntoken->y);
		this->remove_token(ntoken->x - 2, ntoken->y);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x, ntoken->y + 1) == 1)
		 && (this->whoisHere(ntoken->x, ntoken->y + 2) == 1)
		 && (this->whoisHere(ntoken->x, ntoken->y + 3) == 2) )
	{
		this->remove_token(ntoken->x, ntoken->y + 1);
		this->remove_token(ntoken->x, ntoken->y + 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x, ntoken->y - 1) == 1)
		 && (this->whoisHere(ntoken->x, ntoken->y - 2) == 1)
		 && (this->whoisHere(ntoken->x, ntoken->y - 3) == 2) )
	{
		this->remove_token(ntoken->x, ntoken->y - 1);
		this->remove_token(ntoken->x, ntoken->y - 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x + 1, ntoken->y + 1) == 1)
		 && (this->whoisHere(ntoken->x + 2, ntoken->y + 2) == 1)
		 && (this->whoisHere(ntoken->x + 3, ntoken->y + 3) == 2) )
	{
		this->remove_token(ntoken->x + 1, ntoken->y + 1);
		this->remove_token(ntoken->x + 2, ntoken->y + 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x - 1, ntoken->y - 1) == 1)
		 && (this->whoisHere(ntoken->x - 2, ntoken->y - 2) == 1)
		 && (this->whoisHere(ntoken->x - 3, ntoken->y - 3) == 2) )
	{
		this->remove_token(ntoken->x - 1, ntoken->y - 1);
		this->remove_token(ntoken->x - 2, ntoken->y - 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x + 1, ntoken->y - 1) == 1)
		 && (this->whoisHere(ntoken->x + 2, ntoken->y - 2) == 1)
		 && (this->whoisHere(ntoken->x + 3, ntoken->y - 3) == 2) )
	{
		this->remove_token(ntoken->x + 1, ntoken->y - 1);
		this->remove_token(ntoken->x + 2, ntoken->y - 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x - 1, ntoken->y + 1) == 1)
		 && (this->whoisHere(ntoken->x - 2, ntoken->y + 2) == 1)
		 && (this->whoisHere(ntoken->x - 3, ntoken->y + 3) == 2) )
	{
		this->remove_token(ntoken->x - 1, ntoken->y + 1);
		this->remove_token(ntoken->x - 2, ntoken->y + 2);
		this->c = this->c - 2;
	}
	if (v != this->c)
	{
		sf::Text    text;

		text.setFont(osaka);
		text.setString("Slash!!!");
		text.setCharacterSize(40);
		this->app->clear(sf::Color::White);
		this->drawGrid();
		this->drawToken();
        this->app->draw(text);
        this->app->display();
        this->captur.play();
		sf::sleep(sf::seconds(1));
		this->cap2 = this->cap2 + (v - this->c);
		State.second.nbTakenWhite = cap2;
		return (true);
	}
	return (false);
}

void 			Game::Slashme(){
	sf::Text    text;

	this->time->Pause();
	text.setFont(osaka);
	text.setString("Slash!!!");
	text.setCharacterSize(40);
	this->app->clear(sf::Color::White);
	this->drawGrid();
	this->drawToken();
    this->app->draw(text);
    this->app->display();
    this->captur.play();
	sf::sleep(sf::seconds(1));
	cap1 = State.second.nbTakenBlack;
	cap2 = State.second.nbTakenWhite;
}

bool			Game::CaptureW( t_pions * ntoken ){
	int			v;

	v = this->c;
	this->save.x = ntoken->x;
	this->save.y = ntoken->y;
	this->save.player = ntoken->player;
	if ( (this->whoisHere(ntoken->x + 1, ntoken->y) == 2)
		 && (this->whoisHere(ntoken->x + 2, ntoken->y) == 2)
		 && (this->whoisHere(ntoken->x + 3, ntoken->y) == 1) )
	{
		this->remove_token(ntoken->x + 1, ntoken->y);
		this->remove_token(ntoken->x + 2, ntoken->y);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x - 1, ntoken->y) == 2)
		 && (this->whoisHere(ntoken->x - 2, ntoken->y) == 2)
		 && (this->whoisHere(ntoken->x - 3, ntoken->y) == 1) )
	{
		this->remove_token(ntoken->x - 1, ntoken->y);
		this->remove_token(ntoken->x - 2, ntoken->y);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x, ntoken->y + 1) == 2)
		 && (this->whoisHere(ntoken->x, ntoken->y + 2) == 2)
		 && (this->whoisHere(ntoken->x, ntoken->y + 3) == 1) )
	{
		this->remove_token(ntoken->x, ntoken->y + 1);
		this->remove_token(ntoken->x, ntoken->y + 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x, ntoken->y - 1) == 2)
		 && (this->whoisHere(ntoken->x, ntoken->y - 2) == 2)
		 && (this->whoisHere(ntoken->x, ntoken->y - 3) == 1) )
	{
		this->remove_token(ntoken->x, ntoken->y - 1);
		this->remove_token(ntoken->x, ntoken->y - 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x + 1, ntoken->y + 1) == 2)
		 && (this->whoisHere(ntoken->x + 2, ntoken->y + 2) == 2)
		 && (this->whoisHere(ntoken->x + 3, ntoken->y + 3) == 1) )
	{
		this->remove_token(ntoken->x + 1, ntoken->y + 1);
		this->remove_token(ntoken->x + 2, ntoken->y + 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x - 1, ntoken->y - 1) == 2)
		 && (this->whoisHere(ntoken->x - 2, ntoken->y - 2) == 2)
		 && (this->whoisHere(ntoken->x - 3, ntoken->y - 3) == 1) )
	{
		this->remove_token(ntoken->x - 1, ntoken->y - 1);
		this->remove_token(ntoken->x - 2, ntoken->y - 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x + 1, ntoken->y - 1) == 2)
		 && (this->whoisHere(ntoken->x + 2, ntoken->y - 2) == 2)
		 && (this->whoisHere(ntoken->x + 3, ntoken->y - 3) == 1) )
	{
		this->remove_token(ntoken->x + 1, ntoken->y - 1);
		this->remove_token(ntoken->x + 2, ntoken->y - 2);
		this->c = this->c - 2;
	}
	if ( (this->whoisHere(ntoken->x - 1, ntoken->y + 1) == 2)
		 && (this->whoisHere(ntoken->x - 2, ntoken->y + 2) == 2)
		 && (this->whoisHere(ntoken->x - 3, ntoken->y + 3) == 1) )
	{
		this->remove_token(ntoken->x - 1, ntoken->y + 1);
		this->remove_token(ntoken->x - 2, ntoken->y + 2);
		this->c = this->c - 2;
	}
	if (v != this->c)
	{
		sf::Text    text;

		text.setFont(osaka);
		text.setString("Slash!!!");
		text.setCharacterSize(40);
		this->app->clear(sf::Color::Black);
		this->drawGrid();
		this->drawToken();
        this->app->draw(text);
        this->app->display();
        this->captur.play();
		sf::sleep(sf::seconds(1));
		this->cap1 = this->cap1 + (v - this->c);
		State.second.nbTakenBlack = cap1;
		return (true);
	}
	return (false);
}

void			Game::drawBreakevent( void ){
	sf::Text    text;

    this->app->clear(sf::Color::White);
    this->drawGrid();
    this->drawToken();
    text.setFont(osaka);
    text.setString("Last Stand ?!..");
    text.setCharacterSize(40);
	this->app->draw(text);
	this->drawScore();
	this->app->display();
	sf::sleep(sf::seconds(1));
}

void			Game::breakcapture1( void ){
	if (p2->GetPlayerN() == 2)
		this->CaptureB(this->p2->put_token(*this));
	else
		this->CaptureB(this->p1->put_token(*this));
	this->advance++;
}

void			Game::breakcapture2( void ){
	if (p1->GetPlayerN() == 1)
		this->CaptureW(this->p1->put_token(*this));
	else
		this->CaptureW(this->p2->put_token(*this));
	this->advance++;
}

void			Game::unbreakable1( t_pions *token ){
	if (this->cap1 > 9)
	{
		this->Winner( token->player );
		return ;
	}
	if (this->linebreak == true || this->cap2 > 7)
	{
		std::stringstream		os;
		this->drawBreakevent();
		this->breakstat = 1;
		this->breakcapture1();
		os << this->save.x << " " << this->save.y;
		if (save.player == 1)
			State.second.setMap_char_at_XY(save.x, save.y, 'X');
		if (save.player == 2)
			State.second.setMap_char_at_XY(save.x, save.y, 'O');
		if (ft_check_is_catchable(State.second)){
			cap1 = State.second.nbTakenWhite;
			cap2 = State.second.nbTakenBlack;
		}
		if (this->whoisHere(token->x, token->y) == 0)
		token->player = -1;
		this->clear_all_virtual();
		this->app->clear(sf::Color::White);
		this->drawGrid();
		this->drawToken();
		this->drawScore();
		this->linebreak = false;
		if (!isWin(token))
			return ;
	}
	if (this->cap2 > 9)
	{
		this->app->clear(sf::Color::White);
		this->drawGrid();
		this->drawToken();
		this->drawScore();
		this->Winner(2);
	}
	else
	{
		this->breakstat = 0;
		this->app->clear(sf::Color::White);
		this->drawGrid();
		this->drawToken();
		this->drawScore();
		this->Winner(1);
	}

}

void			Game::unbreakable2( t_pions * token ){
	if (this->cap2 > 9)
	{
		this->Winner( token->player );
		return ;
	}
	if (this->linebreak == true || this->cap1 > 7)
	{
		std::stringstream        os;
		this->drawBreakevent();
		this->breakstat = 2;
		this->breakcapture2();
		os << this->save.x << " " << this->save.y;
		if (save.player == 1)
			State.second.setMap_char_at_XY(save.x, save.y, 'X');
		if (save.player == 2)
			State.second.setMap_char_at_XY(save.x, save.y, 'O');
		if (ft_check_is_catchable(State.second)){
			cap1 = State.second.nbTakenWhite;
			cap2 = State.second.nbTakenBlack;
		}
	if (this->whoisHere(token->x, token->y) == 0)
		token->player = -1;
		this->clear_all_virtual();
		this->app->clear(sf::Color::White);
		this->drawGrid();
		this->drawToken();
		this->drawScore();
		this->linebreak = false;
		if (!isWin(token))
			return ;
	}
	if (this->cap1 > 9)
	{
		this->app->clear(sf::Color::White);
		this->drawGrid();
		this->drawToken();
		this->drawScore();
		this->Winner(1);
	}
	else
	{
		this->breakstat = 0;
		this->app->clear(sf::Color::White);
		this->drawGrid();
		this->drawToken();
		this->drawScore();
		this->Winner(2);
	}
}

void			Game::add_token( t_pions * token ){
	this->time->Pause();
	if (token->player == 1){
		this->stm1.str("");
	this->stm1 << std::setfill ('0') << std::setw (2);
	this->stm1 << time->GetTime() << ":"; 
	this->stm1 << std::setfill ('0') << std::setw (2); 
	this->stm1 << time->GetTime_sec() << ":" ;
	this->stm1 << std::setfill ('0') << std::setw (2);
	this->stm1 << time->GetTime_milli();
	State.second.setMap_char_at_XY(token->x, token->y, 'X');

	}
	else if (token->player == 2){
		this->stm2.str("");
	this->stm2 << std::setfill ('0') << std::setw (2);
	this->stm2 << time->GetTime() << ":"; 
	this->stm2 << std::setfill ('0') << std::setw (2); 
	this->stm2 << time->GetTime_sec() << ":" ;
	this->stm2 << std::setfill ('0') << std::setw (2);
	this->stm2 << time->GetTime_milli();
	State.second.setMap_char_at_XY(token->x, token->y, 'O');

	}
	this->time->Start();
	if (ft_check_is_catchable(State.second)){
			cap1 = State.second.nbTakenWhite;
			cap2 = State.second.nbTakenBlack;
	}
	this->app->clear(sf::Color::White);
	this->drawGrid();
	this->drawToken();
	this->drawScore();
	if (isWin(token))
	{
		if (token->player == 1)
			this->unbreakable1(token);
		if (token->player == 2)
			this->unbreakable2(token);
	}
	if ( this->c >= 360 )
		this->DrawGame();
	this->app->display();
}


void			Game::add_token( int x, int y, int player ){

	t_pions		*ntoken = new t_pions;
	ntoken->x = x;
	ntoken->y = y;
	ntoken->player = player;

	if (player == 1)
		State.second.setMap_char_at_XY(x, y, 'X');
	else if (player == 2)
		State.second.setMap_char_at_XY(x, y, 'O');
	if (ft_check_is_catchable(State.second)){
			cap1 = State.second.nbTakenWhite;
			cap2 = State.second.nbTakenBlack;
	}
	this->app->clear(sf::Color::White);
	this->drawGrid();
	this->drawToken();
	this->drawScore();
	if (isWin(ntoken))
	{
		if (ntoken->player == 1)//human
			this->unbreakable1(ntoken);
		if (ntoken->player == 2)//AI
			this->unbreakable2(ntoken);
	}
	if ( this->c >= 360 )
		this->DrawGame();
	this->app->display();
}

bool			Game::checkfreeHori(int xa, int xb, int y, int player){
	int			c;

	c = 0;
	if ( (whoisHere(xa - 1, y) != 0) || (whoisHere(xb + 1, y) != 0))
		return (false);
	while (xa <= xb)
	{
		if (whoisHere(xa, y) == player)
			c++;
		else if (whoisHere(xa, y) == 0)
			c = c + 0;
		else
			return (false);
		xa++;
	}

	if (c == 2)
		return (true);
	return (false);
}

int				Game::freeThreeHor( t_pions *token ){
	int			xa;
	int			xb;

	xa = token->x - 3;
	xb = token->x;
	if (checkfreeHori(xa, xb, token->y, token->player))
		return (1);
	xa++;
	xb++;
	if (checkfreeHori(xa, xb, token->y, token->player))
		return (1);
	xa++;
	xb++;
	if (checkfreeHori(xa, xb, token->y, token->player))
		return (1);
	xa++;
	xb++;
	if (checkfreeHori(xa, xb, token->y, token->player))
		return (1);
	return (0);
}

bool			Game::checkfreeVer(int x, int ya, int yb, int player){
	int			c;

	c = 0;
	if (( whoisHere(x, ya - 1) != 0) || (whoisHere(x, yb + 1) != 0))
		return (false);
	while (ya <= yb)
	{
		if (whoisHere(x, ya) == player)
			c++;
		else if (whoisHere(x, ya) == 0)
			c = c + 0;
		else
			return (false);
		ya++;
	}
	if (c == 2)
		return (true);
	return (false);
}

int				Game::freeThreeVer( t_pions *token ){
	int			ya;
	int			yb;

	ya = token->y - 3;
	yb = token->y;
	if (checkfreeVer(token->x, ya, yb, token->player))
		return (1);
	ya++;
	yb++;
	if (checkfreeVer(token->x, ya, yb, token->player))
		return (1);
	ya++;
	yb++;
	if (checkfreeVer(token->x, ya, yb, token->player))
		return (1);
	ya++;
	yb++;
	if (checkfreeVer(token->x, ya, yb, token->player))
		return (1);
	return (0);
}


bool			Game::checkfreeDiag1(int xa, int xb, int ya, int yb, int player){
	int			c;

	c = 0;
	if (( whoisHere(xa - 1, ya - 1) != 0) || (whoisHere(xb + 1, yb + 1) != 0))
		return (false);
	while (ya <= yb)
	{
		if (whoisHere(xa, ya) == player)
			c++;
		else if (whoisHere(xa, ya) == 0)
			c = c + 0;
		else
			return (false);
		ya++;
		xa++;
	}
	if (c == 2)
		return (true);
	return (false);
}

int				Game::freeThreeDiag1( t_pions *token ){
	int			xa;
	int			xb;
	int			ya;
	int			yb;

	ya = token->y - 3;
	yb = token->y;
	xa = token->x - 3;
	xb = token->x;
	if (checkfreeDiag1(xa, xb, ya, yb, token->player))
		return (1);
	ya++;
	yb++;
	xa++;
	xb++;
	if (checkfreeDiag1(xa, xb, ya, yb, token->player))
		return (1);
	ya++;
	yb++;
	xa++;
	xb++;
	if (checkfreeDiag1(xa, xb, ya, yb, token->player))
		return (1);
	ya++;
	yb++;
	xa++;
	xb++;
	if (checkfreeDiag1(xa, xb, ya, yb, token->player))
		return (1);
	return (0);
}

bool			Game::checkfreeDiag2(int xa, int xb, int ya, int yb, int player){
	int			c;

	c = 0;
	if (( whoisHere(xa - 1, ya + 1) != 0) || (whoisHere(xb + 1, yb - 1) != 0))
		return (false);
	while (xa <= xb)
	{
		if (whoisHere(xa, ya) == player)
			c++;
		else if (whoisHere(xa, ya) == 0)
			c = c + 0;
		else
			return (false);
		ya--;
		xa++;
	}
	if (c == 2)
		return (true);
	return (false);
}

int				Game::freeThreeDiag2( t_pions *token ){
	int			xa;
	int			xb;
	int			ya;
	int			yb;

	ya = token->y + 3;
	yb = token->y;
	xa = token->x - 3;
	xb = token->x;
	if (checkfreeDiag2(xa, xb, ya, yb, token->player))
		return (1);
	ya--;
	yb--;
	xa++;
	xb++;
	if (checkfreeDiag2(xa, xb, ya, yb, token->player))
		return (1);
	ya--;
	yb--;
	xa++;
	xb++;
	if (checkfreeDiag2(xa, xb, ya, yb, token->player))
		return (1);
	ya--;
	yb--;
	xa++;
	xb++;
	if (checkfreeDiag2(xa, xb, ya, yb, token->player))
		return (1);
	return (0);
}

bool			Game::forbidden( t_pions * token ){
	int			c;
	sf::Text	text;

	this->app->clear(sf::Color::White);
	this->drawGrid();
	this->drawToken();
	text.setFont(osaka);
    text.setString("Forbidden!");

    text.setCharacterSize(40);
    if (token->player == 1)
        text.setColor(sf::Color::White);
    else
        text.setColor(sf::Color::Black);
    text.setPosition(0, 0);
	c = 0;
	if (token->player == 1)
	{
		if (this->CaptureW(token))
			return (false);
	}
	else if (token->player == 2)
		if (this->CaptureB(token))
			return (false);
	c = c + freeThreeHor(token);
	c = c + freeThreeVer(token);
	c = c + freeThreeDiag1(token);
	c = c + freeThreeDiag2(token);
	if (c > 1)
	{
		this->app->draw(text);
		this->app->display();
		this->forbi.play();
		return (true);
	}
	return (false);
}

void		Game::clear_all( void ){

	Node 			Start  = Node();

	State.second.setMap(Start.getMap());
	State.second.x = 0;
	State.second.y = 0;
	State.second.nbTakenWhite = 0;
	State.second.nbTakenBlack = 0;
	State.second.istmpwin = false;
	pions.clear();
	fake.clear();
}

int			Game::whoisHere( int x, int y ){
	std::array<std::array<char, 19>, 19> map = State.second.getMap();
	if ( x >= 0 && x < 19 && y >= 0 && y < 19){
		if (map[y][x] == 'X')
			return (1);
		if (map[y][x] == 'O')
			return (2);
	}
	return(0);
}

int			Game::whoisHere( t_pions * wp )
{
	std::array<std::array<char, 19>, 19> map = State.second.getMap();

	if (wp->x >= 0 && wp->x < 19 && wp->y >= 0 && wp->y < 19){
		if (map[wp->y][wp->x] == 'X')
			return (1);
		if (map[wp->y][wp->x] == 'O')
			return (2);
	}
	return (0);
}

void						Game::drawToken( void ){
	std::array<std::array<char, 19>, 19> map = State.second.getMap();
	for (int i = 0; i < len; ++i){
		for (int j = 0; j < len; ++j){

			sf::CircleShape		shape(DIM);
			if (map[i][j]){
				shape.setPosition(((j * GO_CASE) + ORIGIN_X) - DIM,
								  ((i * GO_CASE) + ORIGIN_Y) - DIM);
				if (map[i][j] == 'X')
					shape.setTexture(&this->blanc);
				else
					shape.setTexture(&this->noir);
			
				this->app->draw(shape);
			}
		}
	}
	sf::Text 	t1;
	sf::Text 	t2;

	t1.setFont(digi);
	t2.setFont(digi);
	
	t1.setCharacterSize(20);
	t2.setCharacterSize(20);
	t1.setString(stm1.str());
	t2.setString(stm2.str());
	t2.setColor(sf::Color::Black);
	t2.setPosition(WIN_LENGTH - 70, WIN_HEIGHT - 100);
	t1.setColor(sf::Color::White);
	t1.setPosition(10, WIN_HEIGHT - 100);
	app->draw(t1);
	app->draw(t2);
}

void						Game::drawScore( void ){
	sf::Text			sc1;
	sf::Text			sc2;
	std::stringstream   stream1;
	std::stringstream   stream2;


	sc1.setFont(osaka);
	sc2.setFont(osaka);
	stream1 << this->cap1;
	if (this->cap1 == 5)
		stream1 << " !!!";
	sc1.setString(stream1.str());
	stream2 << this->cap2;
	if (this->cap2 == 5)
		stream2 << " !!!";
	sc2.setString(stream2.str());

	sc1.setCharacterSize(40);
	sc2.setCharacterSize(40);
	sc1.setColor(sf::Color::White);
	sc2.setColor(sf::Color::Black);
	sc1.setPosition(10, WIN_HEIGHT - 50);
	sc2.setPosition(WIN_LENGTH - 50, WIN_HEIGHT - 50);
	app->draw(sc1);
	app->draw(sc2);
}
void						Game::drawGrid( void )
{
	int						x;
	int						y;
	sf::RectangleShape		plateau;
	sf::RectangleShape		decor;

	x = ORIGIN_X;
	y = ORIGIN_Y;
	decor.setTexture(&fond);
	decor.setPosition(0, 0);
	decor.setSize(sf::Vector2f(WIN_LENGTH, WIN_HEIGHT));
	plateau.setTexture(&woodTex);
	plateau.setPosition(ORIGIN_X - (GO_CASE / 2), ORIGIN_Y - (GO_CASE / 2));
	plateau.setSize(sf::Vector2f(GO_CASE * 19, GO_CASE * 19));
	this->app->draw(decor);
	this->app->draw(plateau);
	while (y < (18 * GO_CASE) + ORIGIN_Y)
	{
		sf::RectangleShape      grille;

		grille.setSize(sf::Vector2f(GO_CASE - 1, GO_CASE - 1));
		grille.setPosition(x, y);
		grille.setFillColor(sf::Color::Transparent);
		grille.setOutlineThickness(2);
		grille.setOutlineColor(sf::Color(0, 0, 0));
		this->app->draw(grille);
		x = x + GO_CASE;
		if (x > (17 * GO_CASE) + ORIGIN_X)
		{
			x = ORIGIN_X;
			y = y + GO_CASE;
		}
	}
	sf::RectangleShape      carre;

	carre.setSize(sf::Vector2f(9, 9));
	carre.setPosition((ORIGIN_X + (9 * GO_CASE)) - 5, (ORIGIN_Y + (9 * GO_CASE)) - 5);
	carre.setFillColor(sf::Color(0, 0, 0));
	this->app->draw(carre);
}

Game		& Game::operator=( Game const &rhs ) {
	this->app = rhs.app;
	return *this;
}
