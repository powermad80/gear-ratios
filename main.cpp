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
  void processLine(std::vector<std::string> schematicPart) {
    char c;
    for (int i = 0; i < schematicPart[1].length(); i++) {
      c = schematicPart[1][i];

      if (isdigit(c) && (i > 0 && i < schematicPart[1].length())) {
        if (i == 0 || schematicPart[0][i - 1] == '.' ||
            isdigit(schematicPart[0][i - 1]) && schematicPart[0][i] == '.' ||
            isdigit(schematicPart[0][i]) && i == schematicPart[1].length() ||
            schematicPart[0][i + 1] == '.' ||
            isdigit(schematicPart[0][i + 1]) && i == 0 ||
            schematicPart[1][i - 1] == '.' ||
            isdigit(schematicPart[1][i - 1]) &&
                i == schematicPart[1].length() ||
            schematicPart[1][i + 1] == '.' ||
            isdigit(schematicPart[1][i + 1]) && i == 0 ||
            schematicPart[2][i - 1] == '.' ||
            isdigit(schematicPart[2][i - 1]) && schematicPart[2][i] == '.' ||
            isdigit(schematicPart[2][i]) && i == schematicPart[1].length() ||
            schematicPart[2][i + 1] == '.' ||
            isdigit(schematicPart[2][i + 1])) {
          schematicPart[1][i] = '.';
        }
      }
    }
  }
  void eliminateInvalidNumbers() {
    getSchematic();
    addLinePadding();
  }
};

int main() {
  SchematicProcessor santa;
  santa.eliminateInvalidNumbers();
  return 0;
}
