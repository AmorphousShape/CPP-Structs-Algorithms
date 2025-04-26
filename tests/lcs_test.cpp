#include "../algorithms.hpp"
#include <cassert>

int main() {
    // Basic LCS test
    LCS lcs("abcdef", "zabcf");
    assert(lcs.get() == "abcf");

    // No matching characters
    lcs.newStrings("abc", "xyz");
    assert(lcs.get() == "");

    // Identical strings
    lcs.newStrings("hello", "hello");
    assert(lcs.get() == "hello");

    // s1 is empty
    lcs.newStrings("", "anything");
    assert(lcs.get() == "");

    // s2 is empty
    lcs.newStrings("something", "");
    assert(lcs.get() == "");

    // Single character match
    lcs.newStrings("abc", "dce");
    assert(lcs.get() == "c");

    // Match at end
    lcs.newStrings("123abc", "xyzabc");
    assert(lcs.get() == "abc");

    // Match at beginning
    lcs.newStrings("abcxyz", "abcmno");
    assert(lcs.get() == "abc");

    // Match in the middle
    lcs.newStrings("xxhelloxx", "yyhelloyy");
    assert(lcs.get() == "hello");

    // Case sensitivity
    lcs.newStrings("ABC", "abc");
    assert(lcs.get() == ""); // case-sensitive

    // Repeated subsequences
    lcs.newStrings("abababab", "babababa");
    lcs.get();
    // LCS must be "abababa" or "bababab"
    assert(lcs.lcsLength() == 7);

    // Overlapping subsequences
    lcs.newStrings("abcabcabc", "abcabc");
    assert(lcs.get() == "abcabc");

    // Unicode characters
    lcs.newStrings("mañana", "ana");
    assert(lcs.get() == "ana");

    // Whitespace characters
    lcs.newStrings("a b c", "abc");
    assert(lcs.get() == "abc");

    return 0;
}