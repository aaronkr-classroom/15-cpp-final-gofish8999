// Student_info.cpp
#include <iostream>

#include "Student_info.h"
#include "Core.h"
#include "Grad.h"
#include "Intl.h"   // 1. Intl.h 헤더 추가!
#include "grade.h"

using namespace std;

// 빈 생성자
Student_info::Student_info(const Student_info& s) : cp(0) {
	if (s.cp) cp = s.cp->clone();
}

istream& Student_info::read(istream& is) {
	delete cp; // 이전 객체 있으면 삭제

	char ch;
	is >> ch;	// record 타입 입력

	// 2. record 타입 확인에 'I' (국제학생) 분기 추가
	if (ch == 'U') {
		cp = new Core(is);
	}
	else if (ch == 'G') {
		cp = new Grad(is);
	}
	else if (ch == 'I') {
		cp = new Intl(is); // 'I'일 때 Intl 객체 생성
	}

	return is;
}

Student_info& Student_info::operator=(const Student_info& s) {
	if (&s != this) {
		delete cp;
		if (s.cp)
			cp = s.cp->clone();
		else
			cp = 0;
	}
	return *this;
}

istream& read_hw(istream& in, Vec<double>& hw) {
	if (in) {
		hw.clear();
		double x;
		while (in >> x) {
			hw.push_back(x);
		}
		in.clear();
	}
	return in;
}