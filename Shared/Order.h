#include "Product.h"
#include "Data.h"
#include <vector>
#pragma once

class Order {

private:
  int number;
  vector<Product*> products;
  Data date;
  double total;

public:
  Order(int number = 0, vector<Product*> products = {}, Data date = Data(1, 1, 2023)) {
    this->number = number;
    this->products = products;
    this->date = date;
    for(auto el : products) {
      this->total += el->getPrice();
    }
    this->total /= double(products.size());
  }

  void addProductToOrder(Product *product) {
    this->products.push_back(product);
  }
  
  void setStock(vector<Product*> newProducts) {
    this->products = newProducts;
    this->total = 0;
    for(auto el : newProducts) {
      this->total += el->getPrice();
    }
    this->total /= double(newProducts.size());
  }

  Data getOrderDate() {
    return this->date;
  }
  int getNumberOfProducts() {
    return this->products.size();
  }
  int getOrderNumber() {
    return this->number;
  }
  vector<Product*> getOrderProducts() {
    return this->products;
  }
};