#include "Board.h"

//After we got stack allocated array as each element represents NMM_Spot, we set as None (Active) relevant spots while rest are NULL
void NineMensMorris::init()
{
	unsigned int skip=3;
	//first
	for (unsigned int i=0;i<=NROW/2;i++)
	{
		if (i==NROW/2)
		{
			for (unsigned int k=0; k<NROW; k++)
				myBoard[i][k].setStatus(None);
			myBoard[NROW/2][NCOL/2].setStatus(Null);
			break;
		}
		//middle
		for(unsigned int j=i;j<NCOL-i;j+=skip)
			myBoard[i][j].setStatus(None);
		skip--;
	}
	
	skip = 3;
	//end
	for(unsigned int i = NROW-1; i>NROW/2; i--)
	{
		for (unsigned int j=i ; j>=NROW-i-1 ; j-=skip)
			myBoard[i][j].setStatus(None);
		skip--;
	}

}


//print whole array by casting each cell status 
void NineMensMorris::print() const
{
	char indicator = 'a';
	unsigned int numindicator = NROW;
	int status;
	for (unsigned int i=NROW-1;i>=0;i--)
	{
		cout << endl << numindicator-- << " ";
		for (unsigned int j=0;j<NCOL;j++)
		{
			status = getSpot(i,j);
			if (status == White)
				cout << "W ";
			else if  (status == Black)
				cout << "B ";
			else if  (status == None)
				cout << "O ";
			else if  (status == Null)
				cout << "- ";
		}
		cout << endl;
	}
	cout << "  ";
	for (unsigned int i= 0 ; i < NROW ; i++ )
		cout << indicator++  << " ";
	cout << endl;
	cout << endl;
}

