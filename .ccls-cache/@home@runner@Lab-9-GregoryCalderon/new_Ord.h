#ifndef NEW_ORD
#define NEW_ORD
#include "inventory.h"
#include <string>
using namespace std;



class NewOrd {
  public:
    NewOrd(int ordQty=0, int shipSpd = 3, int trckNum=100, double shipTotal=0, double ordTotal=0, double bizCost=0, double bizPrft=0);
    NewOrd(const NewOrd& ogOrd);
    NewOrd& operator=(const NewOrd& ogOrd);
    void SetOrd(int, int, int, double, double, double, double);
    void SetQty(int);
    void SetShipSpeed(int);
    void SetTrackNum(int);
    void CalcShipTotal(Inventory&);
    void CalcTotal(Inventory& inv);

    //NewOrd GetOrder(int);
    int GetQty() const;
    int GetShipSpd() const;
    int GetTrckNum() const;
    double GetShipTotal() const;
    double GetOrdTotal() const;
    void SetBizCost(Inventory& inv);
    void SetBizPrft(Inventory&);
    double GetBizCost() const;
    double GetBizPrft() const;
    string ToString() const;

    friend class PriorityQ;

  private:
    
    int ordQty;
    int shipSpd;
    int trckNum;
    double ordTotal;
    double shipTotal;
    double bizCost;
    double bizPrft;
    
    const string ShipStr[3]={"Extrm", "Expd", "Stnd"};
    const double ShipRate[3]={77,55,33};
};


#endif