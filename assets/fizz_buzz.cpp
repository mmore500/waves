#include <iostream>
#include <string>
#include <range/v3/all.hpp>

using namespace ranges;


auto fizz = {"", "", "fizz"}; // fizzes come in 3s

auto fizzes = fizz | views::cycle; // all the 'fizz'es

auto buzz = {"", "", "", "", "buzz"}; // buzzes come in 5s

auto buzzes = buzz | views::cycle; // all the 'buzz'es

auto words = views::zip_with(std::plus<std::string>{}, fizzes,
                            buzzes); // all the 'fizz', 'buzz', and 'fizzbuzz'es

auto nums = views::iota(1); // all the numbers

// if not a 'fizz', 'buzz', or 'fizzbuzz' then a stringy number
auto choice = [](auto w, auto n) { return w.empty() ? std::to_string(n) : w; };

// voila! we have fizzbuzz
auto fizzbuzz = views::zip_with(choice, words, nums);

int main(int , char **argv) {

  for (auto f : fizzbuzz | views::take(std::stoi(argv[1])))
    std::cout << f << '\n';	
}



