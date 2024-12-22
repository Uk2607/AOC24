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

const int N = 71; // for input

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

bool inside(int x, int y) {
    return x>=0 && x<N && y>=0 && y<N;
}

int min_path(vector<vector<char>>&grid) {
    pair<int,int>me = {0, 0};
    pair<int,int>dest = {N-1, N-1};
    vector<vector<bool>>vis(N, vector<bool>(N, false));

    queue<pair<pair<int,int>, int>>q;
    vis[me.first][me.second] = true;
    q.push({me, 0});

    while(!q.empty()) {
        pair<int,int>curr = q.front().first;
        int curr_dist = q.front().second;
        if(curr == dest) return curr_dist;
        q.pop();
        for(auto [dx, dy]: dir) {
            int nx = curr.first+dx, ny = curr.second+dy;
            if(inside(nx, ny) && grid[nx][ny]!='#' && !vis[nx][ny]) {
                vis[nx][ny] = true;
                q.push({{nx, ny}, curr_dist+1});
            }
        }
    }
    return -1;
}

void part1(vector<pair<int,int>>arr, int K) {
    vector<vector<char>>grid(N, vector<char>(N, ' '));
    for(int i=0;i<K;i++) grid[arr[i].first][arr[i].second] = '#';
    int dist = min_path(grid);
    cout<<"PART1: "<<dist<<"\n";
}

void part2(vector<pair<int,int>>arr) {
    vector<vector<char>>grid(N, vector<char>(N, ' '));
    int K;
    for(K=0;K<arr.size();K++) {
        grid[arr[K].first][arr[K].second] = '#';
        if(min_path(grid)==-1)
            break;
    }
    cout<<"PART2: "<<arr[K].first<<","<<arr[K].second<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "18");
    vector<pair<int,int>>arr  = get_input("input/"+file_name+".in");
    part1(arr, 1024); // 292
    part2(arr); // 58,44
}
