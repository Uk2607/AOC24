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

vector<pair<int,int>>dir = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

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

void print(vector<string>&arr) {
    cout<<"\n";
    for(string s: arr) {
        for(char c: s)
            cout<<c<<"";
        cout<<"\n";
    }
    cout<<"\n";
}

int dfs(vector<string>&arr, int x, int y, int r, int c, set<pair<int,int>>&st) {
    if(arr[x][y] == '9') {
        st.insert({x, y});
        return 1;
    }
    int res = 0;
    for(pair<int,int>d: dir) {
        int nx = x+d.first, ny = y+d.second;
        if(nx<0 || nx>=r || ny<0 || ny>=c) continue;
        if((arr[nx][ny]-'0')-(arr[x][y]-'0')!=1) continue;
        res += dfs(arr, nx, ny, r, c, st);
    }
    return res;
}

void solve(vector<string>arr) {
    int res1 = 0, res2 = 0, r = arr.size(), c = arr[0].length(), x;
    vector<pair<int,int>>src_coords;
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            if(arr[i][j]=='0') src_coords.push_back({i,j});
    for(pair<int,int>src: src_coords) {
        set<pair<int,int>>st;
        x = dfs(arr, src.first, src.second, r, c, st);
        res1 += st.size();
        res2 += x;
    }
    cout<<"PART1: "<<res1<<"\n";
    cout<<"PART2: "<<res2<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "10");
    vector<string>arr  = get_input("input/"+file_name+".in");
    solve(arr); // 719 & 1530
}
