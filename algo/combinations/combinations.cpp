#include <bitset>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

template <typename T>
string join(const vector<T> &vec)
{
    ostringstream os;
    for (const auto &i : vec) {
        os << i << " ";
    }
    string str = os.str();
    if (!str.empty())
        str.pop_back();
    return str;
}

string select_join(const vector<string> &vec, const vector<int> &mask)
{
    assert(vec.size() == mask.size());
    ostringstream os;
    for (int i = 0, n = vec.size(); i < n; i++) {
        if (mask[i])
            os << vec[i] << " ";
    }
    string str = os.str();
    if (!str.empty())
        str.pop_back();
    return str;
}

int count_one(const vector<int> &vec)
{
    return count(begin(vec), end(vec), 1);
}

void add_one(vector<int> &vec)
{
    int carry_bit = 1;
    for (int i = 0, n = vec.size(); i < n; i++) {
        int sum = vec[i] + carry_bit;
        carry_bit = sum / 2;
        vec[i] = sum % 2;

        if (carry_bit == 0)
            break;
    }
}

int main(int argc, char *argv[])
{
    // example: a.out 3 a b c d 
    if (argc < 2 || stoi(argv[1]) > argc-2) {
        cout << "usage: " << argv[0]
                << " num item1 [item2] ..."
                << endl;
        return 1;
    }

    auto select_num = atoi(argv[1]);
    auto origin_set = vector<string>(&argv[2], &argv[argc]);
    auto total_num = argc-2;
    cout << "combinations " << select_num
        << " from set: " << join(origin_set)
        << endl;

    auto bit_set = vector<int>(total_num, int(0));

    int one_num;
    while ((one_num = count_one(bit_set)) != total_num) {
        if (one_num == select_num)
            cout << select_join(origin_set, bit_set) << endl;
        add_one(bit_set);
    }

    if (one_num == select_num)
        cout << select_join(origin_set, bit_set) << endl;

    return 0;
}
