#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    // convert all to lowercase for clean comparison
    rawWords = convToLower(rawWords);

    // set to hold the keywords saved
    std::set<std::string> keywords;
    std::string currentWord;

    // iterate through the word to analyze if valid
    for (char c : rawWords)
    {
        if (!isspace(c) && !ispunct(c)) 
        {
            currentWord += c; 
        }
        else 
        {
            if (currentWord.length() >= 2)
            {
                keywords.insert(currentWord);
            }
            currentWord.clear();
        }
    }

    if (currentWord.length() >= 2)
    {
        keywords.insert(currentWord);
    }
    
    return keywords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring

// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
        std::find_if(s.begin(), s.end(), 
            [](unsigned char c) { return !std::isspace(c); }));  // Using lambda function instead of std::ptr_fun
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
        std::find_if(s.rbegin(), s.rend(), 
            [](unsigned char c) { return !std::isspace(c); }).base(), 
        s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
