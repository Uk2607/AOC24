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

vector<pair<int,int>>dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // right->down->left->up

vector<string> get_input(string file_path) {
    string line;
    vector<string>arr;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return arr;
    }

    while(getline(file, line)) {
        arr.push_back(line);
    }
    file.close();

    return arr;
}

void print(vector<string>&arr) {
    cout<<"\n";
    for(string s: arr) {
        for(char c: s)
            cout<<c<<"";
        cout<<"\n";
    }
    cout<<"\n";
}

bool inside(pair<int,int>p, int r, int c) {
    return p.first>=0 && p.first<r && p.second>=0 && p.second<c;
}

int dfs(vector<string>&arr, vector<vector<bool>>&vis, pair<int,int>src, pair<int,int>dest, int r, int c, int res) {
    ;
}

void part1(vector<string>arr) {
    int r = arr.size(), c = arr[0].length();
    pair<int,int>src, dest;
    for(int i=0; i<r; i++)
        for(int j=-0; j<c; j++) {
            if(arr[i][j] == 'S') src = {i, j};
            if(arr[i][j] == 'E') dest = {i, j};
        }
    vector<vector<bool>>vis(r, vector<bool>(c, false));
    int res = dfs(arr, vis, src, dest, r, c, 0);
    cout<<"PART1: "<<arr.size()<<"\n";
}

void part2(vector<string>arr) {
    cout<<"PART2: "<<arr.size()<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "16");
    vector<string>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 
    part2(arr); // 
}
