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

void part1(vector<string>arr, int x, int y) {
    int res=0, r = arr.size(), c = arr[0].length(), d_idx = 0;
    vector<pair<int, int>>dir = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    while(true) {
        arr[x][y] = 'X';
        int dx = x+dir[d_idx].first, dy = y+dir[d_idx].second;
        if(dx<0 || dx>=r || dy<0 || dy>=c) break;
        if(arr[dx][dy] == '#')
            d_idx = (d_idx+1)%4;
        x += dir[d_idx].first;
        y += dir[d_idx].second;
    }
    for(int i=0;i<r;i++) for(int j=0;j<c;j++) if(arr[i][j] == 'X') ++res;
    cout<<"PART1: "<<res<<"\n";
}

void part2(vector<string>arr, int gx, int gy) {
    int res=0, r = arr.size(), c = arr[0].length();
    vector<pair<int, int>>dir = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}, corners;
    for(int ox=0;ox<r;ox++) {
        for(int oy=0;oy<c;oy++) {
            if(arr[ox][oy] == '#' || arr[ox][oy] == '^') continue;
            arr[ox][oy] = '#';

            int x = gx, y = gy, d_idx = 0;
            set<tuple<int,int,int>>st;
            while(true) {
                if(st.find(make_tuple(x,y,d_idx))!= st.end()) {
                    ++res;
                    break;
                }
                st.insert(make_tuple(x, y, d_idx));
                int dx = x+dir[d_idx].first, dy = y+dir[d_idx].second;
                if(dx<0 || dx>=r || dy<0 || dy>=c) break;
                if(arr[dx][dy] == '#') {
                    d_idx = (d_idx+1)%4;
                }
                x += dir[d_idx].first;
                y += dir[d_idx].second;
            }

            arr[ox][oy] = '.';
        }
    }
    cout<<"PART2: "<<res<<"\n";
}

int main() {
    string file_name;
    cout<<"Enter file name: ";
    cin>>file_name;
    vector<string>arr  = get_input("input/"+file_name+".in");
    int x=-1, y=-1;
    for(int i=0;i<arr.size();i++) {
        for(int j=0;j<arr[i].length();j++) {
            if(arr[i][j] == '^') {
                x = i; y = j;
                break;
            }
        }
        if(x!=-1 && y!=-1) break;
    }
    part1(arr, x, y); // 5086
    part2(arr, x, y); // lower than 1845
}
