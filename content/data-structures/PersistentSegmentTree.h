/**
 * Author: ChatGPT
 * Date: 2025-11-08
 * License: CC0
 * Source: ChatGPT
 * Description: We know
 * Time: O(\log N).
 * Status: Not tested
 */

#pragma once

struct node { int l, r, sum; } tree[69];
int tim = 0;

int new_node(int l=-1, int r=-1, int sum=0) {
    tree[++tim] = {l, r, sum}; return tim;
}

int val(int p) { return p==-1 ? 0 : tree[p].sum; }

int update(int p, int l, int r, int i, int x) {
    int q = (p==-1 ? new_node() : new_node(tree[p].l, tree[p].r, tree[p].sum));
    if (l == r) { tree[q].sum += x; return q; }
    int m = l+r>>1;
    if (i <= m) tree[q].l = update(tree[q].l, l, m, i, x);
    else tree[q].r = update(tree[q].r, m + 1, r, i, x);
    tree[q].sum = val(tree[q].l) + val(tree[q].r);
    return q;
}

int query(int p, int l, int r, int x, int y) {
    if (p == -1 || y < l || r < x) return 0;
    if (x <= l && r <= y) return tree[p].sum;
    int m = l+r>>1;
    return query(tree[p].l, l, m, x, y) + query(tree[p].r, m + 1, r, x, y);
}
