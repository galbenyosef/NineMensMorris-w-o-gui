#ifndef _Board_h_
#define _Board_h_

#include "NMM_Spot.h"
#include <iostream>
using namespace std;

static const unsigned int NROW = 7;
static const unsigned int NCOL = NROW;

class NineMensMorris{

private:

	//2d array which each cell represents status
	NMM_Spot myBoard[NROW][NCOL];

public:
	
	//ctor and dtor none
	NineMensMorris(){};
	~NineMensMorris(){};
	void init();
	void print() const;
	//get therefore const
	int getSpot (const unsigned int& i,const unsigned int& j) const {return myBoard[i][j].getStatus();};
	//set therefore not const
	void setSpot (const unsigned int& i,const unsigned int& j,const unsigned int& stat) {myBoard[i][j].setStatus((_status)stat);};

};

#endif