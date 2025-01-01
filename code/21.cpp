#include "file_name.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<assert.h>

#define ll long long
#define ull unsigned long long

using namespace std;

const ll UP=0, LEFT=1, DOWN=2, RIGHT=3, HIT=4, INF=1e19+5;

vector<vector<ll>>numPad = {
    {7, 8, 9},
    {4, 5, 6},
    {1, 2, 3},
    {-1, 0, 10} // 10=A
};
ll getInt(char val) {
    if(isdigit(val)) return val-'0';
    if(val=='A') return 10;
    return false;
}
char getChar(ll val) {
    if(0<=val && val<10) return '0'+val;
    if(val==10) return 'A';
    return false;
}

vector<pair<ll,ll>>dirs = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
vector<vector<ll>>keyPad = {
    {-1, UP, HIT},
    {LEFT, DOWN, RIGHT}
};

pair<ll,ll> f(pair<ll,ll>me, ll dir) {
    assert(0<=dir && dir<4);
    return {me.first+dirs[dir].first, me.second+dirs[dir].second};
}
// state: (chars_printed, r1, r2, r3);
ll dist[5][5][5][11];
bool vis[5][5][5][11];

const ll M = 25; // Number of robots using keypads
ll dp[M+2][11][11];

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

char makeMove(ll mv, ll &x, vector<vector<ll>>pad) {
    assert(0<=mv && mv<4);
    ll H = pad.size(), W = pad[0].size();
    for(ll r=0;r<H;r++) {
        for(ll c=0;c<W;c++) {
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
// char apply(ll mv, ll i, vector<ll>&v) {
//     assert(v.size()==3);
//     assert(0<=i && i<3);
//     if(mv==HIT) {
//         if(i==2) {
//             return getChar(v[2]);
//         }
//         return apply(v[i], i+1, v);
//     }
//     // movement
//     return makeMove(mv, v[i], ((i==2)?numPad:keyPad));
// }

void preprocesses() {
    // dp[robot_id][from][to] --- assuming all the previous robots are set to 'A',
    // min number of moves to move this robot 'from' -> 'to'

    // dp[0][...] = 0

    for(ll id=1;id<=M+1;id++) {
        const ll X = (id==M+1)?11:5;
        for(ll from = 0;from<X;from++) {
            vector<vector<ll>>small(5, vector<ll>(11, INF));
            small[HIT][from] = 0;
            set<pair<ll,pair<ll,ll>>>pq;
            pq.insert({0, {HIT, from}});

            auto consider = [&](ll prev, ll me, ll maybe) {
                if(maybe<small[prev][me]) {
                    pq.erase({small[prev][me], {prev, me}});
                    small[prev][me] = maybe;
                    pq.insert({maybe, {prev, me}});
                }
            };

            while(!pq.empty()) {
                ll my_dist = pq.begin()->first;
                ll prev = pq.begin()->second.first;
                ll me = pq.begin()->second.second;
                pq.erase(pq.begin());
                for(ll prev2 = 0; prev2<5;prev2++) {
                    ll maybe = my_dist+dp[id-1][prev][prev2];
                    consider(prev2, me, maybe);
                }
                if(prev!=HIT) {
                    if(makeMove(prev, me, (id==M+1?numPad:keyPad))=='$') {
                        consider(prev, me, my_dist+1);
                    }
                }
            }
            for(ll to=0;to<(id==M+1?11:5);to++) {
                dp[id][from][to] = small[HIT][to];
            }
        }
    }
}

// Given an array of numbers, count ways to split it into subarrays so that every subarray (of length K) would be a permutation of numbers 1 through K

ll solve(string str) {

    char prev = 'A';
    ll total = 0;
    for(char c: str) {
        total+=dp[M+1][getInt(prev)][getInt(c)]+1;
        prev = c;
    }
    return total;

    // memset(dist, 0, sizeof(vis));
    // memset(vis, 0, sizeof(vis));

    // dist[0][HIT][HIT][10] = 0;
    // vis[0][HIT][HIT][10] = true;
    // vector<vector<ll>>q;
    // q.push_back({0, HIT, HIT, 10});
    // for(ll z=0;z<q.size();z++) {
    //     ll chars = q[z][0], r1=q[z][1], r2=q[z][2], r3=q[z][3];
    //     if(chars == str.length()) {
    //         return dist[chars][r1][r2][r3];
    //     }
    //     for(ll mv=0;mv<5;mv++) {
    //         vector<ll>v = q[z];
    //         v.erase(v.begin()); // v stores 3 robots
    //         char pr = apply(mv, 0, v);
    //         if(pr == '@') continue;
    //         if(pr != '$') {
    //             if(pr != str[chars]) continue;
    //         }
    //         ll s1 = chars + (pr!='$'), s2 = v[0], s3 = v[1], s4 = v[2];
    //         if(!vis[s1][s2][s3][s4]) {
    //             vis[s1][s2][s3][s4] = true;
    //             dist[s1][s2][s3][s4] = dist[chars][r1][r2][r3]+1;
    //             q.push_back({s1, s2, s3, s4});
    //         }

    //     }
    // }
    // assert(false);
}

void part1(vector<string>arr) {
    ll res = 0;
    preprocesses();
    for(string target: arr) {
        ll x = solve(target);
        target.pop_back();  
        res+=(x*stoi(target));
    }
    cout<<"PART1: "<<res<<"\n";
}

void part2(vector<string>arr) {
    ll res = 0;
    preprocesses();
    for(string target: arr) {
        ll x = solve(target);
        target.pop_back();  
        res+=(x*stoi(target));
    }
    cout<<"PART2: "<<res<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "21");
    vector<string>arr  = get_input("input/"+file_name+".in");

    // part1(arr); // 217662
    part2(arr); // 263617786809000 
}
