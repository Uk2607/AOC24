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

vector<pair<string, string>> get_input(string file_path) {
    string line;
    vector<pair<string, string>>arr;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return arr;
    }

    while(getline(file, line))
        arr.push_back({line.substr(0, 2), line.substr(3)});
    file.close();

    return arr;
}

void print(vector<pair<string, string>>&arr) {
    cout<<"\n";
    for(auto [a, b]: arr) cout<<a<<"-"<<b<<"\n";
    cout<<"\n";
}

void part1(vector<pair<string, string>>arr) {
    map<string, vector<string>>mp;
    for(auto [a, b]: arr) {
        mp[a].push_back(b);
        mp[b].push_back(a);
    }
    cout<<"PART1: "<<arr.size()<<"\n";
}

void part2(vector<pair<string, string>>arr) {
    cout<<"PART2: "<<arr.size()<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "23");
    vector<pair<string, string>>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 
    part2(arr); // 
}
