#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

struct Image {
    double quality;
    double freshness;
    double rating;
};

struct Params {
    double a;
    double b;
    double c;
};

class FunctionPart {
private:
    char operation;
    double value;

public:
    FunctionPart(char new_c, double new_v) : operation(new_c), value(new_v) {};

    double Apply(double source_value) const {
        if (operation == '+') {
            return source_value + value;
        }
        else if (operation == '-') {
            return source_value - value;
        }
        else if (operation == '*') {
            return source_value * value;
        }
        else {
            return source_value / value;
        }
    }

    void Invert() {
        if (operation == '+') operation = '-';
        else if (operation == '-') operation = '+';
        else if (operation == '*') operation = '/';
        else operation = '*';
    }
};

class Function {
private:
    std::vector<FunctionPart> parts;

public:
    void AddPart(char oper, double value) {
        parts.push_back({ oper, value });
    }

    double Apply(double value) const {
        for (const auto &part : parts) {
            value = part.Apply(value);
        }
        return value;
    }

    void Invert() {
        for (auto &part : parts) {
            part.Invert();
        }
        std::reverse(parts.begin(), parts.end());
    }
};

Function MakeWeightFunction(const Params &params, const Image &image) {
    Function function;
    function.AddPart('*', params.a);
    function.AddPart('-', image.freshness * params.b);
    function.AddPart('+', image.rating * params.c);
    return function;
}

double ComputeImageWeight(const Params &params, const Image &image) {
    Function function = MakeWeightFunction(params, image);
    return function.Apply(image.quality);
}

double ComputeQualityByWeight(const Params &params,
    const Image &image, double weight) {
    Function function = MakeWeightFunction(params, image);
    function.Invert();
    return function.Apply(weight);
}

int main() {
    Image image = { 10, 2, 6 };
    Params params = { 4, 2, 6 };
    std::cout << ComputeImageWeight(params, image) << std::endl;
    std::cout << ComputeQualityByWeight(params, image, 52) << std::endl;

    return 0;
}



