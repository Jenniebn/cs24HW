#include "Dictionary.h"
#include <iostream> 
#include <vector>
#include <sstream>
#include <cmath>
#include<numeric>
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

Heap Dictionary::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const{
    
    vector<Point> location;
    vector<float> score;
    size_t num = 31;
    float d = 0;
    float s = 0;
    float wordScore = 0;
    
    Heap heap(maxcount);
    heap.push("nothing", 0);
    for (auto word : mWords){
        if (word.length() == points.size()){
            for (size_t i = 0; i < word.length(); i++){
                location.push_back(QWERTY[(word[i] & num) - 1]); // c - 'a'
            }
            for (size_t j = 0; j < word.length(); j++){
                d = sqrt(pow((points[j].x - location[j].x), 2) + pow((points[j].y - location[j].y), 2));
                s = 1 / (10 * pow(d, 2) + 1);
                score.push_back(s);
            }
            wordScore = accumulate(score.begin(), score.end(), 0.0) / score.size();
            if ((wordScore >= cutoff) && (wordScore > heap.top().score)){
                heap.pushpop(word, wordScore);
            }
            location.clear();
            score.clear();
        }
    }
    return heap;
}
