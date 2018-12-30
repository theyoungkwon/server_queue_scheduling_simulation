///////////////////////////////////////////////////////
// System Software Experiment 3.
// Project 2 : Mini Factory.
// written by Youngdae Kwon.
// MIT license.
///////////////////////////////////////////////////////

#include "connection_module.h"

Connection::Connection(){
	entitySize = 0; util=0.0; timeInConnection=0;
	// runTimeEntity = 0;
	numPassedEntity = 0;
}

void Connection::setVertex(int a, int b){ vertexFrom = a; vertexTo = b; }

int Connection::getVertexFrom(){ return vertexFrom; }

int Connection::getVertexTo(){ return vertexTo; }

void Connection::setCapacity(int num){ capacity = num; }

void Connection::setDistance(int num){ distance = num; }

int Connection::getCapacity(){ return capacity; }

int Connection::getDistance(){ return distance; }

void Connection::setParams(int from, int to, int cap, int dist){
	vertexFrom = from;
	vertexTo = to;
	capacity = cap;
	distance = dist;
}

void Connection::putEntity(Entity* pEntity, int timeCount){
	if(vEntities.size() < capacity){
		entitySize += 1;
		vUtils.push_back(double(entitySize)/double(capacity));
		pEntity->timeInConnectionFrom = timeCount;
		pEntity->timeInConnectionTo = timeCount+(distance/pEntity->typeSpeed);
		vEntities.push_back(*pEntity);
	}else{
		// cout << "\nconnection is full";
	}
}

int Connection::getWhichEntity(int timeCount){
	int i;
	for(i=0; i<vEntities.size(); i++){
		if( vEntities[i].timeInConnectionTo == timeCount) break;
	}
	return i;
}

Entity Connection::getEntity(int timeCount, int position){
	int temp = timeCount - vEntities[position].timeInConnectionFrom;
	timeInConnection += temp;
	vEntities[position].timeInConnection += temp ;
	return (vEntities[position]);
}

void Connection::popEntity(int position){
	entitySize -= 1;
	numPassedEntity += 1;
	vEntities.erase(vEntities.begin()+position);
}

///////////////////////////////////////////////////////////
Way::Way() : Connection(){  }

Way::Way(int num) : Connection(){
	wayID = num;
}

int Way::calCost(){ cost = 100*capacity; return cost; }

int Way::calPassTime(Entity* pEntity){ return distance/(pEntity->typeSpeed); }

///////////////////////////////////////////////////////////
Bus::Bus() : Connection(){  }

Bus::Bus(int num) : Connection(){
	busID = num;
}

void Bus::setSpeed(int num){ speed = num; }

int Bus::getSpeed(){ return speed; }

int Bus::calCost(){
	if(speed > 8){
		cost = 10*capacity + 20*speed;
	}else{
		cost = 10*capacity + 10*speed;
	}
	return cost;
}

int Bus::calPassTime(){ return distance/speed; }

Entity Bus::getEntity(int timeCount){
	int temp = timeCount - vEntities.front().timeInConnectionFrom;
	timeInConnection += temp;
	vEntities.front().timeInConnection += temp ;
	return (vEntities.front());
}

void Bus::popEntity(){
	entitySize -= 1;
	numPassedEntity += 1;
	vEntities.erase(vEntities.begin());
}
///////////////////////////////////////////////////////////
Interconnect::Interconnect(){ numWay = 0; numBus = 0; }

Interconnect::Interconnect(int ID, int way, int bus){
	interconnectNum = ID; numWay = way; numBus = bus;
}

// void Interconnect::insertEntityToQueueInter(Entity* pEntity, int timeCount){
// 	ClassQueueInter.putEntity(pEntity, timeCount);
// }

// int Interconnect::checkQueue(){
// 	return ClassQueue.vEntities.size();
// }

// Entity Interconnect::getEntityFromQueue(int timeCount){
// 	cout<<"\n Interconnect::getEntityFromQueue";
// 	Entity p;
// 	p = ClassQueue.getEntity(timeCount);
// 	ClassQueue.popEntity();
// 	return p;
// }

// void Interconnect::putEntity(Entity* pEntity, int timeCount){
// 	if(vEntities.size() < maxEntitySize){
// 		entitySize += 1;
// 		// Interconnect stats
// 		timeFrom = timeCount; timeTo = timeCount+pEntity->vTime.front();
// 		timeBusy += timeTo - timeFrom;
// 		vUtils.push_back(double(timeBusy)/double(timeTo));
// 		// entity stats
// 		pEntity->timeInCore += pEntity->vTime.front();
// 		vEntities.push_back(*pEntity);
// 	}else{
// 		cout << "\nqueue is full";
// 	}
// }
// Entity Interconnect::getEntity(){
// 	if(vEntities.front().del()){}
// 	numEntityFinished += 1;
// 	return (vEntities.front());
// }
// void Interconnect::popEntity(){
// 	entitySize -= 1;
// 	vEntities.erase(vEntities.begin());
// }


///////////////////////////////////////////////////////////

void Distance::setNumServer(int num){ numServer = num; }

void Distance::disp(){
	// cout << "\nDistance::disp";
	int i, j;
	for(i=1; i<=numServer; i++){
		for(j=1; j<=numServer; j++){
			cout << " " << distArr[i][j] << " ";
		}
		cout << "\n";
	}
}


