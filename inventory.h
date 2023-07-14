#ifndef INVENTORY
#define INVENTORY
#include <string>
using namespace std;


class Inventory {
  public:
    Inventory(string="widg", int qty=400, double const price= 10.0, double const cost=5.0, double profit=2.5);

    void SetQty(int);
    void AdjQty(int);
    void SetCost(double);
    string GetName() const;
    int GetQty() const;
    double GetPrice() const;
    double GetCost() const;
    double GetPrft() const;
    void Show();

  friend class NewOrd;

  private:
    string name="widg";
    int qty;
    double price;
    double cost;
    double profit;

};

#endif