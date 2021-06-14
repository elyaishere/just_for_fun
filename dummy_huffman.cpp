#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
struct tree {
    int val;
    char c;
    tree* left;
    tree* right;
    tree(int a, char ch): val(a), c(ch), left(nullptr), right(nullptr) {}
    tree(int a, char ch, tree* l, tree* r): val(a), c(ch), left(l), right(r) {}
};

void build_code(map<char, string>& ans, tree* root, string code) {
    if (!root) return;
    if (!root->left && !root->right) {
        ans[root->c] = code;
        return;
    }
    build_code(ans, root->left, code + '0');
    build_code(ans, root->right, code + '1');
}

int main() {
    string s;
    cin >> s;
    map<char, int> f;
    for (auto i: s)
        if (f.find(i) != f.end()) f[i] += 1;
        else f[i] = 1;
    vector<tree*> H;
    for (auto i: f) H.emplace_back(new tree(i.second, i.first));
    while (H.size() != 1) {
        sort(H.begin(), H.end(), [] (tree* a, tree*b){return a->val < b->val;});
        auto t1 = H[0];
        auto t2 = H[1];
        H.erase(H.begin(), H.begin() + 2);
        auto t = new tree(t1->val + t2->val, ' ', t1, t2);
        H.emplace_back(t);
    }
    auto root = H[0];
    map<char, string> ans;
    build_code(ans, root, "");
    if (ans.size() == 1) {
        ans.begin()->second = "0";
    }
    string res;
    for (auto i: s) res += ans[i];
    cout << ans.size() << " " << res.size() << endl;
    for (auto i: ans) cout << i.first << ": " << i.second << endl;
    cout << res << endl;
    return 0;
}
