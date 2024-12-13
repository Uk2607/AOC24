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

vector<ull> get_input(string file_path) {
    string line;
    vector<ull>arr;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return arr;
    }

    getline(file, line);
    file.close();

    stringstream ss(line);
    int x;
    while(ss>>x) arr.push_back(x);

    return arr;
}

void print(vector<ull>&arr) {
    cout<<"\n";
    for(ull x: arr)
        cout<<x<<" ";
    cout<<"\n";
}

void part1(vector<ull>arr) {
    int blink = 25;
    while (blink--) {
        vector<ull>t;
        for(ull x: arr) {
            string str_x = to_string(x);
            int l = str_x.length();
            if(x==0) t.push_back(1);
            else if(l%2==0) {
                t.push_back(stoull(str_x.substr(0, l/2)));
                t.push_back(stoull(str_x.substr(l/2)));
            }
            else t.push_back(x*2024);
        }
        arr = t;
    }
    cout<<"PART1: "<<arr.size()<<"\n";
}

void part2(vector<ull>arr) {
    int blink = 75;
    ;
    cout<<"PART2: "<<arr.size()<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "11");
    vector<ull>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 203953
    part2(arr); // 
}
