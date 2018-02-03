/// Test driver for hashtable.h
#include "hashtable.h"
#include "test_helpers.h"

#include <iostream>
#include <string>

using namespace ndl;
using namespace std;

using StrHashT = Hashtable<string, string>;

template <typename F>
void RunKeys(StrHashT& hashtable, F func) {
    for (char i = 'a'; i <= 'z'; ++i) {
        for (char j = 'a'; j <= 'z'; ++j) {
            for (char k = 'a'; k <= 'z'; ++k) {
                string key = std::string(i, 1) + j + k;
                func(hashtable, key);
            }
        }
    }
}
    
int main() {
    StrHashT hashtable;

    auto insert_func = [](StrHashT& hashtable, const string& key) {
        EXPECT_TRUE(hashtable.Add(key, key));
    };
    RunKeys(hashtable, insert_func);
  
    auto update_func = [](StrHashT& hashtable, const string& key) {
        EXPECT_FALSE(hashtable.AddOrUpdate(key, "sheep"));  // false means update
        string* val = hashtable.Get(key);
        EXPECT_TRUE(val != nullptr);
        EXPECT_TRUE(*val == "sheep");
    };
    RunKeys(hashtable, update_func);
  
    auto erase_func = [](StrHashT& hashtable, const string& key) {
        EXPECT_TRUE(hashtable.Erase(key));
    };
    RunKeys(hashtable, erase_func);
  
    auto contains_func = [](StrHashT& hashtable, const string& key) {
        string* val = hashtable.Get(key);
        EXPECT_TRUE(val == nullptr);
    };

    RunKeys(hashtable, contains_func);

    auto update_func2 = [](StrHashT& hashtable, const string& key) {
        EXPECT_TRUE(hashtable.AddOrUpdate(key, "cows"));  // true means new add
        string* val = hashtable.Get(key);
        EXPECT_TRUE(val != nullptr);
        EXPECT_TRUE(*val == "cows");
    };
    RunKeys(hashtable, update_func2);
    cout << "\n -- Tests passed --" << std::endl;
    return 1;
}

