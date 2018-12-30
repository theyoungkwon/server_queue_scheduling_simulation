///////////////////////////////////////////////////////
// System Software Experiment 3.
// Project 2 : Mini Factory.
// written by Youngdae Kwon.
// MIT license.
///////////////////////////////////////////////////////

#ifndef __LIB_PROCESS_MODULE_H__
#define __LIB_PROCESS_MODULE_H__

#include "setup.h"
using namespace std;

class Process : public Schedule
{
	public:
		// variables for run()
		int numEntity;
		int numEntityCreated;
		int startTimeToProduceEntity;
		int timePeriodRemakingEntity;
		bool bRunFlag;

		// variables for stats
		// member methods declaration.
		Process();
		Process(string str);
		Process(int num);
		void setType(string str);
		void setNumEntity(int num);
		void setStartTimeToProduceEntity(int num);
		void setTimePeriodRemakingEntity(int num);
		string getType();
		int getNumEntity();
		int getStartTimeToProduceEntity();
		int getTimePeriodRemakingEntity();
		Entity createEntity(vector<Schedule>& vSchedule);
};

#endif