///////////////////////////////////////////////////////
// System Software Experiment 3.
// Project 2 : Mini Factory.
// written by Youngdae Kwon.
// MIT license.
///////////////////////////////////////////////////////


#ifndef __LIB_SETUP_H__
#define __LIB_SETUP_H__

#include <stdio.h>
// #include <string.h>
#include <stdlib.h>
// #include <sys/time.h>

#include <iostream>		// std::cout
#include <sstream>		// std::stringstream
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <array> 		// std::array
#include <map>			// std::map
#include <string> 		// string concatenation
#include <cstring> 		// strcpy, strlen, strcat
using namespace std;

struct InterStatus
{
	int way12_bus3;
	int interconnectID;
};

class Schedule
{
	public:
		string name;
		int typeNum;
		bool bShouldEnd;
		int typeSpeed;
		vector<int> vScenario;
		vector<int> vTime;

		Schedule();
		Schedule(string str);
		Schedule(int typeNum);
		void setScenario(int num);
		void setTime(int num);
		void setSpeed(int );
		bool del();
		// member methods declaration.
};

class Entity : public Schedule
{
	public:
		// variables for stats
		int timeInQueue;
		int timeInCore;
		int timeInConnection;
		int timeInConnectionFrom;
		int timeInConnectionTo;
		int timeInQueueFrom;
		int timeInQueueTo;
		int timeInCoreTo;
		int age;
		int remainFlag;
		// member methods declaration.
		Entity();
		Entity(string typeName, vector<Schedule>& vSchedule);
		Entity(int num, vector<Schedule>& vSchedule);
};


class Queue
{
	public:
		// variables for run()
		vector<Entity> vEntities;
		vector<double> vUtils;
		int idx_min;
		// variables for stats
		int timeInQueue;
		int runTimeEntity;
		int maxEntitySize;
		int entitySize;
		double util;
		// member methods declaration.
		Queue();
		void putEntity(Entity* pEntity, int );
		Entity getEntity(int );
		void popEntity();
		Entity getEntitySchedule(int , int );
		void popEntitySchedule(int );
		void dispUtils();
};


#endif
