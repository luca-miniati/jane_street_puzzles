#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rand;
    mt19937 gen(rand());
    uniform_real_distribution<double> dist(0.0, 1.0);
    long long int MAX_SAMPLES = 10000000000;

    for (long long int num_samples = 10; num_samples < MAX_SAMPLES; num_samples *= 10) {
        int count = 0;
        double total_rand = 0;
        for (int i = 0; i < num_samples; i++) {
            double x1 = dist(gen), y1 = dist(gen), x2 = dist(gen), y2 = dist(gen);
            total_rand += x1;
            
            double r = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) / 2.0;
            double x3 = (x1 + x2) / 2.0, y3 = (y1 + y2) / 2.0;

            double min_x = x3 - r, max_x = x3 + r, min_y = y3 - r, max_y = y3 + r;

            if (min_x < 0.0 || max_x > 1.0 || min_y < 0.0 || max_y > 1.0) {
                // cout << "P_1: (" << x1 << ", " << y1 << ")" << endl;
                // cout << "P_2: (" << x2 << ", " << y2 << ")" << endl;
                // cout << "r: " << r << endl;
                // cout << "M: (" << x3 << ", " << y3 << ")" << endl;
                count += 1;
            }
        }

        cout << "Num. Samples: " << num_samples << endl;
        cout << "P(x): " << static_cast<double>(count) / static_cast<double>(num_samples) << endl;
        cout << "Avg. rand value: " << total_rand / static_cast<double>(num_samples) << endl;
        cout << endl;
    }
}
