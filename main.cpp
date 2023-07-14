//Calderon, Gregory

/******** Instructor's Feedback Do NOT DELETE

check feedback.md

*********/
#include <iostream>
#include "inventory.h"
#include "new_Ord.h"
#include "priorityQ.h"
#include <limits>
using namespace std;

void Menu();
void TakeOrder(Inventory&, PriorityQ&);
int NewOrdQty(int);
int NewOrdShipSpd();
void CloseOut(Inventory&, PriorityQ&);

enum MENU_OPTIONS {
  VIEW=1,
  NEWORD,
  PROCESS,
  QUIT,
};


enum PRIOTIY_ORDER {
  XTREME=1,      // +77%
  XPEDITE,       // +55%
  STND,          // +33%
  MAIN,
};

int main() {  
  Menu();
  return 0;
} 

// proceses user order request 
// post: order is created and inventory is updated 
void TakeOrder(Inventory& newInv, PriorityQ& n_Q) {
  NewOrd n_Ord;
  int ordQty=newInv.GetQty();

  n_Ord.SetQty(NewOrdQty(ordQty));
  newInv.AdjQty(n_Ord.GetQty());
  n_Ord.SetShipSpeed(NewOrdShipSpd());
  n_Ord.CalcShipTotal(newInv);
  n_Ord.CalcTotal(newInv);
  n_Ord.SetBizCost(newInv);
  n_Ord.SetBizPrft(newInv);
  
  int trackNum = n_Q.GetQSize()+1;
  n_Ord.SetTrackNum(trackNum);
  n_Q.EnQ(n_Ord);
  n_Ord.CalcShipTotal(newInv);
}


// request order qty from user validate
// post: returns order qty to be processed by TakeOrder()
int NewOrdQty(int invCnt) {
  int ordQty=-1;
  bool valid=true;

  do{
    valid =true;
    cout << "Enter order Quanity: ";
    cin >> ordQty;
    cout << '\n';
    if(ordQty>invCnt){
      cerr << "INSUFFICIENT INVENTORY. CURRENT INVENTORY CNT: " << invCnt <<"\n\n";
      valid = false;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }while(!valid);
return ordQty;
}


// request ship priority from customer and validate 
// post: return ship priority 
int NewOrdShipSpd() {
  int option=-1;
  int shipspd=-1;
  bool valid=false;
  do{
    
    cout << "1. Extreme: +77%\n"
         << "2. Expedite: +55%\n"
         << "3. Standard: +33%\n"
         << "Select Ship Speed: ";
    cin >> option;
    
    switch(option) {
      case XTREME:
          shipspd=0;
          valid = true;
        break;
      case XPEDITE:
          shipspd=1;
          valid = true;
        break;
      case STND: 
          shipspd=2;
          valid = true;
        break;
      default:
        cerr << "\nERROR. INVALID SELECTION.\n\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }  
    if(valid) cout << "Order Confirmed!\n";
  }while(!valid);
return shipspd;
}

//final close of inventory 
//post: output days orders stats
void CloseOut(Inventory& newInv, PriorityQ& pQueue) {
  cout << "Stock Qty: " << newInv.GetQty() << "\nOrders Processed: " << pQueue.GetProcCnt() << "\n\n";  
}


//main menu Inventory& newInv, PriorityQ& pQueue
void Menu() {
  Inventory newInv;
  PriorityQ n_Queue;
  int option=-1;
  do{
    cout << "\n1. View Inventory\n"
         << "2. New Order\n"
         << "3. Process Orders\n"
         << "4. Quit\n"
         << "Enter Choice: ";
    cin >> option;
    cout << '\n';
    switch(option) {
      case VIEW:
        newInv.Show();
        break;
      case NEWORD:
        TakeOrder(newInv, n_Queue);
        break;
      case PROCESS:
        if(n_Queue.GetQSize()){
          n_Queue.Print();
          CloseOut(newInv, n_Queue);
        }else {
          cerr << "NO NEW ORDERS TO PROCESS.\n";
        }
        break;
      case QUIT:
        cout << "\nPROGRAM TERMINATED\n";
        break;
      default:
        cerr << "\nERROR. INVALID SELECTION\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }
  }while(option!=QUIT);
}


/*TEST CASES 


------------------------------------------------------------------------
|TckNum | RushStat| Qty|  %MrkUp|  $MrkUp|  CstTotal|  BizCost| BizPrft|
------------------------------------------------------------------------
|102    |Extrm    |   5|      77|   21.25|     48.85|    15.65|   33.20|
|103    |Extrm    |   2|      77|    8.50|     19.54|     6.26|   13.28|
|106    |Extrm    |   6|      77|   25.50|     58.62|    18.78|   39.84|
|107    |Extrm    |   3|      77|   12.75|     29.31|     9.39|   19.92|
|105    |Expd     |   4|      55|   12.14|     34.22|    12.52|   21.70|
|109    |Expd     |   7|      55|   21.25|     59.89|    21.91|   37.98|
|101    |Std      |   3|      33|    5.46|     22.02|     9.39|   12.63|
|104    |Std      |   2|      33|    3.64|     14.68|     6.26|    8.42|
|108    |Std      |   1|      33|    1.82|      7.34|     3.13|    4.21|
|110    |Std      |   5|      33|    9.11|     36.71|    15.65|   21.06|
|111    |Std      |   6|      33|   10.93|     44.05|    18.78|   25.27|
------------------------------------------------------------------------
Stock Qty: 356
Orders Processed: 11


1. View Inventory
2. New Order
3. Process Orders
4. Quit
Enter Choice: 4


PROGRAM TERMINATED


1. View Inventory
2. New Order
3. Process Orders
4. Quit
Enter Choice: 3

NO NEW ORDERS TO PROCESS.

1. View Inventory
2. New Order
3. Process Orders
4. Quit
Enter Choice: 2

Enter order Quanity: 5

1. Extreme: +77%
2. Expedite: +55%
3. Standard: +33%
Select Ship Speed: 3
Order Confirmed!

1. View Inventory
2. New Order
3. Process Orders
4. Quit
Enter Choice: 3

------------------------------------------------------------------------
|TckNum | RushStat| Qty|  %MrkUp|  $MrkUp|  CstTotal|  BizCost| BizPrft|
------------------------------------------------------------------------
|    100|        3|   5|    0.33|    9.16|     36.91|    17.75|   19.16|
------------------------------------------------------------------------
Stock Qty: 25
Orders Processed: 1


1. View Inventory
2. New Order
3. Process Orders
4. Quit
Enter Choice: 3

NO NEW ORDERS TO PROCESS.

1. View Inventory
2. New Order
3. Process Orders
4. Quit
Enter Choice: 4


PROGRAM TERMINATED



1. View Inventory
2. New Order
3. Process Orders
4. Quit
Enter Choice: 1

----------------------------------------
|ItemID|  Qty|   Price|    Cost| Profit|
----------------------------------------
|widg  |   30|    5.55|    3.55|   2.25|
----------------------------------------

1. View Inventory
2. New Order
3. Process Orders
4. Quit
Enter Choice: 2

Enter order Quanity: 5

1. Extreme: +77%
2. Expedite: +55%
3. Standard: +33%
Select Ship Speed: 2
Order Confirmed!

1. View Inventory
2. New Order
3. Process Orders
4. Quit
Enter Choice: 2

Enter order Quanity: 6

1. Extreme: +77%
2. Expedite: +55%
3. Standard: +33%
Select Ship Speed: 3
Order Confirmed!

1. View Inventory
2. New Order
3. Process Orders
4. Quit
Enter Choice: 2

Enter order Quanity: 7

1. Extreme: +77%
2. Expedite: +55%
3. Standard: +33%
Select Ship Speed: 1
Order Confirmed!

1. View Inventory
2. New Order
3. Process Orders
4. Quit
Enter Choice: 2

Enter order Quanity: 8

1. Extreme: +77%
2. Expedite: +55%
3. Standard: +33%
Select Ship Speed: 1
Order Confirmed!

1. View Inventory
2. New Order
3. Process Orders
4. Quit
Enter Choice: 1

----------------------------------------
|ItemID|  Qty|   Price|    Cost| Profit|
----------------------------------------
|widg  |    4|    5.55|    3.55|   2.25|
----------------------------------------

1. View Inventory
2. New Order
3. Process Orders
4. Quit
Enter Choice: 2

Enter order Quanity: 3

1. Extreme: +77%
2. Expedite: +55%
3. Standard: +33%
Select Ship Speed: 2
Order Confirmed!

1. View Inventory
2. New Order
3. Process Orders
4. Quit
Enter Choice: 1

----------------------------------------
|ItemID|  Qty|   Price|    Cost| Profit|
----------------------------------------
|widg  |    1|    5.55|    3.55|   2.25|
----------------------------------------


1. View Inventory
2. New Order
3. Process Orders
4. Quit
Enter Choice: 2

Enter order Quanity: 2

INSUFFICIENT INVENTORY. CURRENT INVENTORY CNT: 1

Enter order Quanity: 1

1. Extreme: +77%
2. Expedite: +55%
3. Standard: +33%
Select Ship Speed: 2
Order Confirmed!

1. View Inventory
2. New Order
3. Process Orders
4. Quit
Enter Choice: 3

------------------------------------------------------------------------
|TckNum | RushStat| Qty|  %MrkUp|  $MrkUp|  CstTotal|  BizCost| BizPrft|
------------------------------------------------------------------------
|    102|        1|   7|    0.77|   29.91|     68.76|    24.85|   43.91|
|    103|        1|   8|    0.77|   34.19|     78.59|    28.40|   50.19|
|    105|        2|   1|    0.55|    3.05|      8.60|     3.55|    5.05|
|    100|        2|   5|    0.55|   15.26|     43.01|    17.75|   25.26|
|    104|        2|   3|    0.55|    9.16|     25.81|    10.65|   15.16|
|    101|        3|   6|    0.33|   10.99|     44.29|    21.30|   22.99|
------------------------------------------------------------------------
Stock Qty: 0
Orders Processed: 6


1. View Inventory
2. New Order
3. Process Orders
4. Quit
Enter Choice: 4


PROGRAM TERMINATED
*/