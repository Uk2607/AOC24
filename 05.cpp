#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
#include<set>

using namespace std;

pair<vector<pair<int,int>>, vector<vector<int>>> get_input(string file_path) {
    string line;
    vector<pair<int,int>>ordering;
    vector<vector<int>>version;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return {ordering, version};
    }
    //Assuming page number will be in two digits only
    bool flag = true;
    while(getline(file, line)) {
        if(line.length()==0) {
            flag = false;
            continue;
        }
        if(flag) {
            ordering.push_back({stoi(line.substr(0, 2)), stoi(line.substr(3, 2))});
        } else {
            vector<int>t;
            for(int i=0;i<line.length(); i+=3) t.push_back(stoi(line.substr(i, 2)));
            version.push_back(t);
        }
    }
    file.close();

    return {ordering, version};
}

void print(vector<pair<int,int>>&page_order, vector<vector<int>>&version) {
    for(auto [l, r]: page_order) cout<<l<<"<->"<<r<<"\n";
    cout<<"\n";
    for(vector<int>v: version) {
        for(int x: v) cout<<x<<" ";
        cout<<"\n";
    }
}

int fix_pages(vector<pair<int,int>>&page_order, vector<int>version, map<int, set<int>>&pages_before, map<int, set<int>>&pages_after) {
    map<int,int>mp;
    // topological sort
    for(int x: version) {
        mp[x] = 0;
        if(pages_before.find(x)!=pages_before.end()) {
            for(int v:version)
                if(pages_before[x].find(v)!=pages_before[x].end())
                    ++mp[x];
        }
    }

    deque<int> deq;
    vector<int>res;
    for(auto it: mp) if(it.second == 0) deq.push_back(it.first); // pushing elements whose has no elements on their left side
    while(!deq.empty()) {
        int x = deq.front(); deq.pop_front();
        res.push_back(x);
        for(int v: pages_after[x]) {
            if(mp.find(v)!=mp.end()) {
                --mp[v];
                if(mp[v] == 0) deq.push_back(v);
            }
        }
    }
    return res[res.size()/2];
}

void solve(vector<pair<int,int>>&page_order, vector<vector<int>>&version) {
    int res1=0, res2=0;
    map<int, set<int>>pages_after, pages_before;
    for(pair<int,int>p: page_order) {
        pages_after[p.first].insert(p.second);
        pages_before[p.second].insert(p.first);
    }
    for(vector<int>v: version) {
        bool flag = true;
        int n = v.size();
        for(int i=0;i<n;i++)
            for(int j=i+1;j<n;j++) {
                if(pages_before.find(v[i])==pages_before.end()) continue;
                if(pages_before[v[i]].find(v[j]) != pages_before[v[i]].end()) {
                    flag = false;
                    break;
                }
            }

        if(flag) res1 += v[n/2];
        else res2 += fix_pages(page_order, v, pages_before, pages_after);
    }
    cout<<"PART1: "<<res1<<"\n";
    cout<<"PART2: "<<res2<<"\n";
}

int main() {
    string file_name;
    cout<<"Enter file name: ";
    cin>>file_name;
    pair<vector<pair<int,int>>, vector<vector<int>>>p  = get_input("input/"+file_name+".in");
    solve(p.first, p.second); // 4924 & 6805
}
