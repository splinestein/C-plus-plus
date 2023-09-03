#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip>

// Reads a FASTA DNA sequence and calculates its G/C percentage.

class DNA {
public:
    std::string sequence;
    std::unordered_map<char, int> freq;
    double cachedGCPercentage;

    DNA(const std::string& sequence) : sequence(sequence) {
        // Initialize the freq unordered_map and calculate GC percentage.
        initializeFreq();
        initializeGCPercentage();
    }

private:
    void initializeFreq() {
        for (char letter : this->sequence) {
            if (letter == 'G' || letter == 'C') {
                auto it = this->freq.find(letter);

                if (it == this->freq.end()) {
                    // Not found. Initialize.
                    this->freq.insert(std::pair<char, int>(letter, 1));
                }
                else {
                    // Found. Add 1.
                    it->second++;
                }
            }
        }
    }

    void initializeGCPercentage() {
        const int totalGC = this->freq['G'] + this->freq['C'];
        double percentageGC = 0.0;

        // Main calculation & ensures no 0 division error.
        if (totalGC > 0) {
            percentageGC = (static_cast<double>(totalGC) / this->sequence.length()) * 100.0;
        }

        this->cachedGCPercentage = percentageGC;
    }
};

void createSequence() {
    std::string dnaSequence;

    std::cout << "Type a DNA sequence: ";
    std::cin >> dnaSequence;

    DNA dna(dnaSequence);

    // Ensures that output will always display precision up to 10 decimal places.
    std::cout << std::fixed << std::setprecision(10);
    std::cout << dna.sequence << " : " << dna.cachedGCPercentage << "%" << std::endl;
}

int main() {
    createSequence();

    return 0;
}
