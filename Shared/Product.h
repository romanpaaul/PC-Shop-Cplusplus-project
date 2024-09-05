#include <string>
#pragma once

using namespace std;

class Product {

private:
  string category;
  string name;
  string barcode;
  int quantity;
  double price;

public:

  Product(string category = "default", string name = "default", string barcode = "default", int quantity=0, double price=0) {
    this->category = category;
    this->name = name;
    this->barcode = barcode;
    this->quantity = quantity;
    this->price = price;
  }

  double getPrice() {
    return this->price;
  }
  int getQuantity() {
    return this->quantity;
  }
  string getBarcode() {
    return this->barcode;
  }
  string getName() {
    return this->name;
  }
  string getCategory() {
    return this->category;
  }

  void setCategory(string newCategory) {
    this->category = newCategory;
  }
  void setPrice(double newPrice) {
    this->price = newPrice;
  }
  void setName(string newName) {
    this->name = newName;
  }
  void updateQuantity(int value) {
    if(this->quantity > 0) {
      if(value < 0 && this->quantity + value < 0)
        this->quantity = 0;
      else
        this->quantity += value;
    }
  }
  void setBarcode(string newBarcode) {
    this->barcode = newBarcode;
  }
  void setQuantity(int newQuantity) {
    this->quantity = newQuantity;
  }

};

