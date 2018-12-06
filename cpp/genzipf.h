#include <vector>

#ifndef LZZ_genzipf_h
#define LZZ_genzipf_h
class GenZipf {
public:
    GenZipf(double alpha, int n);
    int get();
private:
    std::vector<double> sum_probs;
    double alpha;
    int n;
};
#endif
