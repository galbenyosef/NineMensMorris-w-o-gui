#ifndef _Player_h_
#define _Player_h_

#include <string>
using namespace std;

const unsigned int _AMOUNTDISKS = 9;
const string DEFAULT_PLAYER_NAME = "Player";

class Player{

private:

	string name;
	unsigned int onboard;
	unsigned int offboard;

public:

	Player():name(DEFAULT_PLAYER_NAME),onboard(0),offboard(0){};
	Player(string newname):name(newname),onboard(0),offboard(0){};
	~Player(){};
	string getName() const {return name;};
	void setName(string newname){name=newname;}; 
	//used by placement event
	void place() {onboard++;};
	//used by both placement and movement
	void drop() {offboard++;};
	unsigned int getDiscNum() const {return onboard;};
	//how many disc's one left
	unsigned int offsetboard() const {return (onboard-offboard);};

};

#endif