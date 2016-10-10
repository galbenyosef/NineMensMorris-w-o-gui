#ifndef _NMM_Spot_h
#define _NMM_Spot_h

//no need to remember numbers
typedef enum {Black,White,None,Null} _status;

class NMM_Spot{

private:

	//much more understandable to input and to compare
	_status status;

public:

	//ctor makes null all points
	NMM_Spot():status(Null){};	
	~NMM_Spot(){};
	//set status by given
	void setStatus(const _status& newStatus){status=newStatus;};
	//get therefore const
	int getStatus() const {return status;};

};


#endif