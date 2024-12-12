#include "file_name.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>

using namespace std;

vector<vector<int>> get_input(string file_path) {
    string line;
    vector<vector<int>>arr;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return arr;
    }

    while(getline(file, line)) {
        int x;
        vector<int>t;
        stringstream ss(line);
        while(ss>>x) t.push_back(x);
        arr.push_back(t);
    }
    file.close();

    return arr;
}

bool isSafe(vector<int>v) {
    bool safe = true;
    int n = v.size(), inc = 0;
    for(int i=0;i<n-1;i++)
        inc += (v[i]<=v[i+1]) ? 1 : -1;
    for(int i=1;i<v.size();i++) {
        if(inc>=0) {
            if(v[i]-v[i-1]>3 || v[i]-v[i-1]<1) {safe = false; break;}
        } else {
            if(v[i-1]-v[i]>3 || v[i-1]-v[i]<1) {safe = false; break;}
        }
    }
    return safe;
}

void part1(vector<vector<int>>arr) {
    int x=0;
    for(vector<int>v: arr)
        if(isSafe(v)) ++x;
    cout<<"PART1: "<<x<<"\n";
}

void part2(vector<vector<int>>arr) {
    int x=0;
    for(vector<int>v: arr) {
        bool safe = false;
        int n = v.size();
        for(int i=0;i<n;i++) {
            vector<int>t = v;
            t.erase(t.begin() + i);
            safe = safe | isSafe(t);
        }
        if(safe) ++x;
    }
    cout<<"PART2: "<<x<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "02");
    vector<vector<int>>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 314
    part2(arr); // 373
}
