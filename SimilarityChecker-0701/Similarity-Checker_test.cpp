#include "gmock/gmock.h"
#include <string>
#include "Similarity-Checker.cpp"

// 위에 구현한 클래스가 다른 파일에 있다면 #include "SimilarityChecker.cpp" 추가

TEST(SimilarityCheckerTest, CheckLengthScore) {
    SimilarityChecker checker;

    // Case 1: 글자 수가 완전히 같을 때 -> 60점 (예: ASD, DSA)
    EXPECT_EQ(60, checker.getLengthScore("ASD", "DSA"));

    // Case 2: 길이가 2배 이상 차이 날 때 -> 0점 (예: A, BB)
    EXPECT_EQ(0, checker.getLengthScore("A", "BB"));
    EXPECT_EQ(0, checker.getLengthScore("ABC", "ABCDEF")); // 3글자, 6글자 (정확히 2배)

    // Case 3: 부분 점수 계산 (예: AA, AAE)
    // A = 3 (AAE), B = 2 (AA), Gap = 1
    // 공식: (1 - 1/2) * 60 = 0.5 * 60 = 30점
    EXPECT_EQ(30, checker.getLengthScore("AA", "AAE"));

    // Case 4: 부분 점수 계산 (예: AAABB, BAA)
    // A = 5 (AAABB), B = 3 (BAA), Gap = 2
    // 공식: (1 - 2/3) * 60 = 1/3 * 60 = 20점
    EXPECT_EQ(20, checker.getLengthScore("AAABB", "BAA"));
}