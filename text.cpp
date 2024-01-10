#include <vector>
#include <algorithm>
#include <iostream>

bool next_perm(std::vector<int>& nums) {
    int i = nums.size() - 2;
    while (i >= 0 && nums[i] >= nums[i + 1]) {
        i--;
    }
    if (i >= 0) {
        int j = nums.size() - 1;
        while (j >= 0 && nums[j] <= nums[i]) {
            j--;
        }
        std::swap(nums[i], nums[j]);
    }
    std::reverse(nums.begin() + i + 1, nums.end());
    return i >= 0;
}

void print(const std::vector<int>& v) {
    for (int i : v) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::vector<int> v{1, 2, 3};
    print(v);
    while (next_perm(v)) {
        print(v);
    }
    return 0;
}