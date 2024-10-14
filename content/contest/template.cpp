#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define mp make_pair
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define rep(i, l, r) for (int i = (int)(l); i <= (int)(r); i++)
#define per(i, r, l) for (int i = (int)(r); i >= (int)(l); i--)

template<typename T> bool maximize(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
template<typename T> bool minimize(T& a, const T& b) { return a > b ? a = b, 1 : 0; }

typedef long long ll;
typedef pair<int, int> pii;

const string file = "";

signed main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	if (fopen((file + ".inp").c_str(), "r")) {
		freopen((file + ".inp").c_str(), "r", stdin);
		freopen((file + ".out").c_str(), "w", stdout);
	}
	return 0;
}