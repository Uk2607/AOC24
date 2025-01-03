#include "file_name.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>

using namespace std;

vector<string> get_input(string file_path) {
    string line;
    vector<string>arr;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return arr;
    }

    while(getline(file, line)) arr.push_back(line);
    file.close();

    return arr;
}

int search_XMAS(vector<string>&arr, int i, int j, int r, int c) {
    int res = 0;

    if(i>2) { // can go up
        if(arr[i-1][j] == 'M' && arr[i-2][j] == 'A' && arr[i-3][j] == 'S') ++res;
        if(j>2) { // go left
            if(arr[i-1][j-1] == 'M' && arr[i-2][j-2] == 'A' && arr[i-3][j-3] == 'S') ++res;
        }
        if(j<c-3) { // go right
            if(arr[i-1][j+1] == 'M' && arr[i-2][j+2] == 'A' && arr[i-3][j+3] == 'S') ++res;
        }
    }
    if(j>2) { // go left
        if(arr[i][j-1] == 'M' && arr[i][j-2] == 'A' && arr[i][j-3] == 'S') ++res;
    }
    if(j<c-3) { // go right
        if(arr[i][j+1] == 'M' && arr[i][j+2] == 'A' && arr[i][j+3] == 'S') ++res;
    }
    if(i<r-3) { // can go down
        if(arr[i+1][j] == 'M' && arr[i+2][j] == 'A' && arr[i+3][j] == 'S') ++res;
        if(j>2) { // go left
            if(arr[i+1][j-1] == 'M' && arr[i+2][j-2] == 'A' && arr[i+3][j-3] == 'S') ++res;
        }
        if(j<c-3) { // go right
            if(arr[i+1][j+1] == 'M' && arr[i+2][j+2] == 'A' && arr[i+3][j+3] == 'S') ++res;
        }
    }

    return res;
}

void part1(vector<string>arr) {
    int res=0, r = arr.size(), c = arr[0].length();
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            if(arr[i][j] == 'X')
                res += search_XMAS(arr, i, j, r, c);
    
    cout<<"PART1: "<<res<<"\n";
}

bool search_X_MAS(vector<string>&arr, int i, int j, int r, int c) {
    if(((arr[i-1][j-1] == 'M' && arr[i+1][j+1] == 'S') || (arr[i-1][j-1] == 'S' && arr[i+1][j+1] == 'M')) && 
    ((arr[i-1][j+1] == 'M' && arr[i+1][j-1] == 'S') || (arr[i-1][j+1] == 'S' && arr[i+1][j-1] == 'M'))) return true;
    return false;
}

void part2(vector<string>arr) {
    int res=0, r = arr.size(), c = arr[0].length();
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            if(arr[i][j] == 'A')
                if((i>0 && i<r-1 && j>0 && j<c-1) && search_X_MAS(arr, i, j, r, c)) ++res;
    
    cout<<"PART2: "<<res<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "04");
    vector<string>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 2639
    part2(arr); // 2005
}
