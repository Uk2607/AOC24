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

vector<pair<int,int>> get_input(string file_path) {
    string line;
    vector<pair<int,int>>arr;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return arr;
    }

    while(getline(file, line)) {
        stringstream ss(line);
        int x, y;
        char c;
        ss>>x>>c>>y;
        arr.push_back({x, y});
    }
    file.close();

    return arr;
}

void print(vector<pair<int,int>>&arr) {
    cout<<"\n";
    for(pair<int,int> p: arr) cout<<p.first<<" "<<p.second<<"\n";
    cout<<"\n";
}

void part1(vector<pair<int,int>>arr) {
    cout<<"PART1: "<<arr.size()<<"\n";
}

void part2(vector<pair<int,int>>arr) {
    cout<<"PART2: "<<arr.size()<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "18");
    vector<pair<int,int>>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 
    part2(arr); // 
}
