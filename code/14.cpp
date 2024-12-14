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

// int R = 101, C = 103; // for 14.in
int R = 11, C = 7; // for ex.in

vector<pair<vector<int>, vector<int>>> get_input(string file_path) {
    string line;
    vector<pair<vector<int>, vector<int>>>arr;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return arr;
    }

    while(getline(file, line)) {
        stringstream ss(line);
        string p, v, s;
        ss>>p>>v;
        p = p.substr(2);
        v = v.substr(2);
        vector<int>P, V;
        stringstream ssp(p), ssv(v);
        while (getline(ssp, s, ',')) P.push_back(stoi(s));
        while (getline(ssv, s, ',')) V.push_back(stoi(s));
        
        arr.push_back({P, V});
    }
    file.close();

    return arr;
}

void print(vector<pair<vector<int>, vector<int>>>&arr) {
    cout<<"\n";
    for(auto [p, v]: arr) {
        cout<<"p: ";
        for(int x: p) cout<<x<<" "; cout<<":: ";
        cout<<"v: ";
        for(int x: v) cout<<x<<" ";
        cout<<"\n";
    }
    cout<<"\n";
}

void part1(vector<pair<vector<int>, vector<int>>>arr) {
    ;
    cout<<"PART1: "<<arr.size()<<"\n";
}

void part2(vector<pair<vector<int>, vector<int>>>arr) {
    cout<<"PART2: "<<arr.size()<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "__");
    vector<pair<vector<int>, vector<int>>>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 
    part2(arr); // 
}
