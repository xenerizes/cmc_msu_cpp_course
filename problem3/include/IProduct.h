#include "IShop.h"

class IProduct {
public:
    IProduct(double p) : _price(p) { }

    double GetPrice() const { return _price; } 

private:
    double _price;
};

