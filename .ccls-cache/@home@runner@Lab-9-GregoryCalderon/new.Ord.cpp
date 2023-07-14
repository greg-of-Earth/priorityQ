#include "new_Ord.h"
#include "inventory.h"
#include <iostream>
#include <iomanip>


// constructor
NewOrd::NewOrd(int n_qty, int n_shipSpd, int n_trckNum, double n_shpTotal, double n_ordTotal, double n_bizCost, double n_bizPrft) {
  SetOrd(n_qty, n_shipSpd, n_trckNum, n_shpTotal, n_ordTotal, n_bizCost, n_bizPrft);
}

//copy constructor 
NewOrd::NewOrd(const NewOrd& ogOrd){
  SetOrd(ogOrd.ordQty, ogOrd.shipSpd, ogOrd.trckNum, ogOrd.shipTotal, ogOrd.ordTotal, ogOrd.bizCost, ogOrd.bizPrft);
}

//copy assignnment
NewOrd& NewOrd::operator=(const NewOrd& ogOrd){
  if(this!=&ogOrd){
    SetOrd(ogOrd.ordQty, ogOrd.shipSpd, ogOrd.trckNum, ogOrd.shipTotal, ogOrd.ordTotal, ogOrd.bizCost, ogOrd.bizPrft);
  }
  return *this;
}

//set new order details
void NewOrd::SetOrd(int n_qty, int n_shipSpd, int n_trckNum, double n_shpTotal, double n_ordTotal, double n_bizCost, double n_bizPrft) {
  ordQty=n_qty;
  shipSpd=n_shipSpd;
  trckNum=n_trckNum;
  shipTotal=n_shpTotal;
  ordTotal=n_ordTotal;
  bizCost=n_bizCost;
  bizPrft=n_bizPrft;
}


void NewOrd::SetQty(int n_qty){
  SetOrd(n_qty, shipSpd, trckNum, shipTotal, ordTotal, bizCost, bizPrft);
}

void NewOrd::SetShipSpeed(int n_shipSpd){
  SetOrd(ordQty, n_shipSpd, trckNum, shipTotal, ordTotal, bizCost, bizPrft);
}

void NewOrd::SetTrackNum(int qSize){
  SetOrd(ordQty, shipSpd, trckNum += qSize, shipTotal, ordTotal, bizCost, bizPrft);
}

 void NewOrd::SetBizCost(Inventory& inv) {
   SetOrd(ordQty, shipSpd, trckNum, shipTotal, ordTotal, bizCost = inv.cost * ordQty, bizPrft);
 }


 void NewOrd::SetBizPrft(Inventory& inv) {
   SetOrd(ordQty, shipSpd, trckNum, shipTotal, ordTotal, bizCost, bizPrft = ordTotal-bizCost);
 }

// calculate shipping total and set to new order 
void NewOrd::CalcShipTotal(Inventory& inv){
  double baseTotal = ordQty*inv.price;
  double n_shpTotal = baseTotal * (ShipRate[shipSpd]/100);
  SetOrd(ordQty, shipSpd, trckNum, n_shpTotal, ordTotal, bizCost, bizPrft);
}

// calculate order total and set to new order 
void NewOrd::CalcTotal(Inventory& inv) {
  double baseTotal = ordQty*inv.price;
  double n_ordTotal = baseTotal + (baseTotal*(ShipRate[shipSpd]/100));
  SetOrd(ordQty, shipSpd, trckNum, shipTotal, n_ordTotal, bizCost, bizPrft);
  ordTotal= n_ordTotal;
}

int NewOrd::GetQty() const {return ordQty;}

int NewOrd::GetShipSpd() const {return shipSpd;}

int NewOrd::GetTrckNum() const {return trckNum;}

double NewOrd::GetShipTotal() const{return shipTotal;}

double NewOrd::GetOrdTotal() const {return ordTotal;}

double NewOrd::GetBizCost() const {return bizCost;}

double NewOrd::GetBizPrft() const {return bizPrft;}

// set new order to string
string NewOrd::ToString() const {
  stringstream ordStr;
  ordStr << left << "|"  << setw(7)<< trckNum << "|" <<  setw(9) << ShipStr[shipSpd] <<setw(4) <<  "|" <<right <<  ordQty << "|"<<  setw(8) << ShipRate[shipSpd] << "|"<<  setw(8) << fixed << setprecision(2) << shipTotal << "|"<<  setw(10) << ordTotal << "|"<<  setw(9) << bizCost<< "|"<<  setw(8) << bizPrft << "|";
  return ordStr.str();
}
