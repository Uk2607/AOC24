#include "file_name.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
#include<set>

#define ll long long int
#define ull unsigned long long int
using namespace std;

vector<int> get_input(string file_path) {
    string line;
    vector<int>arr;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return arr;
    }

    getline(file, line);
    file.close();

    stringstream ss(line);
    int x;
    while(ss>>x) arr.push_back(x);

    return arr;
}

void print(vector<int>&arr) {
    cout<<"\n";
    for(int x: arr)
        cout<<x<<" ";
    cout<<"\n";
}

void part1(vector<int>arr) {
    print(arr);
}

void part2(vector<int>arr) {
    ;
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "11");
    vector<int>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 
    part2(arr); // 
}
