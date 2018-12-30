///////////////////////////////////////////////////////
// System Software Experiment 3.
// Project 2 : Mini Factory.
// written by Youngdae Kwon.
// MIT license.
///////////////////////////////////////////////////////

#include "time_module.h"

void TimeModule::insert(int time, int ID, int whichEvent){
  event e;
  switch(whichEvent){
    case 1:
      e.processID=ID; e.serverID=0;
      e.coreID=0;e.coreID_entity=0;e.interconnectID=0; e.way12_bus3=0;
      break;
    case 2:
      e.processID=0; e.serverID=ID;
      e.coreID=0;e.coreID_entity=0;e.interconnectID=0; e.way12_bus3=0;
      break;
    case 3:
      e.processID=0; e.serverID=0;
      e.coreID=ID;e.coreID_entity=0;e.interconnectID=0; e.way12_bus3=0;
      break;
    case 4:
      e.processID=0; e.serverID=0;
      e.coreID=0;e.coreID_entity=ID;e.interconnectID=0; e.way12_bus3=0;
      break;
    // case 5:
    //   e.processID=0; e.serverID=0;
    //   e.coreID=0;e.coreID_entity=0;e.interconnectID=ID;
      break;
    default:
      // cout << "\n TimeModule : insert function -> wrong whichEvent ";
      break;
  }
  // mTime.insert(pair<int,vector<event> >(time, vector<event>()));
  mTime[time].push_back(e);
}

void TimeModule::insert(int time, int ID, int coreNum, int whichEvent){
  event e;
  switch(whichEvent){
    case 1:
      e.processID=ID; e.serverID=0;e.coreID=0;
      e.coreID_entity=0;e.interconnectID=0;e.way12_bus3=0;
      break;
    case 2:
      e.processID=0; e.serverID=ID;e.coreID=0;
      e.coreID_entity=0;e.interconnectID=0;e.way12_bus3=0;
      break;
    case 3:
      e.processID=0; e.serverID=ID;e.coreID=coreNum;
      e.coreID_entity=0;e.interconnectID=0;e.way12_bus3=0;
      break;
    case 4:
      e.processID=0; e.serverID=0;e.coreID=0;
      e.coreID_entity=0;e.interconnectID=ID;e.way12_bus3=coreNum;
      break;
    // case 5:
    //   e.processID=0; e.serverID=0;e.coreID=0;e.coreID_entity=0;e.interconnectID=ID;;e.way12_bus3=0;
    //   break;
    default:
      // cout << "\n TimeModule : insert function -> wrong whichEvent ";
      break;
  }
  // mTime.insert(pair<int,vector<event> >(time, vector<event>()));
  mTime[time].push_back(e);
}

void TimeModule::insert(int time, event e_old, int whichEvent){
  event e_new;
  switch(whichEvent){
    case 1:
      e_new.processID=e_old.processID; e_new.serverID=0;e_new.coreID=0;
      e_new.coreID_entity=0;e_new.interconnectID=0;e_new.way12_bus3=0;
      break;
    case 2:
      e_new.processID=0; e_new.serverID=e_old.serverID;e_new.coreID=0;
      e_new.coreID_entity=0;e_new.interconnectID=0;e_new.way12_bus3=0;
      break;
    case 3:
      e_new.processID=0; e_new.serverID=e_old.serverID;e_new.coreID=e_old.coreID;
      e_new.coreID_entity=0;e_new.interconnectID=0;e_new.way12_bus3=0;
      break;
    case 4:
      e_new.processID=0; e_new.serverID=e_old.serverID;e_new.coreID=0;e_new.coreID_entity=0;
      e_new.interconnectID=e_old.interconnectID;e_new.way12_bus3=e_old.way12_bus3;
      break;
    default:
      // cout << "\n TimeModule : insert function -> wrong whichEvent ";
      break;
  }
  mTime[time].push_back(e_new);
}