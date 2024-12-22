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

struct Coord {
    int x, y, d;
};


int bfs(vector<string>&arr, pair<int,int>me, pair<int,int>dest, int r, int c) {
    vector<vector<bool>>vis(r, vector<bool>(c, false));
    queue<pair<Coord, int>>q;

    int nx, ny, d;
    Coord curr = {me.first, me.second, 0};
    q.push({curr, 0});
    vis[me.first][me.second] = true;

    while(!q.empty()) {
        curr = q.front().first;
        int curr_dist = q.front().second;
        if(curr.x == dest.first && curr.y == dest.second) return curr_dist;
        q.pop();
        // straight
        d = curr.d;
        nx = curr.x+dir[d].first, ny = curr.y+dir[d].second;
        if(inside({nx, ny}, r, c) && arr[nx][ny]!='#' && !vis[nx][ny]) {
            vis[nx][ny] = true;
            q.push({{nx, ny, d}, curr_dist+1});
        }
        // left
        d = (curr.d+3)%4;
        nx = curr.x+dir[d].first, ny = curr.y+dir[d].second;
        if(inside({nx, ny}, r, c) && arr[nx][ny]!='#' && !vis[nx][ny]) {
            vis[nx][ny] = true;
            q.push({{nx, ny, d}, curr_dist+1000});
        }
        // right
        d = (curr.d+1)%4;
        nx = curr.x+dir[d].first, ny = curr.y+dir[d].second;
        if(inside({nx, ny}, r, c) && arr[nx][ny]!='#' && !vis[nx][ny]) {
            vis[nx][ny] = true;
            q.push({{nx, ny, d}, curr_dist+1000});
        }
        
    }
    return -1;
}

void part1(vector<string>arr) {
    int r = arr.size(), c = arr[0].length();
    pair<int,int>src, dest;
    for(int i=0; i<r; i++)
        for(int j=-0; j<c; j++) {
            if(arr[i][j] == 'S') { src = {i, j}; arr[i][j] = '.'; }
            if(arr[i][j] == 'E') { dest = {i, j}; arr[i][j] = '.'; }
        }
    int res = bfs(arr, src, dest, r, c);
    cout<<"PART1: "<<res<<"\n";
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
