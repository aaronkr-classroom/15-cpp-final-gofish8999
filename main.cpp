// main.cpp
#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Core.h"
#include "Grad.h"
#include "intl.h" 
#include "Vec.h"
#include "Student_info.h"
#include "median.h"

using namespace std;

// [변경] 이름 중복을 피하기 위해 함수 이름을 'compare_by_grade'로 새로 정의합니다.
bool compare_by_grade(const Core* x, const Core* y) {
	try {
		// 높은 점수 순서(내림차순) 정렬 기준
		return x->grade() > y->grade();
	}
	catch (domain_error&) {
		return false;
	}
}

int main() {
	vector<Core*> students;
	Core* record;
	char ch;
	string::size_type maxlen = 0;

	// 데이터 읽고 저장하기
	while (cin >> ch) {
		if (cin.eof()) break;

		// 입력 조건 검사에 'I' 추가
		if (ch != 'U' && ch != 'G' && ch != 'I') {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		// 'I' 일 때 Intl 객체 동적 할당하는 로직 추가
		if (ch == 'U')
			record = new Core;
		else if (ch == 'G')
			record = new Grad;
		else
			record = new Intl; // 'I'인 경우 Intl 객체 생성

		record->read(cin);

		maxlen = max(maxlen, record->getName().size());
		students.push_back(record);
	}

	// [수정] 중복 에러가 나던 기존 함수 대신, 우리가 새로 만든 'compare_by_grade'를 전달합니다.
	sort(students.begin(), students.end(), compare_by_grade);

	// 이름과 점수를 출력하기
	for (vector<Core*>::size_type i = 0;
		i != students.size(); i++) {

		// dynamic_cast 부분에 Intl 분기 추가하여 (I) 출력 조건 확보
		if (dynamic_cast<Grad*>(students[i])) {
			cout << "(G) ";
		}
		else if (dynamic_cast<Intl*>(students[i])) {
			cout << "(I) "; // 국제학생일 때 (I) 출력
		}
		else {
			cout << "(U) ";
		}

		cout << students[i]->getName()
			<< string(maxlen + 1
				- students[i]->getName().size(), ' ');


		try {
			double final_grade = students[i]->grade();
			streamsize prec = cout.precision();
			cout << setprecision(3) << final_grade << "%"
				<< setprecision(prec) << endl;
		}
		catch (domain_error e) {
			cout << e.what() << endl;
		}

		delete students[i];
	}

	return 0;
}