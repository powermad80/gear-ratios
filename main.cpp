#include <fstream>
#include <iostream>
#include <vector>

class SchematicProcessor {
public:
  std::vector<std::string> schematic;
  int partNumber;
  void getSchematic() {
    std::ifstream file("input.txt");
    std::string line;
    if (!file.is_open()) {
      std::cout << "Can't read input.txt, does it exist?";
      return;
    }

    while (std::getline(file, line)) {
      schematic.push_back('.' + line + '.');
    }
  }
  void addLinePadding() {
    std::string line1;
    std::string line2;
    for (int i = 0; i < schematic[0].length(); i++) {
      line1.push_back('.');
      line2.push_back('.');
    }
    schematic.insert(schematic.begin(), line1);
    schematic.push_back(line2);
  }
  int processLine(std::string prevLine, std::string &curLine,
                  std::string nextLine) {
    int total = 0;
    std::string numLine;
    bool isValid;
    char c;
    for (int i = 1; i < curLine.length() - 1; i++) {
      c = curLine[i];
      isValid = false;
      numLine = "";
      while (isdigit(c) && i < curLine.length() - 1) {
        if (prevLine[i] != '.' && !isdigit(prevLine[i]) ||
            prevLine[i - 1] != '.' && !isdigit(prevLine[i - 1]) ||
            prevLine[i + 1] != '.' && !isdigit(prevLine[i + 1]) ||
            curLine[i - 1] != '.' && !isdigit(curLine[i - 1]) ||
            curLine[i + 1] != '.' && !isdigit(curLine[i + 1]) ||
            nextLine[i] != '.' && !isdigit(nextLine[i]) ||
            nextLine[i - 1] != '.' && !isdigit(nextLine[i - 1]) ||
            nextLine[i + 1] != '.' && !isdigit(nextLine[i + 1])) {
          isValid = true;
        }

        numLine.push_back(c);
        i++;
        c = curLine[i];
      }
      if (isValid && numLine != "") {
        total += stoi(numLine);
      }
    }
    return total;
  }

  int eliminateInvalidNumbers() {
    int total = 0;
    for (int i = 1; i < schematic.size() - 1; i++) {
      total += processLine(schematic[i - 1], schematic[i], schematic[i + 1]);
    }
    return total;
  }

  int addValidNumbers() {

    std::string::iterator lineIt;
    std::vector<std::string>::iterator it;
    std::string numberLine = "";
    int total = 0;
    for (auto it = schematic.begin(); it != schematic.end(); it++) {
      for (auto lineIt = it->begin(); lineIt != it->end(); lineIt++) {
        numberLine = "";
        while (lineIt != it->end() && isdigit(*lineIt)) {
          numberLine += *lineIt;
          lineIt++;
        }
        if (numberLine != "") {
          total += stoi(numberLine);
        }
      }
    }
    return total;
  }

  int getModelNumber() {
    std::cout << "Retrieving schematic...\n";
    getSchematic();
    std::cout << "Padding boundaries...\n";
    addLinePadding();
    std::cout << "Eliminating invalid numbers...\n";
    return eliminateInvalidNumbers();
  }
};

int main() {
  SchematicProcessor santa;
  int result;
  result = santa.getModelNumber();
  std::cout << result << "\n";
  return 0;
}
