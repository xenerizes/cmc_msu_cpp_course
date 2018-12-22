#pragma once

#include <memory>
#include <mutex>
#include <unordered_map>

struct IProduct;
using IProductPtr = std::shared_ptr< IProduct >;
using IProductWeakPtr = std::weak_ptr< IProduct >;

class IShop {
public:
    explicit IShop(const std::string& name) noexcept;
    void StartSales(IProductWeakPtr p);
    void StopSales(std::string name);
    virtual void ChangePrice(const std::string& name) = 0;

protected:
    std::string _name;
    std::unordered_map< std::string, IProductPtr > _products;
};

using IShopPtr = std::shared_ptr< IShop >;
using IShopWeakPtr = std::weak_ptr< IShop >;
