#include <iostream>
#include <sstream>
#include <string>

// �Էµ� ������ ��� ���� ������ ��¥�� ������ ����ϴ� �Լ�
void printLastDaysOfMonth(int year) {
    std::cout << year << "���� ��� ���� ������ ��¥�� ����:" << std::endl;
    for (int month = 1; month <= 12; ++month) {
        int lastDay;
        if (month == 2) {
            // 2���� ��� ���� ���ο� ���� ������ ��¥�� �޶���
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
                lastDay = 29;
            }
            else {
                lastDay = 28;
            }
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11) {
            // 30���� ��
            lastDay = 30;
        }
        else {
            // 31���� ��
            lastDay = 31;
        }
        std::cout << month << "��: " << lastDay << "��" << std::endl;
    }
}

int main() {
    std::string sDate;
    std::cout << "��¥�� �Է��ϼ���: ";
    std::getline(std::cin, sDate);

    std::stringstream ss(sDate);
    char input;
    ss >> input;
    


    int year, month, day;
    if (input == 'f') {
        // f�� �ԷµǸ� �ش� ������ ��� ���� ������ ��¥�� ������ ���
        ss >> year;
        printLastDaysOfMonth(year);
    }
    else if (input == 'q') {
        // q�� �ԷµǸ� ���α׷� ����
        return 0;
    }
    else {
        // ����/��/�� ���·� �Էµ� ���
        std::getline(ss, sDate, '/');
        year = std::stoi(sDate);
        std::getline(ss, sDate, '/');
        month = std::stoi(sDate);
        std::getline(ss, sDate, '/');
        day = std::stoi(sDate);

        std::cout << year << " " << month << " " << day;
        // TODO: �ش� ��¥�� ����, ��, ���� ����ϰ�, ������ ��¥�� ������ ����ϴ� �ڵ� �߰�
        // ...
    }

    return 0;
}