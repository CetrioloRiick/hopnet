#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
 
namespace ranges = std::ranges;
 
constexpr bool some_of(auto&& r, auto&& pred) // some but not all
{
    return not (ranges::all_of(r, pred) or ranges::none_of(r, pred));
}
 
constexpr auto w = {1, 2, 3};
static_assert(!some_of(w, [](int x) { return x < 1; }));
static_assert( some_of(w, [](int x) { return x < 2; }));
static_assert(!some_of(w, [](int x) { return x < 4; }));
 
int main()
{
    std::vector<int> v(10, 2);
    std::partial_sum(v.cbegin(), v.cend(), v.begin());
    std::cout << "Among the numbers: ";
    ranges::copy(v, std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
 
    if (ranges::all_of(v.cbegin(), v.cend(), [](int i) { return i % 2 == 0; }))
        std::cout << "All numbers are even\n";
 
    if (ranges::none_of(v, std::bind(std::modulus<int>(), std::placeholders::_1, 2)))
        std::cout << "None of them are odd\n";
 
    auto DivisibleBy = [](int d)
    {
        return [d](int m) { return m % d == 0; };
    };
 
    if (ranges::any_of(v, DivisibleBy(7)))
        std::cout << "At least one number is divisible by 7\n";
}