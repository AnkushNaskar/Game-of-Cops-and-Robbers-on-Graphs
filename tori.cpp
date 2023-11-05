// #include <bits/stdc++.h>
#include <math.h>
#include <vector>
#include <algorithm> 
#include <iostream>

using namespace std;


int guardEst;
bool copEst[2] = { false };

int guard(vector<pair<int, int>> &c, pair<int, int> r, int copCnt, int m, int n, vector<pair<int,int>> shortXdist);
void chaseInd(vector<pair<int, int>> &c, pair<int, int> r, int i);
void tori(vector<pair<int, int>> &c, pair<int, int> r, pair<int, int> lastRpos, int copCnt, int m, int n);
void orient(vector<pair<int, int>>& c, pair<int, int> r, int copCnt, int m, int n, bool copEst[]);
void grid(vector<pair<int, int>>& c, pair <int, int> r, int copCnt);
bool found = false;
bool start = 0;
int cg = -1;

vector<pair<int, int>> shortXdist;

void tori(vector<pair<int, int>>& c, pair<int, int> r, pair<int, int> lastRpos, int copCnt, int m, int n)
{

    if (start == 0) {

        for (int i = 0; i < 3; i++) {
            int distX;
            distX = c[i].first - r.first;
            shortXdist.push_back({ distX, i });
        }

        sort(shortXdist.begin(), shortXdist.end());
        start = 1;
    }

    int moveLeft = 0;
    if (guardEst == 0)// || check == false)
    {
        moveLeft = guard(c, r, copCnt, m, n, shortXdist);
        if (guardEst == 1) {
            swap(c[2], c[cg]);
            cg = 2;
        }
        
        if (!moveLeft) {
            return;
        }
    }

    if (moveLeft == 1 || guardEst == 1) {
        
        c[cg].first = r.first;
        if (lastRpos.second < r.second) {
           // cout << "UP\n";
            c[cg].second = (c[cg].second - 1 + m) % m;
        }
        else if(lastRpos.second > r.second) {
           // cout << "DOWN\n";
            c[cg].second = (c[cg].second + 1) % m;
        }
        for (int i = 0; i < 2; i++) {
            if (c[i].second == r.second) {
                copEst[i] = 1;
            }
        }
        if (copEst[0] == 1 && copEst[1] == 1) {
            if (c[0].first < r.first && c[1].first < r.first) {
                if (c[0].first < c[1].first) {
                    c[0].first += n;
                }
                else {
                    c[1].first += n;
                }
            }
            else if(c[0].first > r.first && c[1].first > r.first){
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
                if (copEst[i] == 1) {
                    chaseInd(c, r, i);
                }
            }
            orient(c, r, copCnt, m, n, copEst);
        }      
        
        
    }
}

void orient(vector<pair<int, int>>& c, pair<int, int> r, int copCnt, int m, int n, bool copEst[]) {
    for (int i = 0; i < 2; i++) {
        if (copEst[i] == 0) {
            if (c[i].second < r.second) {
                c[i].second++;
            }
            else {
                c[i].second--;
            }
            if (c[i].second == r.second) {
                copEst[i] = 1;
            }
        }
    }
    
}


int guard(vector<pair<int, int>> &c, pair<int, int> r, int copCnt, int m, int n, vector<pair<int, int>> shortXdist)
{
    for (int i = 0; i < copCnt; i++) {
        if (c[i].first == r.first) {
            guardEst = 1;
            cg = i;
            return 1;
        }
    }
    if (shortXdist[0].first > 0) {
        c[shortXdist[0].second].first--;
        c[shortXdist[2].second].first = (c[shortXdist[2].second].first + 1) % n;
    }
    else if(shortXdist[2].first < 0){
        c[shortXdist[0].second].first = (c[shortXdist[0].second].first - 1 + n) % n;
        c[shortXdist[2].second].first++;
    }
    else {
        if (shortXdist[1].first > 0) {
            c[shortXdist[0].second].first++;
            c[shortXdist[1].second].first--;
        }
        else {
            c[shortXdist[1].second].first++;
            c[shortXdist[2].second].first--;
        }
    }

    for (int i = 0; i < copCnt; i++) {
        if (c[i].first == r.first) {
            guardEst = 1;
            cg = i;
            return 0;
        }
    }
}

void chaseInd(vector<pair<int, int>>& c, pair<int, int> r, int i) {
    if (abs(c[i].second - r.second) < abs(c[i].first - r.first)) {
        if (c[i].first < r.first) {
            c[i].first++;
        }
        else {
            c[i].first--;
        }
    }
    else if (abs(c[i].second - r.second) > abs(c[i].first - r.first)) {
        if (c[i].second < r.second) {
            c[i].second++;
        }
        else {
            c[i].second--;
        }
    }
    else {
        if (c[i].second < r.second) {
            c[i].second++;
        }
        else {
            c[i].second--;
        }
    }
}
