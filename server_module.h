///////////////////////////////////////////////////////
// System Software Experiment 3.
// Project 2 : Mini Factory.
// written by Youngdae Kwon.
// MIT license.
///////////////////////////////////////////////////////

#ifndef __LIB_SERVER_MODULE_H__
#define __LIB_SERVER_MODULE_H__

#include "setup.h"
using namespace std;

class Core
{
	public:
		// variables for run()
		vector<Entity> vEntities;
		vector<double> vUtils;
		bool bBusy;
		// variables for stats
		int timeFrom;
		int timeTo;
		int timeBusy;
		int numEntityFinished;
		int timeQuantum;

		double util;
		int maxEntitySize;
		int entitySize;
		// variables for stats
		// member methods declaration.
		Core();
		void setTimeQuantum(int );
		void putEntity(Entity* pEntity, int time);
		Entity getEntity();
		void putEntitySchedule(Entity* pEntity, int time, int );
		Entity getEntitySchedule(int , int );
		void popEntity();
		void setCoreBusyFlag();
		void setCoreBusyFlagDown();
		void dispUtils();
		void setCoreLevel(int );
};

class Server
{
	public:
		// variables for run()
		int numCore;
		int serverNum;
		vector<Core> vCores;
		Queue ClassQueue;
		Queue ClassQueueInter;
		// variables for stats

		int maxWorkingCoreNum;
		double averageWorkingCore;
		double util;
		int cost;
		// member methods declaration.
		Server();
		Server(int num);
		Server(int , int );
		void setNumCore(int );
		void insertEntityToQueue(Entity* pEntity, int);
		void insertEntityToQueueInter(Entity* pEntity, int);
		int checkQueue();
		int checkQueueInter();
		int checkCoreStatus();

		Entity getEntityFromQueue(int );
		Entity getEntityFromQueueInter(int );
		void assignEntityToCore(int , int , Entity* );
		Entity getEntityFromCore(int coreID);

		Entity getEntityFromQueueSchedule(int timeCount, int policy);
		void assignEntityToCoreSchedule(int num, int timeCount, Entity* pEntity, int policy);
		Entity getEntityFromCoreSchedule(int coreID, int timeCount, int policy);
		void popEntityFromCore(int coreID);

		Entity policyFIFO(int );
		Entity policyRR(int );
		Entity policySJF(int );
		int calCost();
};

#endif