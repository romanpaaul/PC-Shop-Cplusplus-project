#include <iostream>
#include <string.h>
#include <fstream>
#include <limits>
#include "App1.cpp"
#include "App2.cpp"

using namespace std;

// fisierul main reprezinta un exemplu de interactiune cu magazinul online
// user-ul are acces la stoc si de acolo poate creea o comanda
// comanda respectiva va fi scrisa in fisier

vector<Product*> stock;
vector<Order*> orders;
vector<Product*> basket;


Data today = Data(7, 6, 2023);

Store Store1 = Store("Store1", "0001", stock, orders);

vector<Product*> readStock() {
  ifstream fin("stock.txt");

  vector<Product*> stockToBeReturned;
  int number_of_products;
  fin >> number_of_products;
  fin.ignore(numeric_limits<streamsize>::max(), '\n');
  for (int i = 0; i < number_of_products; i++) {
    string category, name, barcode;
    double price;
    int quantity;

    getline(fin, category);
    getline(fin, name);
    getline(fin, barcode);
    fin >> price;
    fin >> quantity;

    stockToBeReturned.push_back(new Product(category, name, barcode, quantity, price));
    fin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  fin.close();
  return stockToBeReturned;
}

vector<Order*> readOrders(Store& store) {
  ifstream fin("orders.txt");

  vector<Order*> ordersToBeReturned;
  int number_of_orders;
  fin >> number_of_orders;
  fin.ignore(numeric_limits<streamsize>::max(), '\n');

  for (int i = 0; i < number_of_orders; i++) {
    int orderNumber;
    fin >> orderNumber;
    fin.ignore(numeric_limits<streamsize>::max(), '\n');

    int number_of_products;
    fin >> number_of_products;
    fin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<Product*> products;

    for (int j = 0; j < number_of_products; j++) {
      string barcode;
      fin >> barcode;

      Product* product = store.getProductByBarcode(barcode);
      if (product != nullptr) {
        products.push_back(product);
      }
    }

    Order* order = new Order(orderNumber, products);
    ordersToBeReturned.push_back(order);
    fin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  fin.close();
  return ordersToBeReturned;
}




int main(int argc, char* argv[]) {
  Store1.setStock(readStock());
  Store1.setOrders(readOrders(Store1));
  if (argc < 2) {
    cout << "Usage: ./main.exe <command>" << endl;
    cout << "Available commands: -display_products, -display_category, -display_order -change_category, -add_component, -change_component, -add_product, -create_order," << endl;
    return 1;
  }
  string command = argv[1];
  
  if(command == "-display_products"){
    displayProducts(Store1);
  }
  else if (command == "-delete_category") {
    if (argc < 3) {
      cout << "Invalid command. Usage: ./main.exe -delete_category <category>" << endl;
      return 1;
    }
    string category = argv[2];
    deleteCategory(Store1, category);
    return 0;
  }
  else if (command == "-change_category") {
    if (argc < 4) {
      cout << "Invalid command. Usage: ./main.exe -change_category <category> <new_category>" << endl;
      return 1;
    }
    string category = argv[2];
    string newCategory = argv[3];
    changeCategory(Store1, category, newCategory);
    return 0;
  }
  else if (command == "-add_component") {
    if (argc < 7) {
      cout << "Invalid command. Usage: ./main.exe -add_component <category> <product_name> <barcode> <quantity> <price>" << endl;
      return 1;
    }
    string category = argv[2];
    string productName = argv[3];
    string barcode = argv[4];
    int quantity = atoi(argv[5]);
    double price = atof(argv[6]);
    addProduct(Store1, category, productName, barcode, quantity, price);
    return 0;
  }

  else if (command == "-delete_component") {
    if (argc < 3) {
      cout << "Invalid command. Usage: ./main.exe -delete_component <barcode>" << endl;
      return 1;
    }
    string barcode = argv[2];
    deleteProduct1(Store1, barcode);
    return 0;
  }

  else if (command == "-change_component") {
    if (argc < 5) {
      cout << "Invalid command. Usage: ./main.exe -change_component <barcode> <type> <value_to_be_modified>" << endl;
      return 1;
    }
    string barcode = argv[2];
    string type = argv[3];
    string value_to_be_modified = argv[4];
    ModifyProduct(Store1, barcode, type, value_to_be_modified);
    return 0;
  }

  else if (command == "-add_product") {
    if (argc < 4) {
      cout << "Invalid command. Usage: ./main.exe -add_product <OrderNumber> <Barcode>" << endl;
      return 1;
    }
    int OrderNumber = stoi(argv[2]);
    string Barcode = argv[3];
    addToOrder(Store1, OrderNumber, Barcode);
    return 0;
  }

  else if (command == "-change_product_byOrder") {
    if (argc < 5) {
      cout << "Invalid command. Usage: ./main.exe -change_product_byOrder <OrderNumber> <Barcode> <NewBarcode>" << endl;
      return 1;
    }
    int OrderNumber = stoi(argv[2]);
    string Barcode = argv[3];
    string NewBarcode = argv[4];
    modifyProduct(Store1, OrderNumber, Barcode, NewBarcode);
    return 0;
  }

  else if (command == "-delete_product") {
    if (argc < 4) {
      cout << "Invalid command. Usage: ./main.exe -delete_product <OrderNumber> <Barcode>" << endl;
      return 1;
    }
    int OrderNumber = stoi(argv[2]);
    string Barcode = argv[3];
    deleteProduct2(Store1, OrderNumber, Barcode);
    return 0;
  }

  else if (command == "-create_order") {
    if (argc < 4) {
      cout << "Invalid command. Usage: ./main.exe -create_order <OrderNumber> <Date> <Product1> <Product2> ..." << endl;
      return 1;
    }

    int OrderNumber = stoi(argv[2]);
    string Date = argv[3];
    vector<Product*> basket;
    for (int i = 4; i < argc; ++i) {
      string Barcode = argv[i];
      Product* product = Store1.getProductByBarcode(Barcode);
      if (product == nullptr) {
        cout << "Invalid product barcode: " << Barcode << endl;
        return 1;
      }
      basket.push_back(product);
    }
    Data orderDate; 
    createOrder(Store1, basket, OrderNumber, orderDate);
    return 0;
}
else if(command == "-display_category"){
  if (argc < 4){
    cout << "Invalid command. Usage: ./main.exe -display_category <Store> <type>" << endl;
    return 1;
  }
  string store = argv[2];
  string type = argv[3];
  displayCategory(Store1, type);
}
else if(command == "-display_order"){
  if(argc < 4){
    cout << "Invalid command. Usage: ./main.exe -display_order <store>, <orderNumber>" << endl;
    return 1;
  }
  string store = argv[2];
  int orderNumber = stoi(argv[3]);
  displayOrder(Store1, orderNumber);
}
else if(command == "-help"){
  cout << "Available commands: -display_products, -display_category, -display_order, -change_category, -add_component, -change_component, -add_product, -create_order," << endl;
  cout << "Usage: ./main.exe -display_products" << endl;
  cout << "Usage: ./main.exe -display_category <store> <type>" << endl;
  cout << "Usage: ./main.exe -display_order <store>, <orderNumber>" << endl;
  cout << "Usage: ./main.exe -change_category <category> <new_category>" << endl;
  cout << "Usage: ./main.exe -add_component <category> <product_name> <barcode> <quantity> <price>" << endl;
  cout << "Usage: ./main.exe -change_component <barcode> <type> <value_to_be_modified>" << endl;
  cout << "Usage: ./main.exe -add_product <OrderNumber> <Barcode>" << endl;
  cout << "Usage: ./main.exe -create_order <OrderNumber> <Date> <Product1> <Product2> ..." << endl;
  }

  else {
    cout << "Invalid command. Usage: ./main.exe <command>" << endl;
    cout << "Available commands: -display_products, -display_category, -display_order, -change_category, -add_component, -change_component, -add_product, -create_order" << endl;
    return 1;
  }
  
  return 0;
}

