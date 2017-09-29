#include "TableDrawer.h"

typedef BOOL(WINAPI *SETCONSOLEFONT)(HANDLE, DWORD);
SETCONSOLEFONT SetConsoleFont;

enum COLORS {
	BLACK = 0x00,
	YELLOW = 0x60,
};

namespace tabledrawer {

	COORD getCurrentConsoleCursorPosition(HANDLE& consoleHandle) {
		COORD coord;

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (GetConsoleScreenBufferInfo(consoleHandle, &csbi)) {
			coord.X = csbi.dwCursorPosition.X;
			coord.Y = csbi.dwCursorPosition.Y;
		}

		return coord;
	}

	WORD getCurrentConsoleColorAttributes(HANDLE& consoleHandle) {
		WORD oldColorAttrs;
		CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

		GetConsoleScreenBufferInfo(consoleHandle, &csbiInfo);
		oldColorAttrs = csbiInfo.wAttributes;

		return oldColorAttrs;
	}

	void customizeConsole(HANDLE& handle, WORD color) {
		HMODULE hmod = GetModuleHandleA("kernel32.dll");
		SetConsoleFont = (SETCONSOLEFONT)GetProcAddress(hmod, "SetConsoleFont");
		
		if (!SetConsoleFont) {
			throw "ERROR";
		}

		// SetConsoleFont(handle, 3);
		SetConsoleTextAttribute(handle, color);
	}

	void print(HANDLE& handle, COORD coord, WORD color, std::string primitive = " ") {
		customizeConsole(handle, color);
		SetConsoleCursorPosition(handle, coord);

		std::cout << primitive << std::endl;
	}

	void print(HANDLE& handle, COORD coord, std::string primitive = " ") {
		SetConsoleCursorPosition(handle, coord);

		std::cout << primitive << std::endl;
	}

	void printColumnRowData(HANDLE& handle, COORD coord, std::string fieldValue) {
		short fieldValueX = coord.X + LEFT_HORIZONTAL_PADDING;
		short fieldValueY = coord.Y;

		print(handle, { fieldValueX, fieldValueY }, YELLOW, fieldValue);
	}

	void printColumnRow(HANDLE& handle, short x, short y, std::vector<std::string> fieldValues) {
		for (short j = 0; j < (short)fieldValues.size(); j++)
		{
			short cellX = COLUMN_COORD_X(x, j);

			print(handle, { cellX, y }, BLACK);
			printColumnRowData(handle, { cellX + LEFT_HORIZONTAL_PADDING, y }, fieldValues[j]);
		}

		print(handle, { COLUMN_COORD_X(x, (short)fieldValues.size()), y }, BLACK);
	}

	void printTable(short x, short y, std::vector<std::vector<std::string>> table) {
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		WORD oldConsoleColorAttributes = getCurrentConsoleColorAttributes(consoleHandle);
		COORD oldConsoleCursorPosition = getCurrentConsoleCursorPosition(consoleHandle);

		x += oldConsoleCursorPosition.X;
		y += oldConsoleCursorPosition.Y;

		COORD coord = { x, y };

		short rowCount = (short)table.size();
		short columnCount = (short)table[0].size();
		short tableWidth = columnCount * COLUMN_SIZE + 1;

		print(consoleHandle, coord, BLACK, LINE(tableWidth));

		for (short i = 0; i < rowCount; i++)
		{
			printColumnRow(consoleHandle, x, ROW_COORD_Y(y, i), table[i]);
			print(consoleHandle, { x, ROW_LINE_COORD_Y(y, i) }, BLACK, LINE(tableWidth));
		}

		print(consoleHandle, { coord.X, coord.Y + rowCount * 2 }, BLACK, LINE(tableWidth));

		customizeConsole(consoleHandle, oldConsoleColorAttributes);
	}

}