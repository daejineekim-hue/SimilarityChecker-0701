#include <string>
#include <algorithm>
#include <cmath>
#include <set>

class SimilarityChecker {
public:
    // 전체 총점을 반환하는 메인 함수 (60점 + 40점 = 100점 만점)
    int getFullScore(const std::string& str1, const std::string& str2) {
        return getLengthScore(str1, str2) + getAlphabetScore(str1, str2);
    }

    // 1. 글자 수 검사 (max 60점)
    int getLengthScore(const std::string& str1, const std::string& str2) {
        size_t len1 = str1.length();
        size_t len2 = str2.length();

        if (len1 == len2) return 60;

        size_t A = std::max(len1, len2);
        size_t B = std::min(len1, len2);

        if (A >= B * 2) return 0;

        double gap = static_cast<double>(A - B);
        double score = (1.0 - (gap / static_cast<double>(B))) * 60.0;
        return static_cast<int>(score);
    }

    // 2. 등장 알파벳 검사 (max 40점)
    int getAlphabetScore(const std::string& str1, const std::string& str2) {
        std::set<char> set1, set2;

        // 각 문자열의 알파벳을 중복 없이 set에 담기
        for (char c : str1) set1.insert(c);
        for (char c : str2) set2.insert(c);

        // SameCnt (교집합) 구하기
        int sameCnt = 0;
        for (char c : set1) {
            if (set2.count(c)) {
                sameCnt++;
            }
        }

        // 모두 다르면 0점
        if (sameCnt == 0) return 0;

        // TotalCnt (합집합) = 집합1 크기 + 집합2 크기 - 교집합 크기
        int totalCnt = set1.size() + set2.size() - sameCnt;

        // 같은 종류의 알파벳만 사용되었다면 (교집합 == 합집합) 최대 점수 40점
        if (sameCnt == totalCnt) return 40;

        // 부분 점수 공식 적용: (SameCnt / TotalCnt) * 40
        double score = (static_cast<double>(sameCnt) / static_cast<double>(totalCnt)) * 40.0;
        return static_cast<int>(score);
    }
};