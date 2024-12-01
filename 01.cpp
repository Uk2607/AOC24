#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<stack>
#include<unordered_map>

using namespace std;

pair<int,int> get_input(string file_path) {
    string line;
    vector<string>data;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return {-1, -1};
    }

    while(getline(file, line)) {
        data.push_back(line);
    }
    file.close();

    return {0, 0};
}

void part1(int a, int b) {
    cout<<"PART1: "<<a<<", "<<b<<"\n";
}

void part2(int a, int b) {
    cout<<"PART2: "<<a<<", "<<b<<"\n";
}

int main() {
    string file_name;
    cout<<"Enter file name: ";
    cin>>file_name;
    auto [a, b] = get_input(file_name);
    part1(a, b);
    part2(a, b);
}