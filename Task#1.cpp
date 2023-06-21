#include <iostream>
#include <vector>
#include <string>

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

int main() {
	size_t numberCount;

	std::cerr << "Enter number count: ";
	std::cin >> numberCount;
	std::vector<size_t> numbers(numberCount);
	std::cerr << "Enter numbers : ";
	for (size_t i = 0; i < numberCount; i++) {
		std::cin >> numbers[i];
	}

	size_t binCount;
	std::cerr << "Enter bin count: ";
	std::cin >> binCount;
	std::vector<size_t> bins(binCount);

	// для нашего варианта
	std::string longestLabel;
	std::string lineLabel;
	std::vector<std::string> labels(binCount);
	for (size_t i = 0; i < binCount; i++) {
		std::cerr << "Enter label " << i + 1 << " column: ";
		std::getline(std::cin >> std::ws, lineLabel);
		labels[i] = lineLabel;
		std::cin.clear();
		if (labels[i].length() > longestLabel.length()) {
			longestLabel = labels[i];
		}
	}

	double min = numbers[0];
	double max = numbers[0];
	for (double x : numbers) {
		if (x < min) {
			min = x;
		}
		else if (x > max) {
			max = x;
		}
	}

	double binSize = (max - min) / binCount;
	for (size_t i = 0; i < numberCount; i++) {
		bool found = false;
		for (size_t j = 0; (j < binCount - 1) && !found; j++) {
			auto low = min + j * binSize;
			auto high = min + (j + 1) * binSize;
			if ((low <= numbers[i]) && (numbers[i] < high)) {
				bins[j]++;
				found = true;
			}
		}
		if (!found) {
			bins[binCount - 1]++;
		}
	}

	// для 2 этапа
	// labels[0] = std::to_string(bins[0]);
	// longestLabel = labels[0];
	// for (size_t i = 1; i < binCount; i++) {
	// 	labels[i] = std::to_string(bins[i]);
	// 	if (std::to_string(bins[i]).length() > longestLabel.length()) {
	// 		longestLabel = std::to_string(bins[i]);
	// 	}
	// }

	// вывод
	for (size_t i = 0; i < binCount; i++) {
		std::cout.width(longestLabel.length());
		std::cout << std::right << labels[i] << '|';
		for (size_t j = 0; j < bins[i]; j++) {
			std::cout << '*';
		}
		std::cout << std::endl;
	}

    // Вывод с маштабированием
    size_t max_count = bins[0];
    for(size_t i = 1; i < binCount; i++) {
        if(max_count < bins[i]) max_count = bins[i];
    }
	for (size_t i = 0; i < binCount; i++) {
		std::cout.width(longestLabel.length());
		std::cout << std::right << labels[i] << '|';
		for (size_t j = 0; j < static_cast<size_t>(MAX_ASTERISK * (static_cast<double>(bins[i]) / max_count)); j++) {
			std::cout << '*';
		}
		std::cout << std::endl;
	}

	return 0;
}