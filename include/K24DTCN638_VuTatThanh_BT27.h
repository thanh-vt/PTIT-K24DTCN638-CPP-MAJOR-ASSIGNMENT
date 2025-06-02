#ifndef K24DTCN638_VUTATTHANH_BT27_H
#define K24DTCN638_VUTATTHANH_BT27_H
#include <iosfwd>
#include <memory>
#include <vector>

std::unique_ptr<std::vector<std::vector<int>>> read_and_validate_matrix(std::ifstream file, int size);

void print_convolution_matrix(const std::vector<std::vector<int>> &A, const std::vector<std::vector<int>> &B, int M, int N);

#endif //K24DTCN638_VUTATTHANH_BT27_H
