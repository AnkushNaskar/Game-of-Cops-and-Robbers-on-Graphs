#include <math.h>
#include <vector>
#include <algorithm> 
#include <iostream>

using namespace std;

void chaseInd(vector<pair<int, int>>& c, pair<int, int> r, int i);
void orient(vector<pair<int, int>>& c, pair<int, int> r, int copCnt, int m, int n, bool copEst[]);
void grid(vector<pair<int, int>>& c, pair <int, int> r, int copCnt);

bool copEstCyl[2] = { false };

void cylinder(vector<pair<int, int>>& c, pair<int, int> r, int copCnt, int m, int n){
    for (int i = 0; i < 2; i++) {
        if (c[i].second == r.second) {
            copEstCyl[i] = 1;
        }
    }
    if (copEstCyl[0] == 1 && copEstCyl[1] == 1) {
        if (c[0].first < r.first && c[1].first < r.first) {
            if (c[0].first < c[1].first) {
                c[0].first += n;
            }
            else {
                c[1].first += n;
            }
        }
        else if (c[0].first > r.first && c[1].first > r.first) {
            if (c[0].first < c[1].first) {
                c[1].first -= n;
            }
            else {
                c[0].first -= n;
            }
        }
        grid(c, r, 2);
    }
    else {
        for (int i = 0; i < 2; i++) {
            if (copEstCyl[i] == 1) {
                chaseInd(c, r, i);
            }
        }
        orient(c, r, copCnt, m, n, copEstCyl);
    }

}