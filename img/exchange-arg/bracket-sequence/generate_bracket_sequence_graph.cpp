#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
  freopen("in", "w", stdout);
  mt19937 rng(time(0));
  auto random = [&rng](int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
  };
  int n = 20;
  vector<int> p(n+1);
  p[0] = 0;
  vector<string> color(n+1);
  vector<int> stk;
  for(int i = 1; i <= n; ++i) {
    int x = 2 * random(0, 1) - 1;
    if(x < 0) {
      if(stk.empty()) {
        color[i] = "red";
      } else {
        stk.pop_back();
      }
    } else {
      stk.push_back(i);
    }
    p[i] = p[i-1] + x;
  }
  while(stk.size()) {
    color[stk.back()] = "blue";
    stk.pop_back();
  }
  for(int i = 1; i <= n; ++i) {
    if(color[i] == "") {
      color[i] = "black";
    }
  }
  for(int i = 1; i <= n; ++i) {
    cout << i-1 << ' ' << p[i-1] << ' ' << i << ' ' << p[i] << ' ' << color[i] << endl;
  }

  system("python plot_bracket_sequence_graph.py in");
  return 0;
}