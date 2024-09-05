#include "Order.h"
#include <vector>
#pragma once

using namespace std;

class Store {
private:
  string name;
  string id;
  vector<Product*> stock;
  vector<Order*> orders;

public:
  Store(string name, string id, vector<Product*> stock, vector<Order*> orders) {
    this->name = name;
    this->id = id;
    this->stock = stock;
    this->orders = orders;
  }

  void addProduct(Product* product) {
    this->stock.push_back(product);
  }

  void setStock(vector<Product*> stock) {
    this->stock = stock;
  }
  void setOrders(vector<Order*> orders) {
    this->orders = orders;
  }

  void addOrder(Order* order) {
    this->orders.push_back(order);
  }

  vector<Order*> getOrders() {
    return this->orders;
  }
  vector<Product*> getStock() {
    return this->stock;
  }


  Order* getOrderByNumber(int OrderNumber) {
    bool orderFound = false;
    for(auto el : this->getOrders()) {
      if(el->getOrderNumber() == OrderNumber) {
        orderFound == true;
        return el;
      }
    }
    if(orderFound == false) {
      cout << "The order number provided is invalid!";
      return nullptr;
    }
  }

  Product* getProductByBarcode(string barcode) {
    bool productFound = false;

    for(auto el : this->getStock()) {
      if(el->getBarcode() == barcode) {
        if(el->getQuantity() < 1) {
          cout << "Product out of stock!" << endl;
          return nullptr;
        } else {
          productFound = true;
          return el;
        }
      }
    }

    if(productFound == false) {
      return nullptr;
    }
  }

};