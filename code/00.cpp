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
        for(char c: s)
            cout<<c<<"";
        cout<<"\n";
    }
    cout<<"\n";
}

void part1(vector<string>arr) {
    ;
}

void part2(vector<string>arr) {
    ;
}

int main() {
    string file_name;
    cout<<"Enter file name: ";
    cin>>file_name;
    vector<string>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 
    part2(arr); // 
}
