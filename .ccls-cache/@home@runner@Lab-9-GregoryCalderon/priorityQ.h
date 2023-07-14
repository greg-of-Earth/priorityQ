#ifndef PRIORITYQ
#define PRIORITYQ
#include "new_Ord.h"

const int MAX = 50;

class PriorityQ{
  public:
    PriorityQ(int n_QSize=0, int procCnt=0);
    void EnQ(NewOrd&);
    void DeQ();
    int GetQSize();
    bool IsEmptyQ() const;
    void HeapUp(int);
    void HeapDwn(int);
    int GetProcCnt() const;

  

    void Print();

  private:
    NewOrd OrdQ[MAX];
    int QSize;    
    int procCnt;
    //int prntIndx=1;


};

#endif