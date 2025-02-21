#include <sstream>
#include <iomanip>
#include <cctype>
#include "clothing.h"
#include "util.h"

using namespace std;

// constructor list
Clothing::Clothing(const string& category, const string& name, double price, int qty, const string& size, const string& brand)
    : Product("clothing", name, price, qty), size_(size), brand_(brand) {}

// destructor
Clothing::~Clothing() { }

// keywords implementation
// for clothing: name of item & words in the brand should be searchable
set<string> Clothing::keywords() const
{
    set<string> clothingKeywords;

    // item name keyword(s)
    set<string> nameSet = parseStringToWords(name_);
    clothingKeywords.insert(nameSet.begin(), nameSet.end());

    // clothing brand keyword(s)
    set<string> brandSet = parseStringToWords(brand_);
    clothingKeywords.insert(brandSet.begin(), brandSet.end());

    return clothingKeywords;
}

// display string implementation
// creates a string to display the product info for the keyword hit
string Clothing::displayString() const
{
    stringstream ss;
    ss << name_ << endl;
    ss << "Size: " << size_ << " " <<"Brand: " << brand_ << endl; 
    ss << price_ << " " << qty_ << " left." ;

    return ss.str();

}

// dump implementation
void Clothing::dump(ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n"
        << size_ << "\n" << brand_ << endl;
}
