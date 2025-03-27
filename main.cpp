#include <iostream>
#include<string>
using namespace std;
const int Max = 100;
struct customer {
    int Id;
    string password;
    string name;
    string phone;
    string location;
};
customer customers[Max];
int customer_count = 0;
struct date {
    int day, month, year;
};
struct product {
    int code, quantity;
    string name;
    string Category;
    date productionDate;
    date expirationDate;
    double price;
};
product products[Max];
int product_count = 0;
struct order {
    int customerId;
    string productName[Max];
    double totalPrice;
    int numProducts;
    ss
};