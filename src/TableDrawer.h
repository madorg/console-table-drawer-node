#include "windows.h"

#include <iostream>
#include <string>
#include <vector>
#include <tlhelp32.h>   // TODO: what is it and should it be removed?

#define COLUMN_SIZE 12
#define DRAW_UNIT_WIDTH 1
#define COLUMN_COORD_X(x, n) x + n * COLUMN_SIZE
#define ROW_LINE_COORD_Y(y, n) y + n * 2
#define ROW_COORD_Y(y, n) ROW_LINE_COORD_Y(y, n) + 1
#define LEFT_HORIZONTAL_PADDING 1
#define LINE(x) std::string(x, ' ').c_str()

namespace tabledrawer {

	void printTable(short x, short y, std::vector<std::vector<std::string>> table);

}