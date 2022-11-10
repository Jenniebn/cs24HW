#include "Dictionary.h"
#include <iostream> 
#include <vector>
#include <sstream>
using namespace std;

Dictionary::Dictionary(std::istream& stream){
    std::string word;
    while(std::getline(stream, word)) {
        for (size_t i = 0; i < word.length(); i++){
            if (isupper(word[i])){
                continue;
            }
        }
        mWords.push_back(word);
    }
}

Heap Dictionary::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const{}