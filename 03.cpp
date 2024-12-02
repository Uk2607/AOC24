#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>

using namespace std;

vector<vector<int>> get_input(string file_path) {
    string line;
    vector<vector<int>>arr;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return arr;
    }

    while(getline(file, line)) {
        int x;
        vector<int>t;
        stringstream ss(line);
        while(ss>>x) t.push_back(x);
        arr.push_back(t);
    }
    file.close();

    return arr;
}

void part1(vector<vector<int>>arr) {
    int x=0;
    cout<<"PART1: "<<x<<"\n";
}

void part2(vector<vector<int>>arr) {
    int x=0;
    cout<<"PART2: "<<x<<"\n";
}

int main() {
    string file_name;
    cout<<"Enter file name: ";
    cin>>file_name;
    vector<vector<int>>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 
    part2(arr); // 
}
