#include <iostream> // for cout, cin
#include <string>
using namespace std;

string sentence(string sent);

string sentence(string sent){
    int arraysize = 0;
    int substringB = 0;
    int substringE = 0;
    int size = sent.length();
    for (int i = 0; i < size; i++){
        if (isalnum(sent[i])){
            substringE ++;
        }
        else if (isspace(sent[i]) || ispunct(sent[i])){
            if (substringE != 0){
                substringE = 0;
                arraysize += 2;
            }
            else{
                arraysize ++;
            }
        }
    }
    string arrayR[arraysize];
    int n = 0;
    substringE = 0;
    for (int j = 0; j < size; j++){
        if (isalnum(sent[j])){
            substringE ++;
        }
        else if (isspace(sent[j]) || ispunct(sent[j])){
            if (substringE != 0){
                arrayR[n] = sent.substr(substringB, substringE);
                substringB = j + 1;
                arrayR[n + 1] = sent[j];
                substringE = 0;
                n += 2;
            }
            else{
                arrayR[n] = sent[j];
                n++;
                substringB = j + 1;
            }
        }
    }
    string newString = "";
    for (int k = 0; k <arraysize; k++){
        reverse(arrayR[k].begin(), arrayR[k].end());
        newString += arrayR[k];
    }
    return newString;
}

int main( )
{
    string input;
    getline(cin, input);
    cout << sentence(input) << endl;

    
    return 0;
}

