// intl.cpp
#include <algorithm>
#include <vector>
#include "intl.h"

// Student_info.cpp의 std::vector& 타입과 매칭
istream& read_hw(istream& in, std::vector<double>& hw);

istream& Intl::read(istream& in) {
	Core::read_common(in);  // 이름, 중간, 기말 점수 읽기
	in >> toeic;            // 데이터에서 토익 점수 읽기
	read_hw(in, homework);  // 과제 점수 배열 읽기
	return in;
}

double Intl::grade() const {
	// 일반 학부생 성적 산출 결과와 토익 점수 중 최솟값 반환
	return min(Core::grade(), toeic);
}