#include <iostream>
#include <vector>
#include <string>
#include "json.hpp"  // make sure json.hpp is in the same folder

using namespace std;
using json = nlohmann::json;

// Function to multiply two polynomials
vector<long long> multiplyPoly(vector<long long> a, vector<long long> b) {
    vector<long long> res(a.size() + b.size() - 1, 0);
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < b.size(); j++) {
            res[i + j] += a[i] * b[j];
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read entire JSON input from stdin
    string input((istreambuf_iterator<char>(cin)), istreambuf_iterator<char>());
    json j = json::parse(input);

    int n = j["keys"]["n"];
    int k = j["keys"]["k"];

    vector<long long> roots;

    // Convert all roots into decimal
    for (auto& el : j.items()) {
        if (el.key() == "keys") continue;
        int base = stoi(el.value()["base"].get<string>());
        string value = el.value()["value"].get<string>();
        long long root = stoll(value, nullptr, base);
        roots.push_back(root);
    }

    // Use only first k roots
    roots.resize(k);

    // Build polynomial
    vector<long long> poly = {1}; // start with 1
    for (long long r : roots) {
        vector<long long> factor = {-r, 1}; // (x - r)
        poly = multiplyPoly(poly, factor);
    }

    // Output coefficients
    for (long long c : poly) {
        cout << c << " ";
    }
    cout << "\n";

    return 0;
}
