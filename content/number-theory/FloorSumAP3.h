/**
 * Author: Asif Jawad
 * Date: 2020-04-24
 * License: CC0
 * Source: https://asfjwd.github.io/2020-04-24-floor-sum-ap/
 * Description: Given $a, b, c, n, k_1, k_2$, compute $\sum_{x=0}^{n} x^{k_1} \left\lfloor \frac{ax + b}{c} \right\rfloor^{k_2}$.
 * Status: tested
 * Time: O((k_1 + k_2)^3 \log a)
 */
#pragma once

struct dat{ ll F[11][11]; };
dat FloorSumAP3(ll k1, ll k2, ll a, ll b, ll c, ll n) {
    if (!a) {
        dat ret;
        for (int _k1 = 0; _k1 <= k1 + k2; ++_k1) {
            ret.F[_k1][0] = powerSum(n, _k1);
            for (int _k2 = 1; _k1 + _k2 <= k1 + k2; ++_k2) {
                ret.F[_k1][_k2] = (ret.F[_k1][0] * bigMod(b / c, _k2)) % MOD;
            }
        }
        return ret;
    }
    dat ret;
    if (a >= c) {
        dat nxt = F(k1, k2, a % c, b, c, n);
        for (int _k1 = 0; _k1 <= k1 + k2; ++_k1) {
            ret.F[_k1][0] = powerSum(n, _k1);
            for (int _k2 = 1; _k1 + _k2 <= k1 + k2; ++_k2) {
                ret.F[_k1][_k2] = 0;
                for (int y = 0; y <= _k2; ++y) {
                    ret.F[_k1][_k2] += ((ncr[_k2][y] * bigMod(a / c, y) ) % MOD) * nxt.F[_k1 + y][_k2 - y];
                    ret.F[_k1][_k2] %= MOD;
                }
            }
        }
    } else if (b >= c) {
        dat nxt = F(k1, k2, a, b % c, c, n);
        for (int _k1 = 0; _k1 <= k1 + k2; ++_k1) {
            ret.F[_k1][0] = powerSum(n, _k1);
            for (int _k2 = 1; _k1 + _k2 <= k1 + k2; ++_k2) {
                ret.F[_k1][_k2] = 0;
                for (int y = 0; y <= _k2; ++y) {
                    ret.F[_k1][_k2] += ((ncr[_k2][y] * bigMod(b / c, y) ) % MOD) * nxt.F[_k1][_k2 - y];
                    ret.F[_k1][_k2] %= MOD;
                }
            }
        }
    } else {
        ll m = (a * n + b) / c;
        dat nxt = F(k1, k2, c, c - b - 1, a, m - 1);
        vector<ll> psumM(k1 + k2 + 1), pre(k1 + k2 + 1);
        for (int i = 0; i <= k1 + k2; ++i) psumM[i] = powerSum(m - 1, i);
        for (int _k1 = 0; _k1 <= k1 + k2; ++_k1) {
            for (int i = 0; i <= k1 + k2; ++i) {
                pre[i] = 0;
                for (int j = 0; j <= _k1 + 1; ++j) {
                    pre[i] += (d[_k1][j] * nxt.F[i][j]) % MOD;
                    pre[i] %= MOD;
                }
            }
            ret.F[_k1][0] = powerSum(n, _k1);
            for (int _k2 = 1; _k1 + _k2 <= k1 + k2; ++_k2) {
                ret.F[_k1][_k2] = 0;
                for (int i = 0; i < _k2; ++i) {
                    ret.F[_k1][_k2] += ( (ncr[_k2][i] * psumM[i]) % MOD) * ret.F[_k1][0];
                    ret.F[_k1][_k2] -= ncr[_k2][i] * pre[i];
                    ret.F[_k1][_k2] %= MOD;
                }
            }
        }
    }
    return ret;
}
