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

vector<pair<int,int>>dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

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

void dfs(vector<string>&arr, char ch, int x, int y, int r, int c, vector<vector<bool>>&vis, int &per, int &ar) {
    for(pair<int,int>d: dir) {
        int nx = x + d.first, ny = y + d.second;
        if(nx>=0 && nx<r && ny>=0 && ny<c && arr[nx][ny]==ch && !vis[nx][ny]) {
            vis[nx][ny] = true;
            ++ar;
            dfs(arr, ch, nx, ny, r, c, vis, per, ar);
        }
        else {
            ++per;
        }
    }
}

void part1(vector<string>arr) {
    int r = arr.size(), c = arr[0].length(), res = 0;
    vector<vector<bool>>vis(r, vector<bool>(c, false));
    for(int i=0;i<r;i++) {
        for(int j=0;j<c;j++) {
            if(!vis[i][j]) {
                vis[i][j] = true;
                int perimeter = 0, area = 1;
                dfs(arr, arr[i][j], i, j, r, c, vis, perimeter, area);
                cout<<arr[i][j]<<":"<<area<<"|"<<perimeter<<"\n";
                res += area*perimeter;
            }
        }
    }
    cout<<"PART1: "<<res<<"\n";
}

void part2(vector<string>arr) {
    ;
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "12");
    vector<string>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 
    part2(arr); // 
}
