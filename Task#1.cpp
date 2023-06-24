#include <iostream>
#include <vector>
#include <string>
#include "svg.h"

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

std::vector<double> input_numbers(size_t count);
void show_histogram(std::vector<double> bins, std::vector<std::string> labels, std::string longestLabel, size_t binCount);
void show_histogram_scaling(std::vector<double> bins, std::vector<std::string> labels, std::string longestLabel, size_t binCount);
void show_histogram_svg(std::vector<double> bins, std::vector<std::string> labels, std::string longestLabel, size_t binCount);
void find_minmax(std::vector<double> numbers, double& min, double& max);
void make_histogram(std::vector<double> numbers, size_t binCount);

int main() {

	// std::cout << "Enter A and B: ";
	// double a, b;
	// std::cin >> a >> b;
    // std::cout << "A + B = " << a + b << '\n'
	// 		  << "A - B = " << a - b << '\n'
	// 		  << "A * B = " << a * b << '\n'
	// 		  << "A / B = " << a / b << '\n';

	////// Ввод данных
	size_t numberCount;
	std::cerr << "Enter number count: ";
	std::cin >> numberCount;
	std::cerr << "Enter numbers : ";
	const auto numbers = input_numbers(numberCount);

	size_t binCount;
	std::cerr << "Enter bin count: ";
	std::cin >> binCount;
	make_histogram(numbers, binCount);

	return 0;
}

std::vector<double> input_numbers(size_t count) {
	std::vector<double> result(count);
	for (size_t i = 0; i < count; i++) {
		std::cin >> result[i];
	}
	return result;
}

void show_histogram(std::vector<double> bins, std::vector<std::string> labels, std::string longestLabel, size_t binCount) {
	for (size_t i = 0; i < binCount; i++) {
		//std::cerr.width(longestLabel.length());
		std::cerr << std::right << labels[i] << '|';
		for (size_t j = 0; j < bins[i]; j++) {
			std::cerr << '*';
		}
		std::cerr << std::endl;
	}
}

void show_histogram_scaling(std::vector<double> bins, std::vector<std::string> labels, std::string longestLabel, size_t binCount) {
	size_t max_count = bins[0];
    for(size_t i = 1; i < binCount; i++) {
        if(max_count < bins[i]) max_count = bins[i];
    }
	for (size_t i = 0; i < binCount; i++) {
		std::cerr.width(longestLabel.length());
		std::cerr << std::right << labels[i] << '|';
		for (size_t j = 0; j < static_cast<size_t>(MAX_ASTERISK * (static_cast<double>(bins[i]) / max_count)); j++) {
			std::cerr << '*';
		}
		std::cerr << std::endl;
	}
}

void show_histogram_svg(std::vector<double> bins, std::vector<std::string> labels, std::string longestLabel, size_t binCount){
	svg_begin(400, 300);

	//std::string temp;
	double top = 0;
	for (size_t bin : bins) {
		const double bin_width = BLOCK_WIDTH * bin;
		svg_text(TEXT_LEFT, top + TEXT_BASELINE, std::to_string(bin));
		svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, getRandomColor(), "black");
		top += BIN_HEIGHT;
	}
	
	svg_end();
}

void find_minmax(std::vector<double> numbers, double& min, double& max) {
	min = numbers[0];
	max = numbers[0];
	for (double x : numbers) {
		if (x < min) {
			min = x;
		}
		else if (x > max) {
			max = x;
		}
	}
}

void make_histogram(std::vector<double> numbers, size_t binCount) {
	double min, max;
	find_minmax(numbers, min, max);
	std::vector<double> bins(binCount);

	////// для нашего варианта 1ЛАБ ///////
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

	////// для 2 этапа 1ЛАБ //////
	// labels[0] = std::to_string(bins[0]);
	// longestLabel = labels[0];
	// for (size_t i = 1; i < binCount; i++) {
	// 	labels[i] = std::to_string(bins[i]);
	// 	if (std::to_string(bins[i]).length() > longestLabel.length()) {
	// 		longestLabel = std::to_string(bins[i]);
	// 	}
	// }


	double binSize = (max - min) / binCount;
	for (size_t i = 0; i < numbers.size(); i++) {
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
	
	//show_histogram(bins, labels, longestLabel, binCount);
	//show_histogram_scaling(bins, labels, longestLabel, binCount);
	show_histogram_svg(bins, labels, longestLabel, binCount);
}
