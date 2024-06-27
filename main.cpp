#include <fstream>
#include <iostream>
#include <vector>

class SchematicProcessor {
public:
  std::vector<std::string> schematic;
  void getSchematic() {
    std::ifstream file("input.txt");
    std::string line;
    if (!file.is_open()) {
      std::cout << "Can't read input.txt, does it exist?";
      return;
    }

    while (std::getline(file, line)) {
      schematic.push_back(line);
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
  void processLine(std::string prevLine, std::string &curLine,
                   std::string nextLine) {
    char c;
    for (int i = 0; i < curLine.length(); i++) {
      c = curLine[i];

      if (isdigit(c) && (i > 0 && i < curLine.length())) {
        if (i == 0 || prevLine[i - 1] == '.' ||
            isdigit(prevLine[i - 1]) && prevLine[i] == '.' ||
            isdigit(prevLine[i]) && i == curLine.length() ||
            prevLine[i + 1] == '.' || isdigit(prevLine[i + 1]) && i == 0 ||
            curLine[i - 1] == '.' ||
            isdigit(curLine[i - 1]) && i == curLine.length() ||
            curLine[i + 1] == '.' || isdigit(curLine[i + 1]) && i == 0 ||
            nextLine[i - 1] == '.' ||
            isdigit(nextLine[i - 1]) && nextLine[i] == '.' ||
            isdigit(nextLine[i]) && i == curLine.length() ||
            nextLine[i + 1] == '.' || isdigit(nextLine[i + 1])) {
          curLine[i] = '.';
        }
      }
    }
  }

  void eliminateInvalidNumbers() {
    for (int i = 1; i < schematic.size() - 1; i++) {
      processLine(schematic[i - 1], schematic[i], schematic[i + 1]);
    }
  }
};

int main() {
  SchematicProcessor santa;
  santa.eliminateInvalidNumbers();
  return 0;
}
