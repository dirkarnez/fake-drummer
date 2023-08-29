#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <cmath>

// Function to generate random numbers based on ECDF and samples
double generateRandomNumber(const std::vector<double>& samples) {
    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Create a uniform distribution [0, 1) for interpolation
    std::uniform_real_distribution<> uniformDist(0.0, 1.0);

    // Generate a random value between 0 and 1
    double randomValue = uniformDist(gen);

    // Find the interval in the ECDF where the random value falls
    auto it = std::upper_bound(samples.begin(), samples.end(), randomValue);

    // Calculate the interpolation weight
    double weight = (randomValue - *(it - 1)) / (*it - *(it - 1));

    // Perform linear interpolation between the two samples
    double interpolatedValue = *(it - 1) + weight * (*it - *(it - 1));

    // Return the interpolated value
    return interpolatedValue;
}

void a(const std::vector<double>& ecdfSamples) {
    // Generate a large number of random numbers based on the ECDF
    const int numSamples = 100000;
    std::vector<double> generatedSamples(numSamples);
    for (int i = 0; i < numSamples; ++i) {
        generatedSamples[i] = generateRandomNumber(ecdfSamples);
    }

    // Compute statistics of the generated samples
    double mean = std::accumulate(generatedSamples.begin(), generatedSamples.end(), 0.0) / numSamples;
    double variance = 0.0;
    for (double value : generatedSamples) {
        variance += (value - mean) * (value - mean);
    }
    variance /= numSamples;
    double standardDeviation = std::sqrt(variance);

    // Print the statistics
    std::cout << "Generated samples statistics:" << std::endl;
    std::cout << "Mean: " << mean << std::endl;
    std::cout << "Variance: " << variance << std::endl;
    std::cout << "Standard Deviation: " << standardDeviation << std::endl;
}
int main() {
    // Define the ECDF samples
    std::vector<double> ecdfSamples = {0.2, 0.4, 0.6, 0.8, 1.0};

    // Generate 10 continuous random numbers based on the ECDF
    for (int i = 0; i < 10; ++i) {
        double randomNumber = generateRandomNumber(ecdfSamples);
        std::cout << "Random number " << i+1 << ": " << randomNumber << std::endl;
    }

    a(ecdfSamples);
    
     // Compute statistics of the generated samples
    double mean = std::accumulate(ecdfSamples.begin(), ecdfSamples.end(), 0.0) / ecdfSamples.size();
    double variance = 0.0;
    for (double value : ecdfSamples) {
        variance += (value - mean) * (value - mean);
    }
    variance /= ecdfSamples.size();
    double standardDeviation = std::sqrt(variance);

    // Print the statistics
    std::cout << "ecdfSamples samples statistics:" << std::endl;
    std::cout << "Mean: " << mean << std::endl;
    std::cout << "Variance: " << variance << std::endl;
    std::cout << "Standard Deviation: " << standardDeviation << std::endl;
    return 0;
}
