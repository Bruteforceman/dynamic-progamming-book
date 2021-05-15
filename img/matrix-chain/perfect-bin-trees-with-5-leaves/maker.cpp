#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
#define all(v) begin(v), end(v)
#define sz(v) (int)(v).size()
#define fi first
#define se second
#define ts to_string

/* https://stackoverflow.com/a/26221725 */
template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
  int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
  if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
  auto size = static_cast<size_t>( size_s );
  auto buf = std::make_unique<char[]>( size );
  std::snprintf( buf.get(), size, format.c_str(), args ... );
  return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}

double unit = 0.5;
double y_gap = unit * 1.5;

struct node {
  double x, y;
  int index;
  string caption;
  node () {}
  node(double _x, double _y, int _index, string _caption)
    : x(_x), y(_y), index(_index), caption(_caption) {}
  string to_string() {
    /*return string_format(
      "\\node (%d) at (%lf,%lf) {$\\bm{\\mathsf{%s}}$};",
      index, x, y, caption.data()
    );*/
    return string_format(
      "\\node[scale=0.8] (%d) at (%lf,%lf) {$\\mathsf{%s}$};",
      index, x, y, caption.data()
    );
  }
};
struct edge {
  int from, to;
  edge () {}
  edge (int _from,  int _to) : from(_from), to(_to) {}
  string to_string() {
    return string_format(
      "\\path[draw,thick,->] (%d) -- (%d);", from, to
    );
  }
};
struct bbox {
  double left = 1e18, right = -1e18, top = -1e18, bottom = 1e18;
  bbox operator + (const bbox& o) const {
    return {
      min(left, o.left),
      max(right, o.right),
      max(top, o.top),
      min(bottom, o.bottom)
    };
  }
};
bbox calc_bbox(vector<node> v) {
  bbox ret;
  for(node u : v) {
    bbox me = {u.x, u.x, u.y, u.y};
    ret = ret + me;
  }
  return ret;
}
template <typename Head, typename... Tail>
bbox calc_bbox(Head H, Tail... T) {
  return calc_bbox(H) + calc_bbox(T...);
}

mt19937 rng(69);
int random(int l, int r) {
  return uniform_int_distribution<int>(l, r)(rng);
}

string base = "ABCDE";
int idx = 0;
vector<int> code;
set<vector<int>> visited_codes;
int n = 5;
vector<edge> egs;
vector<node> nds;

pair<int, string> build(int b, int e, int L, int R, double y_val) {
  int u = ++idx;
  if(b == e) {
    nds.push_back(node(double(L+R)/2.0, y_val, u, base.substr(b, 1)));
    return {u, base.substr(b, 1)};
  }
  int m = random(b, e-1);
  int M = (L + R) / 2;
  code.emplace_back(m);
  auto [lc, lstr] = build(b, m, L, M, y_val-y_gap);
  auto [rc, rstr] = build(m+1, e, M+1, R, y_val-y_gap);
  egs.push_back(edge(lc, u));
  egs.push_back(edge(rc, u));
  nds.push_back(node(double(L+R)/2.0, y_val, u, lstr + rstr));
  return {u, "(" + lstr + rstr + ")"};
}

int main(int argc, char const *argv[])
{
#ifdef LOCAL
  freopen("in", "r", stdin);
#endif
  map<vi, pair<vector<node>, vector<edge>>> mp;
  while(sz(mp) < 14) {
    code.clear();
    egs.clear();
    nds.clear();
    build(0, n-1, 0, (1<<(n-1))-1, 0);
    mp[code] = {nds, egs};
  }

  vector<pair<vector<node>, vector<edge>>> trees;
  for(auto x : mp) trees.push_back(x.se);
  reverse(all(trees));

  vector<pair<vector<node>, vector<edge>>> g[7];
  for(int i = 0; i < 7; ++i)
    for(int j = 0; j < 2; ++j)
      g[i].push_back(trees[2*i+j]);

  for(int i = 0; i < 7; ++i)
    for(int j = 0; j < 2; ++j) {

    }

  double cur_bottom = 1;
  for(int i = 0; i < 7; ++i) {
    double y_of_this_row = cur_bottom - y_gap;
    for(int j = 0; j < 2; ++j) {
      auto& [nodes, edges] = g[i][j];
      for(node& u : nodes) {
        u.y += y_of_this_row;
        u.x += j * (1 << (n-1));
        u.x *= unit;
        cur_bottom = min(cur_bottom, u.y);
      }
    }
  }

  for(int i = 0; i < 7; ++i) {
    double rightmost = calc_bbox(g[i][0].fi).right;
    double leftmost = calc_bbox(g[i][1].fi).left;
    double delta_x = (rightmost + 4.0 * unit) - leftmost;
    for(node& u : g[i][1].fi)
      u.x += delta_x;
    double mid = (calc_bbox(g[i][0].fi, g[i][1].fi).left
                + calc_bbox(g[i][0].fi, g[i][1].fi).right) / 2.0;
    for(int j : {0, 1})
      for(node& u : g[i][j].fi)
        u.x -= mid;
  }

  ofstream out("code.tikz");
  out << "\\begin{tikzpicture}[scale=0.9]\n";
  for(int i = 0; i < 7; ++i)
    for(int j = 0; j < 2; ++j) {
      auto [nodes, edges] = g[i][j];
      for(node u : nodes)
        out << "  " << u.ts() << endl;
      for(edge e : edges)
        out << "  " << e.ts() << endl;
    }
  out << "\\end{tikzpicture}" << endl;
  system("xelatex test.tex");
  return 0;
}
/*
* use std::array instead of std::vector, if u can
* overflow?
* array bounds
*/
