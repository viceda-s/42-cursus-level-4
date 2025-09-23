#include <iostream>
#include <fstream>
#include <string>

#define RESET	"\033[0m"
#define RED		"\033[1;31m"
#define GREEN	"\033[1;32m"
#define YELLOW	"\033[1;33m"

std::string replace(const std::string& content, const std::string& s1, const std::string& s2) {
	if (s1.empty())
		return content;
		
	std::string result;
	size_t pos = 0;
	size_t found = 0;
		
	while ((found = content.find(s1, pos)) != std::string::npos) {
		result += content.substr(pos, found - pos);
		result += s2;
		pos = found + s1.length();
	}
	result += content.substr(pos);
		
	return result;
}

int main(int ac, char **av) {
	if (ac != 4) {
		std::cerr << YELLOW << "⚠️  Usage: " << av[0] << " <filename> <s1> <s2>" << RESET << std::endl;
		return 1;
	}
		
	std::string filename = av[1];
	std::string s1 = av[2];
	std::string s2 = av[3];
		
	std::ifstream inputFile(filename.c_str());
	if (!inputFile.is_open()) {
		std::cerr << RED << "❌  Error: Cannot open file '" << filename << "'" << RESET << std::endl;
		return 1;
	}
		
	std::string content;
	std::string line;
	bool firstLine = true;
		
	while (std::getline(inputFile, line)) {
		if (!firstLine)
			content += "\n";
		content += line;
		firstLine = false;
	}
	inputFile.close();
		
	std::string replacedContent = replace(content, s1, s2);
		
	std::string outputFilename = filename + ".replace";
	std::ofstream outputFile(outputFilename.c_str());
	if (!outputFile.is_open()) {
		std::cerr << RED << "❌ Error: Cannot create output file '" << outputFilename << "'" << RESET << std::endl;
		return 1;
	}
		
	outputFile << replacedContent;
	outputFile.close();
		
	std::cout << GREEN << "✅ File processed successfully. Output written to '" << outputFilename << "'" << RESET << std::endl;
	return 0;
}