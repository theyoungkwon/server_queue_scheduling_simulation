///////////////////////////////////////////////////////
// System Software Experiment 3.
// Project 2 : Mini Factory.
// written by Youngdae Kwon.
// MIT license.
///////////////////////////////////////////////////////

#include "process_module.h"

Process::Process() : Schedule(){
	int i;
	int num=1;
	for(i=0; i<num; i++) vScenario.push_back(1);
	// TODO : below will be changed
	startTimeToProduceEntity = 10;
	timePeriodRemakingEntity = 2;
	numEntity = 1000;
	numEntityCreated = 0;
	bRunFlag = false;
}

Process::Process(string str) : Schedule(){
	// cout << "\n Process constructor : string"<<str;
	name = str;
	numEntityCreated = 0;
	bRunFlag = false;
}

Process::Process(int num) : Schedule(){
	// cout << "\n Process constructor : int"<<num;
	typeNum = num;
	numEntityCreated = 0;
	bRunFlag = false;
}

void Process::setType(string str){
	name = str;
}

void Process::setNumEntity(int num){
	numEntity = num;
}

void Process::setStartTimeToProduceEntity(int num){
	startTimeToProduceEntity = num;
}

void Process::setTimePeriodRemakingEntity(int num){
	timePeriodRemakingEntity = num;
}

string Process::getType(){
	return name;
}

int Process::getNumEntity(){
	return numEntity;
}

int Process::getStartTimeToProduceEntity(){
	return startTimeToProduceEntity;
}

int Process::getTimePeriodRemakingEntity(){
	return timePeriodRemakingEntity;
}

Entity Process::createEntity(vector<Schedule>& vSchedule){
	// Entity Count is Infinite
	if(numEntity == 0){
		Entity entity(typeNum, vSchedule);
		// entity = new Entity(typeNum, vSchedule);
		bRunFlag = true;
		numEntityCreated += 1;
		return entity;
	}
	// Entity count is finite
	else{
		if( numEntityCreated < numEntity) {
			Entity entity(typeNum, vSchedule);
			// entity = new Entity(typeNum, vSchedule);
			bRunFlag = true;
			numEntityCreated += 1;
			return entity;
		}else{
			bRunFlag = false;
			// cout << "\nProcess produces all entities ";
			return Entity();
		}
	}
}