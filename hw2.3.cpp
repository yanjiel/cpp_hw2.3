#include <iostream>
#include <vector>  
#include <format>

struct Row : std::vector<int> {
    std::vector<int> row;

    Row() {}
    Row(std::vector<int> r) {
        row = r;
    }

    void push_back(int i) {
        row.push_back(i);
    }

    int max() {
        return *max_element(row.begin(), row.end());
    }

    Row nextRow() {
        Row result;
        int previous = 0;
        for (auto elt : row) {
            result.push_back(previous + elt);
            previous = elt;
        }
        result.push_back(previous);
        return result;
    }

    void printRow(std::ostream& os, int brickSize) {
        for (auto elt : row) {
            os << std::format("{:^{}}", elt, brickSize) << " ";
        }
        os << std::endl;
    }
};


struct Triangle : std::vector<Row> {
    std::vector<Row> triangle;

    Triangle() {}
    Triangle(std::vector<Row> tri) {
        triangle = tri;
    }

    void push_back(Row r) {
        triangle.push_back(r);
    }

    friend std::ostream& operator <<(std::ostream& os, const Triangle triangle);

    //void printTriangle() {
    //    
    //    Row lastRow = triangle[triangle.size() - 1];
    //    int brickSize = std::to_string(lastRow.max()).size();
    //    //std::cout << "printTriangle: " << brickSize << "," << triangle.size() << std::endl;
    //
    //    for (int i = 0; i < triangle.size(); i++) {
    //        Row row = triangle[i];
    //        std::string spaces((triangle.size() - i - 1) * (brickSize + 1) / 2, ' ');
    //        std::cout << spaces;
    //        for (auto elt : row.row) {
    //            std::cout << std::format("{:^{}}", elt, brickSize) << " ";
    //        }
    //        std::cout << std::endl;;
    //    }
    //}
};

std::ostream& operator <<(std::ostream& os, const Triangle triangle) {
    Row lastRow = triangle.triangle[triangle.triangle.size() - 1];
    int brickSize = std::to_string(lastRow.max()).size();

    for (int i = 0; i < triangle.triangle.size(); i++) {
        Row row = triangle.triangle[i];
        std::string spaces((triangle.triangle.size() - i - 1) * (brickSize + 1) / 2, ' ');
        os << spaces;
        row.printRow(os, brickSize);
    }
    return os;
}

int main() {

    Triangle triangle;
    Row previousRow = std::vector<int>{ 1 };

    int constexpr rows = 20;
    for (int i = 0; i < rows; i++) {
        triangle.push_back(previousRow);
        previousRow = previousRow.nextRow();
    }

    std::cout << triangle;
    //triangle.printTriangle();

    return 0;
}
