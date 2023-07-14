#include "inventory.h"
#include <iostream>
#include <iomanip>


// constructor
Inventory::Inventory(string n_name, int n_qty, double n_price, double n_cost, double n_profit){
  name=n_name;
  qty=n_qty;
  price=n_price;
  cost = n_cost;
  profit= n_profit;
}

// set cost to warehouse 
void Inventory::SetCost(double n_Cost){cost = n_Cost;}

// adjust inventory qty after new order 
void Inventory::AdjQty(int remQty){
  qty -= remQty;
}

// return item name
string Inventory::GetName() const{return name;}

// return invtry qty
int Inventory::GetQty() const {return qty;}

// return item price
double Inventory::GetPrice() const {return price;}

// return cost to warehous 
double Inventory::GetCost() const {return cost;}

// return profit to warehouse 
double Inventory::GetPrft() const {return price-cost;}

// show inventory details 
void Inventory::Show() {
  
  int nameWidth = 7;  
  int qtyWidth = 5;   
  int priceWidth = 8; 
  int costWidth = 8;  
  int profitWidth = 7;

  cout << setfill('-') << setw(nameWidth + qtyWidth + priceWidth + costWidth + profitWidth +5) << "-" << setfill(' ') << '\n'
    << "|" << left << setw(nameWidth+1) << "ItemID| " 
    << right << setw(qtyWidth + 1) << "Qty| "
    << setw(priceWidth + 1) << "Price| " 
    << setw(costWidth + 1) << "Cost| " << setw(profitWidth + 1) 
    << "Profit|\n"
    << setfill('-') << setw(nameWidth + qtyWidth + priceWidth + costWidth + profitWidth +5) << "-" << setfill(' ') << '\n';


  cout << "|" << setw(nameWidth-1) << left
    << name << "|" << right << setw(qtyWidth) 
    << qty << "|" << setw(priceWidth)
    << price << "|" << setw(costWidth) 
    << cost << "|" << setw(profitWidth) 
    << price-cost << "|\n"
    << setfill('-') << setw(nameWidth + qtyWidth + priceWidth + costWidth + profitWidth + 5) << "-" << setfill(' ') << "\n\n";
}


