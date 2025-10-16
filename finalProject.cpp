#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int obtainData(const string filename, vector<int>& x, vector<string>& c, vector<int>& y) {
    ifstream data(filename);
    if (!data.is_open()) {
        cout << "Failed to open data.txt" << endl;
        return 0;
    }
    string line;

    while(getline(data, line)) {
        stringstream currentLine(line);                                                 //stringstream automatically ignores spaces and tabs
        int tempx, tempy;   //initializing the temp variables
        string tempc;       //has to be a string, allows for encoding characters beyond the standard ASCII

        currentLine >> tempx >> tempc >> tempy;     //known value placements, no room for error
        x.push_back(tempx);                         
        c.push_back(tempc);
        y.push_back(tempy);

    }
    data.close();
    return 1;
}

//int createSortedList(string filename) //will define later if needed


int main() {
    vector<int> x;
    vector<int> y;
    vector<string> c; //has to be string because char only holds one byte and the characters are larger than one byte, learned the hard way
    int maxX = 0;
    int maxY = 0;

    if (obtainData("data.tsv", x, c, y) == 0) {
        return 0;
    }
    int i;
    int v = x.size();
    for(i = 0; i < v; ++i) {
       if(x[i] > maxX) {                                                //determining the max X and max Y values for vector size
        maxX = x[i];
       }
       if (y[i] > maxY) {
        maxY = y[i];
       }
    }

    vector<vector<string>> image(maxX+1, vector<string>(maxY+1, " ")); //2d vector, because arrays don't like me, +1 because the max values don't account for the 0 value, had to learn on stack exchange and cplusplus.com, but easier to work with

    for (i = 0; i < v; ++i) {                                          //inputting the values into the 2d vector
        image[x[i]][y[i]] = c[i];   
    }
    int j;
    for (j = 0; j <= maxY; ++j) {
        for(i = 0; i <= maxX; ++i) {
            cout << image[i][j];                                        //outputs a space if there isn't a character initialized in that spot, see image initialization
        }
        cout << endl;
    }

    return 1;
}