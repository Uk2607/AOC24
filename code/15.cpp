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

pair<vector<string>, vector<string>> get_input(string file_path) {
    string line;
    vector<string>arr;
    vector<string>instructions;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return {arr, instructions};
    }

    bool flag = false;
    while(getline(file, line)) {
        if(line.length()==0) {
            flag = true;
            continue;
        }
        if(!flag) arr.push_back(line);
        else instructions.push_back(line);
    }
    file.close();

    return {arr, instructions};
}

void print(vector<string>&arr, vector<string>&ins) {
    cout<<"\n";
    for(string s: arr) {
        for(char c: s)
            cout<<c<<"";
        cout<<"\n";
    }
    cout<<"\n";
    for(string s: ins) {
        for(char c: s)
            cout<<c<<"";
        cout<<"\n";
    }
    cout<<"\n";
}

bool inside(int i, int j, int r, int c) {
    return i>=0 && i<r && j>=0 && j<c;
}

void part1(vector<string>arr, vector<string>ins) {
    int r = arr.size(), c = arr[0].size();
    pair<int,int>robot_pos;
    vector<pair<int,int>>boxes;
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++) {
            if(arr[i][j] == '@') {
                robot_pos = make_pair(i, j);
                arr[i][j] = '.';
            }
            else if(arr[i][j] == 'O') boxes.push_back(make_pair(i, j));
        }

    int nx, ny;
    for(string row: ins) {
        for(char dir: row) {
            if(dir == '^') { // up
                nx = robot_pos.first-1;
                ny = robot_pos.second;
                if(inside(nx, ny, r, c)) {
                    if(arr[nx][ny] == '.') robot_pos.first -= 1;
                    else {
                        while(nx>=0 && arr[nx][ny]=='O') --nx;
                        if(nx>=0 && arr[nx][ny] == '.') {
                            arr[robot_pos.first-1][robot_pos.second] = '.';
                            arr[nx][ny] = 'O';
                            robot_pos.first -= 1;
                        }
                    }
                }
            } else if(dir == '>') { // right
                nx = robot_pos.first;
                ny = robot_pos.second+1;
                if(inside(nx, ny, r, c)) {
                    if(arr[nx][ny] == '.') robot_pos.second += 1;
                    else {
                        while(ny<c && arr[nx][ny]=='O') ++ny;
                        if(ny<c && arr[nx][ny] == '.') {
                            arr[robot_pos.first][robot_pos.second+1] = '.';
                            arr[nx][ny] = 'O';
                            robot_pos.second += 1;
                        }
                    }
                }
            } else if(dir == 'v') { // down
                nx = robot_pos.first+1;
                ny = robot_pos.second;
                if(inside(nx, ny, r, c)) {
                    if(arr[nx][ny] == '.') robot_pos.first += 1;
                    else {
                        while(nx<r && arr[nx][ny]=='O') ++nx;
                        if(nx<r && arr[nx][ny] == '.') {
                            arr[robot_pos.first+1][robot_pos.second] = '.';
                            arr[nx][ny] = 'O';
                            robot_pos.first += 1;
                        }
                    }
                }
            } else { // left
                nx = robot_pos.first;
                ny = robot_pos.second-1;
                if(inside(nx, ny, r, c)) {
                    if(arr[nx][ny] == '.') robot_pos.second -= 1;
                    else {
                        while(ny>=0 && arr[nx][ny]=='O') --ny;
                        if(ny>=0 && arr[nx][ny] == '.') {
                            arr[robot_pos.first][robot_pos.second-1] = '.';
                            arr[nx][ny] = 'O';
                            robot_pos.second -= 1;
                        }
                    }
                }
            }
        }
    }

    int res = 0;
    for(int i=0;i<r;i++) {
        for(int j=0;j<c;j++) {
            // cout<<arr[i][j];
            if(arr[i][j] == 'O') {
                res += (100*i)+j;
            }
        }
        // cout<<"\n";
    }

    cout<<"PART1: "<<res<<"\n";
}

void part2(vector<string>arr, vector<string>ins) {
    cout<<"PART2: "<<arr.size()<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "__");
    pair<vector<string>, vector<string>>ip = get_input("input/"+file_name+".in");
    part1(ip.first, ip.second); // 1430536
    part2(ip.first, ip.second); // 
}
