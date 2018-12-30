///////////////////////////////////////////////////////
// System Software Experiment 3.
// Project 2 : Mini Factory.
// written by Youngdae Kwon.
// MIT license.
///////////////////////////////////////////////////////

#ifndef __LIB_MAIN_H__
#define __LIB_MAIN_H__

#include "setup.h"
#include "server_module.h"
#include "process_module.h"
#include "connection_module.h"
#include "time_module.h"
using namespace std;
struct Params{
	int numWay;
	int wayCapacity;
  	int numBus;
  	int busCapacity;
  	int busSpeed;
  	int POLICY;
  	int simulationTime;
};

// calculate finished entity's info
class End
{
	public:
		map<int, int>::iterator it;

		map<int, int> type_finishFlags;
		map<int, int> type_numProducedEntity;
		map<int, int> type_numFinishedEntity;
		map<int, int> type_avgRunTimeEntity;
		map<int, int> type_avgWaitTimeEntity;
		map<int, int> type_timeInConnection;
		int total_type_numProducedEntity;
		int total_type_numFinishedEntity;
		int total_type_avgRunTimeEntity;
		int total_type_avgWaitTimeEntity;
		int total_type_timeInConnection;

		map<int, int> server_numFinishedEntity;
		map<int, int> server_avgRunTimeEntity;
		map<int, int> server_avgWaitTimeQueue;
		map<int, int> server_avgWaitTimeQueueInter;
		int total_server_numFinishedEntity;
		int total_server_avgRunTimeEntity;
		int total_server_avgWaitTimeQueue;
		int total_server_avgWaitTimeQueueInter;

		map<int, int> interconnect_numPassedEntity;
		map<int, int> interconnect_timeInConnection;
		int total_interconnect_numPassedEntity;
		int total_interconnect_timeInConnection;

		// member methods declaration.
		void init(int , int , int);
		void calEachEntity(Entity* );
		void calTotalTypes(vector<Process>& , int , int );
		void calEachServer(Server& );
		void calTotalServers(vector<Server>& , int , int );
		void calEachInterconnect(Interconnect& );
		void calTotalInterconnects(vector<Interconnect>& , int , int );
		void dispStats(int , int , int);
		void dispStatsToFile(int , int, int , Params);
};

class Simulation
{
	public:
		// vectors
		vector<Process> vProcesses;
		vector<Server> vServers;
		// vector<Way> vWays;
		// vector<Bus> vBuses;
		vector<Interconnect> vInterconnect;
		vector<Schedule> vSchedules;
		vector<int> vScenarioSize;
		// classses
		TimeModule ClassTime;
		End ClassEnd;
		Distance ClassDistance;
		// variables
		int numServer;
		int numType;
		int numScenario;
		int numProcess;
		int numInterconnect;
		int simulationTime;
		int numCore;
		int numEntity;
		int timeCount;
		event tempEvent;
		Entity entityServ;
		Entity entityInter;
		// int numWay;
		// int wayCapacity;
		// int numBus;
		// int numCapacity;
		// int busSpeed;
		Params param;

		int INSERT_PROCESS;
		int INSERT_SERVER;
		int INSERT_CORE;
		int INSERT_WAY;
		int INSERT_BUS;
		int INSERT_INTERCONNECT;

		int WAY_BUS_QUEUE_SIZE_STAND;

		int POLICY;
		int POLICY_FIFO;
		int POLICY_SJF;
		int POLICY_RR;
		int POLICY_SJF_AGING;
		// stats
		int cost;
		int numEntityFinished;
		double throughput;

	public:
		// member methods declaration.
		Simulation();
		void init();
		void setTestSetUp();
		void run();
		void runProcess();
		void runServer();
		void runServerDealCore();
		void runServerSendEntityToNextServer();
		void runServerSendEntityToCore();
		void runServerDealQueue();
		void runServerSendEntityToNextInterconnect();
		InterStatus checkInterconnectStatus(int, int, int);

		void runInterconnect();
		void runInterconnectDealWay();
		void runInterconnectDealBus();
		void runInterconnectSendEntityToNextServer();
		void runInterconnectSendEntityToInterconnect(int );
		void runInterconnectDealQueue();
		void runWay();
		void runBus();

		void runFree();
		void stats();
		void printOutputFile();
};

#endif