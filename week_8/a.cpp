#include <iostream>
#include <cmath>

double calculatePolarAngle(double x, double y) {
    // 使用 atan2 函数计算极坐标角度
    double angle = atan2(y, x);

    // 确保角度在 [0, 2*pi] 范围内
    if (angle < 0) {
        angle += 2 * M_PI;
    }

    return angle;
}

int main() {
    double x, y;
    std::cout << "请输入点的 x 坐标: ";
    std::cin >> x;
    std::cout << "请输入点的 y 坐标: ";
    std::cin >> y;

    double angle = calculatePolarAngle(x, y);
    std::cout << "极坐标角度为: " << angle << std::endl;

    return 0;
}
