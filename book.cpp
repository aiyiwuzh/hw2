#include <sstream>
#include <iomanip>
#include <cctype>
#include "book.h"
#include "util.h"

using namespace std;

// constructor list
Book::Book(const string& category, const string& name, double price, int qty, const string& author, const string& isbn)
    : Product("book", name, price, qty), author_(author), isbn_(isbn) {}

// destructor 
Book::~Book() { }

// keywords implementation
// for book: book name, author's name, & isbn should be searchable
set<string> Book::keywords() const 
{
    set<string> bookKeywords;

    // book name keyword(s)
    set<string> nameSet = parseStringToWords(name_);
    bookKeywords.insert(nameSet.begin(), nameSet.end());

    // author's name keyword(s)
    set<string> authorSet = parseStringToWords(author_);
    bookKeywords.insert(authorSet.begin(), authorSet.end());

    // isbn keyword
    bookKeywords.insert(isbn_);

    return bookKeywords;

}

// display string implementation
// creates a string to display the product info for the keyword hit
string Book::displayString() const
{
    stringstream ss;
    ss << name_ << endl;
    ss << "Author: " << author_ << " "<< "ISBN: " << isbn_ << endl; 
    ss << price_ << " " << qty_ << " left.";

    return ss.str();

}

// dump implementation
void Book::dump(ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" 
    << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}
