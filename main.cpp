#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <fstream>

std::string removeUnnecessaryElements(std::string str){
    str.erase(
            std::remove_if(str.begin(), str.end(), [](char c) { return c != '(' && c != ')'; }),
            str.end()
    );
    return str;
}

auto maxNestedParenthesesDepth(std::string str) {
    if (str.empty()) return 0;
    str = removeUnnecessaryElements(str);

    auto numericRepresentation{ std::vector<int>(str.size()) };
    std::transform(
            str.begin(), str.end(),
            numericRepresentation.begin(),
            [](auto ch) { return ch == '(' ? 1 : -1; }
    );

    std::partial_sum(numericRepresentation.begin(),
                     numericRepresentation.end(),
                     numericRepresentation.begin(),
                     std::plus<int>()
    );

    if (*std::prev(numericRepresentation.end()) != 0) {
        return -1;
    }

    auto value{
            *std::max_element(
                    numericRepresentation.begin(),
                    numericRepresentation.end()
            )
    };
    return value;
}

void printResults(const std::vector<std::string>& records){
    auto counter { 0u };
    for (const auto& sample : records){
        auto depth { maxNestedParenthesesDepth(sample) };
        std::cout << '[' << ++counter <<']' << ' ' << depth << std::endl;
    }
}




int main() {
    try {
        std::ifstream file{"records.txt"};
        auto data { std::vector<std::string>{} };
        if (!file) {
            throw std::ios::failure("Error opening a file");
        }
        while (file){
            std::string record{};
            std::getline(file, record);
            if (!record.empty()) {
                data.emplace_back(std::move(record));
            }
        }
        printResults(data);
    }
    catch (const std::exception &ex) {
        std::cerr << "Exception occurred: " << ex.what();
    }

    return 0;
}
