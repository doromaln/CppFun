/// An implementation for solving the coin change problem. 
/// See: https://www.hackerrank.com/challenges/coin-change/problem

#include <bits/stdc++.h>

/// TEST INPUT 1 
// 10 4
// 2 5 3 6
// --> 5

/// TEST INPUT 2 
// 15 24
// 49 22 45 6 11 20 30 10 46 8 32 48 2 41 43 5 39 16 28 44 14 4 27 36
// --> 10

/// TEST INPUT 3
// 219 24
// 36 10 42 7 50 1 49 24 37 12 34 13 39 18 8 29 19 43 5 44 28 23 35 26
// --> 168312708

// TEST INPUT 4
// 250 24
// 41 34 46 9 37 32 42 21 7 13 1 24 3 43 2 23 8 45 19 30 29 18 35 11
// --> 15685693751
    
using namespace std;

bool debug = false;
bool dump_output = false;

// The store hashes on the remaining coins and also the amount.
using Store = std::unordered_map<long, long>;
long hash_store(long n, long coin_index) {
    coin_index *= 2654435761U;
    return n ^ coin_index;
}

using DebugList = std::map<long, long>;
    
long getWaysImpl(long n, vector<long> c, Store& store, DebugList& dl, int depth, int coin_index);

long getWays(long n, vector<long> c){
    Store store;  // represents the number of ways we can compute change for given amount.
    DebugList dl;
    std::sort(c.begin(), c.end(), less<long>());  // want coins from lowest to greatest
    return getWaysImpl(n, c, store, dl, 0, c.size() - 1);
}

void dump(const DebugList& dl) {
    if (dump_output) {
        if (dl.empty()) return;
        for (const auto& p: dl) {
            if (p.second) {
                std::cout << "<" << p.first << "-"
                    << p.second << "> ";
            }
        }    
        std::cout << "\n";
    }
}

void spacer(int depth) {
    for (int i = 0; i < depth; ++i) cout << "  ";   
}

long getWaysImpl(long n, vector<long> c, Store& store, DebugList& dl, int depth, int coin_index) {
    // 0. Check if the amount is present in our store (represents number of ways that can made with amount n)
    // 1. Iterate through the list of coins from largest to smallest.
    // 2. For each coin, makes a decision to take 1...d coins, and then iterate.
    // 3. We know that this decision is unique if we subsequently remove this coin from the recursion.
    // 4. Add up these different ways.
    if (debug) {
        spacer(depth);
        cout << "Check Amount: " << n << " coin_index " << coin_index << "\n";
    }
    
    long hash_val = hash_store(n, coin_index);
    if (store.count(hash_val) > 0) {
        long cached_ret = store[hash_val];
        if (debug) {
            spacer(depth);
            cout << "Return cached amount " << n << " ways " << cached_ret << "\n";
        }
        return cached_ret;
    }
    
    long ret_val = 0;
    
    // we iterate from coin-index all the way down to the smallest size coin.
    long coin = numeric_limits<long>::max();
    for (int i = coin_index; i >= 0; --i) {
        /*std::cout << "i " << i << " new coin: " << c[i] 
            << " old coin " << coin << " index " << coin_index 
            << " d " << depth << endl;
        */
        assert(c[i] < coin);  // we should be processing from largest coin to smallest.
        coin = c[i];
        
        if (debug) {
            spacer(depth);
            std::cout << "Process coin " << coin << "\n";
        }
        
        long d = n / coin;
        if (debug) {
            spacer(depth);
            std::cout << "Max d: " << d << "\n";
        }
        for (int j = d; j > 0; --j) {
            long new_n = n - j * coin;
            if (new_n < 0) continue;
            if (debug) {
                spacer(depth);
                cout << "Take " << j << " of coin " << coin << " r: " << new_n << "\n";
            }
            
            if (dump_output) {
                dl[coin] += j;
            }

            if (new_n == 0) {
                ++ret_val;
                dump(dl);
            } else {
                ret_val += getWaysImpl(new_n, c, store, dl, depth + 1, i - 1);
            }

            if (dump_output) {
                dl[coin] -= j;
            }
        }
    }
    
    if (debug) {
        std::cout << "Write Amount: " << n << " Ways: " << ret_val << "\n";
    }
    
    store[hash_val] = ret_val;
    
    return ret_val;
} 

int main() {
    int n;
    int m;
    cin >> n >> m;
    vector<long> c(m);
    for(int c_i = 0; c_i < m; c_i++){
       cin >> c[c_i];
    }
    // Print the number of ways of making change for 'n' units using coins having the values given by 'c'
    long ways = getWays(n, c);
    std::cout << ways << endl;
    return 0;
}
