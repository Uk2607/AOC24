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

struct State {
    int x, y, d;
    bool operator <(const State &a) const {
        return make_pair(x, make_pair(y, d)) < make_pair(a.x, make_pair(a.y, a.d));
    }
};

int bfs(vector<string>&arr, pair<int,int>me, pair<int,int>dest, int r, int c) { // gives shortest path and ignores cost
    vector<vector<bool>>vis(r, vector<bool>(c, false));
    queue<pair<State, int>>q;

    int nx, ny, d;
    State curr = {me.first, me.second, 0};
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
            q.push({{nx, ny, d}, curr_dist+1001});
        }
        // right
        d = (curr.d+1)%4;
        nx = curr.x+dir[d].first, ny = curr.y+dir[d].second;
        if(inside({nx, ny}, r, c) && arr[nx][ny]!='#' && !vis[nx][ny]) {
            vis[nx][ny] = true;
            q.push({{nx, ny, d}, curr_dist+1001});
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
    // int res = bfs(arr, src, dest, r, c);
    // cout<<"PART1: "<<res<<"\n";
    // return;

    // Dijkstra
    set<pair<int, State>>st;
    map<State, int>dist;
    State starting_state{src.first, src.second, 0};
    dist[starting_state] = 0;
    st.insert(make_pair(0, starting_state));

    while(!st.empty()) {
        State state = st.begin()->second;
        st.erase(st.begin());
        for(int i=0;i<3;i++) {
            int cost = dist[state];
            State s2 = state;
            if(i==0) {
                s2.x += dir[s2.d].first;
                s2.y += dir[s2.d].second;
                if(!inside({s2.x, s2.y}, r, c)) continue;
                if(arr[s2.x][s2.y]=='#') continue;
                cost++;
            } else if(i==1) {
                s2.d = (s2.d+1)%4;
                cost+=1000;
            } else if(i==2) {
                s2.d = (s2.d+3)%4;
                cost+=1000;
            }
            if(!dist.count(s2) || dist[s2]>cost) {
                if(dist.count(s2)) {
                    st.erase(make_pair(dist[s2], s2));
                }
                dist[s2] = cost;
                st.insert(make_pair(cost, s2));
            }
        }
    }
    int res = INT_MAX;
    for(int i=0;i<4;i++) {
        State t{dest.first, dest.second, i};
        if(dist.count(t))
            res = min(res, dist[t]);
    }

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
