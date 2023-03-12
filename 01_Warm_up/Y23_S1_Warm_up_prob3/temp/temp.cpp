#include <iostream>
#include <sstream>
#include <string>

// 입력된 연도의 모든 달의 마지막 날짜와 요일을 출력하는 함수
void printLastDaysOfMonth(int year) {
    std::cout << year << "년의 모든 달의 마지막 날짜와 요일:" << std::endl;
    for (int month = 1; month <= 12; ++month) {
        int lastDay;
        if (month == 2) {
            // 2월의 경우 윤년 여부에 따라 마지막 날짜가 달라짐
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
                lastDay = 29;
            }
            else {
                lastDay = 28;
            }
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11) {
            // 30일인 달
            lastDay = 30;
        }
        else {
            // 31일인 달
            lastDay = 31;
        }
        std::cout << month << "월: " << lastDay << "일" << std::endl;
    }
}

int main() {
    std::string sDate;
    std::cout << "날짜를 입력하세요: ";
    std::getline(std::cin, sDate);

    std::stringstream ss(sDate);
    char input;
    ss >> input;
    


    int year, month, day;
    if (input == 'f') {
        // f가 입력되면 해당 연도의 모든 달의 마지막 날짜와 요일을 출력
        ss >> year;
        printLastDaysOfMonth(year);
    }
    else if (input == 'q') {
        // q가 입력되면 프로그램 종료
        return 0;
    }
    else {
        // 연도/월/일 형태로 입력된 경우
        std::getline(ss, sDate, '/');
        year = std::stoi(sDate);
        std::getline(ss, sDate, '/');
        month = std::stoi(sDate);
        std::getline(ss, sDate, '/');
        day = std::stoi(sDate);

        std::cout << year << " " << month << " " << day;
        // TODO: 해당 날짜의 연도, 월, 일을 출력하고, 마지막 날짜와 요일을 출력하는 코드 추가
        // ...
    }

    return 0;
}