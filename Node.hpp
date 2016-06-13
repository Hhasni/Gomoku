#ifndef NODE_HPP
# define NODE_HPP

# include <iostream>
# include <array>

class Node
{
	public:
		int 	x;
		int 	y;
		int 	nbTakenWhite;
		int 	nbTakenBlack;
		bool 	isSlash;
		bool 	istmpwin;


		Node();
		Node(std::array<std::array<char, 19>, 19>);
		Node & operator=( Node const &rhs );
		virtual ~Node();
		void 	setMap_char_at_XY(int, int, char);
		void 	setMap(std::array<std::array<char, 19>, 19>);

		char 	getMap_char_at_XY(int, int);
		std::array<std::array<char, 19>, 19> 	getMap() const;



	private:
		std::array<std::array<char, 19>, 19> _map;
		const Node* 	Parent;
};

#endif