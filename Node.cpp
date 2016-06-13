#include "Node.hpp"


Node::Node(){

   _map =   {{
                                  /*1,2,3,4,5,6,7,8,910111213141516171819*/
                                 /*A*/{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
                                 /*B*/{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
                                 /*C*/{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
                                 /*D*/{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
                                 /*E*/{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
                                 /*F*/{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
                                 /*G*/{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
                                 /*H*/{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
                                 /*I*/{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
                                 /*J*/{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
                                 /*K*/{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
                                 /*L*/{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
                                 /*M*/{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
                                 /*N*/{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
                                 /*O*/{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
                                 /*P*/{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
                                 /*Q*/{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
                                 /*R*/{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
                                 /*S*/{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}
                              }};                          
	Parent = NULL;
	x = 0;
	y = 0;
	nbTakenWhite = 0;
	nbTakenBlack = 0;
   isSlash = false;
   istmpwin = false;
}

Node      & Node::operator=( Node const &rhs ) {
   this->Parent = rhs.Parent;
   this->_map = rhs._map;
   this->x = rhs.x;
   this->y = rhs.y;
   this->nbTakenWhite = rhs.nbTakenWhite;
   this->nbTakenBlack = rhs.nbTakenBlack;
   this->isSlash = rhs.isSlash;
   istmpwin = rhs.istmpwin;
   return *this;
}

Node::Node(std::array<std::array<char, 19>, 19> map){
	Parent = NULL;
	_map = map;
	x = 0;
	y = 0;
	nbTakenWhite = 0;
	nbTakenBlack = 0;
   isSlash = false;
   istmpwin = false;
}


void 	Node::setMap_char_at_XY(int tmpx, int tmpy, char c){
	_map[tmpy][tmpx] = c;
	x = tmpx;
	y = tmpy;
}

char 	Node::getMap_char_at_XY(int tmpx, int tmpy){
	return 	_map[tmpy][tmpx];
}

void 	Node::setMap(std::array<std::array<char, 19>, 19> newmap){
	_map = newmap;
}

std::array<std::array<char, 19>, 19>  Node::getMap() const{
	return (_map);
}

Node::~Node(){

}