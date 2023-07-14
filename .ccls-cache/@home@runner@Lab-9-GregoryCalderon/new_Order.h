#ifndef NEW_ORDER
#define NEW_ORDER


class NewOrder {
  public:
    NewOrder(int ordQty=0, int shipPriority = 3, int trackingNum=100);
    void SetQty();
    void SetShipSpeed();
    void SetTrackNum();

  private:
    int ordQty;
    int shipPriority;
    int trackingNum = 100;
};


#endif