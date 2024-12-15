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

void dfs1(vector<string>&arr, char ch, int x, int y, int r, int c, vector<vector<bool>>&vis, int &per, int &ar) {
    for(pair<int,int>d: dir) {
        int nx = x + d.first, ny = y + d.second;
        if(nx>=0 && nx<r && ny>=0 && ny<c && arr[nx][ny]==ch) {
            if(vis[nx][ny]) continue;
            vis[nx][ny] = true;
            ++ar;
            dfs1(arr, ch, nx, ny, r, c, vis, per, ar);
        }
        else ++per;
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
                dfs1(arr, arr[i][j], i, j, r, c, vis, perimeter, area);
                res += area*perimeter;
            }
        }
    }
    cout<<"PART1: "<<res<<"\n";
}

bool inside(int x, int y, int r, int c) {
    return x>=0 && x<r && y>=0 && y<c;
}

void dfs2(vector<string>&arr, int x, int y, int r, int c, vector<vector<bool>>&vis, int &per, int &ar) {
    vis[x][y] = true;
    ar++;
    auto good = [&](pair<int,int>dir) {
        int r1 = x+dir.first;
        int c1 = y+dir.second;
        return inside(r1, c1, r, c) && arr[r1][c1]==arr[x][y];
    };

    for(int i=0;i<4;i++) { // looking for corners in the shape because sides == corners
        pair<int, int>d1 = dir[i];
        pair<int, int>d2 = dir[(i+1)%4];
        if(!good(d1) && !good(d2)) {
            per++;
        }
        if(good(d1) && good(d2) && !good(make_pair(d1.first+d2.first, d1.second+d2.second))) {
            per++;
        }
    }

    for(pair<int,int>d: dir) {
        int nx = x + d.first, ny = y + d.second;
        if(good(d) && !vis[nx][ny]) {
            dfs2(arr, nx, ny, r, c, vis, per, ar);
        }
    }
}

void part2(vector<string>arr) {
    int r = arr.size(), c = arr[0].length(), res = 0;
    vector<vector<bool>>vis(r, vector<bool>(c, false));
    for(int i=0;i<r;i++) {
        for(int j=0;j<c;j++) {
            if(!vis[i][j]) {
                int perimeter = 0, area = 0;
                dfs2(arr, i, j, r, c, vis, perimeter, area);
                res += area*perimeter;
            }
        }
    }
    cout<<"PART1: "<<res<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "12");
    vector<string>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 1319878
    part2(arr); // 
}
