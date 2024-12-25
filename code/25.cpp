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

vector<vector<string>> get_input(string file_path) {
    string line;
    vector<vector<string>>arr;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return arr;
    }
    vector<string>grid;
    while(getline(file, line)) {
        if(line.length()==0) {
            arr.push_back(grid);
            grid.clear();
            continue;
        }
        grid.push_back(line);
    }
    arr.push_back(grid);

    file.close();

    return arr;
}

void print(vector<vector<string>>&arr) {
    cout<<"\n";
    for(vector<string> v: arr) {
        for(string s: v) cout<<s<<"\n";
        cout<<"\n";
    }
    cout<<"\n";
}

void part1(vector<vector<string>>arr) {
    cout<<"PART1: "<<arr.size()<<"\n";
}

void part2(vector<vector<string>>arr) {
    cout<<"PART2: "<<arr.size()<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "25");
    vector<vector<string>>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 
    part2(arr); // 
}
