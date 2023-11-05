
#include <iostream>
#include <vector>

using namespace std;

void chaseInd(vector<pair<int, int>>& c, pair<int, int> r, int i);

void grid(vector<pair<int, int>> &c, pair <int, int> r, int copCnt) {
	if (abs(c[0].second - r.second) == abs(c[0].first - r.first) && abs(c[1].second - r.second) == abs(c[1].first - r.first)) {
		if (abs(c[0].first - r.first) == 1 && abs(c[1].first - r.first) == 1) {
			if (abs(c[0].first - c[1].first) == 2) {
				if (c[0].second < r.second) {
					c[0].second++;
				}
				else {
					c[0].second--;
				}
			}
			else if (abs(c[0].second - c[1].second) == 2) {
				if (c[0].first < r.first) {
					c[0].first++;
				}
				else {
					c[0].first--;
				}
			}
			return;
		}
	}

	for (int i = 0; i < copCnt; i++) {
		chaseInd(c, r, i);
	}

}

