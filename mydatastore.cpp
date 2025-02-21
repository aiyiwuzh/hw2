#include "mydatastore.h"
#include "user.h"
#include "util.h"
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <iterator>
#include <queue>
#include <algorithm>
#include <fstream>

using namespace std;
void displayProducts(vector<Product*>& hits);

// constructor
MyDataStore::MyDataStore() {    }

// destructor
MyDataStore::~MyDataStore() {   

    // delete all created products
    for (map<string, Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
        delete it->second;
    }

    // delete all created users
    for (map<string, User*>::iterator it2 = users_.begin(); it2 != users_.end(); ++it2)
    {
        delete it2->second;
    }
}

// adds a product to the datastore
void MyDataStore::addProduct(Product* p)
{
    // store product in products_ map 
    products_[p->getName()] = p; 

    // get the product's keywords
    set<string> keywords = p->keywords();

    // insert the product into map of keywords
    for (set<string>::iterator it = keywords.begin(); it != keywords.end(); ++it) {
        keywordsMap_[convToLower(*it)].insert(p);
    }
}

// adds a user to the datastore
void MyDataStore::addUser(User* u)
{
    users_[u->getName()] = u;
}

// searches for products 
// AND = 0 
// OR = 1
vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
    // holds the search results
    vector<Product*> hits;
    set<Product*> results;
    
    // AND search: products will hit if it matches all the search keywords
    if (type == 0) 
    {
        bool firstTerm = true;

        for (vector<string>::iterator it = terms.begin(); it != terms.end(); ++it)
        {
            if (keywordsMap_.find(*it) != keywordsMap_.end())
            {
                if (firstTerm) {
                    results = keywordsMap_[*it];
                    firstTerm = false; 
                }
                else {
                    results = setIntersection(results, keywordsMap_[*it]);
                }
            }
            else {
                results.clear();
                break;
            }
        }
    }
    // OR search: products will hit if it contains any of the search keywords
    else if (type == 1) 
    {
        for (vector<string>::iterator it2 = terms.begin(); it2 != terms.end(); ++it2)
        {
            results = setUnion(results, keywordsMap_[*it2]);
        }
    }

    // add results to the hits vector 
    for (set<Product*>::iterator it = results.begin(); it != results.end(); ++it)
    {
        hits.push_back(*it);
    }

    hits_ = hits;
    return hits_; 
}

// dumps to the database file 
void MyDataStore::dump(ostream& ofile) 
{
    // product dump
    ofile << "<products>" << endl;
    for (map<string, Product*>::iterator it = products_.begin(); it != products_.end(); ++it)
    {
        it->second->dump(ofile);
    }
    ofile << "</products>" << endl;

    // user dump
    ofile << "<users>" << endl;
    for (map<string, User*>::iterator it2 = users_.begin(); it2 != users_.end(); ++it2)
    {
        it2->second->dump(ofile);

    }
    ofile << "</users>" << endl;
}

// adds an item from search to cart
void MyDataStore::addToCart(const string& username, int hit_result_index)
{
    // find the user in the system
    map<string, User*>::iterator it = users_.find(username); 
    

    // error msg if user does not exist
    if (it == users_.end())
    {
        cout << "Invalid request" << endl;
        return; 
    }

    // error msg if hit result index is not valid
    if (hit_result_index < 0 || hit_result_index >= static_cast<int>(hits_.size()))
    {
        cout << "Invalid request" << endl;
        return;
    }

    Product* product = hits_[hit_result_index];
    userCarts_[username].push(product);
}

// views an user's cart
// display with numbering in the output
void MyDataStore::viewCart(const string& username)
{
    map<string, User*>::iterator it = users_.find(username);

    // error msg if user does not exist
    if (it == users_.end())
    {
        cout << "Invalid username" << endl;
        return; 
    }

    // get the cart of the user
    queue<Product*>& cart = userCarts_[username];

    // temporary cart to iterate to print out every item in cart
    queue<Product*> tempCart = cart; 
    int i = 1;
    while (!tempCart.empty()) 
    {
        Product* p = tempCart.front();
        cout << "Item " << i++ << "\n" << p->displayString() << endl;
        tempCart.pop(); 
    }
}

// buys the items in a user's cart
void MyDataStore::buyCart(const string& username) 
{
    string lowerUsername = convToLower(username); 
    map<string, User*>::iterator it = users_.find(lowerUsername);
    
    // check if the user exists
    if (it == users_.end()) 
    {
        cout << "Invalid username" << endl;
        return; 
    }

    // get the user's cart
    queue<Product*>& cart = userCarts_[lowerUsername]; 
    User* user = it->second;
    
    // temporary cart to hold items that have not yet been purchased
    queue<Product*> tempCart; 

    while (!cart.empty())
    {
        Product* product = cart.front();
        cart.pop(); 

        // check if product is in stock and the user has enough balance
        if (product->getQty() > 0 && user->getBalance() >= product->getPrice())
        {
            product->subtractQty(1);
            user->deductAmount(product->getPrice());
        }
        else 
        {
            // leave unpurchased items in temp cart
            tempCart.push(product); 
        }
    }

    // replace old cart with the updated one
    userCarts_[lowerUsername] = tempCart;
}


// quits and saves datastore to a file 
void MyDataStore::quit(const string& filename)
{
    ofstream file(filename);
    dump(file);
}