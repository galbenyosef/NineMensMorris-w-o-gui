#ifndef _NMM_Gameplay_h
#define _NMM_Gameplay_h

#include "Player.h"
#include "Board.h"
#include <iostream>
#include <cstdlib>

//this const used as gameover indicator
const unsigned int _MINDISKS = 2;

class Gameplay{

private:

	Player player_black;
	Player player_white;
	unsigned int role;
	NineMensMorris Gameboard;

public:

	Gameplay():role(0){Gameboard.init();};
	Gameplay(const string& player1 ,const string& player2):player_black(player1),player_white(player2),role(0){Gameboard.init();};
	~Gameplay(){cout << "\nGameplay destructor executed";};
	bool BoardSet(const unsigned int&,const unsigned int&);
	bool isMill(const unsigned int&,const unsigned int&,const int&) const;
	bool hasMill(const int&) const;
	bool isPath(const unsigned int,const unsigned int,const unsigned int,const unsigned int) const;
	bool checkInputPlacement(const string&);
	bool checkInputMovement(const string&);
	bool RemoveRival();
	bool checkName(const string&) const;
	bool isBlocked(const unsigned int&) const;
	bool isBlockedSpot(const unsigned int&, const unsigned int&) const;
	void askNames();
	void gameover()const;
	void Event_Placement();
	void Event_Movement();
	void InputHandlerPlacement(unsigned int&, unsigned int&);
	void InputHandlerMovement(unsigned int&, unsigned int&,unsigned int&, unsigned int&);
	void changeTurn(){role++;};
	//this function is mainly used, first role is 0, then by modulo by 2, we get only 1 or 0 which indicates the role
	//every turn we increase role in order to change the turn
	unsigned int whosTurn() const {return (role%2==0?0:1);};
	unsigned int myConv(const char&);
};

#endif