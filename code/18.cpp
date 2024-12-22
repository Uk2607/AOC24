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

const int N = 7, K = 12; // for example
// const int N = 71, K = 1024; // for input

vector<pair<int,int>>dir = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

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

int min_path(vector<vector<char>>&grid, pair<int,int>&me, vector<vector<bool>>&vis) {
    return -1;
}

void part1(vector<pair<int,int>>arr) {
    vector<vector<char>>grid(N, vector<char>(N, ' '));
    vector<vector<bool>>vis(N, vector<bool>(N, false));
    for(int i=0;i<K;i++) grid[arr[i].first][arr[i].second] = '#';
    pair<int,int>me={0, 0};
    int res = min_path(grid, me, vis);
    cout<<"PART1: "<<res<<"\n";
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
