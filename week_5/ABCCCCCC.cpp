#include <iostream>
#include <vector>
#include <cstring>
#include <cstdint>
#include <stack>
#include <cmath>

std::vector<int> find_longest_sequence(int n) {

    if (n < 1) return std::vector<int>();

    struct hash_map {

        struct data {
            int64_t u;
            int v, nex;
        };

        data e[107897 << 1]; 
        int h[107897], cnt;

        int hash(int64_t u) { return (u % 107897 + 107897) % 107897; }

        int& operator[] (int64_t u) {
            int hu = hash(u);
            for (int i = h[hu]; i; i = e[i].nex)
            if (e[i].u == u) return e[i].v;
            return e[++cnt] = (data) {u, 0, h[hu]}, h[hu] = cnt, e[cnt].v;
        }

        hash_map() {
            cnt = 0;
            memset(h, 0, sizeof(h));
        }
    };

    auto gen_hash = [&](int var1, int var2, int var3) {
        return var1 * (n + 1) * (n + 1) + var2 * (n + 1) + var3;
    };

    std::vector<int> best_sequence;

    std::stack<std::pair<std::vector<int>, hash_map>> s;
    for (int i = 1; i <= 1; ++i) {
        for (int j = 1; j <= std::min(n, 2); ++j) {
            for (int k = 1; k <= std::min(n, 3); ++k) {
                hash_map map;
                map[gen_hash(i, j, k)] = 1;
                s.push({{i, j, k}, map});          
            }
        }
    }

    while (!s.empty()) {
        auto [sequence, map] = s.top();
        s.pop();
        if (sequence.size() > best_sequence.size()) {
            best_sequence = sequence;
        }
        if (sequence.size() >= std::pow(n, 3) + 2) break;
        auto var1 = sequence.at(sequence.size() - 2), 
            var2 = sequence.at(sequence.size() - 1);
        for (int var3 = 1; var3 <= n; ++var3) {
            if (!map[gen_hash(var1, var2, var3)]) {
                map[gen_hash(var1, var2, var3)] = 1;
                sequence.push_back(var3);
                s.push({sequence, map});
                sequence.pop_back();
                map[gen_hash(var1, var2, var3)] = 0;
            }
        }
    }

    return best_sequence;
}

int main() {
    for (int i = 1; i <= 10; ++i) {
        auto ans = find_longest_sequence(i);
        std::cout << "Case #" << i << ": " << ans.size() << std::endl;
        for (const auto& i : ans) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}