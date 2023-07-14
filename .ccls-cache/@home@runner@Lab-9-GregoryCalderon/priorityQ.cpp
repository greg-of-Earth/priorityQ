#include "priorityQ.h"
#include <cmath>
#include <iostream>
#include <string>
#include <iomanip>


// construtor 
PriorityQ::PriorityQ(int n_QSize, int n_procCnt){
  QSize = n_QSize;
  procCnt= n_procCnt;
}


// add new orders to priority queue
// post: first places new element at end of array (last position of heap) and then bubbles up to create min heap structure by calling HeapUp()
void PriorityQ::EnQ(NewOrd& n_ord){
  int indx = QSize+1;
  if(indx<MAX){
    OrdQ[indx].SetOrd(n_ord.ordQty, n_ord.shipSpd, n_ord.trckNum, n_ord.shipTotal, n_ord.ordTotal, n_ord.bizCost, n_ord.bizPrft);
     HeapUp(indx);
  }
  QSize++;
}

// ensure order of min heap by bubbling up min values 
void PriorityQ::HeapUp(int indx){
  int prntIndx = floor(indx/2);
  
  while(indx>1){
  if(OrdQ[indx].shipSpd < OrdQ[prntIndx].shipSpd) {
    NewOrd temp;
    temp = OrdQ[prntIndx];
    OrdQ[prntIndx] = OrdQ[indx];
    OrdQ[indx] = temp;
    }
    indx=prntIndx;
    prntIndx = floor(indx/2);    
  }
}

//ensures priority ranking and heap order during deque by bubbling down
//bubbled dwn into positon to maintain order 
void PriorityQ::HeapDwn(int indx){
  int chldIndx = 2*indx;
  
  // while not last child in queue
  while(chldIndx <= QSize){

    //if the Lchild ship speed is higher priority than Rchild OR if they have the same priority AND the Lchild was entered into the queue first THEN we have correct order and check next child by incrementing chldIndx
    if(chldIndx < QSize && (OrdQ[chldIndx+1].shipSpd < OrdQ[chldIndx].shipSpd || (OrdQ[chldIndx+1].shipSpd == OrdQ[chldIndx].shipSpd && OrdQ[chldIndx+1].trckNum < OrdQ[chldIndx].trckNum))){
      chldIndx++;
    }
    
    // else we have wrong order and: if Child has higher ship priority than parent OR if they have same ship priority AND child was entered into queue first THEN swap 
    if(OrdQ[chldIndx].shipSpd < OrdQ[indx].shipSpd || (OrdQ[chldIndx].shipSpd == OrdQ[indx].shipSpd && OrdQ[chldIndx].trckNum < OrdQ[indx].trckNum)) {
      NewOrd temp;
      temp = OrdQ[indx];
      OrdQ[indx] = OrdQ[chldIndx];
      OrdQ[chldIndx] = temp;
    }
    indx=chldIndx;
    chldIndx=2*indx;
  }
}


// ensures structure of heap 
// when item is dequed, last item in array (last of heap) is put as the root and passed to HeapDwn() to be put into positon 
void PriorityQ::DeQ(){
  while(!IsEmptyQ()){
    
    cout << OrdQ[1].ToString() << endl;
    if(QSize>1){
        OrdQ[1] = OrdQ[QSize];       
        HeapDwn(1);
    }
    QSize--;
    procCnt++;
  }
}

bool PriorityQ::IsEmptyQ() {
  return QSize==0; 
}

int PriorityQ::GetQSize(){
  return QSize;
}

// track orders processed 
int PriorityQ::GetProcCnt() const {return procCnt;}

// output days order in as to be processed 
void PriorityQ::Print() {
  cout << setfill('-') << setw(72) << "-" << setfill(' ') << "\n|"<< left << "TckNum |" << right <<  setw(10) << "RushStat|" << setw(5) << "Qty|" <<  setw(9) <<"%MrkUp|" <<  setw(9) <<"$MrkUp|"  <<  setw(11) <<"CstTotal|" <<  setw(10) <<"BizCost|" <<  setw(10) <<"BizPrft|\n" << setfill('-') << setw(72) << "-" << setfill(' ') <<'\n';
  
  DeQ();

  cout << setfill('-') << setw(72) << "-" << setfill(' ') << "\n";
}