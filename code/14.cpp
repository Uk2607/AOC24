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

int R = 101, C = 103; // for 14.in
// int R = 11, C = 7; // for ex.in

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
    int n = arr.size(), t = 100, res = 1;
    vector<pair<int,int>>pos;
    for(auto [p, v]: arr) pos.push_back({p[0], p[1]});
    while(t--) {
        for(int i=0;i<n;i++) {
            pos[i].first = (pos[i].first+arr[i].second[0]+R)%R;
            pos[i].second = (pos[i].second+arr[i].second[1]+C)%C;
        }
    }
    vector<vector<int>>grid(R, vector<int>(C, 0));
    for(pair<int, int>p: pos) ++grid[p.first][p.second];
    vector<int>quad(4, 0);
    for(int i=0;i<R;i++) {
        for(int j=0;j<C;j++) {
            if(i<R/2 && j<C/2) quad[0]+=grid[i][j];
            else if(i<R/2 && j>C/2) quad[1]+=grid[i][j];
            else if(i>R/2 && j<C/2) quad[2]+=grid[i][j];
            else if(i>R/2 && j>C/2) quad[3]+=grid[i][j];
            else continue;
        }
    }
    for(int x: quad) res = res * x;
    cout<<"PART1: "<<res<<"\n";
}

void part2(vector<pair<vector<int>, vector<int>>>arr) {
    int n = arr.size(), t = 100, step = 0;
    vector<pair<int,int>>pos;
    for(auto [p, v]: arr) pos.push_back({p[0], p[1]});
    while(true) {
        set<pair<int,int>>st;
        for(int i=0;i<n;i++) {
            pos[i].first = (pos[i].first+arr[i].second[0]+R)%R;
            pos[i].second = (pos[i].second+arr[i].second[1]+C)%C;
            st.insert(pos[i]);
        }
        ++step;
        if(st.size() == n) break;
    }
    // vector<vector<char>>grid(R, vector<char>(C, ' '));
    // for(pair<int,int>p: pos) grid[p.first][p.second] = '#';
    // for(vector<char>row: grid) {
    //     for(char c: row) cout<<c;
    //     cout<<"\n";
    // }
    cout<<"PART2: "<<step<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "14");
    vector<pair<vector<int>, vector<int>>>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 215987200
    part2(arr); // 8050
}
