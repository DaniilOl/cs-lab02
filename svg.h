#include <iostream>
#include <string>

const auto IMAGE_WIDTH = 400;
const auto IMAGE_HEIGHT = 300;
const auto TEXT_LEFT = 20;
const auto TEXT_BASELINE = 20;
const auto TEXT_WIDTH = 50;
const auto BIN_HEIGHT = 30;
const auto BLOCK_WIDTH = 10;

std::vector<std::string> COLORS = {"#DC143C", "#98FB98", "#20B2AA", "#00FFFF", "#FFFF00", "#FF00FF", "#FFDEAD", "#D2691E"};

std::string getRandomColor() {
    size_t index = rand() % COLORS.size();
    size_t lastColorIndex = index;
    if (index == lastColorIndex) {
        index = (lastColorIndex + 1) % COLORS.size();
    }
    lastColorIndex = index;
    return COLORS[index];
}

void svg_begin(double width, double height) {
    std::cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    std::cout << "<svg ";
    std::cout << "width='" << width << "' ";
    std::cout << "height='" << height << "' ";
    std::cout << "viewBox='0 0 " << width << " " << height << "' ";
    std::cout << "xmlns='http://www.w3.org/2000/svg'>\n";
    } 

void svg_end() {
    std::cout << "</svg>\n";
    }

void
svg_text(double left, double baseline, std::string text) {
    std::cout << "<text x='"<< left <<"' y='" << baseline << "'>"  << text << " |" << "</text>";
}

void svg_rect(double x, double y, double width, double height, std::string color, std::string colorStroke) {
    std::cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' fill='" << color;
    std::cout << "' stroke='" << colorStroke << "' stroke-width='" << 1;
    std::cout <<"'/>";
}

