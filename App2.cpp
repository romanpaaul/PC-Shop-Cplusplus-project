#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include ".\Shared\Store.h"

using namespace std;

void UpdateOrders(Store& store) {
  ofstream fout("orders.txt");
  int number_of_orders = store.getOrders().size();
  fout << number_of_orders << endl;

  for (auto order : store.getOrders()) {
    fout << order->getOrderNumber() << endl;

    int number_of_products = order->getOrderProducts().size();
    fout << number_of_products << endl;

    for (auto product : order->getOrderProducts()) {
      fout << product->getBarcode() << endl;
    }
  }

  fout.close();
}

void displayOrder(Store &store, const int OrderNumber) {
  if(store.getOrderByNumber(OrderNumber) != nullptr) {
    cout << OrderNumber << endl;
    for(auto el : store.getOrderByNumber(OrderNumber)->getOrderProducts()) {
      cout << el->getName() << endl;
    }
  } else {
    return;
  }
}

void createOrder(Store &store, const vector<Product*> &basket, int OrderNumber, const Data &date) {
  vector<Product*> basketCopy = basket;
  Order *toBeReturned = new Order(OrderNumber, basketCopy, date);
  store.addOrder(toBeReturned);

  UpdateOrders(store);
}

void addToOrder(Store &Store1, int OrderNumber, string Barcode) {

  if(Store1.getOrderByNumber(OrderNumber) == nullptr || Store1.getProductByBarcode(Barcode) == nullptr) 
    return;
  
  Store1.getOrderByNumber(OrderNumber)->addProductToOrder(Store1.getProductByBarcode(Barcode));
  
  UpdateOrders(Store1);
}

void deleteProduct2(Store &Store1, const int OrderNumber, const string Barcode) {

  for(auto it = Store1.getOrderByNumber(OrderNumber)->getOrderProducts().begin(); it != Store1.getOrderByNumber(OrderNumber)->getOrderProducts().end(); ++it) {
    if((*it)->getBarcode() == Barcode) {
      delete *it;
      Store1.getOrderByNumber(OrderNumber)->getOrderProducts().erase(it);
      UpdateOrders(Store1);
      return;
    }
  }

  cout << "Product not found!" << endl;
}

void modifyProduct(Store &Store1, const int OrderNumber, const string Barcode, const string newBarcode) {
  bool productFound = false;

  for(auto el : Store1.getOrderByNumber(OrderNumber)->getOrderProducts()) {
    if(el->getBarcode() == Barcode) {
      deleteProduct2(Store1, OrderNumber, Barcode);
      addToOrder(Store1, OrderNumber, newBarcode);
      UpdateOrders(Store1);
      productFound = true;
      return;
    }
  }

  if(productFound == false) {
    cout << "Product with the barcode provided not found!" << endl;
  }

}