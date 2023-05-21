#include "library.h"
#include "function.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

std::vector<char> symbol_board = {
	'G','G','G','T','T','T','T','T','G','G',
	'G','T','T','T',' ',' ',' ','T','G','G',
	'G','T','F','P','A',' ',' ','T','G','G',
	'G','T','T','T',' ','A','F','T','G','G',
	'G','T','F','T','T','A',' ','T','G','G',
	'G','T',' ','T',' ','F',' ','T','T','G',
	'G','T','A',' ',' ','A','A','F','T','G',
	'G','T',' ',' ',' ','F',' ',' ','T','G',
	'G','T','T','T','T','T','T','T','T','G',
	'G','G','G','G','G','G','G','G','G','G'
};
std::vector<char> board_level1 = {
	'G','G','G','T','T','T','T','T','G','G',
	'G','T','T','T',' ',' ',' ','T','G','G',
	'G','T','F','P','A',' ',' ','T','G','G',
	'G','T','T','T',' ','A','F','T','G','G',
	'G','T','F','T','T','A',' ','T','G','G',
	'G','T',' ','T',' ','F',' ','T','T','G',
	'G','T','A',' ',' ','A','A','F','T','G',
	'G','T',' ',' ',' ','F',' ',' ','T','G',
	'G','T','T','T','T','T','T','T','T','G',
	'G','G','G','G','G','G','G','G','G','G'
};
std::vector<char> board_level2 = {
	'T','T','T','T','T','T','T','T','T','T',
	'T','F','T','T','T','T','T','F','T','T',
	'T',' ','F',' ',' ',' ',' ','F','T','T',
	'T',' ','T',' ','A',' ','A','F','T','T',
	'T',' ','F',' ','A','R','A',' ',' ','T',
	'T',' ','T',' ',' ',' ','A',' ',' ','T',
	'T','F','F','A',' ',' ',' ',' ',' ','T',
	'T','A','T','A','T','T','T','T',' ','T',
	'T','P',' ',' ',' ',' ',' ',' ',' ','T',
	'T','T','T','T','T','T','T','T','T','T'
};
std::vector<char> board_level3 = {
	'G','G','G','G','G','G','G','G','G','G',
	'G','G','G','T','T','T','T','T','T','G',
	'G','T','T','T',' ','T',' ','F','T','G',
	'G','T','F',' ','A',' ','A',' ','T','G',
	'G','T','T',' ','A','F',' ',' ','T','G',
	'G','T','T',' ',' ',' ',' ','F','T','G',
	'G','T',' ',' ','F','A','P',' ','T','G',
	'G','T',' ','A',' ',' ',' ',' ','T','G',
	'G','T','T','T','T','T',' ',' ','T','G',
	'G','G','G','G','G','T','T','T','T','G'
};
std::vector<char> board_level4 = {
	'G','G','G','G','T','T','T','T','T','G',
	'G','T','T','T','T',' ',' ','T','T','G',
	'G','T','T','F',' ',' ',' ',' ','T','T',
	'G','T','F','A',' ',' ','A','F',' ','T',
	'G','T',' ','A',' ','A',' ',' ',' ','T',
	'T','T',' ',' ',' ',' ','F','A','T','T',
	'T',' ',' ',' ',' ','F','A',' ','T','G',
	'T',' ','F',' ','P',' ','A','F','T','G',
	'T',' ','A',' ',' ',' ','F','T','T','G',
	'T','T','T','T','T','T','T','T','G','G'
};
std::vector<char> board_level5 = {
	'G','T','T','T','T','T','T','T','T','G',
	'G','T','F','A',' ',' ','A','F','T','G',
	'G','T','F','A',' ',' ','A','F','T','G',
	'G','T','F','A',' ',' ','A','F','T','G',
	'G','T','F','A',' ',' ','A','F','T','G',
	'G','T','F','A',' ','P','A','F','T','G',
	'G','T','F','A',' ',' ','A','F','T','G',
	'G','T','F','A',' ',' ','A','F','T','G',
	'G','T','F','A',' ',' ','A','F','T','G',
	'G','T','T','T','T','T','T','T','T','G'
};

std::vector <HBITMAP> board(symbol_board.size());

std::vector <char> restart_level(symbol_board.size());

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		MyMenu(hWnd);
		OnPaintBackGround(hWnd);
		OnPaintMenu(hWnd);
		OnPaintButtonBack(hWnd);
		OnPaintButtonRestart(hWnd);
		OnPaintLevels(hWnd);
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case BUTTONPLAY:
			ShowWindow(hButtonPlay, SW_HIDE);
			ShowWindow(hStatic, SW_HIDE);
			state = "Levels";
			GetClientRect(hWnd, &rt);
			InvalidateRect(hWnd, &rt, FALSE);
			break;
		case LEVEL_1:
			if (can_be_start >= 1) {
				level = LEVEL_1;
				restart_level = board_level1;
				symbol_board = board_level1;
				Kol_final_place = GetKolFinalPlace() + GetKolRedApple();
				state = "Board";
				start_level = true;
				GetClientRect(hWnd, &rt);
				InvalidateRect(hWnd, &rt, FALSE);
			}
			break;
		case LEVEL_2:
			if (can_be_start >= 2) {
				level = LEVEL_2;
				restart_level = board_level2;
				symbol_board = board_level2;
				Kol_final_place = GetKolFinalPlace() + GetKolRedApple();
				state = "Board";
				start_level = true;
				GetClientRect(hWnd, &rt);
				InvalidateRect(hWnd, &rt, FALSE);
			}
			break;
		case LEVEL_3:
			if (can_be_start >= 3) {
				level = LEVEL_3;
				restart_level = board_level3;
				symbol_board = board_level3;
				Kol_final_place = GetKolFinalPlace() + GetKolRedApple();
				state = "Board";
				start_level = true;
				GetClientRect(hWnd, &rt);
				InvalidateRect(hWnd, &rt, FALSE);
			}
			break;		
		case LEVEL_4:
			if (can_be_start >= 4) {
				level = LEVEL_4;
				restart_level = board_level4;
				symbol_board = board_level4;
				Kol_final_place = GetKolFinalPlace() + GetKolRedApple();
				state = "Board";
				start_level = true;
				GetClientRect(hWnd, &rt);
				InvalidateRect(hWnd, &rt, FALSE);
			}
			break;
		case LEVEL_5:
			if (can_be_start >= 5) {
				level = LEVEL_5;
				restart_level = board_level5;
				symbol_board = board_level5;
				Kol_final_place = GetKolFinalPlace() + GetKolRedApple();
				state = "Board";
				start_level = true;
				GetClientRect(hWnd, &rt);
				InvalidateRect(hWnd, &rt, FALSE);
			}
			break;
		case BUTTONBACK:
			switch (back)
			{
			case 2:
				ShowWindow(level1, SW_HIDE);
				ShowWindow(level2, SW_HIDE);
				ShowWindow(level3, SW_HIDE);
				ShowWindow(level4, SW_HIDE);
				ShowWindow(level5, SW_HIDE);
				ShowWindow(hButtonBack, SW_HIDE);
				state = "Menu";
				GetClientRect(hWnd, &rt);
				InvalidateRect(hWnd, &rt, FALSE);
				break;
			case 3:
				ShowWindow(hButtonRestart, SW_HIDE);
				state = "Levels";
				GetClientRect(hWnd, &rt);
				InvalidateRect(hWnd, &rt, FALSE);
				break;
			default:
				break;
			}
			break;
		case BUTTONRESTART:
			symbol_board = restart_level;
			Kol_final_place = GetKolFinalPlace() + GetKolRedApple();
			state = "Board";
			move = 0;
			On_F = false;
			SetFocus(hWnd);
			GetClientRect(hWnd, &rt);
			InvalidateRect(hWnd, &rt, FALSE);
			break;
		case ID_INSTRUCTION:
		{
			mes = "Message";
			GetClientRect(hWnd, &rt);
			InvalidateRect(hWnd, &rt, FALSE);
			break;
		}
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_CTLCOLORSTATIC:
	{
		if ((HWND)lParam == GetDlgItem(hWnd, NAME)) {
			HDC hdc = (HDC)wParam;
		    SetBkColor(hdc, RGB(209,247,202));
			return (int)GetStockObject(NULL_BRUSH);
		}

	}
		break;
	case WM_PAINT:
	{
		if (state == "Menu")
		{
			ShowWindow(hStatic, SW_SHOW);
			ShowWindow(hButtonPlay, SW_SHOW);
			if (state != " ")
			{
				state = " ";
				UpdateWindow(hWnd);
			}
			back = 1;
		}
		else if (state == "Levels") {
			ShowWindow(level1, SW_SHOW);
			ShowWindow(level2, SW_SHOW);
			ShowWindow(level3, SW_SHOW);
			ShowWindow(level4, SW_SHOW);
			ShowWindow(level5, SW_SHOW);
			ShowWindow(hButtonBack, SW_SHOW);
			ShowWindow(hButtonRestart, SW_HIDE);
			if (state != " ")
			{
				state = " ";
				UpdateWindow(hWnd);
			}
			back = 2;
		}
		else if (state == "Board") {
			if (start_level) {
				ShowWindow(level1, SW_HIDE);
				ShowWindow(level2, SW_HIDE);
				ShowWindow(level3, SW_HIDE);
				ShowWindow(level4, SW_HIDE);
				ShowWindow(level5, SW_HIDE);
				ShowWindow(hButtonRestart, SW_SHOW);
				start_level = false;
			}
			board = GetPictureBoard(symbol_board);
			OnPaintBoard(hWnd, board);
			back = 3;
			if (WinOrNo())
			{
				state = "Levels";
				MessageBox(NULL, L"Ви перемогли!", L"Вітаємо", MB_OK);
				GetClientRect(hWnd, &rt);
				InvalidateRect(hWnd, &rt, FALSE);
			}
		}
		if (mes == "Message") { mes = " "; OnPaintMessageBox(hWnd);}
	}
	break;
	case WM_MOVE:
	{
		GetClientRect(hWnd, &rt);
		InvalidateRect(hWnd, &rt, FALSE);
		break;
	}
	case WM_SIZE:
	{
		GetClientRect(hWnd, &rt);
		InvalidateRect(hWnd, &rt, FALSE);
		UpdateWindow(hWnd);
		break;
	}
	case WM_KEYDOWN:
	{
		if (state == "Board") {
			GetClientRect(hWnd, &rt);
			switch (wParam)
			{
			case VK_DOWN:
				movement = LENGTH;
				symbol_board = GetNewPosition(movement);
				InvalidateRect(hWnd, &rt, FALSE);
				break;

			case VK_UP:
				movement = -LENGTH;
				symbol_board = GetNewPosition(movement);
				InvalidateRect(hWnd, &rt, FALSE);
				break;

			case VK_RIGHT:
				movement = 1;
				symbol_board = GetNewPosition(movement);
				InvalidateRect(hWnd, &rt, FALSE);
				break;

			case VK_LEFT:
				movement = -1;
				symbol_board = GetNewPosition(movement);
				InvalidateRect(hWnd, &rt, FALSE);
				break;
			default:
				break;
			}
		}
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

