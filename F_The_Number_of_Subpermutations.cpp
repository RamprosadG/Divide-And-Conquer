#include<bits/stdc++.h>
using namespace std;

#define ll             long long
#define LL             long long
#define pii            pair<int, int>
#define pll            pair<ll, ll>
#define pil            pair<int, ll>
#define pli            pair<ll, int>
#define vi             vector<int>
#define vl             vector<ll>
#define vii            vector<pii>
#define vll            vector<pll>
#define vil            vector<pil>
#define vli            vector<pli>
#define pb             push_back
#define ppb            pop_back
#define mp             make_pair
#define ff             first
#define ss             second
#define sz(x)          (int)x.size()
#define TN             typename
#define all(v)         v.begin(), v.end()
#define fill(a, b)     memset(a, b, sizeof(a))
#define endl           '\n'

template <TN T> T gcd(T a, T b) {return !b ? a : gcd(b, a % b);}
template <TN T> T lcm(T a, T b) {return a * (b / gcd(a, b));}
template <TN T> T sqr(T a) {return a * a;}
template <TN T> T cube(T a) {return a * a * a;}
template <TN T> inline void smin(T &a, T b) {a = a < b ? a : b;}
template <TN T> inline void smax(T &a, T b) {a = a > b ? a : b;}

template <TN T> inline void Int(T &n) {
	n = 0; int f = 1; register int ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
	for (; isdigit(ch); ch = getchar()) n = (n << 3) + (n << 1) + ch - '0';
	n = n * f;
}

#define error(args...) {vector <string> _v = split(#args, ','); err(_v.begin(), args); cout << endl;}
vector <string> split(const string &s, char c) {
	vector <string> v;
	stringstream ss(s); string x;
	while (getline(ss, x, c)) v.emplace_back(x);
	return move(v);
}
void err(vector <string> :: iterator it) {}
template <typename T, typename... Args>
void err(vector <string> :: iterator it, T a, Args... args) {
	cout << it -> substr((*it)[0] == ' ', it -> length()) << " = " << a << ", ";
	err(++it, args...);
}

inline int in() {int n; scanf("%d", &n); return n;}
inline ll Lin() {ll n; scanf("%lld", &n); return n;}
inline double Din() {double n; scanf("%lf", &n); return n;}

inline int add(int a, int b, int mod) {a += b; return a >= mod ? a - mod : a;}
inline int sub(int a, int b, int mod) {a -= b; return a < 0 ? a + mod : a;}
inline int mul(int a, int b, int mod) {return (ll)a * b % mod;}

const int N          = 4e5 + 5;
const int inf        = (int)2e9 + 5;
const ll  Inf        = (ll)1e18 + 5;
const int mod        = (int)1e9 + 7;
const ll  Mod        = (ll)1e9 + 7;

int a[N];
int mx[N], mn[N], cnt[N];

int B, L, R;

bool cmp(pii a, pii b) {
	int Block_a = (a.ff - L + 1) / B, Block_b = (b.ff - L + 1) / B;
	if (Block_a == Block_b) return a.ss < b.ss;
	else return Block_a < Block_b;
}

void ADD(int& cur, int x) {
	x = a[x];
	cnt[x]++;
	if (cnt[x] == 1) cur++;
}

void DELETE(int& cur, int x) {
	x = a[x];
	cnt[x]--;
	if (cnt[x] == 0) cur--;
}

ll divide(int left, int right) {
	if (left == right) {
		if (a[left] == 1) return 1LL;
		return 0LL;
	}
	int mid = (left + right) >> 1;
	ll ans = 0;
	for (int i = mid + 1; i <= right; i++) {
		cnt[a[i]] = 0;
		if (i == mid + 1) mn[i] = a[i], mx[i] = a[i];
		else mn[i] = min(mn[i - 1], a[i]), mx[i] = max(mx[i - 1], a[i]);
	}

	for (int i = mid; i >= left; i--) {
		cnt[a[i]] = 0;
		if (i == mid) mn[i] = a[i], mx[i] = a[i];
		else mn[i] = min(mn[i + 1], a[i]), mx[i] = max(mx[i + 1], a[i]);
	}

	vii range;
	range.clear();

	for (int i = mid + 1; i <= right; i++) {
		int len = mx[i];
		if (i - len + 1 > mid || i - len + 1 < left) continue;
		if (min(mn[i], mn[i - len + 1]) == 1 && mx[i - len + 1] < len) range.pb({i - len + 1, i});
	}

	for (int i = mid; i >= left; i--) {
		int len = mx[i];
		if (i + len - 1 < mid + 1 || i + len - 1 > right) continue;
		if (min(mn[i], mn[i + len - 1]) == 1 && mx[i + len - 1] < len) range.pb({i, i + len - 1});
	}

	B = (int)sqrt(right - left + 1) + 1, L = left;
	sort(all(range), cmp);

	L = left, R = left - 1;
	int dis_value = 0;
	for (auto cur : range) {
		while (L > cur.ff) ADD(dis_value, --L);
		while (R < cur.ss) ADD(dis_value, ++R);
		while (L < cur.ff) DELETE(dis_value, L++);
		while (R > cur.ss) DELETE(dis_value, R--);

		if (dis_value == cur.ss - cur.ff + 1) ans++;
	}

	return ans + divide(left, mid) + divide(mid + 1, right);
}

int solve() {
	int n = in();
	for (int i = 1; i <= n; i++) {
		a[i] = in();
	}
	printf("%lld\n", divide(1, n));
	return 0;
}

int main() {
	int test = 1, tc = 0;
	//scanf("%d", &test);
	while (test--) {
		//printf("Case %d: ", ++tc);
		solve();
	}
	return 0;
}
