///////////////////////////////////////////////////////
// System Software Experiment 3.
// Project 2 : Mini Factory.
// written by Youngdae Kwon.
// MIT license.
///////////////////////////////////////////////////////

#ifndef __LIB_TIME_MODULE_H__
#define __LIB_TIME_MODULE_H__

#include "setup.h"
using namespace std;

struct event
{
	int processID;
	int serverID;
	int coreID;
	int coreID_entity;
	int interconnectID;
	int way12_bus3;
	// int wayID;
	// int busID;
};

class TimeModule
{
	public:
		map<int, vector<event> > mTime;
		map<int, vector<event> >::iterator it;
		// member methods declaration.
	    void insert(int time, int ID, int whichEvent);
	    void insert(int time, int ID, int coreNum, int whichEvent);
	    void insert(int time, event e, int whichEvent);
};

#endif