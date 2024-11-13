/**
 * Author: Asif Jawad
 * Date: 2020-04-24
 * License: CC0
 * Source: https://asfjwd.github.io/2020-04-24-floor-sum-ap/
 * Description: Given $a, b, c, n$, compute $\sum_{x = 0}^{n} \left\lfloor \frac{ax + b}{c} \right\rfloor$.
 * Time: O(\log a)
 * Status: tested
 */
#pragma once

ll FloorSumAP1(ll a, ll b, ll c, ll n) {
	if (!a) return (b / c) * (n + 1);
	if (a >= c || b >= c) return ((n * (n + 1)) / 2) * (a / c) + (n + 1) * (b / c) + FloorSumAP1(a % c, b % c, c, n);
	ll m = (a * n + b) / c;
	return m * n - FloorSumAP(c, c - b - 1, a, m - 1);
}
