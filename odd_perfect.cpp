#include <cstdio>

// If `cond` is true, value is a+b
// If `cond` is false, value is a
template<int a, int b, bool cond>
struct add_if;

template<int a, int b>
struct add_if<a, b, true> {
    constexpr static int value = a + b;
};

// Helper for ProperDivisor sum
// `n` is the number which we are finding the divisors of
// `i` is the candidate divisor we are trying
// `sum` is the running sum of the proper divisors so far
// `done` is whether we are done
template<int n, int i, int sum, bool done>
struct ProperDivisorSumHelper;

// If we are done, the value is just the sum
template<int n, int i, int sum>
struct ProperDivisorSumHelper<n, i, sum, true> {
    constexpr static int value = sum;
};

// If we are not done, we add `i` to the the sum if it is a perfect divisor and
// continue on to the next number
template<int n, int i, int sum>
struct ProperDivisorSumHelper<n, i, sum, false> {
    constexpr static int value =
        ProperDivisorSumHelper<
            n, i+1, add_if<sum, i, n%i==0>::value, i>=n/2
        >::value;
};

// Gives the proper divisor sum for `n`
template<int n>
struct ProperDivisorSum {
    constexpr static int value = ProperDivisorSumHelper<n, 1, 0, false>::value;
};


template<int a, int b>
struct add_if<a, b, false> {
    constexpr static int value = a;
};

// Finds odd perfect numbers (starting search at `n`)
template<int n> struct OddPerfectFinder;

// Helper for OddPerfectFinder
// If `found` is true, value is n
// If `found` is false, value is OddPerfectFinder<n+2>
template<int n, bool found> struct OddPerfectFinderHelper;

template<int n>
struct OddPerfectFinderHelper<n, true> {
    constexpr static int value = n;
};

template <int n>
struct OddPerfectFinderHelper<n, false> {
    constexpr static int value = OddPerfectFinder<n+2>::value;
};

template<int n>
struct OddPerfectFinder {
    constexpr static int value =
        OddPerfectFinderHelper<n, ProperDivisorSum<n>::value==n>::value;
};

int main() {
    printf("%d\n", OddPerfectFinder<3>::value);
}
