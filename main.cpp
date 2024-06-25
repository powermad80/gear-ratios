#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::string> getSchematic() {
  std::ifstream file("input.txt");
  std::string line;
  std::vector<std::string> schematic;
  if (!file.is_open()) {
    std::cout << "Can't read input.txt, does it exist?";
    return schematic;
  }

  while (std::getline(file, line)) {
    schematic.push_back(line);
  }
  return schematic;
}

void eliminateInvalidNumbers(std::vector<std::string> &schematic) {
  bool elimination = false;

  for (int i = 0; i < schematic.size(); i++) {
  }
}

int getValidInts(std::vector<std::string> schematic) {
  int total;

  return total;
}
