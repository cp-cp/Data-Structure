#include <iostream>
#include <cmath>

double calculatePolarAngle(double x, double y) {
    // ʹ�� atan2 �������㼫����Ƕ�
    double angle = atan2(y, x);

    // ȷ���Ƕ��� [0, 2*pi] ��Χ��
    if (angle < 0) {
        angle += 2 * M_PI;
    }

    return angle;
}

int main() {
    double x, y;
    std::cout << "�������� x ����: ";
    std::cin >> x;
    std::cout << "�������� y ����: ";
    std::cin >> y;

    double angle = calculatePolarAngle(x, y);
    std::cout << "������Ƕ�Ϊ: " << angle << std::endl;

    return 0;
}
