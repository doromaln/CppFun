/// Contains test helpers for use in unit testing.

#include <cassert>
#include <iostream>

#define EXPECT_EQ(LHS, RHS) ExpectEq(LHS, RHS, __FILE__, __LINE__);
#define EXPECT_TRUE(cond) ExpectTrue(cond, __FILE__, __LINE__);
#define EXPECT_FALSE(cond) ExpectFalse(cond, __FILE__, __LINE__);

template <typename LhsT, typename RhsT>
void ExpectEq(const LhsT& lhs, const RhsT& rhs,
              const char* file = nullptr, int line = 0) {
    if (lhs != rhs) {
        std::cout << "\nGot: " << lhs << " Expected: " << rhs;
        if (file != nullptr || line) {
            std::cout << " on file: " << file << " line " << line;
        }
        std::cout << std::endl;
    }
    assert(lhs == rhs);
}

void ExpectTrue(bool cond, const char* file = nullptr, int line = 0) {
    if (!cond) {
        std::cout << "\nExpected true value";
        if (file != nullptr || line) {
            std::cout << " on file: " << file << " line " << line;
        }
        std::cout << std::endl;
    }
    assert(cond);
}

void ExpectFalse(bool cond, const char* file = nullptr, int line = 0) {
    if (!cond) {
        std::cout << "\nExpected false value";
        if (file != nullptr || line) {
            std::cout << " on file: " << file << " line " << line;
        }
        std::cout << std::endl;
    }
    assert(!cond);
}
