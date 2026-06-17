#pragma once
// intl.h

#ifndef GUARD_intl_h
#define GUARD_intl_h

#include <iostream>
#include <vector>
#include "Core.h"

using namespace std;

// Grad와 구조는 같지만 thesis 대신 toeic 변수를 사용합니다.
class Intl : public Core {
public:
	Intl() : toeic(0) {};
	Intl(istream& is) { read(is); };

	double grade() const;
	istream& read(istream&);

private:
	double toeic; // 국제학생을 위한 토익 점수 변수
	Intl* clone() const { return new Intl(*this); }
};

#endif