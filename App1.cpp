#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include ".\Shared\Store.h"

using namespace std;

void UpdateStock(Store store) {
  ofstream fout("stock.txt");
  int number_of_products = 0;
  for(auto el : store.getStock())
    number_of_products += 1;

  fout << number_of_products << endl;
  for(auto el : store.getStock()) {
    fout << el->getCategory() << endl;
    fout << el->getName() << endl;
    fout << el->getBarcode() << endl;
    fout << el->getPrice() << endl;
    fout << el->getQuantity() << endl;
  }

  fout.close();
}

void displayCategory(Store Store1, const string type) {
  // functia va returna un container elementele care sunt de categoria data ca parametru "type"
  ofstream fout("filtered.txt");
  vector<Product*> filtered;
  for(auto el : Store1.getStock()) {
    if(el->getCategory() == type)
      filtered.push_back(el);
  }
  for(auto el: filtered){
    fout << el->getCategory() << endl;
    fout << el->getName() << endl;
    fout << el->getBarcode() << endl;
    fout << el->getPrice() << endl;
    fout << el->getQuantity() << endl;
  }
  fout.close();
}

void displayProducts(Store Store1) {
  if(Store1.getStock().empty()) {
    cout << "ie gol";
  } else {
    for(auto el : Store1.getStock()) {
      cout << el->getName() << " , pret=" << el->getPrice() << endl;
    }
  }
}

void changeCategory(Store &Store1, const string category, const string newCategory) {
  for(auto el : Store1.getStock()) {
    if(el->getCategory() == category)
      el->setCategory(newCategory);
  }
  UpdateStock(Store1);
}

bool check_category(Product *product, string category) {
  if(product->getCategory() == category) return true;
  return false;
}

void deleteCategory(Store& Store1, string category) {
    vector<Product*> stockCopy = Store1.getStock();
      stockCopy.erase(remove_if(stockCopy.begin(), stockCopy.end(), [&](Product* product) {
        return product->getCategory() == category;
    }), stockCopy.end());
    UpdateStock(Store1);
}


void addProduct(Store &Store1, string category, string product_name, string barcode, int quantity, double price) {
  Store1.addProduct(new Product(category, product_name, barcode, quantity, price));
  UpdateStock(Store1);
}


void deleteProduct1(Store& Store1, const string& barcode) {
    vector<Product*> stockCopy = Store1.getStock(); 

    auto it = remove_if(stockCopy.begin(), stockCopy.end(), [&](Product* product) {
        return product->getBarcode() == barcode;
    });

    if (it != stockCopy.end()) {
        stockCopy.erase(it, stockCopy.end());
        UpdateStock(Store1);
    } else {
        cout << "Product not found!" << endl;
    }
}


// aceasta functie va modifica in functie de un string, care va identifica ce atribut al produsului vom modifica
void ModifyProduct(Store& Store1, string &barcode, string type, string value_to_be_modified) {
  // type - categorie, barcode, quantity, nume, pret
  // value_to_be_modified - valoarea care va fi luata de catre atributul "type" a produsului instantiat
  if(Store1.getProductByBarcode(barcode) != nullptr) {

    if(type == "barcode") {
      Store1.getProductByBarcode(barcode)->setBarcode(value_to_be_modified);
    } else if(type == "category") {
      Store1.getProductByBarcode(barcode)->setCategory(value_to_be_modified);
    } else if(type == "price") {
      Store1.getProductByBarcode(barcode)->setPrice(stod(value_to_be_modified));
    } else if(type == "name") {
      Store1.getProductByBarcode(barcode)->setName(value_to_be_modified);
    } else if(type == "quantity") {
      Store1.getProductByBarcode(barcode)->setQuantity(stoi(value_to_be_modified));
    } else {
      cout << "The category you're trying to modify does not exist!" << endl;
    }

  } else {
    return ;
  }
  UpdateStock(Store1);
}