///////////////////////////////////////////////////////
// System Software Experiment 3.
// Project 2 : Mini Factory.
// written by Youngdae Kwon.
// MIT license.
///////////////////////////////////////////////////////

// server 1
// queue
// p1 t1 1000, from 10s every 2s
// t1 at S1 5sec

#include "main.h"

int main(int argc, char* argv[]){
  Simulation logistic;
  logistic.init();
  // logistic.setTestSetUp();
  // for(int i=0; i< ; i++){  }
  logistic.run();
  logistic.printOutputFile();
  return 0;
}

///////////////////////////////////////////////////////
void End::init(int numType, int numServer, int numInterconnect){
  int i;
  for(i=1; i<=numType; i++){
    type_numProducedEntity[i] = 0;
    type_numFinishedEntity[i] = 0;
    type_avgRunTimeEntity[i] = 0;
    type_avgWaitTimeEntity[i] = 0;
    type_finishFlags[i] = 0;
    type_timeInConnection[i] = 0;
  }
  for(i=1; i<=numServer; i++){
    server_numFinishedEntity[i] = 0;
    server_avgRunTimeEntity[i] = 0;
    server_avgWaitTimeQueue[i] = 0;
    server_avgWaitTimeQueueInter[i] = 0;
  }
  for(i=1; i<=numInterconnect; i++){
    interconnect_numPassedEntity[i] = 0;
    interconnect_timeInConnection[i] = 0;
  }

  total_type_numProducedEntity = 0;
  total_type_numFinishedEntity = 0;
  total_type_avgRunTimeEntity = 0;
  total_type_avgWaitTimeEntity = 0;
  total_type_timeInConnection = 0;

  total_server_numFinishedEntity = 0;
  total_server_avgRunTimeEntity = 0;
  total_server_avgWaitTimeQueue = 0;
  total_server_avgWaitTimeQueueInter = 0;

  total_interconnect_numPassedEntity = 0;
  total_interconnect_timeInConnection = 0;
}

void End::calEachEntity(Entity* pEntity){
  // calculate average run time of entity
  type_avgRunTimeEntity[pEntity->typeNum] += pEntity->timeInCore;
  // calculate average wait time of entity
  type_avgWaitTimeEntity[pEntity->typeNum] += pEntity->timeInQueue;
  // calcuate number of finished entity
  type_numFinishedEntity[pEntity->typeNum] += 1;
  type_timeInConnection[pEntity->typeNum] += pEntity->timeInConnection;
}

void End::calTotalTypes(vector<Process>& vProcesses, int timeCount, int numType){
  int i;
  for(i=0; i<vProcesses.size(); i++){
    type_numProducedEntity[vProcesses[i].typeNum] = vProcesses[i].numEntityCreated;
    total_type_numProducedEntity += vProcesses[i].numEntityCreated;
  }

  for(i=1; i<=numType; i++){
    total_type_numFinishedEntity += type_numFinishedEntity[i];
    total_type_avgRunTimeEntity += type_avgRunTimeEntity[i];
    total_type_avgWaitTimeEntity += type_avgWaitTimeEntity[i];
    total_type_timeInConnection += type_timeInConnection[i];
  }
}

void End::calEachServer(Server& server){
  int numEntityFinished=0,i;
  for(i=0; i<server.numCore; i++){
    numEntityFinished += server.vCores[i].numEntityFinished;
  }
  server_numFinishedEntity[server.serverNum] = numEntityFinished;
  server_avgWaitTimeQueue[server.serverNum] = server.ClassQueue.timeInQueue;
  server_avgWaitTimeQueueInter[server.serverNum] = server.ClassQueueInter.timeInQueue;
  server_avgRunTimeEntity[server.serverNum] = server.ClassQueue.runTimeEntity;
}

void End::calTotalServers(vector<Server>& vServers, int timeCount, int numServer){
  int i;
  for(i=0; i<vServers.size(); i++){
    calEachServer(vServers[i]);
  }

  for(i=1; i<=numServer; i++){
    total_server_numFinishedEntity += server_numFinishedEntity[i];
    total_server_avgWaitTimeQueue += server_avgWaitTimeQueue[i];
    total_server_avgWaitTimeQueueInter += server_avgWaitTimeQueueInter[i];
    total_server_avgRunTimeEntity += server_avgRunTimeEntity[i];
  }
}

void End::calEachInterconnect(Interconnect& interconnect){
  int numPassedEntity=0, timeInConnection=0, i;
  for(i=0; i<interconnect.vWays.size(); i++){
    numPassedEntity += interconnect.vWays[i].numPassedEntity;
    timeInConnection += interconnect.vWays[i].timeInConnection;
  }
  for(i=0; i<interconnect.vBuses.size(); i++){
    numPassedEntity += interconnect.vBuses[i].numPassedEntity;
    timeInConnection += interconnect.vBuses[i].timeInConnection;
  }
  interconnect_numPassedEntity[interconnect.interconnectNum] = numPassedEntity;
  interconnect_timeInConnection[interconnect.interconnectNum] = timeInConnection;
}

void End::calTotalInterconnects(vector<Interconnect>& vInterconnect, int timeCount, int numInterconnect){
  int i;
  for(i=0; i<vInterconnect.size(); i++){
    calEachInterconnect(vInterconnect[i]);
  }

  for(i=1; i<=numInterconnect; i++){
    total_interconnect_numPassedEntity += interconnect_numPassedEntity[i];
    total_interconnect_timeInConnection += interconnect_timeInConnection[i];
  }
}

void End::dispStats(int numType, int numServer, int numInterconnect){
  int i;
  cout<<"\n\n ======== DISPLAY STATS =======";
  cout<<"\n === TYPE INFORMATION ===";
  for(i=1; i<=numType; i++){
    cout<<"\n KEY="<<i;
    cout<<"\n type_numProducedEntity=" << type_numProducedEntity[i];
  }

  cout<<"\n\n === SERVER INFORMATION ===";
  for(i=1; i<=numServer; i++){
    cout<<"\n KEY="<<i;
    cout<<"\n server_numFinishedEntity=" << server_numFinishedEntity[i];
    cout<<"\n server_avgRunTimeEntity=" << server_avgRunTimeEntity[i];
    cout<<"\n server_avgWaitTimeQueue=" << server_avgWaitTimeQueue[i];
    cout<<"\n server_avgWaitTimeQueueInter=" << server_avgWaitTimeQueueInter[i];
  }

  cout<<"\n\n === INTERCONNECT INFORMATION ===";
  for(i=1; i<=numInterconnect; i++){
    cout<<"\n KEY="<<i;
    cout<<"\n interconnect_numPassedEntity=" << interconnect_numPassedEntity[i];
    cout<<"\n interconnect_timeInConnection=" << interconnect_timeInConnection[i];
  }

  cout<<"\n\n = TOTAL_TYPE_INFO =";
  cout<<"\n total_type_numProducedEntity=" << total_type_numProducedEntity;

  cout<<"\n\n = TOTAL_SERVER_INFO =";
  cout<<"\n total_server_numFinishedEntity=" << total_server_numFinishedEntity;
  cout<<"\n total_server_avgRunTimeEntity=" << total_server_avgRunTimeEntity;
  cout<<"\n total_server_avgWaitTimeQueue=" << total_server_avgWaitTimeQueue;
  cout<<"\n total_server_avgWaitTimeQueueInter=" << total_server_avgWaitTimeQueueInter;

  cout<<"\n\n = TOTAL_INTERCONNECT_INFO =";
  cout<<"\n total_interconnect_numPassedEntity=" << total_interconnect_numPassedEntity;
  cout<<"\n total_interconnect_timeInConnection=" << total_interconnect_timeInConnection;
  cout<<"\n\n";
}

void End::dispStatsToFile(int numType, int numServer, int numInterconnect , Params param){
  int numWay=param.numWay, wayCapacity=param.wayCapacity;
  int numBus=param.numBus, busCapacity=param.busCapacity, busSpeed=param.busSpeed;
  int POLICY = param.POLICY, simulationTime = param.simulationTime;
  double throughput =0;
  int cost;
  // char* filename1 = "./test_for_best_throughput_1.txt";
  // char* filename2 = "./test_for_best_throughput/cost_1.txt";
  FILE* wfp = fopen("./test_for_best_throughput_4.txt", "w");
  // FILE* wfp = fopen("./test_for_best_throughput/cost_1.txt", "w");
  fprintf(wfp, " ======== DISPLAY PARAMETERS =======");
  fprintf(wfp, "\n Number of Ways : %d", numWay);
  fprintf(wfp, "\n Capacity of Ways : %d", wayCapacity);
  fprintf(wfp, "\n Number of Buses : %d", numBus);
  fprintf(wfp, "\n Capacity of Buses : %d", busCapacity);
  fprintf(wfp, "\n Speed of Buses : %d", busSpeed);
  switch(POLICY){
    case 1:
      fprintf(wfp, "\n Scheduling Policy : FIFO (First In First Out) ");
      break;
    case 2:
      fprintf(wfp, "\n Scheduling Policy : SJF (Shortest Job First)");
      break;
    case 3:
      fprintf(wfp, "\n Scheduling Policy : RR (Round Robin)");
      break;
    case 4:
      fprintf(wfp, "\n Scheduling Policy : SJF_AGING (Shortest Job First with Aging)");
      break;
  }
  fprintf(wfp, "\n\n ======== DISPLAY STATS =======");
  throughput = (double)total_server_numFinishedEntity/(double)simulationTime;

  fprintf(wfp, "\n Thoughput = %G" , throughput );
  // fprintf(wfp, "\n Cost = %d" , cost);
  // fprintf(wfp, "\n Thoughput/Cost = %G" , throughput/(double)cost);
  fprintf(wfp, "\n Server Queue Scheduling Policy Performance = %G" , (double)total_server_avgWaitTimeQueue/(double)total_server_numFinishedEntity);

  fprintf(wfp, "\n\n = TOTAL_TYPE_INFO =");
  fprintf(wfp, "\n total_type_numProducedEntity=%d" , total_type_numProducedEntity);
  // fprintf(wfp, "\n total_type_numFinishedEntity=%d" , total_type_numFinishedEntity);
  // fprintf(wfp, "\n total_type_RunTimeEntity=%d" , total_type_avgRunTimeEntity);
  // fprintf(wfp, "\n total_type_WaitTimeEntity=%d" , total_type_avgWaitTimeEntity);
  // fprintf(wfp, "\n total_type_timeInConnection=%d" , total_type_timeInConnection);

  fprintf(wfp, "\n\n = TOTAL_SERVER_INFO =");
  fprintf(wfp, "\n total_server_numFinishedEntity=%d" , total_server_numFinishedEntity);
  fprintf(wfp, "\n total_server_RunTimeEntity=%d" , total_server_avgRunTimeEntity);
  // fprintf(wfp, "\n total_server_WaitTimeQueue=%d" , total_server_avgWaitTimeQueue);
  fprintf(wfp, "\n total_server_WaitTimeQueueInter=%d" , total_server_avgWaitTimeQueueInter);

  fprintf(wfp, "\n\n = TOTAL_INTERCONNECT_INFO =");
  fprintf(wfp, "\n total_interconnect_numPassedEntity=%d" , total_interconnect_numPassedEntity);
  fprintf(wfp, "\n total_interconnect_timeInConnection=%d" , total_interconnect_timeInConnection);
  int i;
  fprintf(wfp, "\n\n === TYPE INFORMATION ===");
  for(i=1; i<=numType; i++){
    fprintf(wfp, "\n KEY=%d", i);
    fprintf(wfp, "\n type_numProducedEntity=%d" , type_numProducedEntity[i]);
    // fprintf(wfp, "\n type_numFinishedEntity=%d" , type_numFinishedEntity[i]);
    // fprintf(wfp, "\n type_RunTimeEntity=%d" , type_avgRunTimeEntity[i]);
    // fprintf(wfp, "\n type_WaitTimeEntity=%d" , type_avgWaitTimeEntity[i]);
    // fprintf(wfp, "\n type_timeInConnection=%d" , type_timeInConnection[i]);
  }

  fprintf(wfp, "\n\n === SERVER INFORMATION ===");
  for(i=1; i<=numServer; i++){
    fprintf(wfp, "\n KEY=%d",i);
    fprintf(wfp, "\n server_numFinishedEntity=%d" , server_numFinishedEntity[i]);
    fprintf(wfp, "\n server_RunTimeEntity=%d" , server_avgRunTimeEntity[i]);
    // fprintf(wfp, "\n server_WaitTimeQueue=%d" , server_avgWaitTimeQueue[i]);
    fprintf(wfp, "\n server_WaitTimeQueueInter=%d" , server_avgWaitTimeQueueInter[i]);
  }

  fprintf(wfp, "\n\n === INTERCONNECT INFORMATION ===");
  for(i=1; i<=numInterconnect; i++){
    fprintf(wfp, "\n KEY=%d",i);
    fprintf(wfp, "\n interconnect_numPassedEntity=%d" , interconnect_numPassedEntity[i]);
    fprintf(wfp, "\n interconnect_timeInConnection=%d" , interconnect_timeInConnection[i]);
  }
  fprintf(wfp, "\n\n");
  fclose(wfp);
}
//////////////////////////////////////////////////////////////////
Simulation::Simulation(){}
void Simulation::init(){
  INSERT_PROCESS=1; INSERT_SERVER=2; INSERT_CORE=3; INSERT_INTERCONNECT=4;INSERT_WAY=5; INSERT_BUS=6;
  POLICY_FIFO = 1; POLICY_SJF = 2;
  POLICY_RR = 3;  POLICY_SJF_AGING = 4;
  int i,j,k, temp, serverNum;

  //////////// variables for this mini factory simulation ////////
  param.numWay=2; param.wayCapacity=50;
  param.numBus=0; param.busCapacity=60; param.busSpeed=70;
  param.POLICY = POLICY_SJF_AGING;
  param.simulationTime = simulationTime;
  int numCore = 1;
	////////////////////////////////////////////////////////////////////
  int numWay=param.numWay, wayCapacity=param.wayCapacity;
  int numBus=param.numBus, busCapacity=param.busCapacity, busSpeed=param.busSpeed;
  POLICY = param.POLICY;
  WAY_BUS_QUEUE_SIZE_STAND = param.busCapacity/2;
  string str, infoStr, infoStrs;
  // simulation time :
  cin >> str >> str >> str >> str >> infoStr;
  if( !(istringstream(infoStr) >> simulationTime)) simulationTime=0;

  // Type init
  cin >> str >> str >> str >> infoStr;
  if( !(istringstream(infoStr) >> numType)) numType=0;
  numScenario = numType;

  for(i=0; i<numType; i++){
    cin >> str >> str >> infoStr >> str >> infoStrs;
    // type name
    vSchedules.push_back(Schedule(i+1));
    // type speed
    if( !(istringstream(infoStrs) >> temp)) temp=0;
    vSchedules[i].setSpeed(temp);
    // type's scenario
    if( !(istringstream(infoStr) >> temp)) temp=0;
    vScenarioSize.push_back(temp);
    for(j=0; j<vScenarioSize.at(i); j++){
      cin >> infoStr;
      infoStr.erase(infoStr.begin());
      if( !(istringstream(infoStr) >> temp)) temp=0;
      vSchedules[i].setScenario(temp);
    }
    // type's time
    for(j=0; j<vScenarioSize.at(i); j++){
      cin >> infoStr;
      if( !(istringstream(infoStr) >> temp)) temp=0;
      vSchedules[i].setTime(temp);
    }
  }

  // Process init
  cin >> str >> str >> str >> infoStr;
  if( !(istringstream(infoStr) >> numProcess)) numProcess=0;
  cin >> str >> str >> str >> str >> str;
  for(i=0; i<numProcess; i++){
    cin >> str >> infoStr;
    infoStr.erase(infoStr.begin());
    if( !(istringstream(infoStr) >> temp)) temp=0;
    vProcesses.push_back(Process(temp));
    // count >> start >> period
    cin >> str >> infoStr >> infoStrs;
    if( str == "Inf"){
      vProcesses[i].setNumEntity(0);
    }
    else{
      if( !(istringstream(str) >> temp)) temp=0;
      vProcesses[i].setNumEntity(temp);
    }
    if( !(istringstream(infoStr) >> temp)) temp=0;
    vProcesses[i].setTimePeriodRemakingEntity(temp);
    if( !(istringstream(infoStrs) >> temp)) temp=0;
    vProcesses[i].setStartTimeToProduceEntity(temp);
  }

  // Server init
  cin >> str >> str >> str >> infoStr;
  if( !(istringstream(infoStr) >> numServer)) numServer=0;
  // allocate memory to Distance
  ClassDistance.distArr = new int*[numServer+1];
  for(i=0; i<=numServer; i++){
    ClassDistance.distArr[i] = new int[numServer+1];
  }
  ClassDistance.setNumServer(numServer);
  cin >> str;
  for(i=0; i<numServer; i++){
    cin >> str;
    str.erase(str.begin());
    if( !(istringstream(str) >> serverNum)) serverNum=0;
    vServers.push_back(Server(serverNum, numCore));
    // if( !(istringstream(infoStr) >> numCore = 60;)) numCore = 60;=0;
  }
  for(i=1; i<=numServer; i++){
    cin >> str;
    for(j=1; j<=numServer; j++){
      cin >> str;
      if(j>=i){
        if( !(istringstream(str) >> temp)) temp=0;
        ClassDistance.distArr[i][j] = temp;
        ClassDistance.distArr[j][i] = temp;
      }
    }
  }
  // ClassDistance.disp();

  // Interconnect init
  k = 0;temp=0;
  // vInterconnect.push_back(Interconnect(k, numWay, numBus));
  for(i=1; i<=numServer; i++){
   for(j=1; j<=numServer; j++){
      if(j>i){
        // way init
        vInterconnect.push_back(Interconnect(k, numWay, numBus));
        vInterconnect[k].vWays.push_back(Way());
        vInterconnect[k].vWays[0].setParams(i,j,wayCapacity,ClassDistance.distArr[i][j] );
        vInterconnect[k].vWays.push_back(Way());
        vInterconnect[k].vWays[1].setParams(j,i,wayCapacity,ClassDistance.distArr[i][j] );
        // bus init
        // vInterconnect[k].vBuses.push_back(Bus());
        // vInterconnect[k].vBuses[0].setParams(i,j,wayCapacity,ClassDistance.distArr[i][j] );
        k += 1;
      }
    }
  }
  numInterconnect = k;
  // End init
  ClassEnd.init(numType, numServer, numInterconnect);

  // TimeModule Init (first insert processes)
  for(i=0; i <numProcess; i++){
    ClassTime.insert(vProcesses[i].startTimeToProduceEntity, i+1, 1);
  }
}

void Simulation::setTestSetUp(){
  // read test setup file & run simulation program.
}

void Simulation::run(){
  int i, j, k;
  tempEvent.processID=0;  tempEvent.serverID=0; tempEvent.coreID=0;
  tempEvent.coreID_entity=0; tempEvent.interconnectID=0; tempEvent.way12_bus3 = 0;
  // tempEvent.tempID=0;
  bool bIsEventEmpty=true;
  // Entity pEntity, pEntityServ;
  timeCount = 0;
  while(timeCount < simulationTime){
    ClassTime.it = ClassTime.mTime.find(timeCount);
    if( ClassTime.it == ClassTime.mTime.end() ){
      bIsEventEmpty = true;
    }else{
      bIsEventEmpty = false;
      // execute vEvent Queue and then delete this node

      for(i=0; i<ClassTime.it->second.size(); i++){
        tempEvent.processID = ClassTime.it->second[i].processID;
        tempEvent.serverID = ClassTime.it->second[i].serverID;
        tempEvent.coreID = ClassTime.it->second[i].coreID;
        tempEvent.coreID_entity = ClassTime.it->second[i].coreID_entity;
        tempEvent.interconnectID = ClassTime.it->second[i].interconnectID;
        tempEvent.way12_bus3 = ClassTime.it->second[i].way12_bus3;
        // tempEvent.wayID = ClassTime.it->second[i].wayID;
        // tempEvent.busID = ClassTime.it->second[i].busID;
        // tempEvent.tempID = 0;
        // when process ID is in vEvent vector
        if( (tempEvent.processID!=0)&&(tempEvent.serverID==0)&&(tempEvent.interconnectID==0) ){
          runProcess();
        }
        // when server ID is in vEvent vector
        else if( (tempEvent.processID==0)&&(tempEvent.serverID!=0)&&(tempEvent.interconnectID==0) ){
          runServer();
        }
        // when way ID is in vEvent vector
        else if( (tempEvent.processID==0)&&(tempEvent.serverID!=0)&&(tempEvent.interconnectID!=0) ){
          runInterconnect();
        }
        // // when bus ID is in vEvent vector
        // else if( (tempEvent.processID==0)&&(tempEvent.serverID==0)&&(tempEvent.wayID==0)&&(tempEvent.busID!=0) ){
        //   runBus();
        // }
        else{
        }
      }

    }
    // delete this node
    if(!bIsEventEmpty){
      ClassTime.mTime.erase(ClassTime.it);
    }
    timeCount++;
    // ClassEnd.shouldFinishLoop();
  }
}

void Simulation::runProcess(){
  int coreNum, tempID, k;
  Entity pEntity;
  Entity entity;
  pEntity = vProcesses[tempEvent.processID-1].createEntity(vSchedules);
  // if( vProcesses[tempEvent.processID-1].bRunFlag ){

  if( pEntity.typeNum != 0 ){
    ClassTime.insert(timeCount+vProcesses[tempEvent.processID-1].timePeriodRemakingEntity, tempEvent.processID, INSERT_PROCESS);
    tempID = pEntity.vScenario.front();
    // for(k=0;k<pEntity->vScenario.size();k++){
    // }
    vServers[tempID-1].insertEntityToQueue(&pEntity, timeCount);
    // if queue is empty
    if( vServers[tempID-1].checkQueue()==1){
      // check core status, and then insert to core
      if( (coreNum=vServers[tempID-1].checkCoreStatus())!=0){
        entity = vServers[tempID-1].getEntityFromQueueSchedule(timeCount, POLICY);
        ClassTime.insert(timeCount+entity.vTime.front(),tempID, coreNum, INSERT_CORE);
        vServers[tempID-1].assignEntityToCoreSchedule(coreNum, timeCount, &entity, POLICY);
      }
    }
  }
  // delete pEntity;
}

void Simulation::runServer(){
  // dealing server's cores
  if( tempEvent.coreID > 0){
    runServerDealCore();
  }
  // dealing server's queue
  else{
    runServerDealQueue();
  }
}

void Simulation::runServerDealCore(){
  entityServ = vServers[tempEvent.serverID-1].getEntityFromCoreSchedule(tempEvent.coreID, timeCount, POLICY);
  // entityServ = vServers[tempEvent.serverID-1].getEntityFromCore(tempEvent.coreID);
  vServers[tempEvent.serverID-1].popEntityFromCore(tempEvent.coreID);
  // when no element left
  if( entityServ.bShouldEnd == true ){
    // send entity to END instance...
    ClassEnd.calEachEntity(&entityServ);
  }
  // send entity to next server
  else{
    if( entityServ.remainFlag > 0){ // entity still has time to run
      // runServerSendEntityToNextServer();
      // return to queue of this server
      entityServ.remainFlag = 0;
      vServers[tempEvent.serverID-1].insertEntityToQueue(&entityServ, timeCount);
    }
    else{ // entity time for this server expired

      runServerSendEntityToNextInterconnect();
    }
  }
  // put entity from queue to core
  if( vServers[tempEvent.serverID-1].checkQueue()>0){
    runServerSendEntityToCore();
  }
}

void Simulation::runServerSendEntityToCore(){
  int k, coreNum;
  Entity entity;
  // if core is free, get entity from queue and put it to core
  if( (coreNum=vServers[tempEvent.serverID-1].checkCoreStatus())!=0){
    entity = vServers[tempEvent.serverID-1].getEntityFromQueueSchedule(timeCount, POLICY);
    ClassTime.insert(timeCount+entity.vTime.front(),tempEvent.serverID, coreNum, INSERT_CORE);
    vServers[tempEvent.serverID-1].assignEntityToCoreSchedule(coreNum, timeCount, &entity, POLICY);
  }
}

void Simulation::runServerDealQueue(){
}

void Simulation::runServerSendEntityToNextInterconnect(){
  int i, tempID, numEntityQueueInter, way12_bus3, timeTemp;
  InterStatus interStatus;
  Entity entity;
  event e;
  vServers[tempEvent.serverID-1].insertEntityToQueueInter(&entityServ, timeCount);
  tempID = entityServ.vScenario.front();
  // if queue is only one,
  numEntityQueueInter = vServers[tempEvent.serverID-1].checkQueueInter();
  if( numEntityQueueInter == 1 ){
    // check Interconnect status, and then insert to Interconnect
    interStatus = checkInterconnectStatus(tempEvent.serverID, tempID, numEntityQueueInter);
    e.serverID = tempEvent.serverID; e.interconnectID=interStatus.interconnectID; e.way12_bus3 = interStatus.way12_bus3;
    if( interStatus.way12_bus3 > 0){
      switch(interStatus.way12_bus3){
        case 1:
          entity = vServers[tempEvent.serverID-1].getEntityFromQueueInter(timeCount);
          timeTemp = vInterconnect[interStatus.interconnectID-1].vWays[0].calPassTime(&entity);
          ClassTime.insert(timeCount+timeTemp,e, INSERT_INTERCONNECT);
          vInterconnect[interStatus.interconnectID-1].vWays[0].putEntity(&entity, timeCount);
          break;
        case 2:
          entity = vServers[tempEvent.serverID-1].getEntityFromQueueInter(timeCount);
          timeTemp = vInterconnect[interStatus.interconnectID-1].vWays[1].calPassTime(&entity);
          ClassTime.insert(timeCount+timeTemp,e, INSERT_INTERCONNECT);
          vInterconnect[interStatus.interconnectID-1].vWays[1].putEntity(&entity, timeCount);
          break;
        case 3:
          timeTemp = vInterconnect[interStatus.interconnectID-1].vBuses[0].calPassTime();
          ClassTime.insert(timeCount+timeTemp,e, INSERT_INTERCONNECT);
          for(i=0; i<numEntityQueueInter; i++){
            if( i < vInterconnect[interStatus.interconnectID-1].vBuses[0].capacity){
              entity = vServers[tempEvent.serverID-1].getEntityFromQueueInter(timeCount);
              vInterconnect[interStatus.interconnectID-1].vBuses[0].putEntity(&entity, timeCount);
            }
          }
          break;
        default:
          break;
      }
    }
  }
}

InterStatus Simulation::checkInterconnectStatus(int currentID, int nextID, int numEntityQueueInter){
  InterStatus interStatus;
  int way12_bus3=0;
  int i,j, lowID, highID;
  int wayFlag=0, busFlag=0;
  // calculate interconnect ID
  if( nextID > currentID ){
    for(i=0; i<vInterconnect.size(); i++){
      if( vInterconnect[i].vWays.size() > 0){
        if( (vInterconnect[i].vWays[0].vertexFrom==currentID)&&(vInterconnect[i].vWays[0].vertexTo==nextID) ){
          if( vInterconnect[i].vWays[0].entitySize < vInterconnect[i].vWays[0].capacity){
            wayFlag = 1;
            break;
          }
        }
      }else{
        break;
      }
    }
  }else{
    for(i=0; i<vInterconnect.size(); i++){
      if( vInterconnect[i].vWays.size() > 0){
        if( (vInterconnect[i].vWays[1].vertexFrom==currentID)&&(vInterconnect[i].vWays[0].vertexTo==nextID) ){
          if( vInterconnect[i].vWays[1].entitySize < vInterconnect[i].vWays[1].capacity){
            wayFlag = 2;
            break;
          }
        }
      }else{
        break;
      }
    }
  }
  j = i;
  if( vInterconnect[i].vBuses.size() > 0 ){
    if( wayFlag > 0){
      if( (vInterconnect[j].vBuses[0].vertexFrom==currentID)&&(vInterconnect[j].vBuses[0].vertexTo==nextID) ){
        if( currentID == vInterconnect[j].vBuses[0].currentID) busFlag = 1;
      }
      if( (vInterconnect[j].vBuses[0].vertexFrom==nextID)&&(vInterconnect[j].vBuses[0].vertexTo==currentID) ){
        if( currentID == vInterconnect[j].vBuses[0].currentID) busFlag = 1;
      }
    }else{
      for(i=0; i<vInterconnect.size(); i++){
        if( (vInterconnect[i].vBuses[0].vertexFrom==currentID)&&(vInterconnect[i].vBuses[0].vertexTo==nextID) ){
          if( currentID == vInterconnect[i].vBuses[0].currentID){
            busFlag = 1;
            j=i;
            break;
          }
        }
        if( (vInterconnect[i].vBuses[0].vertexFrom==nextID)&&(vInterconnect[i].vBuses[0].vertexTo==currentID) ){
          if( currentID == vInterconnect[i].vBuses[0].currentID) {
            busFlag = 1;
            j=i;
            break;
          }
        }
      }
    }
  }
  interStatus.interconnectID = j+1;

  // select way 1 way 2 or bus 3 : 0 for not selecting
  if( busFlag != 0){
    switch(wayFlag){
      case 0:
        if( numEntityQueueInter > WAY_BUS_QUEUE_SIZE_STAND ){
          way12_bus3 = 3;
        }
        break;
      case 1:
        if( numEntityQueueInter > WAY_BUS_QUEUE_SIZE_STAND ){
          way12_bus3 = 3;
        }else{
          way12_bus3 = 1;
        }
        break;
      case 2:
        if( numEntityQueueInter > WAY_BUS_QUEUE_SIZE_STAND ){
          way12_bus3 = 3;
        }else{
          way12_bus3 = 2;
        }
        break;
      default:
        break;
    }
  }else{
    switch(wayFlag){
      case 0:
        way12_bus3 = 0;
        break;
      case 1:
        way12_bus3 = 1;
        break;
      case 2:
        way12_bus3 = 2;
        break;
      default:
        break;
    }
  }
  interStatus.way12_bus3 = way12_bus3;

  return interStatus;
}
/////////////////////////////////////////////////////////////////////////
void Simulation::runInterconnect(){
  // dealing Interconnect's ways
  switch(tempEvent.way12_bus3){
    case 1:
    case 2:
      runInterconnectDealWay();
      break;
    case 3:
      runInterconnectDealBus();
      break;
  // dealing Interconnect's queue
    default:
      runInterconnectDealQueue();
      break;
  }
}

void Simulation::runInterconnectDealWay(){
  int i, temp_position, tempID, coreNum;
  Entity entity;
  // extract entity from ways
  if( tempEvent.way12_bus3 == 1){
    temp_position = vInterconnect[tempEvent.interconnectID-1].vWays[0].getWhichEntity(timeCount);
    entityInter = vInterconnect[tempEvent.interconnectID-1].vWays[0].getEntity(timeCount, temp_position);
    vInterconnect[tempEvent.interconnectID-1].vWays[0].popEntity(temp_position);
  }else{
    temp_position = vInterconnect[tempEvent.interconnectID-1].vWays[1].getWhichEntity(timeCount);
    entityInter = vInterconnect[tempEvent.interconnectID-1].vWays[1].getEntity(timeCount, temp_position);
    vInterconnect[tempEvent.interconnectID-1].vWays[1].popEntity(temp_position);
  }
  // put extracted entity to next server queue.
  tempID = entityInter.vScenario.front();
  vServers[tempID-1].insertEntityToQueue(&entityInter, timeCount);
  // if queue is empty
  if( vServers[tempID-1].checkQueue()==1){
    // check core status, and then insert to core
    if( (coreNum=vServers[tempID-1].checkCoreStatus())!=0){
      entity = vServers[tempID-1].getEntityFromQueueSchedule(timeCount, POLICY);
      ClassTime.insert(timeCount+entity.vTime.front(),tempID, coreNum, INSERT_CORE);
      vServers[tempID-1].assignEntityToCoreSchedule(coreNum, timeCount, &entity, POLICY);
    }
  }
  // put entity from previous server inter queue to way
  if( vServers[tempEvent.serverID-1].checkQueueInter()>0){
    runInterconnectSendEntityToInterconnect(tempID);
  }
}

void Simulation::runInterconnectDealBus(){
  int i, temp_position, tempID, entitySize,coreNum;
  Entity entity;
  // extract entity from Buses
  entitySize = vInterconnect[tempEvent.interconnectID-1].vBuses[0].entitySize;
  for(i=0; i< entitySize; i++){
    entityInter = vInterconnect[tempEvent.interconnectID-1].vBuses[0].getEntity(timeCount);
    vInterconnect[tempEvent.interconnectID-1].vBuses[0].popEntity();

    // put extracted entity to next server queue.
    tempID = entityInter.vScenario.front();
    vServers[tempID-1].insertEntityToQueue(&entityInter, timeCount);
    // if queue is empty
    if( vServers[tempID-1].checkQueue()==1){
      // check core status, and then insert to core
      if( (coreNum=vServers[tempID-1].checkCoreStatus())!=0){
        entity = vServers[tempID-1].getEntityFromQueueSchedule(timeCount, POLICY);
        ClassTime.insert(timeCount+entity.vTime.front(),tempID, coreNum, INSERT_CORE);
        vServers[tempID-1].assignEntityToCoreSchedule(coreNum, timeCount, &entity, POLICY);
      }
    }
  }
  vInterconnect[tempEvent.interconnectID-1].vBuses[0].currentID = tempID;
  // put entity from previous server inter queue to way
  if( vServers[tempEvent.serverID-1].checkQueueInter()>0){
    runInterconnectSendEntityToInterconnect(tempID);
  }
}

void Simulation::runInterconnectSendEntityToInterconnect(int tempID){
  int i, numEntityQueueInter, way12_bus3, timeTemp;
  InterStatus interStatus;
  Entity entity;
  event e;
  // vServers[tempEvent.serverID-1].insertEntityToQueueInter(&entityServ, timeCount);
  // tempID = entityServ.vScenario.front();
  // if queue is only one,
  numEntityQueueInter = vServers[tempEvent.serverID-1].checkQueueInter();

  // check Interconnect status, and then insert to Interconnect
  interStatus = checkInterconnectStatus(tempEvent.serverID, tempID, numEntityQueueInter);
  e.serverID = tempEvent.serverID; e.interconnectID=interStatus.interconnectID; e.way12_bus3 = interStatus.way12_bus3;
  if( interStatus.way12_bus3 > 0){
    switch(interStatus.way12_bus3){
      case 1:
        entity = vServers[tempEvent.serverID-1].getEntityFromQueueInter(timeCount);
        timeTemp = vInterconnect[interStatus.interconnectID-1].vWays[0].calPassTime(&entity);
        ClassTime.insert(timeCount+timeTemp,e, INSERT_INTERCONNECT);
        vInterconnect[interStatus.interconnectID-1].vWays[0].putEntity(&entity, timeCount);
        break;
      case 2:
        entity = vServers[tempEvent.serverID-1].getEntityFromQueueInter(timeCount);
        timeTemp = vInterconnect[interStatus.interconnectID-1].vWays[1].calPassTime(&entity);
        ClassTime.insert(timeCount+timeTemp,e, INSERT_INTERCONNECT);
        vInterconnect[interStatus.interconnectID-1].vWays[1].putEntity(&entity, timeCount);
        break;
      case 3:
        timeTemp = vInterconnect[interStatus.interconnectID-1].vBuses[0].calPassTime();
        ClassTime.insert(timeCount+timeTemp,e, INSERT_INTERCONNECT);
        for(i=0; i<numEntityQueueInter; i++){
          if( i < vInterconnect[interStatus.interconnectID-1].vBuses[0].capacity){
            entity = vServers[tempEvent.serverID-1].getEntityFromQueueInter(timeCount);
            vInterconnect[interStatus.interconnectID-1].vBuses[0].putEntity(&entity, timeCount);
          }
        }
        break;
      default:
        break;
    }
  }
}

void Simulation::runInterconnectDealQueue(){
}

////////////////////////////////////////////////////////////
void Simulation::runFree(){
  int i;
  for(i=0; i<=numServer; i++){
    delete[] ClassDistance.distArr[i];
  }
  delete[] ClassDistance.distArr;
}

void Simulation::stats(){ }

void Simulation::printOutputFile(){
  ClassEnd.calTotalTypes(vProcesses, timeCount, numType);
  ClassEnd.calTotalServers(vServers, timeCount, numServer);
  ClassEnd.calTotalInterconnects(vInterconnect, timeCount, numInterconnect);
  ClassEnd.dispStats(numType, numServer, numInterconnect);
  ClassEnd.dispStatsToFile(numType, numServer, numInterconnect, param);

  runFree();
}

// void Simulation::runServerSendEntityToNextServer(){
//   int k, coreNum, tempID;
//   Entity entity;
//   for(k=0;k<entityServ.vScenario.size();k++){
//     cout << " "<<entityServ.vScenario[k];
//   }
//   tempID = entityServ.vScenario.front();
//   vServers[tempID-1].insertEntityToQueue(&entityServ, timeCount);
//   cout<<"\tempID : "<<tempID;
//   // if queue is only one,
//   if( vServers[tempID-1].checkQueue()==1){
//     cout <<"\n SERVER : if queue is only one of serverID :"<<tempID;
//     // check core status, and then insert to core
//     if( (coreNum=vServers[tempID-1].checkCoreStatus())!=0){
//       cout << "\nSERVER : insert to core at " << timeCount;
//       entity = vServers[tempID-1].getEntityFromQueueSchedule(timeCount, POLICY);
//       ClassTime.insert(timeCount+entity.vTime.front(),tempID,coreNum, INSERT_CORE);
//       vServers[tempID-1].assignEntityToCoreSchedule(coreNum, timeCount, &entity, POLICY);
//     }
//   }
// }