#ifndef BOOK_H
#define BOOK_H

#include "product.h"
#include <iostream>
#include <string>
#include <set>
#include <algorithm>

// Book inherits from Product
// add on author & isbn
class Book : public Product {
public:
    Book(const std::string& category, const std::string& name, double price, int qty, const std::string& author, const std::string& isbn);
    virtual ~Book();

    /**
     * Returns the appropriate keywords that this product should be associated with
     */
    std::set<std::string> keywords() const;

    /**
     * Returns a string to display the product info for hits of the search
     */
    std::string displayString() const;

    /**
     * Outputs the product info in the database format
     */
    void dump(std::ostream& os) const;

private:
    std::string author_;
    std::string isbn_;
};

#endif