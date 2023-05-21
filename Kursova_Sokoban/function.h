#pragma once

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <vector>
#include "library.h"

#define MAX_LOADSTRING 100

#define LENGTH 10
#define Icon 1
#define BUTTONPLAY 2
#define NAME 3
#define PICTURE 4
#define LEVEL_1 5
#define LEVEL_2 6
#define LEVEL_3 7
#define LEVEL_4 8
#define LEVEL_5 9
#define BUTTONBACK 11
#define BUTTONRESTART 12
#define ID_INSTRUCTION 13

// Глобальные переменные
HINSTANCE hInst;                                // текущий экземпляр                // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
WCHAR szTitle[MAX_LOADSTRING];
PAINTSTRUCT ps;
RECT rt;
WNDCLASSEXW wcex;
BITMAP bm = { 0 };
ICONINFO iconInfo = { 0 };
LPCWSTR Intruction = L"1.Щоб почати гру необдхідно натиснути кнопку 'Play' та обрати рівень \n2.Користувач грає за жовто-чорний трикутник"
"\n3.Керування здійснюється за допомогою стрілок на клавіатурі \n4.Щоб перемогти у грі потрібно пересунути усі зелені яблука на позиції блакитних кіл і зелене яблуко буде ставати червоним"
"\n5.Якщо ви пересунули яблука так, що перемогти вже не зможете, то можна нажати кнопку 'Restart', щоб рівень почався спочатку \nПриємної гри!";

HWND hButtonPlay;
HWND hStatic;
HWND level1;
HWND level2;
HWND level3;
HWND level4;
HWND level5;
HWND hButtonBack;
HWND hButtonRestart;
HMENU hMenu;

extern std::vector<char> board_level1;
extern std::vector<char> board_level2;
extern std::vector<char> board_level3;
extern std::vector<char> board_level4;
extern std::vector<char> board_level5;
extern std::vector<char> symbol_board;
extern std::vector<char> restart_level;
//std::vector<HBITMAP> board;

std::string state = "Menu";
std::string mes = " ";


//int Player_position;
int Kol_final_place;
int movement;
int back;
int can_be_start = 1;
int level = 0;
int move = 0;
static int cxClient, cyClient;
bool start_level;
bool On_F = false;
int GetKolFinalPlace() {
	int result = 0;
	for (size_t i = 0; i < symbol_board.size(); ++i) {
		if (symbol_board[i] == 'F') { result++; }
	}
	return result;
}

int GetKolRedApple() {
	int result = 0;
	for (size_t i = 0; i < symbol_board.size(); ++i) {
		if (symbol_board[i] == 'R') { result++; }
	}
	return result;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	// Создание битмапы для иконки
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, L"./images/Red_icon.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(hBitmap, sizeof(BITMAP), &bm);

	// Создание иконки на основе битмапы
	iconInfo.fIcon = TRUE;
	iconInfo.xHotspot = 0;
	iconInfo.yHotspot = 0;
	iconInfo.hbmMask = CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);
	iconInfo.hbmColor = hBitmap;
	HICON hIcon = CreateIconIndirect(&iconInfo);

	hBitmap = (HBITMAP)LoadImage(NULL, L"./images/Background.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// установка битмапа в качестве фона окна
	HBRUSH hBrush = CreatePatternBrush(hBitmap);


	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = hIcon;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = hBrush;//(HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_KURSOVASOKOBAN);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = hIcon;
	// загрузка битмапа


	// освобождаем кисть
	DeleteObject(hBrush);
	DeleteObject(hBitmap);
	DeleteObject(hIcon);
	return RegisterClassExW(&wcex);
}//Регистрирует класс окна.

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{

	hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_KURSOVASOKOBAN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	int Width = 800;
	int Height = 600;
	int xPos = (GetSystemMetrics(SM_CXSCREEN) - Width) / 2;
	int yPos = (GetSystemMetrics(SM_CYSCREEN) - Height) / 2;
	DWORD dwStyle = WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX;

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, dwStyle,
		xPos, yPos, Width, Height, nullptr, nullptr, hInstance, nullptr);

	//HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
	//SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
	//SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KURSOVASOKOBAN));

	MSG msg;

	// Цикл основного сообщения:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); //Обрабатывает сообщения в главном окне.

void OnPaintBackGround(HWND hWnd) {
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, L"./images/Background.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// установка битмапа в качестве фона окна
	HBRUSH hBrush = CreatePatternBrush(hBitmap);
	SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)hBrush);
	DeleteObject(hBitmap);
}

void OnPaintButtonBack(HWND hWnd) {
	int x = 0; int y = 0;
	int weight = 100; int height = 40;
	hButtonBack = CreateWindow(_T("button"), _T("back"), WS_CHILD, x, y, weight, height, hWnd, (HMENU)BUTTONBACK, hInst, NULL);
}

void OnPaintButtonRestart(HWND hWnd) {
	int x = 0; int y = 60;
	int weight = 100; int height = 40;
	hButtonRestart = CreateWindow(_T("button"), _T("restart"), WS_CHILD, x, y, weight, height, hWnd, (HMENU)BUTTONRESTART, hInst, NULL);
}

void OnPaintBoard(HWND hWnd, std::vector<HBITMAP> board)
{
	OnPaintBackGround(hWnd);
	HDC hdc = BeginPaint(hWnd, &ps);
	HDC hdcMem = CreateCompatibleDC(hdc);

	// Отрисовываем все изображения в векторе
	GetClientRect(hWnd, &rt);

	int x = ((rt.right - rt.left) - (LENGTH * 48))/ 2;
	int y = ((rt.bottom - rt.top)- (LENGTH * 48)) / 2;
	int i = 0;
	for (const HBITMAP image : board)
	{
		i++;
		if (i % LENGTH) {
			SelectObject(hdcMem, image);
			BitBlt(hdc, x, y, 48, 48, hdcMem, 0, 0, SRCCOPY);
			x += 48; // увеличиваем координаты по X для следующего изображения
		}
		else {
			SelectObject(hdcMem, image);
			BitBlt(hdc, x, y, 48, 48, hdcMem, 0, 0, SRCCOPY);
			x = ((rt.right - rt.left) / 2 - (LENGTH * 48) / 2);
			y += 48; // увеличиваем координаты по X для следующего изображения
		}
	}

	for (const HBITMAP image : board)
	{
		DeleteObject(image);
	}
	DeleteDC(hdcMem);
	EndPaint(hWnd, &ps);
}

void OnPaintMenu(HWND hWnd) {
	GetClientRect(hWnd, &rt);
	int button_height = 60;
	int button_weight = 300;
	int button_x = (rt.right - button_weight) / 2;
	int button_y = (rt.bottom - button_height) / 2;
	hButtonPlay = CreateWindow(_T("button"), _T("Play"), WS_CHILD, button_x, button_y, button_weight, button_height, hWnd, (HMENU)BUTTONPLAY, hInst, NULL);

	HFONT hFont = CreateFont(
		50, 0, 0, 0, FW_NORMAL,
		FALSE, FALSE, FALSE,
		DEFAULT_CHARSET,
		OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY,
		DEFAULT_PITCH,
		L"Arial"
	);

	hStatic = CreateWindow(_T("static"), _T("SOKOBAN"), WS_CHILD | SS_CENTER | SS_NOTIFY, button_x, button_y - (button_height + 1), button_weight, button_height, hWnd, (HMENU)NAME, hInst, NULL);
	SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
}

void OnPaintLevels(HWND hWnd) {
	int x = 20;
	int y = 60;
	int weight = 80;
	int height = 80;
	level1 = CreateWindow(_T("button"), _T("1"), WS_CHILD, x, y, weight, height, hWnd, (HMENU)LEVEL_1, hInst, NULL);
	x += 100;
	level2 = CreateWindow(_T("button"), _T("2"), WS_CHILD, x, y, weight, height, hWnd, (HMENU)LEVEL_2, hInst, NULL);
	x += 100;
	level3 = CreateWindow(_T("button"), _T("3"), WS_CHILD, x, y, weight, height, hWnd, (HMENU)LEVEL_3, hInst, NULL);
	x += 100;
	level4 = CreateWindow(_T("button"), _T("4"), WS_CHILD, x, y, weight, height, hWnd, (HMENU)LEVEL_4, hInst, NULL);
	x += 100;
	level5 = CreateWindow(_T("button"), _T("5"), WS_CHILD, x, y, weight, height, hWnd, (HMENU)LEVEL_5, hInst, NULL);

}

void OnPaintMessageBox(HWND hWnd) {
	HDC hdc = BeginPaint(hWnd, &ps);
	MessageBox(NULL, Intruction, L"Інструкція", MB_OK | MB_ICONINFORMATION);
	EndPaint(hWnd, &ps);
};

std::vector <HBITMAP> GetPictureBoard(std::vector<char> symbol_board) {
	std::vector <HBITMAP> result(symbol_board.size());
	for (size_t i = 0; i < symbol_board.size(); ++i) {
		DeleteObject(result[i]);
		switch (symbol_board[i])
		{
		case 'A':
			result[i] = (HBITMAP)LoadImage(NULL, L"./images/Box.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			break;
		case 'P':
			result[i] = (HBITMAP)LoadImage(NULL, L"./images/Hero.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			break;
		case 'T':
			result[i] = (HBITMAP)LoadImage(NULL, L"./images/Tree.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			break;
		case ' ':
			result[i] = (HBITMAP)LoadImage(NULL, L"./images/Free.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			break;
		case 'R':
			result[i] = (HBITMAP)LoadImage(NULL, L"./images/Box_Apply.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			break;
		case 'G':
			result[i] = (HBITMAP)LoadImage(NULL, L"./images/Grass.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			break;
		case 'F':
			result[i] = (HBITMAP)LoadImage(NULL, L"./images/Final_place.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			break;

		default:
			break;
		}
	}
	return result;
}

int PlayerPosition() {
	for (int i = 0; i < symbol_board.size(); ++i) {
		if (symbol_board[i] == 'P') { return i; }
	}
	return 0;
}

std::vector<char> GetNewPosition(int movement) {
	int Player_position = PlayerPosition();
	int New_Player_position = Player_position + movement;
	char temp;
	int kol_F = GetKolFinalPlace();
	int kol_R = GetKolRedApple();
	//int plus_F = 1000;
	int Old_Player_position = Player_position;
	if (symbol_board[New_Player_position] == 'T') {}
	else {
		if (symbol_board[New_Player_position] == 'A' or symbol_board[New_Player_position] == 'R') {
			if (symbol_board[New_Player_position + movement] == 'T' or symbol_board[New_Player_position + movement] == 'A' or symbol_board[New_Player_position + movement] == 'R') {}

			else if (symbol_board[New_Player_position + movement] == 'F') {
				if (On_F) { move++; }
				if (symbol_board[New_Player_position] == 'A') { On_F = false; }
				//if (Kol_final_place != kol_F + kol_R) { plus_F = Player_position; }
				if (symbol_board[New_Player_position] == 'R') { On_F = true; }

				symbol_board[New_Player_position + movement] = 'R';
				symbol_board[New_Player_position] = symbol_board[Player_position];
				symbol_board[Player_position] = ' ';
				Player_position = New_Player_position;
			}
			else {
				if (On_F) { move++; }
				On_F = false;
				//if (Kol_final_place != kol_F + kol_R) { plus_F = Player_position; }
				if (symbol_board[New_Player_position] == 'R') { On_F = true; }

				temp = symbol_board[New_Player_position + movement];
				symbol_board[New_Player_position + movement] = 'A';
				symbol_board[New_Player_position] = symbol_board[Player_position];
				symbol_board[Player_position] = temp;
				Player_position = New_Player_position;
			}
		}
		else if (symbol_board[New_Player_position] == 'F') {
			if (On_F) { move++; }
			On_F = true;

			symbol_board[New_Player_position] = symbol_board[Player_position];
			symbol_board[Player_position] = ' ';
			Player_position = New_Player_position;
		}
		else {
			if (On_F) { move++; }
			On_F = false;
			//if (Kol_final_place != (kol_F + kol_R)) { plus_F = Player_position; }

			temp = symbol_board[New_Player_position];
			symbol_board[New_Player_position] = symbol_board[Player_position];
			symbol_board[Player_position] = temp;
			Player_position = New_Player_position;
		}
	}
	//if (plus_F + movement == Player_position) {
	//	symbol_board[plus_F] = 'F';
	//}



	if (move == 1) {
		symbol_board[Old_Player_position] = 'F';
		move = 0;
	}


	return symbol_board;
}

bool WinOrNo() {
	if (Kol_final_place == GetKolRedApple()) { 
		if (level - 4 >= can_be_start) {
			can_be_start++;
		}
		return true; }
	else { return false; }
}

void MyMenu(HWND hWnd) {
	hMenu = CreateMenu();
	AppendMenu(hMenu, MF_STRING, ID_INSTRUCTION, L"Інструкція");
	SetMenu(hWnd, hMenu);
}

#endif