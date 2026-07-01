#include "gmock/gmock.h"
#include <string>
#include "Similarity-Checker.cpp"
#include "gmock/gmock.h"
#include <string>

// -----------------------------------------------------------------
// [알파벳 검사] Case 1: 구성 알파벳 종류가 완전히 같은 경우 (40점 만점)
// -----------------------------------------------------------------
TEST(SimilarityCheckerTest, ReturnMaxAlphaScoreWhenSameAlphabets) {
    SimilarityChecker checker;

    // 예: "ASD", "DSA" -> 사용된 알파벳 {A, D, S}로 동일
    EXPECT_EQ(40, checker.getAlphabetScore("ASD", "DSA"));

    // 예: "AAABB", "BA" -> 사용된 알파벳 {A, B}로 동일
    EXPECT_EQ(40, checker.getAlphabetScore("AAABB", "BA"));
}

// -----------------------------------------------------------------
// [알파벳 검사] Case 2: 사용된 알파벳이 완전히 다를 경우 (0점)
// -----------------------------------------------------------------
TEST(SimilarityCheckerTest, ReturnZeroAlphaScoreWhenNoMatch) {
    SimilarityChecker checker;

    // 예: "A", "BB" -> 공통 알파벳 없음
    EXPECT_EQ(0, checker.getAlphabetScore("A", "BB"));
}

// -----------------------------------------------------------------
// [알파벳 검사] Case 3: 알파벳이 일부만 겹치는 경우 (부분 점수)
// -----------------------------------------------------------------
TEST(SimilarityCheckerTest, ReturnPartialAlphaScore) {
    SimilarityChecker checker;

    // 예: "AA", "AAE"
    // 문자열 1 알파벳: {A} (1개)
    // 문자열 2 알파벳: {A, E} (2개)
    // SameCnt = 1 ({A}), TotalCnt = 2 ({A, E})
    // 공식: (1 / 2) * 40 = 20점
    EXPECT_EQ(20, checker.getAlphabetScore("AA", "AAE"));
}

// -----------------------------------------------------------------
// [통합 점수 검사] 전체 100점 만점 시나리오 테스트
// -----------------------------------------------------------------
TEST(SimilarityCheckerTest, ReturnFullTotalScoreScenario) {
    SimilarityChecker checker;

    // 예: "AA" vs "AAE"
    // 1. 글자수 점수: A=3, B=2, Gap=1 -> (1 - 0.5) * 60 = 30점
    // 2. 알파벳 점수: Same=1, Total=2 -> (1 / 2) * 40 = 20점
    // 총점 = 50점
    EXPECT_EQ(50, checker.getFullScore("AA", "AAE"));
}

TEST(SimilarityCheckerTest, Return100FullScoreWhenPerfectMatch) {
    SimilarityChecker checker;

    // "ASD" vs "DSA"
    // 1. 글자 수 검사: 3글자 vs 3글자 -> 완전히 같으므로 60점 만점
    // 2. 알파벳 검사: {A, D, S} vs {A, D, S} -> 종류가 완전히 같으므로 40점 만점
    // 총점 = 100점
    EXPECT_EQ(100, checker.getFullScore("ASD", "DSA"));
}