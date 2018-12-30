///////////////////////////////////////////////////////
// System Software Experiment 3.
// Project 2 : Mini Factory.
// written by Youngdae Kwon.
// MIT license.
///////////////////////////////////////////////////////

#include "server_module.h"

Core::Core(){
	bBusy = false; timeFrom=0; timeTo =0;timeBusy = 0;
	maxEntitySize=1; entitySize=0; numEntityFinished = 0;
	util = 0.0; timeQuantum = 40;
}

void Core::setTimeQuantum(int num){ timeQuantum = num; }

void Core::putEntity(Entity* pEntity, int timeCount){
	if(vEntities.size() < maxEntitySize){
		entitySize += 1;
		// core stats
		timeFrom = timeCount; timeTo = timeCount+pEntity->vTime.front();
		timeBusy += timeTo - timeFrom;
		vUtils.push_back(double(timeBusy)/double(timeTo));
		// entity stats
		pEntity->timeInCore += pEntity->vTime.front();
		vEntities.push_back(*pEntity);
	}else{
		// cout << "\nqueue is full";
	}
}
Entity Core::getEntity(){
	if(vEntities.front().del()){}
	numEntityFinished += 1;
	return (vEntities.front());
}

void Core::putEntitySchedule(Entity* pEntity, int timeCount, int policy){
	// cout << "\n Core::putEntitySchedule";
	switch(policy){
		case 1: // FIFO
		case 2: // SJF
		case 4: // SJF with aging
			if(vEntities.size() < maxEntitySize){
				entitySize += 1;
				// core stats
				timeFrom = timeCount;
				timeTo = timeCount+(pEntity->vTime.front());
				timeBusy += timeTo - timeFrom;
				vUtils.push_back(double(timeBusy)/double(timeTo));
				// entity stats
				pEntity->timeInCore += pEntity->vTime.front();
				pEntity->timeInCoreTo += timeTo;
				vEntities.push_back(*pEntity);
			}else{
				// cout << "\nqueue is full";
			}
			break;
		case 3: // Round Robin Schedule
			if(vEntities.size() < maxEntitySize){
				entitySize += 1;
				// core stats
				timeFrom = timeCount;
				if( timeQuantum > pEntity->vTime.front()){
					timeTo = timeCount+pEntity->vTime.front();
				}else{
					timeTo = timeCount + timeQuantum;
					pEntity->remainFlag += 1;
					pEntity->vTime.front() -= timeQuantum;
				}
				timeBusy += timeTo - timeFrom;
				vUtils.push_back(double(timeBusy)/double(timeTo));
				// entity stats
				pEntity->timeInCore += (timeTo - timeFrom);
				pEntity->timeInCoreTo += timeTo;
				vEntities.push_back(*pEntity);
			}else{
				// cout << "\nqueue is full";
			}
			break;
	}
}

Entity Core::getEntitySchedule(int timeCount, int policy){
	int i;
	switch(policy){
		case 1: // FIFO
		case 2: // SJF
		case 4: // SJF with aging
			// for(i=0; i<vEntities.size(); i++){
			// 	if( vEntities[i].timeInCoreTo == timeCount){
			// 		if(vEntities[i].del()){}
			// 		numEntityFinished += 1;
			// 		return (vEntities[i]);
			// 	}
			// }
			if(vEntities.front().del()){}
			numEntityFinished += 1;
			return (vEntities.front());
			break;
		case 3: // RR
			if( vEntities.front().remainFlag >0){
			}else{
				if(vEntities.front().del()){}
				numEntityFinished += 1;
			}
			return (vEntities.front());


			// for(i=0; i<vEntities.size(); i++){
			// 	if( vEntities[i].timeInCoreTo == timeCount){
			// 		if( vEntities[i].remainFlag >0){
			// 		}else{
			// 			if(vEntities[i].del()){}
			// 			numEntityFinished += 1;
			// 		}
			// 		return (vEntities[i]);
			// 	}
			// }
			break;
		// case 4: // SJF with aging
		// 	for(i=0; i<vEntities.size(); i++){
		// 		if( vEntities[i].timeInCoreTo == timeCount){
		// 			if(vEntities[i].del()){}
		// 			numEntityFinished += 1;
		// 			return (vEntities[i]);
		// 		}
		// 	}
		// 	break;
	}
}

void Core::popEntity(){
	entitySize -= 1;
	vEntities.erase(vEntities.begin());
}

void Core::setCoreBusyFlag(){
	bBusy = true;
}

void Core::setCoreBusyFlagDown(){
	bBusy = false;
}

void Core::dispUtils(){
	for(int i=0; i<vUtils.size(); i++){
		// cout << "\nCore : vUtils"<<i<<" : "<<vUtils[i];
	}
}

void Core::setCoreLevel(int num){ maxEntitySize = num; }
/////////////////////////////////////////////////////////
Server::Server(){
	maxWorkingCoreNum = 0;
	averageWorkingCore = 0.0;
	util = 0.0;
}

Server::Server(int num){
	int i;
	numCore = 1;
	serverNum = num;
	for(i=0; i<numCore; i++) vCores.push_back(Core());
	maxWorkingCoreNum = 0;
	averageWorkingCore = 0.0;
	util = 0.0;
	cost = 0;
}

Server::Server(int num1, int num2){
	int i;
	serverNum = num1;
	numCore = num2;
	for(i=0; i<numCore; i++) vCores.push_back(Core());
	maxWorkingCoreNum = 0;
	averageWorkingCore = 0.0;
	util = 0.0;
	cost = 0;
}

void Server::setNumCore(int num){ numCore = num; }

void Server::insertEntityToQueue(Entity* pEntity, int timeCount){
	ClassQueue.putEntity(pEntity, timeCount);
}

void Server::insertEntityToQueueInter(Entity* pEntity, int timeCount){
	ClassQueueInter.putEntity(pEntity, timeCount);
}

int Server::checkQueue(){
	return ClassQueue.vEntities.size();
}

int Server::checkQueueInter(){
	return ClassQueueInter.vEntities.size();
}

Entity Server::getEntityFromQueue(int timeCount){
	// cout<<"\n Server::getEntityFromQueue";
	Entity p;
	p = ClassQueue.getEntity(timeCount);
	ClassQueue.popEntity();
	return p;
}

Entity Server::getEntityFromQueueInter(int timeCount){
	// cout<<"\n Server::getEntityFromQueueInter";
	Entity p;
	p = ClassQueueInter.getEntity(timeCount);
	ClassQueueInter.popEntity();
	return p;
}

Entity Server::getEntityFromQueueSchedule(int timeCount, int policy){
	// 1: FIFO
	// 2: Shortest job first
	// 3: Round Robin
	// 4: Shortest job first with aging
	// cout<<"\n Server::getEntityFromQueueSchedule";
	Entity p;
	p = ClassQueue.getEntitySchedule(timeCount, policy);
	ClassQueue.popEntitySchedule(policy);
	// switch(policy){
	// 	case 1:
	// 		p = policyFIFO(timeCount);
	// 		break;
	// 	case 2:
	// 		p = policySJF(timeCount);
	// 		break;
	// 	case 3:
	// 		p = policyRR(timeCount);
	// 		break;
	// 	default:
	// 		break;
	// }
	return p;
}
/*
Entity Server::policyFIFO(int timeCount){
	cout<<"\n Server::policyFIFO";
	Entity p;
	p = ClassQueue.getEntity(timeCount);
	ClassQueue.popEntity();
	return p;
}

Entity Server::policySJF(int timeCount){
	cout<<"\n Server::policy Shortest Job First";
	Entity p;
	p = ClassQueue.getEntity(timeCount);
	ClassQueue.popEntity();
	return p;
}

Entity Server::policyRR(int timeCount){
	cout<<"\n Server::policy Round Robin";
	Entity p;
	p = ClassQueue.getEntity(timeCount);
	ClassQueue.popEntity();
	return p;
}
*/
/////////////////////////////////////////////////
int Server::checkCoreStatus(){
	int i=0, availCore=0;
	double minCoreUtil=1.0;
	for(i=0; i<vCores.size(); i++){
		if( !(vCores[i].bBusy) ){
			if( minCoreUtil>vCores[i].util){
				minCoreUtil = vCores[i].util;
				availCore = i+1;
			}
		}
	}
	return availCore;
}

void Server::assignEntityToCore(int num, int timeCount, Entity* pEntity){
	// cout<<"\n Server::assignEntityToCore";
	vCores[num-1].putEntity(pEntity, timeCount);
	vCores[num-1].setCoreBusyFlag();
}

Entity Server::getEntityFromCore(int coreID){
	// cout<<"\n Server::getEntityFromCore";
	Entity p;
	p = vCores[coreID-1].getEntity();
	return p;
}

void Server::assignEntityToCoreSchedule(int num, int timeCount, Entity* pEntity, int policy){
	// cout<<"\n Server::assignEntityToCore";
	vCores[num-1].putEntitySchedule(pEntity, timeCount, policy);
	vCores[num-1].setCoreBusyFlag();
	// switch(policy){
	// 	case 1:
	// 		vCores[num-1].putEntitySchedule(pEntity, timeCount, policy);
	// 		vCores[num-1].setCoreBusyFlag();
	// 		break;
	// 	case 2:
	// 		vCores[num-1].putEntitySchedule(pEntity, timeCount, policy);
	// 		vCores[num-1].setCoreBusyFlag();
	// 		break;
	// 	case 3:
	// 		vCores[num-1].putEntitySchedule(pEntity, timeCount, policy);
	// 		vCores[num-1].setCoreBusyFlag();
	// 		break;
	// 	default:
	// 		break;
	// }
}

Entity Server::getEntityFromCoreSchedule(int coreID, int timeCount, int policy){
	// cout<<"\n Server::getEntityFromCore";
	Entity p;
	p = vCores[coreID-1].getEntitySchedule(timeCount, policy);
	// switch(policy){
	// 	case 1:
	// 		p = vCores[coreID-1].getEntitySchedule(policy, timeCount);
	// 		break;
	// 	case 2:
	// 		p = vCores[coreID-1].getEntitySchedule(policy, timeCount);
	// 		break;
	// 	case 3:
	// 		p = vCores[coreID-1].getEntitySchedule(policy, timeCount);
	// 		break;
	// 	default:
	// 		break;
	// }
	return p;
}

void Server::popEntityFromCore(int coreID){
	// cout<<"\n Server::popEntityFromCore";
	vCores[coreID-1].popEntity();
	vCores[coreID-1].setCoreBusyFlagDown();
}

int Server::calCost(){
	int i;
	for(i=0; i<numCore; i++){
		switch(vCores[i].maxEntitySize){
			case 1:
				cost += 500;
				break;
			case 2:
				cost += 1200;
				break;
			case 3:
				cost += 2000;
				break;
			default:
				// cout << "\nServer::calCost : core level error. out of range 1~3";
				break;
		}
	}
	return cost;
}