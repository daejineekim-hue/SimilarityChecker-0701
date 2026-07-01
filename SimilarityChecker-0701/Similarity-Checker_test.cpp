#include "gmock/gmock.h"
#include <string>
#include "Similarity-Checker.cpp"

// #include "SimilarityChecker.cpp" // 구현 클래스 포함

// -----------------------------------------------------------------
// Case 1: 두 문자열의 글자 수가 완전히 같은 경우 (최대 점수 60점 반환)
// -----------------------------------------------------------------
TEST(SimilarityCheckerTest, ReturnMaxScoreWhenLengthIsExactlySame) {
    SimilarityChecker checker;

    // 예: "ASD"와 "DSA"는 둘 다 3글자로 동일함
    EXPECT_EQ(60, checker.getLengthScore("ASD", "DSA"));
}

// -----------------------------------------------------------------
// Case 2: 한쪽 문자열이 다른 쪽보다 2배 이상 긴 경우 (0점 반환)
// -----------------------------------------------------------------
TEST(SimilarityCheckerTest, ReturnZeroScoreWhenOneLengthIsMoreThanDouble) {
    SimilarityChecker checker;

    // 1글자 vs 2글자 (정확히 2배 차이)
    EXPECT_EQ(0, checker.getLengthScore("A", "BB"));

    // 3글자 vs 6글자 (2배 차이)
    EXPECT_EQ(0, checker.getLengthScore("ABC", "ABCDEF"));
}

// -----------------------------------------------------------------
// Case 3: 글자 수가 다르지만 2배 미만으로 차이 날 때 (부분 점수 계산 1)
// 공식: (1 - (Gap / B)) * 60
// -----------------------------------------------------------------
TEST(SimilarityCheckerTest, ReturnPartialScoreCase01) {
    SimilarityChecker checker;

    // A = 3 (AAE), B = 2 (AA), Gap = 1
    // 계산: (1 - 1/2) * 60 = 0.5 * 60 = 30점
    EXPECT_EQ(30, checker.getLengthScore("AA", "AAE"));
}

// -----------------------------------------------------------------
// Case 4: 글자 수가 다르지만 2배 미만으로 차이 날 때 (부분 점수 계산 2)
// -----------------------------------------------------------------
TEST(SimilarityCheckerTest, ReturnPartialScoreCase02) {
    SimilarityChecker checker;

    // A = 5 (AAABB), B = 3 (BAA), Gap = 2
    // 계산: (1 - 2/3) * 60 = 1/3 * 60 = 20점
    EXPECT_EQ(20, checker.getLengthScore("AAABB", "BAA"));
}