#include <string>
#include <algorithm>
#include <cmath>

class SimilarityChecker {
public:
    int getLengthScore(const std::string& str1, const std::string& str2) {
        size_t len1 = str1.length();
        size_t len2 = str2.length();

        // 1. 같은 글자수일 때 최대 점수 60점
        if (len1 == len2) return 60;

        // 긴 문자열(A)과 짧은 문자열(B) 구분
        size_t A = std::max(len1, len2);
        size_t B = std::min(len1, len2);

        // 2. 문자열 길이가 2배 이상 차이가 난다면 0점
        if (A >= B * 2) return 0;

        // 3. 부분 점수 공식 적용: (1 - (Gap / B)) * 60
        double gap = static_cast<double>(A - B);
        double score = (1.0 - (gap / static_cast<double>(B))) * 60.0;

        // 점수는 보통 정수로 반환하므로 내림 또는 반올림 처리 (여기서는 정수형 변환)
        return static_cast<int>(score);
    }
};