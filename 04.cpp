#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>

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

int search(vector<string>&arr, int i, int j, int r, int c) {
    int res = 0;

    if(i>2) { // can go up
        if(arr[i-1][j] == 'M' && arr[i-2][j] == 'A' && arr[i-3][j] == 'S') ++res;
        if(j>2) { // go left
            if(arr[i-1][j-1] == 'M' && arr[i-2][j-2] == 'A' && arr[i-3][j-3] == 'S') ++res;
        }
        if(j<c-3) { // go right
            if(arr[i-1][j+1] == 'M' && arr[i-2][j+2] == 'A' && arr[i-3][j+3] == 'S') ++res;
        }
    }
    if(j>2) { // go left
        if(arr[i][j-1] == 'M' && arr[i][j-2] == 'A' && arr[i][j-3] == 'S') ++res;
    }
    if(j<c-3) { // go right
        if(arr[i][j+1] == 'M' && arr[i][j+2] == 'A' && arr[i][j+3] == 'S') ++res;
    }
    if(i<r-3) { // can go down
        if(arr[i+1][j] == 'M' && arr[i+2][j] == 'A' && arr[i+3][j] == 'S') ++res;
        if(j>2) { // go left
            if(arr[i+1][j-1] == 'M' && arr[i+2][j-2] == 'A' && arr[i+3][j-3] == 'S') ++res;
        }
        if(j<c-3) { // go right
            if(arr[i+1][j+1] == 'M' && arr[i+2][j+2] == 'A' && arr[i+3][j+3] == 'S') ++res;
        }
    }

    return res;
}

void part1(vector<string>arr) {
    int res=0, r = arr.size(), c = arr[0].length();
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            if(arr[i][j] == 'X')
                res += search(arr, i, j, r, c);
    
    cout<<"PART1: "<<res<<"\n";
}

void part2(vector<string>arr) {
    int res=0;
    ;
    cout<<"PART2: "<<res<<"\n";
}

int main() {
    string file_name;
    cout<<"Enter file name: ";
    cin>>file_name;
    vector<string>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 2639
    part2(arr); // 
}
