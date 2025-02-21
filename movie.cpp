#include <sstream>
#include <iomanip>
#include <cctype>
#include "movie.h"
#include "util.h"

using namespace std;

// constructor list
Movie::Movie(const string& category, const string& name, double price, int qty, const string& genre, const string& rating)
    : Product("movie", name, price, qty), genre_(genre), rating_(rating) {}

// destructor
Movie::~Movie() { }

// keywords implementation
set<string> Movie::keywords() const
{
    set<string> movieKeywords;

    // item name keyword(s)
    set<string> nameSet = parseStringToWords(name_);
    movieKeywords.insert(nameSet.begin(), nameSet.end());

    // genre keyword(s)
    movieKeywords.insert(genre_);

    return movieKeywords;
}

// display string implementation
// creates a string to display the product info for the keyword hit
string Movie::displayString() const
{
    stringstream ss;
    ss << name_ << endl;
    ss << "Genre: " << genre_ << " " << "Rating: " << rating_ << endl; 
    ss << price_ << " " << qty_ << " left." ;
    return ss.str();

}

// dump implementation
void Movie::dump(ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n"
        << genre_ << "\n" << rating_ << endl;
}
