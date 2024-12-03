/**
 * Author: Vu Hoang Duy
 * Date: 2024-10-12
 * License: CC0
 * Source: https://github.com/HoangDuyVu/Template-/blob/main/SegMentCalculus.cpp
 * Description: Segment tree with ability to add a polynomial to an interval, and compute sum of intervals.
 * Time: O(\log N).
 * Status: Not tested
 */

#pragma once

struct PolySegmentTree {
    int n;
    vector<ll> f;
    vector<vector<ll>> lazy, pre;
    PolySegmentTree(int n = 0) : n(n) {
        f.assign(n*4,0);
        lazy.assign(4,vector<ll>(n*4,0));
        pre.assign(4,vector<ll>(n + 10,0));

        for (int i = 1; i <= n; i++){
            ll g = 1;
            for (int j = 0; j < 4; j++) {
                pre[j][i] = (pre[j][i - 1] + g) % mod;
                g = g * i % mod;
            }
        }     
    }
    inline ll prepare(int id, int l, int r) {
        return (pre[id][r] - pre[id][l - 1] + mod) % mod;
    }
    void add(ll& x, ll y) {
        x += y;
        x %= mod;
        x += mod;
        if (x >= mod) x -= mod;
    }
    void push(int i, int l, int r) {
        int m = (l + r) >> 1;
        for (int j = 0; j < 3; j++) {
            add(lazy[j][i*2],lazy[j][i]);
            add(lazy[j][i*2 + 1],lazy[j][i]);
            add(f[i*2],lazy[j][i]*prepare(j,l,m));
            add(f[i*2 + 1],lazy[j][i]*prepare(j,m + 1,r));
            lazy[j][i] = 0;
        }
    }
    void update(int i, int l, int r, int d, int c, ll a[]) {
        if (d > r || l > c || d > c || l > r) return;
        if (d <= l && r <= c) {
            for (int j = 0 ; j < 4 ; j++) {
                add(lazy[j][i],a[j]);
                add(f[i],a[j]*prepare(j,l,r));
            }
            return;
        }
        push(i,l,r);
        int m = (l + r) >> 1;
        update(i*2,l,m,d,c,a);
        update(i*2 + 1,m + 1,r,d,c,a);
        f[i] = (f[i*2] + f[i*2 + 1] + mod) % mod;
    }
    ll get(int i, int l, int r, int d, int c) {
        if (d > r || l > c || d > c || l > r) return 0;
        if (d <= l && r <= c) return f[i];
        push(i,l,r);
        int m = (l + r) >> 1;
        return (get(i*2,l,m,d,c) + get(i*2 + 1,m + 1,r,d,c)) % mod;
    }
};
