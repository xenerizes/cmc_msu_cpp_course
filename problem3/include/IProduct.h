#include "IShop.h"

class IProduct {
public:
    IProduct(double p) noexcept;
    double GetPrice() const;
    void ChangePrice(double p);

private:
    double _price;
};

