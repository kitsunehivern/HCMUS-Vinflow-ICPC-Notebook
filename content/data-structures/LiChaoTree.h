/**
 * Author: Minh Quan Dinh Cao
 * Date: 2024-11-14
 * License: CC0
 * Description: Add lines of form $ax + b$ where $l \leq x \leq r$ and query the minimum value at $x$.
 * Time: $O(\log^2 N)$ for insert and $O(\log N)$ for query.
 * Status: tested
 */

struct LiChaoTree {
    struct line {
        int a; ll b;
        line(int a = 0, ll b = MAXX) : a(a), b(b) {}
        ll operator () (ll x) { return a * x + b; }
    };
    struct pnode {
        pnode* lch; pnode* rch; line ln;
        pnode(line ln = line()) : lch(nullptr), rch(nullptr), ln(ln) {}
    };
    ll s, e; pnode* root;
    LiChaoTree(ll s = 0, ll e = 0) : s(s), e(e), root(new pnode()) {}
    void insert(pnode*& root, ll st, ll ed, ll lt, ll rt, line ln) {
        #define new_node(x) if (!x) { x = new pnode(); }
        if (rt < st || ed < lt) { return; }
        ll md = st + (ed - st) / 2;
        if (lt <= st && ed <= rt) {
            bool chk_st = ln(st) < root->ln(st);
            bool chk_md = ln(md) < root->ln(md);
            if (chk_md) { swap(root->ln, ln); }
            if (st == ed) { return; }
            if (chk_st != chk_md) {
                new_node(root->lch);
                insert(root->lch, st, md, lt, rt, ln);
            } else {
                new_node(root->rch);
                insert(root->rch, md + 1, ed, lt, rt, ln);
            }
        } else {
            new_node(root->lch);
            new_node(root->rch);
            insert(root->lch, st, md, lt, rt, ln);
            insert(root->rch, md + 1, ed, lt, rt, ln);
        }
        #undef new_node
    }
    ll query(pnode* root, ll st, ll ed, ll val) {
        if (!root) { return line().b; }
        if (st == ed) { return root->ln(val); }
        ll md = st + (ed - st) / 2;
        if (val <= md) { return min(root->ln(val), query(root->lch, st, md, val)); }
        return min(root->ln(val), query(root->rch, md + 1, ed, val));
    }
    void insert(int a, ll b, ll l, ll r) { insert(root, s, e, l, r, line(a, b)); }
    void insert(int a, ll b) { insert(root, s, e, s, e, line(a, b)); }
    ll query(ll val) { return query(root, s, e, val); }
};
