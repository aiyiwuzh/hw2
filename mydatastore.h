#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "product.h"
#include "user.h"
#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <queue>

class MyDataStore : public DataStore {
public:
    MyDataStore();
    virtual ~MyDataStore();

    // add product to data store
    void addProduct(Product* p);

    // add user to data store
    void addUser(User* u);

    // search for product
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    // reproduce the database file from the current Products and User values
    void dump(std::ostream& ofile); 

    // add product to cart
    void addToCart(const std::string& username, int hit_result_index);

    // views an user's cart 
    void viewCart(const std::string& username);

    // buys items in cart 
    void buyCart(const std::string& username);

    // quit
    void quit(const std::string& filename);

private:
    std::map<std::string, Product*> products_;
    std::map<std::string, User*> users_;
    std::map<std::string, std::set<Product*>> keywordsMap_;
    std::vector<Product*> hits_; 
    std::map<std::string, std::queue<Product*>> userCarts_;
};

#endif