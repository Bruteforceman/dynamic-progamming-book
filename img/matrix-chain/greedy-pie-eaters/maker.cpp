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
struct hbar {
  bool shaded_fill = false;
  double xl, xr, dy, ymid;
  int index;
  hbar(int _index, double x1, double y1, double x2, double y2, bool _shaded_fill = false) {
    xl = x1, xr = x2, dy = y2 - y1, ymid = (y1 + y2) / 2.0;
    shaded_fill = _shaded_fill;
    index = _index;
  }
  string to_string() {
    return string_format(
      "\\draw (%lf, %lf) rectangle (%lf, %lf) [draw=black%s];\n\\draw node[scale=1] at (%lf, %lf) {%s};",
      xl, ymid-0.5*dy, xr, ymid+0.5*dy, shaded_fill ? ",fill=black!20" : "", xl + 0.5 * dy, ymid, std::to_string(index).data()
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

// auto seed = time(0);
auto seed = 1625483752;
mt19937 rng(seed);
int random(int l, int r) {
  return uniform_int_distribution<int>(l, r)(rng);
}

using tri = tuple<int, int, int>;

int K = 0;
vi random_numbers;
void calc(int L, int R, vector<tri> ranges) {
  if(ranges.empty()) return;
  int c, p;
  K++;
  random_numbers.emplace_back(c = random(0, sz(ranges)-1));
  auto [cl, cr, cidx] = ranges[c];
  random_numbers.emplace_back(p = random(cl, cr));
  vector<tri> Lranges, Rranges;
  for(auto [l, r, idx] : ranges) {
    if(r < p) Lranges.emplace_back(l, r, idx);
    if(l > p) Rranges.emplace_back(l, r, idx);
  }
  calc(L, p-1, Lranges);
  calc(p+1, R, Rranges);
}

void solve(double prv, int L, int R, vector<tri> ranges, ofstream& out, double px, double py, bool nopar = true) {
  if(ranges.empty()) return;
  // int c = random(0, sz(ranges)-1);
  int c = random_numbers.back(); random_numbers.pop_back();
  auto [cl, cr, cidx] = ranges[c];
  // int p = random(cl, cr);
  int p = random_numbers.back(); random_numbers.pop_back();
  vector<tri> Lranges, Rranges;
  for(auto [l, r, idx] : ranges) {
    if(r < p) Lranges.emplace_back(l, r, idx);
    if(l > p) Rranges.emplace_back(l, r, idx);
  }
  vector<vector<tri>> groups;
  while(sz(ranges)) {
    /*groups.push_back({});
    bool flag2;
    do {
      flag2 = false;
      for(int i = 0; i < sz(ranges); ++i) {
        bool flag3 = true;
        for(int j = 0; j < sz(groups.back()); ++j) {
          flag3 &= max(get<0>(ranges[i]), get<0>(groups.back()[j])) - min(get<1>(ranges[i]), get<1>(groups.back()[j])) > 1;
        }
        flag2 |= flag3;
      }
      if(flag2) {
        int i;
        bool flag3;
        do {
          i = random(0, sz(ranges)-1);
          flag3 = true;
          for(int j = 0; j < sz(groups.back()); ++j) {
            flag3 &= max(get<0>(ranges[i]), get<0>(groups.back()[j])) - min(get<1>(ranges[i]), get<1>(groups.back()[j])) > 1;
          }
        } while(!flag3);
        groups.back().push_back(ranges[i]);
        ranges.erase(ranges.begin() + i);
      }
    } while(flag2);*/
    int flag = 0;
    for(int i = 0; i < sz(ranges); ++i) {
      for(int j = i+1; j < sz(ranges); ++j) {
        if(max(get<0>(ranges[i]), get<0>(ranges[j])) - min(get<1>(ranges[i]), get<1>(ranges[j])) > 1) {
          flag = 1;
          break;
        }
      }
    }
    if(flag) {
      int i, j;
      do {
        i = random(0, sz(ranges)-1);
        j = random(0, sz(ranges)-2);
        if(j == i) ++j;
      } while(max(get<0>(ranges[i]), get<0>(ranges[j])) - min(get<1>(ranges[i]), get<1>(ranges[j])) <= 1);
      groups.push_back({});
      groups.back().push_back(ranges[i]);
      groups.back().push_back(ranges[j]);
      if(i > j) swap(i, j);
      ranges.erase(ranges.begin() + j);
      ranges.erase(ranges.begin() + i);
    } else {
      groups.push_back({});
      groups.back().push_back(ranges.back());
      ranges.pop_back();
    }
  }
  shuffle(all(groups), rng);

  double cur = prv - 3;

  double x1 = double(L) - 0.3;
  double y1 = cur + 0.3;

  if(!nopar) {
    out << string_format(
      "\\draw[thick,->] (%lf,%lf) -- (%lf,%lf);",
      px, py, double(L+R+1)/2.0, cur + 0.3
    ) << endl;
  }

  double chosen_rect_top;

  for(auto cur_group : groups) {
    for(auto [l, r, idx] : cur_group) {
      out << string_format(
        "\\draw[very thin%s] (%d,%lf) rectangle (%d, %lf);",
        string(idx == cidx ? ",fill=lightgray" : "").data(), l, cur, r+1, cur - 0.5
      ) << endl;
      if(idx == cidx) {
        out << string_format(
          "\\draw[very thin,fill=black!50] (%lf,%lf) rectangle (%lf,%lf);",
          double(p), cur, double(p)+1, cur-0.5
        ) << endl;
        chosen_rect_top = cur;
      }
      out << string_format(
        "\\node[scale=0.6] at (%lf,%lf) {$%d$};",
        double(l) + 0.5, cur - 0.25, idx+1
      ) << endl;
      if(cidx == idx) {
        out << string_format(
          "\\node[scale=0.6] at (%lf,%lf) {$c_%d \\rightarrow$};",
          double(l) - 0.5, cur - 0.25, K
        ) << endl;
      }
    }
    cur -= 0.5 + 0.3;
  }
  /*out << string_format(
    "\\draw (%lf,%lf) grid (%lf,%lf);",
    double(L), cur, double(R+1), cur-1
  ) << endl;*/
  for(int i = L+1; i <= R; ++i) {
    out << string_format(
      "\\draw[thick] (%lf,%lf) -- (%lf,%lf);",
      double(i), cur, double(i), cur-1
    ) << endl;
  }
  out << string_format(
    "\\draw[thick] (%lf,%lf) rectangle (%lf,%lf);",
    double(L), cur, double(R)+1, cur-1
  ) << endl;
  out << string_format(
    "\\node[scale=0.6] at (%lf,%lf) {$p_%d$};",
    double(p) + 0.5, cur - 0.5, K--
  ) << endl;
  out << string_format(
    "\\draw[thick,dashed,->] (%lf,%lf) -- (%lf,%lf);",
    double(p) + 0.5, cur, double(p) + 0.5, chosen_rect_top-0.5
  ) << endl;
  /*out << string_format(
    "\\draw[thick] (%lf,%lf) -- (%lf,%lf);",
    double(L), cur, double(R)+1, cur
  ) << endl;
  out << string_format(
    "\\draw[thick] (%lf,%lf) -- (%lf,%lf);",
    double(L), cur-1, double(R)+1, cur-1
  ) << endl;*/


  solve(cur-1, L, p-1, Lranges, out, double(L) + double(R-L+1)/3.0, cur - 1 - 0.3, false);
  solve(cur-1, p+1, R, Rranges, out, double(L) + double(R-L+1)/3.0*2.0, cur - 1 - 0.3, false);

  double x2 = double(R+1) + 0.3;
  double y2 = cur - 1 - 0.3;

  out << string_format(
    "\\draw[thin,dashed,black!50] (%lf,%lf) rectangle (%lf,%lf);",
    x1, y1, x2, y2
  ) << endl;
}

int main(int argc, char const *argv[])
{
  ofstream out("seed");
  out << seed << endl;
  out.close();

  out.open("code_machine.tikz");
  out << "\\begin{tikzpicture}[scale=0.5]\n";
  // out << "\\begin{scope}\n";

  int n = 25;
  int m = 20;

  vector<tri> ranges;
  for(int i = 0; i < m; ++i) {
    int l = random(0, n-1);
    int r = random(0, n-1);
    if(l > r) swap(l, r);
    ranges.emplace_back(l, r, i);
  }

  calc(0, n-1, ranges);

  reverse(all(random_numbers));

  solve(0, 0, n-1, ranges, out, 0, 0);

  /*out << string_format(
    "\\draw (0, 0) grid (%d, 1);", n
  ) << endl;

  double cur_y = 1;

  for(int i = 0; i < m; ++i) {
    cur_y += 0.2;
    out << string_format(
      "\\draw (%d,%lf) rectangle (%d, %lf);",
      ranges[i].fi, cur_y, ranges[i].se+1, cur_y + 0.5
    ) << endl;
    out << string_format(
      "\\node[scale=0.6] at (%lf,%lf) {$%d$};",
      ranges[i].fi + 0.5, cur_y + 0.25, i+1
    ) << endl;
    cur_y += 0.5;
  }*/

  // out << "\\end{scope}\n";
  out << "\\end{tikzpicture}" << endl;
  system("xelatex test.tex");
  system("okular test.pdf");
  return 0;
}
/*
* use std::array instead of std::vector, if u can
* overflow?
* array bounds
*/
