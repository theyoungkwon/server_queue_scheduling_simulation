///////////////////////////////////////////////////////
// System Software Experiment 3.
// Project 2 : Mini Factory.
// written by Youngdae Kwon.
// MIT license.
///////////////////////////////////////////////////////

#ifndef __LIB_CONNECTION_MODULE_H__
#define __LIB_CONNECTION_MODULE_H__

#include "setup.h"
// #include "server_module.h"
using namespace std;

class Connection
{
public:
	int vertexFrom;
	int vertexTo;
	int capacity;
	int distance;

	// variables for run()
	vector<Entity> vEntities;
	vector<double> vUtils;
	int idx_min;
	// variables for stats
	int timeInConnection;
	int numPassedEntity;
	int entitySize;
	double util;
	// class methods declaration.
	void setVertex(int a, int b);
	int getVertexFrom();
	int getVertexTo();
	void setCapacity(int num);
	void setDistance(int num);
	int getCapacity();
	int getDistance();
	void setParams(int, int , int , int );

	// member methods declaration.
	Connection();
	void putEntity(Entity* pEntity, int );
	int getWhichEntity(int );
	Entity getEntity(int , int);
	void popEntity(int );
	// void dispUtils();
};

class Way : public Connection
{
public:
	int cost;
	int wayID;
	// class methods declaration.
	Way();
	Way(int );
	int calCost();
	int calPassTime(Entity *);
};

class Bus : public Connection
{
public:
	int speed;
	int cost;
	int busID;
	int currentID;
	// class methods declaration.
	Bus();
	Bus(int );
	// int setParams(int, int , int , int , int );
	void setSpeed(int num);
	int getSpeed();
	int calCost();
	int calPassTime();
	Entity getEntity(int );
	void popEntity();
};

class Interconnect{
public:
	int numWay;
	int numBus;
	int interconnectNum;
	vector<Way> vWays;
	vector<Bus> vBuses;
	Queue InterQueue;

	Interconnect();
	Interconnect(int , int , int );
	// void insertEntityToQueueInter(Entity* , int);
	// int checkQueue();
	// Entity getEntityFromQueue(int );
	// void putEntity(Entity* , int );
	// Entity getEntity();
	// void popEntity();
};

class Distance
{
public:
	int ** distArr;
	int numServer;
	// class methods declaration.
	void setNumServer(int );
	void disp();
};

#endif