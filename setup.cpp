///////////////////////////////////////////////////////
// System Software Experiment 3.
// Project 2 : Mini Factory.
// written by Youngdae Kwon.
// MIT license.
///////////////////////////////////////////////////////

#include "setup.h"

Schedule::Schedule(){ bShouldEnd = false; }
Schedule::Schedule(string str){ name = str; }
Schedule::Schedule(int num){ typeNum = num; }

void Schedule::setScenario(int num){
  vScenario.push_back(num);
}

void Schedule::setTime(int num){
  vTime.push_back(num);
}

void Schedule::setSpeed(int num){ typeSpeed = num; }

bool Schedule::del(){
	if(vScenario.size()>1){
		vScenario.erase(vScenario.begin());
		vTime.erase(vTime.begin());
		// at least one elemnt left
		return true;
	}else{
		bShouldEnd = true;
		// no element left
		return false;
	}
}
////////////////////////////////////////////////////////////

Entity::Entity() : Schedule(){
	int i;
	int num=1;
	age = 0;
	typeNum = 0;
	// for(i=0; i<num; i++) vScenario.push_back(1);
	// for(i=0; i<num; i++) vTime.push_back(5);
}

Entity::Entity(string typeName, vector<Schedule>& vSchedule) : Schedule(){
	int i, temp=0;
	age = 0;
	typeName.erase(typeName.begin());
	if( !(istringstream(typeName) >> temp)) temp=0;
	for(i=0; i<vSchedule[temp-1].vScenario.size(); i++) {
		vScenario.push_back(vSchedule[temp-1].vScenario[i]);
		vTime.push_back(vSchedule[temp-1].vTime[i]);
	}
	for(i=0; i<vScenario.size(); i++){
		// cout <<" "<< vScenario[i] << " "<<vTime[i];
	}
}

Entity::Entity(int num, vector<Schedule>& vSchedule) : Schedule(){
	int i;
	age = 0;
	// cout<< "\n Entity : typeNum="<<num;
	for(i=0; i<vSchedule[num-1].vScenario.size(); i++) {
		vScenario.push_back(vSchedule[num-1].vScenario[i]);
		vTime.push_back(vSchedule[num-1].vTime[i]);
		// cout<< "\n Entity : "<<vScenario[i];
	}
	typeSpeed = vSchedule[num-1].typeSpeed;
	typeNum = num;
	timeInQueue=0;
	timeInCore=0;
	timeInConnection=0;
	timeInConnectionFrom=0;
	timeInQueueFrom=0;
	timeInQueueTo=0;
	age = 0;
	remainFlag = 0;
}
///////////////////////////////////////////////////////////////

Queue::Queue(){
	maxEntitySize=200; entitySize=0; util=0.0; timeInQueue=0;
	runTimeEntity = 0;
}

void Queue::putEntity(Entity* pEntity, int timeCount){
	vUtils.push_back(double(entitySize)/double(maxEntitySize));
	pEntity->timeInQueueFrom = timeCount;
	runTimeEntity += pEntity->vTime.front();
	vEntities.push_back(*pEntity);
}

Entity Queue::getEntity(int timeCount){
	// cout<<"\n Queue::getEntity at timeCount"<<timeCount;
	int temp = timeCount - vEntities.front().timeInQueueFrom;
	timeInQueue += temp;
	// cout << "\n Queue::getEntity : timeCount="<< timeCount;
	// cout << "\n Queue::getEntity : timeInQueueFrom="<< vEntities.front().timeInQueueFrom;
	// cout << "\n Queue::getEntity : timeInQueue="<< timeInQueue;
	vEntities.front().timeInQueue += temp ;
	// cout << "\n Queue::getEntity : vEntity's timeInQueue="<< vEntities.front().timeInQueue;
	return (vEntities.front());
}

void Queue::popEntity(){
	// cout<<"\n Queue::popEntity";
	entitySize -= 1;
	vEntities.erase(vEntities.begin());
}

Entity Queue::getEntitySchedule(int timeCount, int policy){
	// cout<<"\n Queue::getEntity at timeCount"<<timeCount;
	int i, min_time=1000, temp;
	idx_min=0;
	switch(policy){
		case 1: // FIFO
			temp = timeCount - vEntities.front().timeInQueueFrom;
			timeInQueue += temp;
			vEntities.front().timeInQueue += temp ;
			return (vEntities.front());
			break;
		case 2: // SJF
			for(i=0; i<vEntities.size(); i++){
				if( vEntities[i].vTime.front() < min_time ){
					min_time = vEntities[i].vTime.front();
					idx_min = i;
				}
			}
			temp = timeCount - vEntities[idx_min].timeInQueueFrom;
			timeInQueue += temp;
			vEntities[idx_min].timeInQueue += temp ;
			return vEntities[idx_min];
			break;
		case 3: // RR
			temp = timeCount - vEntities.front().timeInQueueFrom;
			timeInQueue += temp;
			vEntities.front().timeInQueue += temp ;
			return (vEntities.front());
			break;
		case 4: // SJF with aging
			for(i=0; i<vEntities.size(); i++){
				if( vEntities[i].age > 5 ){
					idx_min = i;
					break;
				}
				vEntities[i].age += 1;
				if( vEntities[i].vTime.front() < min_time ){
					min_time = vEntities[i].vTime.front();
					idx_min = i;
				}
			}
			temp = timeCount - vEntities[idx_min].timeInQueueFrom;
			timeInQueue += temp;
			vEntities[idx_min].timeInQueue += temp ;
			vEntities[idx_min].age = 0 ;
			return vEntities[idx_min];
			break;
		default:
			break;
	}
}

void Queue::popEntitySchedule(int policy){
	// cout<<"\n Queue::popEntity";
	switch(policy){
		case 1: // FIFO
			entitySize -= 1;
			vEntities.erase(vEntities.begin());
			break;
		case 2: // SJF
		case 4: // SJF with aging
			entitySize -= 1;
			vEntities.erase(vEntities.begin()+idx_min);
			break;
		case 3: // RR
			entitySize -= 1;
			vEntities.erase(vEntities.begin());
			break;
		default:
			break;
	}
}

void Queue::dispUtils(){
	for(int i=0; i<vUtils.size(); i++){
		// cout << "\nQueue : vUtils"<<i<<" : "<<vUtils[i];
	}
}
