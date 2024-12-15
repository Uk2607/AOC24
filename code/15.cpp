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

void part1(vector<string>arr, vector<string>ins) {
    print(arr, ins);
    cout<<"PART1: "<<arr.size()<<"\n";
}

void part2(vector<string>arr, vector<string>ins) {
    cout<<"PART2: "<<arr.size()<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "__");
    pair<vector<string>, vector<string>>ip = get_input("input/"+file_name+".in");
    part1(ip.first, ip.second); // 
    part2(ip.first, ip.second); // 
}
