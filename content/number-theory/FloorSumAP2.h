/**
 * Author: Asif Jawad
 * Date: 2020-04-24
 * License: CC0
 * Source: https://asfjwd.github.io/2020-04-24-floor-sum-ap/
 * Description: Given $a, b, c, n$, compute $g = \sum_{x = 0}^{n} x \left\lfloor \frac{ax + b}{c} \right\rfloor$ and $h = \sum_{x = 0}^{n} \left\lfloor \frac{ax + b}{c} \right\rfloor^2$.
 * Time: O(3 \log a)
 * Status: tested
 */
#pragma once

struct dat {
    ll f, g, h;
    dat(ll f = 0, ll g = 0, ll h = 0) : f(f), g(g), h(h) {};
};
ll mul(ll a, ll b) { return (a * b) % MOD; }
dat FloorSumAP2(ll a, ll b, ll c, ll n) {
    if (!a) return {mul(n + 1, b / c), mul(mul(mul(b / c, n), n + 1), inv2), mul(mul(n + 1, b / c), b /c)};
    ll f, g, h; dat nxt;
    if (a >= c || b >= c) {
        nxt = FloorSumAP2(a % c, b % c, c, n);
        f = (nxt.f + mul(mul(mul(n, n + 1), inv2), a / c) + mul(n + 1, b / c)) % MOD;
        g = (nxt.g + mul(a / c, mul(mul(n, n + 1), mul(2 * n + 1, inv6))) + mul(mul(b / c, mul(n, n + 1)), inv2)) % MOD;
        h = (nxt.h + 2 * mul(b / c, nxt.f) + 2 * mul(a / c, nxt.g) + mul(mul(a / c, a / c), mul(mul(n, n + 1), mul(2 * n + 1, inv6))) + mul(mul(b / c, b / c), n + 1) + mul(mul(a / c, b / c), mul(n, n + 1)) ) % MOD;   
        return {f, g, h};
    }
    ll m = (a * n + b) / c;
    nxt = FloorSumAP2(c, c - b - 1, a, m - 1);
    f = (mul(m, n) - nxt.f) % MOD;
    g = mul( mul(m, mul(n, n + 1)) - nxt.h - nxt.f, inv2);
    h = (mul(n, mul(m, m + 1)) - 2 * nxt.g - 2 * nxt.f - f) % MOD;
    return {f, g, h};
}
