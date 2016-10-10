#include "Gameplay.h"
#include "Board.h"
#include "NMM_Spot.h"

using namespace std;

void Gameplay::Event_Placement()
{
	unsigned int i,j;
	//DeclareEventPlacement
	//While there are disks to place for both players (9)
	//Check if current player is not blocked, if do, game over
	while (player_black.getDiscNum() < _AMOUNTDISKS || player_white.getDiscNum() < _AMOUNTDISKS)
	{
		if (isBlocked(whosTurn()))
			gameover();

		do{
		Gameboard.print();
	//Get placement index include check
		InputHandlerPlacement(i,j);
	//Place
		//Safe insertion include index check
		}while (!BoardSet(i,j));

	//Check for mill
		if(isMill(i,j,whosTurn()))
		{
			//Mill! remove rival single disc // Notice if theres a rival Mill and avoid
			do{
				Gameboard.print();
				if (hasMill(!whosTurn()))
					cout << "\nThere is a rival mill, please avoid removing from it!";
				cout << "\nPlease remove rival disc";
			}
			//No option to user skip this if isMill is occurring.
			while(!RemoveRival());
		}
		//next player's turn
		changeTurn();
	}
}

void Gameplay::Event_Movement()
{
	unsigned int oldi,oldj,newi,newj;
	//DeclareEventMain
	//While Both Players Have At least 3 DISKS ON BOARD AND 'Quit' is not entered
	while (player_black.offsetboard() > _MINDISKS && player_white.offsetboard() > _MINDISKS)
	{
		if (isBlocked(whosTurn()))
			gameover();

		do{

			do{

		//Get placement index include check
			Gameboard.print();
			cout << "Please type <oldspot> <newspot>" << endl;
			InputHandlerMovement(oldi,oldj,newi,newj);
			//Check Availability + Authorize
			}while(Gameboard.getSpot(newi,newj)!=None);

		//Player must move disc in order to continue next role
		}while(!isPath(oldi,oldj,newi,newj));

		{
	//Move
			Gameboard.setSpot(oldi,oldj,None);
			Gameboard.setSpot(newi,newj,whosTurn());
		}
	//Check For Mill
		if (isMill(newi,newj,whosTurn()))
		{
			//Mill! remove rival single disc // Notice if rival has also Mill and avoid of drop of it.
			do{
				Gameboard.print();
				if (hasMill(!whosTurn()))
					cout << "\nThere is rival mill, please avoid removing from it!";
				cout << "\nPlease remove rival disc";
			}
			//Player must remove rival disc in order to continue next role
			while(!RemoveRival());
		}
	//Change Turn
	changeTurn();
	}
}

//convert character given by input to its relevant index of the Gameboard
unsigned int Gameplay::myConv(const char& Char)
{
	
	switch (Char)
	{
		case ('a'):
			return 0;
		case ('b'):
			return 1;
		case ('c'):
			return 2;
		case ('d'):
			return 3;
		case ('e'):
			return 4;
		case ('f'):
			return 5;
		case ('g'):
			return 6;
	}
	return 0;

}

//print who's turn to play, take input, check if not 'quit' and nor spaces is entered, check if index is relevant to the board,then use convert
void Gameplay::InputHandlerPlacement(unsigned int& i, unsigned int& j) 
{
	char t;
	//get input
	string name;
	name = ( whosTurn() == 0 ? player_black.getName():player_white.getName() );
	string input;
	do{
	cout << "\nIt's now " << name << "'s " << "turn:  ";
	cin >> input;
	unsigned int i =0;
	while (i<input.length())
	{
		tolower(input[i]);
		i++;
	}
	if (input == "quit")
		{gameover();}
	cin.clear();
	cin.ignore();
	//check input
	}while(!checkInputPlacement(input));

	t = input.at(0);
	i = (unsigned int)(input.at(1)-'0'); 
	i--;
	j=myConv(t);
	//i and j are ready for direct indexes use for Gameboard
}

//same as InputHandlerPlacement except given (old i,j and new i,j)
void Gameplay::InputHandlerMovement(unsigned int& oldi, unsigned int& oldj,unsigned int& newi, unsigned int& newj) 
{
	char c,t;
	//get input
	string name;
	name = ( whosTurn() == 0 ? player_black.getName():player_white.getName() );
	string input;
	do{
	cout << "\nIt's now " << name << "'s " << "turn to move:  ";
	getline(cin,input);
	cin.clear();
	unsigned int i = 0;
	while (i<input.length())
	{
		tolower(input[i]);
		i++;
	}
	if (input == "quit")
		{gameover();}
	//check input
	}while(!checkInputMovement(input));

	t = input.at(0);
	c = input.at(3);

	oldi = (unsigned int)(input.at(1)-'0'); 
	oldi--;
	oldj=myConv(t);

	newi = (unsigned int)(input.at(4)-'0'); 
	newi--;
	newj=myConv(c); 

}

//This function sets a spot on Gameboard by given index and current player using whosTurn
//then only if the spot is None, it is possibly to put and use place player's function that increases player->onboard
bool Gameplay::BoardSet(const unsigned int& i,const unsigned int& j)
{
	//set input
	int current=Gameboard.getSpot(i,j);
	if (current==None)
	{
		Gameboard.setSpot(i,j,whosTurn());
		if (!whosTurn())
			player_black.place();
		else player_white.place();
		return 1;
	}
	if (current == Null)
	{
		cout << "\nWrong index";
		return 0;
	}
	cout << "\nis already taken";
	return 0;
}

//i/o function using checkname and then set name
void Gameplay::askNames()
{
	string push;
	do{
	cout << "Player One: Please Type Your Name: ";
	cin >> push;
	cin.clear();
	cin.ignore();
	}while(!checkName(push));
	player_black.setName(push);

	do{
	cout << "Player Two: Please Type Your Name: ";
	cin >> push;
	cin.clear();
	cin.ignore();
	}while(!checkName(push));
	player_white.setName(push);

}

//check name function checks that given string is less than 17 chars and no space was entered
bool Gameplay::checkName(const string& name) const
{
	if (name.length()>0 && name.length()<17)
	{
		for (unsigned int i=0;i<name.length();i++)
		{
			if (name.at(i)==' ')
				return 0;
		}
		return 1;
	}
	cout << "\nWrong Input";
	return 0;
}

//user must enter relevant index in order to continue (i,j)
bool Gameplay::checkInputPlacement(const string& input)
{
	if (input.length() == 2) 
	{
		char i = input.at(0);
		unsigned int j = (unsigned int)(input.at(1)-'0');
		if ((i >= 'a' || i <= 'g') && (j>0 || j<=NROW))
		{
			return 1;
		}
	}
	cout << "\nWrong Input !";
	return 0;
}

//same as checkInputPlacement but again, (oldi,oldj, newi,newj)
bool Gameplay::checkInputMovement(const string& input)
{
	if (input.length() == 5) 
	{
		if(input.at(2) == ' ')
		{

			char t = input.at(0);
			char c = input.at(3);

			unsigned int oldi = (unsigned int)(input.at(1)-'0'); 
			unsigned int oldj=myConv(t);
			oldi--;

			unsigned int newi = (unsigned int)(input.at(4)-'0'); 
			unsigned int newj=myConv(c);
			newi--;

			if ((oldi >= 'a' || oldi <= 'g') && (oldj>=0 || oldj<NROW) && (newi >= 'a' || newi <= 'g') && (newj>=0 || newj<NROW))
			{
				if ((unsigned int)Gameboard.getSpot(oldi,oldj) == whosTurn())
					return 1;
			}
		}
	}
	cout << "\nWrong Input !";
	return 0;
}

//this function gets an index and player turn 
//Mill is occurring in different ways therefore function is defining number of occurrences
bool Gameplay::isMill(const unsigned int& i,const unsigned int& j,const int& turn) const
{
	unsigned int foundinline=0;
	unsigned int foundinline2=0;
	//any element is not i-mdl and j-mdl
	if (i!=(NCOL/2) && j!=(NCOL/2))
	{
		//horizontal check
		for (unsigned int k=0;k<NROW;k++)
		{
			if(Gameboard.getSpot(i,k)==turn)
				foundinline++;
		}
		//vertical check
		for (unsigned int k=0;k<NROW;k++)
		{
			if(Gameboard.getSpot(k,j)==turn)
				foundinline2++;
		}
	}

	//case i is mdl
	else if (i==(NCOL/2)) // special case for middle of board
	{
		if(j<(NCOL/2)) //seperate two cases, before middle board and after for avoiding count two lines;
		{
		//horizontal check #1
			for (unsigned int k=0;k<(NROW)/2;k++)
			{
				if(Gameboard.getSpot(i,k)==turn)
					foundinline++;
			}
		}
		else
		//horizontal check #2
		for (unsigned int k=(NCOL/2)+1;k<(NROW);k++)
		{
			if(Gameboard.getSpot(i,k)==turn)
				foundinline++;
		}
		//vertical check
		for (unsigned int k=0;k<NROW;k++)
		{
			if(Gameboard.getSpot(k,j)==turn)
				foundinline2++;
		}
	}

	//case j is mdl
	else if (j==(NCOL/2)) // special case for middle of board
	{
		if(i<(NCOL/2)) //seperate two cases, before middle board and after for avoiding count two lines;
		{
		//vertical check #1
			for (unsigned int k=0;k<(NROW)/2;k++)
			{
				if(Gameboard.getSpot(k,j)==turn)
					foundinline2++;
			}
		}
		else
		//vertical check #2
		for (unsigned int k=(NCOL/2)+1;k<(NROW);k++)
		{
			if(Gameboard.getSpot(k,j)==turn)
				foundinline2++;
		}
		//horizontal check
		for (unsigned int k=0;k<NROW;k++)
		{
			if(Gameboard.getSpot(i,k)==turn)
				foundinline++;
		}
	}
	//if we have found 3 of the same player in one of the occurrences then Mill
	if (foundinline > 2 || foundinline2 > 2)
		return 1;
	return 0;


}

//find rival spots all over the board and check if he also got mill to warn about!
bool Gameplay::hasMill(const int& turn) const
{
	for (unsigned int i = 0 ; i < NROW ; i++)
	{
		for (unsigned int j = 0 ; j < NCOL ; j++)
		{
			if (isMill(i,j,turn))
				return 1;
		}
	}
	return 0;
}

//first of all get relevant index by checking its spot,then put None, use drop function to increase Player->offboard
bool Gameplay::RemoveRival()
{
	unsigned int i,j;
	InputHandlerPlacement(i,j);
	if (Gameboard.getSpot(i,j) == (!whosTurn()))
	{
		Gameboard.setSpot(i,j,None);
		if (whosTurn())
		{
			player_white.drop();
			return 1;
		}
		player_black.drop();
		return 1;
	}
	cout << "\nNo rival disc found";
	return 0;
}

//by checking relevant occurrences for movement, function check if new spot is first of all on x,y axis of selected spot then if do
//count vertical/horizontal if theres rival spot and how many intersections moved because we must now move more than one
//
bool Gameplay::isPath(const unsigned int srci,const unsigned int srcj,const unsigned int dsti,const unsigned int dstj) const
{
	int intersections=0;

	//Horizontal movement
	if (srci == dsti)
	{
		//Right movement
		if (srcj < dstj)
		{
			for (unsigned int j = dstj; j>srcj;j--)
			{
				if (Gameboard.getSpot(dsti,j)==(!whosTurn()))
					return 0;
				if (Gameboard.getSpot(dsti,j)==None)
					intersections++;
			}
			if (intersections > 1)
				return 0;
			return 1;
		}
		//Left movement
		if (srcj > dstj)
		{
			for (unsigned int j = srcj; j>dstj;j--)
			{
				if (Gameboard.getSpot(dsti,j)==(!whosTurn()))
					return 0;
				if (Gameboard.getSpot(dsti,j)==None)
					intersections++;
			}
			if (intersections > 1)
				return 0;
			return 1;
		}
	}

	//Vertical movement
	if (srcj == dstj)
	{
		//Down movement
		if (srci < dsti)
		{
			for (unsigned int i = dsti; i>srci;i--)
			{
				if (Gameboard.getSpot(i,dstj)==(!whosTurn()))
					return 0;
				if (Gameboard.getSpot(i,dstj)==None)
					intersections++;
			}
			if (intersections > 1)
				return 0;
			return 1;
		}
		//Up movement
		if (srci > dsti)
		{
			for (unsigned int i = srcj; i>dstj;i--)
			{
				if (Gameboard.getSpot(i,dstj)==(!whosTurn()))
					return 0;
				if (Gameboard.getSpot(i,dstj)==None)
					intersections++;
			}
			if (intersections > 1)
				return 0;
			return 1;
		}

	}
	cout << "\nBad index given, only 1-intersection vertical/horizontal movement is allowed";
	return 0;
}

//if number of current player disc equals the number of current player blocked spots he is blocked!
bool Gameplay::isBlocked(const unsigned int& turn) const
{
	unsigned int blocked=0;
	for (unsigned int i=0 ; i < NROW ; i++)
	{
		for (unsigned int j=0 ; j < NCOL ; j++)
		{
			if ((unsigned)Gameboard.getSpot(i,j)==turn)
			{
				if (isBlockedSpot(i,j))
				{
					blocked++;
				}
			}
		}
	}
	if (turn){
	  
		if (blocked == player_black.offsetboard())
		{
			return 1;
		}
	}
	else if (turn == 0)
	{
		if (blocked == player_white.offsetboard())
		{
			return 1;
		}
	}
	return 0;
}

//When this function called, game is over, pronounce winner (loser call function therefore winner is the opposite), exit the program
void Gameplay::gameover() const
{
	int winner = (!whosTurn());
	cout << "\nGame is over, ";
	if (winner)
	{
		cout << player_white.getName() << " has won!";
		system("pause");
		exit(1);
	}
	cout << player_black.getName() << " has won!";
	system("pause");
	exit(1);
}

//directly check all options for relevant index if its blocked
bool Gameplay::isBlockedSpot(const unsigned int& i, const unsigned int& j) const
{
	if (i==0 && j==0)
	{
		if (Gameboard.getSpot(0,3)!=None && Gameboard.getSpot(3,0)!= None)
			return 1;
	}

	if (i==3 && j==3)
	{
		if (Gameboard.getSpot(0,0)!=None && Gameboard.getSpot(0,6)!= None && Gameboard.getSpot(1,3)!= None)
			return 1;
	}

	if (i==6 && j==6)
	{
		if (Gameboard.getSpot(0,3)!=None && Gameboard.getSpot(3,6)!= None)
			return 1;
	}

	if (i==1 && j==1)
	{
		if (Gameboard.getSpot(1,3)!=None && Gameboard.getSpot(3,1)!= None)
			return 1;
	}

	if (i==1 && j==3)
	{
		if (Gameboard.getSpot(1,1)!=None && Gameboard.getSpot(1,5)!= None 
			&& Gameboard.getSpot(0,3)!=None && Gameboard.getSpot(2,3)!= None)
			return 1;
	}

	if (i==1 && j==5)
	{
		if (Gameboard.getSpot(1,3)!=None && Gameboard.getSpot(3,5)!= None)
			return 1;
	}

	if (i==2 && j==2)
	{
		if (Gameboard.getSpot(2,3)!=None && Gameboard.getSpot(3,2)!= None)
			return 1;
	}

	if (i==2 && j==3)
	{
		if (Gameboard.getSpot(2,2)!=None && Gameboard.getSpot(2,4)!= None && Gameboard.getSpot(1,3)!= None)
			return 1;
	}

	if (i==2 && j==4)
	{
		if (Gameboard.getSpot(2,3)!=None && Gameboard.getSpot(3,4)!= None)
			return 1;
	}

	if (i==3 && j==0)
	{
		if (Gameboard.getSpot(0,0)!=None && Gameboard.getSpot(6,0)!= None && Gameboard.getSpot(3,1)!= None)
			return 1;
	}

	if (i==3 && j==1)
	{
		if (Gameboard.getSpot(3,0)!=None  && Gameboard.getSpot(3,2)!= None
			 && Gameboard.getSpot(1,1)!= None  && Gameboard.getSpot(5,1)!= None )
			return 1;
	}

	if (i==3 && j==2)
	{
		if (Gameboard.getSpot(2,2)!=None && Gameboard.getSpot(4,2)!= None && Gameboard.getSpot(3,1)!= None)
			return 1;
	}

	if (i==3 && j==4)
	{
		if (Gameboard.getSpot(2,4)!=None && Gameboard.getSpot(4,4)!= None && Gameboard.getSpot(3,5)!= None)
			return 1;
	}

	if (i==3 && j==5)
	{
		if (Gameboard.getSpot(3,6)!=None && Gameboard.getSpot(3,4)!= None
			&& Gameboard.getSpot(1,5)!= None && Gameboard.getSpot(5,5)!= None)
			return 1;
	}

	if (i==3 && j==6)
	{
		if (Gameboard.getSpot(0,6)!=None && Gameboard.getSpot(6,6)!= None && Gameboard.getSpot(3,5)!= None)
			return 1;
	}

	if (i==4 && j==2)
	{
		if (Gameboard.getSpot(3,2)!=None && Gameboard.getSpot(4,3)!= None)
			return 1;
	}

	if (i==4 && j==3)
	{
		if (Gameboard.getSpot(4,2)!=None && Gameboard.getSpot(4,4)!= None && Gameboard.getSpot(5,3)!= None)
			return 1;
	}

	if (i==4 && j==4)
	{
		if (Gameboard.getSpot(4,3)!=None && Gameboard.getSpot(3,4)!= None)
			return 1;
	}

	if (i==5 && j==1)
	{
		if (Gameboard.getSpot(5,3)!=None && Gameboard.getSpot(3,1)!= None)
			return 1;
	}

	if (i==5 && j==3)
	{
		if (Gameboard.getSpot(4,3)!=None && Gameboard.getSpot(6,3)!= None
			&& Gameboard.getSpot(5,1)!= None && Gameboard.getSpot(5,5)!= None)
			return 1;
	}

	if (i==5 && j==5)
	{
		if (Gameboard.getSpot(3,5)!=None && Gameboard.getSpot(5,3)!= None)
			return 1;
	}

	if (i==6 && j==0)
	{
		if (Gameboard.getSpot(3,0)!=None && Gameboard.getSpot(6,3)!= None)
			return 1;
	}

	if (i==6 && j==3)
	{
		if (Gameboard.getSpot(6,0)!=None && Gameboard.getSpot(6,6)!= None && Gameboard.getSpot(5,3)!= None)
			return 1;
	}

	if (i==6 && j==6)
	{
		if (Gameboard.getSpot(3,6)!=None && Gameboard.getSpot(6,3)!= None)
			return 1;
	}
	return 0;
}