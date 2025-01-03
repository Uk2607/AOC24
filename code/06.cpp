#include "file_name.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<set>
#include<tuple>

using namespace std;

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
        for(char c: s) cout<<c<<" ";
        cout<<"\n";
    }
    cout<<"\n";
}

set<tuple<int,int>> part1(vector<string>arr, int x, int y) {
    int res=0, r = arr.size(), c = arr[0].length(), d_idx = 0;
    vector<pair<int, int>>dir = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    set<tuple<int,int>>st;
    while(true) {
        st.insert(make_tuple(x, y));
        int dx = x+dir[d_idx].first, dy = y+dir[d_idx].second;
        if(dx<0 || dx>=r || dy<0 || dy>=c) break;
        if(arr[dx][dy] == '#') d_idx = (d_idx+1)%4;
        else { x = dx; y = dy; }
    }
    cout<<"PART1: "<<st.size()<<"\n";
    return st;
}

void part2(vector<string>arr, int gx, int gy, set<tuple<int,int>>&vis) {
    int res=0, r = arr.size(), c = arr[0].length();
    vector<pair<int, int>>dir = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}, corners;
    for(auto[ox, oy]: vis) {
        if(arr[ox][oy] == '#' || arr[ox][oy] == '^') continue;
        arr[ox][oy] = '#';

        int x = gx, y = gy, d_idx = 0;
        int times = 0;
        set<tuple<int,int,int>>st;
        while(true) {
            if(st.find(make_tuple(x,y,d_idx))!= st.end()) {
                ++res;
                break;
            }
            st.insert(make_tuple(x, y, d_idx));
            int dx = x+dir[d_idx].first, dy = y+dir[d_idx].second;
            if(dx<0 || dx>=r || dy<0 || dy>=c) break;
            if(arr[dx][dy] == '#') d_idx = (d_idx+1)%4;
            else { x = dx; y = dy; } // At turn need to include both direction for same position
        }

        arr[ox][oy] = '.';
    }
    cout<<"PART2: "<<res<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "06");
    vector<string>arr  = get_input("input/"+file_name+".in");
    int x, y;
    for(int i=0;i<arr.size();i++)
        for(int j=0;j<arr[i].length();j++)
            if(arr[i][j] == '^') {x = i; y = j;}

    set<tuple<int,int>>vis = part1(arr, x, y); // 5086
    part2(arr, x, y, vis); // 1770
}
