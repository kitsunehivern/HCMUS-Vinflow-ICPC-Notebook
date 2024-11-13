/**
 * Author: Minh Quan Dinh Cao
 * Date: 2024-11-14
 * License: CC0
 * Source: https://codeforces.com/contest/622/submission/228465797
 * Description: Given $f(x) = p_0, f(x + 1) = p_1, \dots, f(x + n) = p_n$ and an integer $k$, computes $f(x + k)$ where $f$ is a polynomial of degree $n$.
 * Time: O(n \log n)
 * Status: tested
 */

#pragma once

int Lagrange(vector<int> p, int x, int k) {
    assert(k >= x);
    int n = sz(p);
    if (k - x < n) { return p[k - x]; }
    int num = 1, den = 1;
    rep (i, 1, n - 1) {
        num = num * (ll)(k - x - i) % mod;
        den = den * (ll)(mod - i) % mod;
    }
    int res = 0;
    rep (i, 0, n - 1) {
        (res += p[i] * (ll)num % mod * inverse(den) % mod) %= mod;
        num = num * (ll)inverse(k - x - i - 1) % mod * (k - x - i) % mod;
        den = den * (ll)inverse(mod - n + i + 1) % mod * (i + 1) % mod;
    }
    return res;
}
