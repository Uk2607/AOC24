#include "file_name.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<assert.h>

#define ll long long int
#define ull unsigned long long int
using namespace std;

const int UP=0, LEFT=1, DOWN=2, RIGHT=3, HIT=4, INF=1e9+5;

vector<vector<int>>numPad = {
    {7, 8, 9},
    {4, 5, 6},
    {1, 2, 3},
    {-1, 0, 10} // 10=A
};
char getChar(int val) {
    if(0<=val && val<10) return '0'+val;
    if(val==10) return 'A';
    return false;
}

vector<pair<int,int>>dirs = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
vector<vector<int>>keyPad = {
    {-1, UP, HIT},
    {LEFT, DOWN, RIGHT}
};

pair<int,int> f(pair<int,int>me, int dir) {
    assert(0<=dir && dir<4);
    return {me.first+dirs[dir].first, me.second+dirs[dir].second};
}
// state: (chars_printed, r1, r2, r3);
int dist[5][5][5][11];
bool vis[5][5][5][11];
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

char makeMove(int mv, int &x, vector<vector<int>>pad) {
    assert(0<=mv && mv<4);
    int H = pad.size(), W = pad[0].size();
    for(int r=0;r<H;r++) {
        for(int c=0;c<W;c++) {
            if(pad[r][c] == x) {
                r+=dirs[mv].first;
                c+=dirs[mv].second;
                if(r>=0 && r<H && c>=0 && c<W && pad[r][c]!=-1) {
                    x = pad[r][c];
                    return '$'; // success
                } else return '@'; // error
            }
        }
    }
    assert(false);
}

// return char printed or info that there is nothing printed or error
char apply(int mv, int i, vector<int>&v) {
    assert(v.size()==3);
    assert(0<=i && i<3);
    if(mv==HIT) {
        if(i==2) {
            return getChar(v[2]);
        }
        return apply(v[i], i+1, v);
    }
    // movement
    return makeMove(mv, v[i], ((i==2)?numPad:keyPad));
}

int solve(string str) {
    memset(dist, 0, sizeof(vis));
    memset(vis, 0, sizeof(vis));

    dist[0][HIT][HIT][10] = 0;
    vis[0][HIT][HIT][10] = true;
    vector<vector<int>>q;
    q.push_back({0, HIT, HIT, 10});
    for(int z=0;z<q.size();z++) {
        int chars = q[z][0], r1=q[z][1], r2=q[z][2], r3=q[z][3];
        if(chars == str.length()) {
            return dist[chars][r1][r2][r3];
        }
        for(int mv=0;mv<5;mv++) {
            vector<int>v = q[z];
            v.erase(v.begin()); // v stores 3 robots
            char pr = apply(mv, 0, v);
            if(pr == '@') continue;
            if(pr != '$') {
                if(pr != str[chars]) continue;
            }
            int s1 = chars + (pr!='$'), s2 = v[0], s3 = v[1], s4 = v[2];
            if(!vis[s1][s2][s3][s4]) {
                vis[s1][s2][s3][s4] = true;
                dist[s1][s2][s3][s4] = dist[chars][r1][r2][r3]+1;
                q.push_back({s1, s2, s3, s4});
            }

        }
    }
    assert(false);
}

void part1(vector<string>arr) {
    int res = 0;
    for(string target: arr) {
        int x = solve(target);
        target.pop_back();  
        res+=(x*stoi(target));
    }
    cout<<"PART1: "<<res<<"\n";
}

void part2(vector<string>arr) {
    cout<<"PART2: "<<arr.size()<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "21");
    vector<string>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 217662
    part2(arr); // 
}
