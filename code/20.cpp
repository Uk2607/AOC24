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

bool inside(pair<int, int>p, int r, int c) {
    return p.first>=0 && p.first<r && p.second>=0 && p.second<c;
}

int bfs(vector<string>&arr, pair<int, int>me, pair<int,int>dest, set<pair<int,int>>&edges) {
    bool original = false;
    if(edges.size()==0) original = true;

    int r = arr.size(), c = arr[0].length(), ccost;
    vector<vector<bool>>vis(r, vector<bool>(c, false));
    queue<pair<pair<int,int>, int>>q;
    q.push({me, 0});
    vis[me.first][me.second] = true;
    while(!q.empty()) {
        me = q.front().first;
        ccost = q.front().second;
        q.pop();
        if(me == dest) return ccost;
        for(pair<int, int>d: dir) {
            int nx = me.first+d.first, ny = me.second+d.second;
            if(original && arr[nx][ny]=='#') edges.insert({nx, ny});
            else if(inside({nx, ny}, r, c) && arr[nx][ny]!='#' && !vis[nx][ny]) {
                vis[nx][ny] = true;
                q.push({{nx, ny}, ccost+1});
            }
        }
    }
    return -1;
}

void part1(vector<string>arr) {
    pair<int,int>me, dest;
    int r = arr.size(), c = arr[0].length();
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++) {
            if(arr[i][j]=='S') { me = {i, j}; arr[i][j] = '.';}
            if(arr[i][j]=='E') { dest = {i, j}; arr[i][j] = '.';}
        }
    set<pair<int,int>>edges;
    int normal_cost = bfs(arr, me, dest, edges), cost;
    map<int,int>mp;
    for(auto [i, j]: edges) {
        arr[i][j] = '.';
        cost = bfs(arr, me, dest, edges);
        mp[normal_cost-cost]++;
        arr[i][j] = '#';
    }
    int res = 0;
    for(auto it: mp) if(it.first>=100) res+=it.second;
    cout<<"PART1: "<<res<<"\n";
}

void part2(vector<string>arr) {
    cout<<"PART2: "<<arr.size()<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "20");
    vector<string>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 1346
    part2(arr); // 
}
