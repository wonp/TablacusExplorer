#include "stdafx.h"
#if defined(_WINDLL) || defined(_DEBUG)

#include "common.h"

extern HWND g_hwndMain;
extern std::unordered_map<DWORD, HHOOK> g_umCBTHook;
extern int g_nException;
extern IDispatch *g_pMBText;
extern OPENFILENAME *g_pofn;
extern BOOL	g_bDialogOk;
extern IDispatch	*g_pOnFunc[Count_OnFunc];
extern HBRUSH	g_hbrDarkBackground;
#ifdef _DEBUG
extern LPWSTR	g_strException;
#endif

extern IUnknown* FindUnkTE();

std::unordered_map<HWND, HWND> g_umSetTheme;
std::unordered_map<HWND, HWND> g_umDlgLVProc;

LPFNSetPreferredAppMode _SetPreferredAppMode = NULL;
LPFNAllowDarkModeForWindow _AllowDarkModeForWindow = NULL;
LPFNSetWindowCompositionAttribute _SetWindowCompositionAttribute = NULL;
LPFNDwmSetWindowAttribute _DwmSetWindowAttribute = NULL;
LPFNShouldAppsUseDarkMode _ShouldAppsUseDarkMode = NULL;
LPFNRefreshImmersiveColorPolicyState _RefreshImmersiveColorPolicyState = NULL;
//LPFNIsDarkModeAllowedForWindow _IsDarkModeAllowedForWindow = NULL;

BOOL g_bDarkMode = FALSE;

BOOL teIsHighContrast()
{
	HIGHCONTRAST highContrast = { sizeof(HIGHCONTRAST) };
	return SystemParametersInfo(SPI_GETHIGHCONTRAST, sizeof(highContrast), &highContrast, FALSE) && (highContrast.dwFlags & HCF_HIGHCONTRASTON);
}

VOID teSetDarkMode(HWND hwnd)
{
	if (_AllowDarkModeForWindow) {
		_AllowDarkModeForWindow(hwnd, g_bDarkMode);
	}
	if (_SetWindowCompositionAttribute) {
		WINCOMPATTRDATA wcpad = { 26, &g_bDarkMode, sizeof(g_bDarkMode) };
		_SetWindowCompositionAttribute(hwnd, &wcpad);
	} else if (_DwmSetWindowAttribute) {
		_DwmSetWindowAttribute(hwnd, 19, &g_bDarkMode, sizeof(g_bDarkMode));
	}
}

VOID teGetDarkMode()
{
	if (_ShouldAppsUseDarkMode && _AllowDarkModeForWindow && _SetPreferredAppMode) {
		g_bDarkMode = _ShouldAppsUseDarkMode() && IsAppThemed() && !teIsHighContrast();
		_SetPreferredAppMode(g_bDarkMode ? APPMODE_ALLOWDARK : APPMODE_DEFAULT);
		if (_RefreshImmersiveColorPolicyState) {
			_RefreshImmersiveColorPolicyState();
		}
		teSetDarkMode(g_hwndMain);
	}
}

BOOL teIsDarkColor(COLORREF cl)
{
	return 299 * GetRValue(cl) + 587 * GetGValue(cl) + 114 * GetBValue(cl) < 127500;
}

VOID teSetTreeTheme(HWND hwnd, COLORREF cl)
{
	if (_AllowDarkModeForWindow) {
		BOOL bDarkMode = teIsDarkColor(cl);
		_AllowDarkModeForWindow(hwnd, bDarkMode);
		SetWindowTheme(hwnd, bDarkMode ? L"darkmode_explorer" : L"explorer", NULL);
	}
}

LRESULT CALLBACK TEDlgLVProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	try {
		switch (msg) {
		case LVM_SETSELECTEDCOLUMN:
			if (g_bDarkMode) {
				wParam = -1;
			}
			break;
		case WM_NOTIFY:
			if (g_bDarkMode) {
				if (((LPNMHDR)lParam)->code == NM_CUSTOMDRAW) {
					LPNMCUSTOMDRAW pnmcd = (LPNMCUSTOMDRAW)lParam;
					if (pnmcd->dwDrawStage == CDDS_PREPAINT) {
						return CDRF_NOTIFYITEMDRAW;
					}
					if (pnmcd->dwDrawStage == CDDS_ITEMPREPAINT) {
						SetTextColor(pnmcd->hdc, TECL_DARKTEXT);
						return CDRF_DODEFAULT;
					}
				}
				DefSubclassProc(hwnd, LVM_SETSELECTEDCOLUMN, -1, 0);
			}
			break;

		}
	} catch (...) {
		g_nException = 0;
#ifdef _DEBUG
		g_strException = L"TEDlgLVProc";
#endif
	}
	return DefSubclassProc(hwnd, msg, wParam, lParam);
}

VOID FixChildren(HWND hwnd)
{
	HWND hwnd1 = NULL;
	while (hwnd1 = ::FindWindowEx(hwnd, hwnd1, NULL, NULL)) {
		if (::GetWindowTheme(hwnd)) {
			break;
		}
		CHAR pszClassA[MAX_CLASS_NAME];
		::GetClassNameA(hwnd1, pszClassA, MAX_CLASS_NAME);
		if (lstrcmpiA(pszClassA, WC_BUTTONA) == 0) {
			::SetWindowTheme(hwnd1, g_bDarkMode ? L"darkmode_explorer" : L"explorer", NULL);
			if (g_bDarkMode) {
				DWORD dwStyle = GetWindowLong(hwnd1, GWL_STYLE);
				if ((dwStyle & BS_TYPEMASK) > BS_DEFPUSHBUTTON && !(dwStyle & BS_BITMAP)) {
					int nLen = ::GetWindowTextLength(hwnd1);
					if (nLen) {
						BSTR bs = ::SysAllocStringLen(NULL, nLen + 1);
						::GetWindowText(hwnd1, bs, nLen + 1);
						HDC hdc = ::GetDC(hwnd);
						if (hdc) {
							HGDIOBJ hFont = (HGDIOBJ)::SendMessage(hwnd1, WM_GETFONT, 0, 0);
							HGDIOBJ hFontOld = ::SelectObject(hdc, hFont);
							RECT rc;
							::GetClientRect(hwnd1, &rc);
							::DrawText(hdc, bs, nLen + 1, &rc, DT_HIDEPREFIX | DT_CALCRECT);
							HBITMAP hBM = ::CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
							HDC hmdc = ::CreateCompatibleDC(hdc);
							HGDIOBJ hOld = ::SelectObject(hmdc, hBM);
							HGDIOBJ hFontOld2 = ::SelectObject(hmdc, hFont);
							::SetTextColor(hmdc, TECL_DARKTEXT);
							::SetBkColor(hmdc, TECL_DARKBG);
							::DrawText(hmdc, bs, nLen + 1, &rc, DT_HIDEPREFIX);
							::SelectObject(hmdc, hFontOld2);
							::SelectObject(hmdc, hOld);
							::DeleteDC(hmdc);
							::SelectObject(hdc, hFontOld);
							::ReleaseDC(hwnd1, hdc);
							::SetWindowLong(hwnd1, GWL_STYLE, (dwStyle | BS_BITMAP));
							::SendMessage(hwnd1, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBM);
							::DeleteObject(hBM);
							::SysFreeString(bs);
						}
					}
				}
			}
		}
		if (lstrcmpiA(pszClassA, WC_COMBOBOXA) == 0) {
			::SetWindowTheme(hwnd1, g_bDarkMode ? L"darkmode_cfd" : L"cfd", NULL);
		}
		if (lstrcmpiA(pszClassA, WC_SCROLLBARA) == 0) {
			::SetWindowTheme(hwnd1, g_bDarkMode ? L"darkmode_explorer" : L"explorer", NULL);
		}
		if (lstrcmpiA(pszClassA, WC_TREEVIEWA) == 0) {
			SetWindowTheme(hwnd1, g_bDarkMode ? L"darkmode_explorer" : L"explorer", NULL);
			TreeView_SetTextColor(hwnd1, g_bDarkMode ? TECL_DARKTEXT : GetSysColor(COLOR_WINDOWTEXT));
			TreeView_SetBkColor(hwnd1, g_bDarkMode ? TECL_DARKBG : GetSysColor(COLOR_WINDOW));
		}
		if (lstrcmpiA(pszClassA, WC_LISTVIEWA) == 0) {
			SetWindowTheme(hwnd1, g_bDarkMode ? L"darkmode_itemsview" : L"explorer", NULL);
			ListView_SetTextColor(hwnd1, g_bDarkMode ? TECL_DARKTEXT : GetSysColor(COLOR_WINDOWTEXT));
			ListView_SetTextBkColor(hwnd1, g_bDarkMode ? TECL_DARKBG : GetSysColor(COLOR_WINDOW));
			ListView_SetBkColor(hwnd1, g_bDarkMode ? TECL_DARKBG : GetSysColor(COLOR_WINDOW));
			if (g_bDarkMode) {
				HWND hHeader = ListView_GetHeader(hwnd1);
				if (hHeader) {
					SetWindowTheme(hHeader, g_bDarkMode ? L"darkmode_itemsview" : L"explorer", NULL);
				}
				auto itr = g_umDlgLVProc.find(hwnd1);
				if (itr == g_umDlgLVProc.end()) {
					SetWindowSubclass(hwnd1, TEDlgLVProc, (UINT_PTR)TEDlgLVProc, 0);
					g_umDlgLVProc[hwnd1] = hwnd;
				}
				ListView_SetSelectedColumn(hwnd1, -1);
			}
		}
		if (lstrcmpiA(pszClassA, WC_TABCONTROLA) == 0) {
			DWORD dwStyle = GetWindowLong(hwnd1, GWL_STYLE);
			if (g_bDarkMode) {
				::SetWindowLong(hwnd1, GWL_STYLE, (dwStyle | TCS_OWNERDRAWFIXED));
				::SetClassLongPtr(hwnd1, GCLP_HBRBACKGROUND, (LONG_PTR)g_hbrDarkBackground);
			} else {
				::SetWindowLong(hwnd1, GWL_STYLE, (dwStyle & ~TCS_OWNERDRAWFIXED));
			}
		}
		/*if (lstrcmpiA(pszClassA, "DirectUIHWND") == 0) {
		SetWindowTheme(hwnd1, g_bDarkMode ? L"darkmode_explorer" : L"explorer", NULL);
		if (_AllowDarkModeForWindow) {
		_AllowDarkModeForWindow(hwnd1, g_bDarkMode);
		}
		}*/
		FixChildren(hwnd1);
	}
}

LRESULT CALLBACK TEDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	try {
		switch (msg) {
		case WM_INITDIALOG:
			if (g_pMBText) {
				for (int i = 1; i < 12; ++i) {
					HWND hButton = GetDlgItem(hwnd, i);
					VARIANT v;
					VariantInit(&v);
					if SUCCEEDED(teGetPropertyAt(g_pMBText, i, &v)) {
						if (v.vt == VT_BSTR) {
							SetDlgItemText(hwnd, i, v.bstrVal);
						}
						VariantClear(&v);
					}
				}
			}
		case WM_SETTINGCHANGE:
			teGetDarkMode();
			teSetDarkMode(hwnd);
			UpdateWindow(hwnd);
		case WM_NCPAINT:
			FixChildren(hwnd);
			break;
		case WM_CTLCOLORLISTBOX:
			if (_AllowDarkModeForWindow) {
				auto itr = g_umSetTheme.find((HWND)lParam);
				if (itr == g_umSetTheme.end()) {
					SetWindowTheme((HWND)lParam, g_bDarkMode ? L"darkmode_explorer" : L"explorer", NULL);
					g_umSetTheme[(HWND)lParam] = hwnd;
				}
			}
			break;
		case WM_COMMAND:
			if (wParam == IDOK && g_pofn) {
				IShellBrowser *pSB = (IShellBrowser *)SendMessage(hwnd, WM_USER + 7, 0, 0);
				if (pSB) {
					LPITEMIDLIST pidlParent = NULL;
					if (teGetIDListFromObject(pSB, &pidlParent)) {
						LPITEMIDLIST pidlChild = NULL;
						IShellView *pSV;
						if SUCCEEDED(pSB->QueryActiveShellView(&pSV)) {
							IFolderView *pFV;
							if SUCCEEDED(pSV->QueryInterface(IID_PPV_ARGS(&pFV))) {
								int iItem;
								if SUCCEEDED(pFV->ItemCount(SVGIO_SELECTION, &iItem)) {
									if (iItem > 0) {
										pFV->GetFocusedItem(&iItem);
										if (iItem >= 0) {
											pFV->Item(iItem, &pidlChild);
										}
									}
								}
								SafeRelease(&pFV);
							}
							SafeRelease(&pSV);
						}
						LPITEMIDLIST pidl = pidlParent;
						if (pidlChild) {
							pidl = ILCombine(pidlParent, pidlChild);
							teCoTaskMemFree(pidlChild);
							teCoTaskMemFree(pidlParent);
						}
						BSTR bs;
						teGetDisplayNameFromIDList(&bs, pidl, SHGDN_FORPARSING | SHGDN_FORADDRESSBAR);
						teCoTaskMemFree(pidl);
						lstrcpyn(g_pofn->lpstrFile, bs, g_pofn->nMaxFile);
						::SysFreeString(bs);
						g_bDialogOk = TRUE;
						wParam = IDCANCEL;
					}
				}
			}
			break;
		case WM_CLOSE:
			for (auto itr = g_umSetTheme.begin(); itr != g_umSetTheme.end();) {
				if (hwnd == itr->second) {
					itr = g_umSetTheme.erase(itr);
				} else {
					++itr;
				}
			}
			for (auto itr = g_umDlgLVProc.begin(); itr != g_umDlgLVProc.end();) {
				if (hwnd == itr->second) {
					RemoveWindowSubclass(itr->first, TEDlgLVProc, (UINT_PTR)TEDlgLVProc);
					itr = g_umDlgLVProc.erase(itr);
				} else {
					++itr;
				}
			}
			break;
		}
		if (g_bDarkMode) {
			HWND hwnd1;
			CHAR pszClassA[MAX_CLASS_NAME];
			switch (msg) {
			case WM_CTLCOLORSTATIC:
				SetTextColor((HDC)wParam, TECL_DARKTEXT);
				SetBkMode((HDC)wParam, TRANSPARENT);
				return (LRESULT)g_hbrDarkBackground;
			case WM_CTLCOLORLISTBOX://Combobox
			case WM_CTLCOLOREDIT:
				SetTextColor((HDC)wParam, TECL_DARKTEXT);
				SetBkMode((HDC)wParam, TRANSPARENT);
				return (LRESULT)GetStockObject(BLACK_BRUSH);
			case WM_ERASEBKGND:
				RECT rc;
				GetClientRect(hwnd, &rc);
				FillRect((HDC)wParam, &rc, g_hbrDarkBackground);
				return 1;
			case WM_PAINT:
				HWND hwndChild;
				hwndChild = NULL;
				BOOL bHandle;
				bHandle = TRUE;
				while (hwndChild = FindWindowEx(hwnd, hwndChild, NULL, NULL)) {
					GetClassNameA(hwndChild, pszClassA, MAX_CLASS_NAME);
					if (bHandle && !PathMatchSpecA(pszClassA, WC_STATICA ";" WC_BUTTONA ";" WC_COMBOBOXA)) {
						bHandle = FALSE;
					}
				}
				if (bHandle) {
					PAINTSTRUCT ps;
					HDC hdc = BeginPaint(hwnd, &ps);
					EndPaint(hwnd, &ps);
				}
				break;
			case WM_DRAWITEM:
				PDRAWITEMSTRUCT pdis;
				pdis = (PDRAWITEMSTRUCT)lParam;
				if (pdis->CtlType == ODT_COMBOBOX) {
					if (pdis->itemState & ODS_SELECTED) {
						break;
					}
					int w = pdis->rcItem.right - pdis->rcItem.left;
					int h = pdis->rcItem.bottom - pdis->rcItem.top;
					BITMAPINFO bmi;
					COLORREF *pcl = NULL, *pcl2 = NULL;
					::ZeroMemory(&bmi.bmiHeader, sizeof(BITMAPINFOHEADER));
					bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
					bmi.bmiHeader.biWidth = w;
					bmi.bmiHeader.biHeight = -(LONG)h;
					bmi.bmiHeader.biPlanes = 1;
					bmi.bmiHeader.biBitCount = 32;
					HGDIOBJ hFont = (HGDIOBJ)::SendMessage(pdis->hwndItem, WM_GETFONT, 0, 0);
					HBITMAP hBM = CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void **)&pcl, NULL, 0);
					HDC hmdc = CreateCompatibleDC(pdis->hDC);
					HGDIOBJ hOld = SelectObject(hmdc, hBM);
					HDC hdc1 = pdis->hDC;
					pdis->hDC = hmdc;
					CopyRect(&rc, &pdis->rcItem);
					pdis->rcItem.left = 0;
					pdis->rcItem.top = 0;
					pdis->rcItem.right = w;
					pdis->rcItem.bottom = h;
					HGDIOBJ hFontOld = ::SelectObject(hmdc, hFont);
					LRESULT lResult = DefSubclassProc(hwnd, msg, wParam, lParam);
					::SelectObject(hmdc, hFontOld);
					/* COLORREF              RGBQUAD
					rgbRed   =  0x000000FF = rgbBlue
					rgbGreen =  0x0000FF00 = rgbGreen
					rgbBlue  =  0x00FF0000 = rgbRed */
					DWORD cl0 = *pcl;
					if (299 * GetBValue(cl0) + 587 * GetGValue(cl0) + 114 * GetRValue(cl0) >= 127500) {
						HBITMAP hBM2 = CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void **)&pcl2, NULL, 0);
						HDC hmdc2 = CreateCompatibleDC(pdis->hDC);
						HGDIOBJ hOld2 = SelectObject(hmdc2, hBM2);
						pdis->hDC = hmdc2;
						pdis->itemState = ODS_SELECTED;
						HGDIOBJ hFontOld2 = ::SelectObject(hmdc2, hFont);
						::DefSubclassProc(hwnd, msg, wParam, lParam);
						::SelectObject(hmdc2, hFontOld2);
						if (*pcl != *pcl2) {
							for (int i = w * h; --i >= 0; ++pcl) {
								if (*pcl != *pcl2) {
									*pcl ^= 0xffffff;
								}
								++pcl2;
							}
						}
						SelectObject(hmdc2, hOld2);
						DeleteDC(hmdc2);
						DeleteObject(hBM2);
					}
					pdis->hDC = hdc1;
					CopyRect(&pdis->rcItem, &rc);
					BitBlt(pdis->hDC, pdis->rcItem.left, pdis->rcItem.top, w, h, hmdc, 0, 0, SRCCOPY);
					SelectObject(hmdc, hOld);
					DeleteDC(hmdc);
					DeleteObject(hBM);
					return lResult;
				} else if (pdis->CtlType == ODT_TAB) {
					::FillRect(pdis->hDC, &pdis->rcItem, g_hbrDarkBackground);
					WCHAR label[64];
					TC_ITEM tci;
					tci.mask = TCIF_TEXT;
					tci.pszText = label;
					tci.cchTextMax = 63;
					TabCtrl_GetItem(pdis->hwndItem, pdis->itemID, &tci);
					SetTextColor(pdis->hDC, (pdis->itemState & (ODS_SELECTED | ODS_HOTLIGHT)) ? TECL_DARKTEXT : TECL_DARKTEXT2);
					SetBkMode(pdis->hDC, TRANSPARENT);
					::DrawText(pdis->hDC, label, -1, &pdis->rcItem, DT_HIDEPREFIX | DT_SINGLELINE | DT_CENTER | ((pdis->itemState & ODS_SELECTED) ? DT_VCENTER : DT_BOTTOM));
				}
				break;
			}
		}
	} catch (...) {
		g_nException = 0;
#ifdef _DEBUG
		g_strException = L"TEDlgProc";
#endif
	}
	return DefSubclassProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK TETTProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	try {
		if (g_pOnFunc[TE_OnToolTip]) {
			if (msg == WM_PAINT || msg == WM_ERASEBKGND || msg == TTM_ACTIVATE) {
				VARIANTARG *pv = GetNewVARIANT(3);
				teSetObject(&pv[2], FindUnkTE());
				teSetLong(&pv[1], msg);
				teSetPtr(&pv[0], hwnd);
				VARIANT vResult;
				VariantInit(&vResult);
				Invoke4(g_pOnFunc[TE_OnToolTip], &vResult, 3, pv);
				if (teVarIsNumber(&vResult)) {
					return GetIntFromVariantClear(&vResult);
				}
				VariantClear(&vResult);
			}
		}
		if (msg == WM_NCPAINT) {
			SetWindowTheme(hwnd, g_bDarkMode ? L"darkmode_explorer" : L"explorer", NULL);
		}
	} catch (...) {
		g_nException = 0;
#ifdef _DEBUG
		g_strException = L"TETTProc";
#endif
	}
	return DefSubclassProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	CHAR pszClassA[MAX_CLASS_NAME];
	if (nCode == HCBT_CREATEWND) {
		HWND hwnd = (HWND)wParam;
		GetClassNameA(hwnd, pszClassA, MAX_CLASS_NAME);
		if (!lstrcmpA(pszClassA, "#32770")) {
			SetWindowSubclass(hwnd, TEDlgProc, (UINT_PTR)TEDlgProc, 0);
		} else if (!lstrcmpA(pszClassA, TOOLTIPS_CLASSA)) {
			SetWindowSubclass(hwnd, TETTProc, (UINT_PTR)TETTProc, 0);
			/*} else if (!lstrcmpA(pszClassA, "#32768")) {
			Sleep(0);*/
		}
	} else if (nCode == HCBT_DESTROYWND) {
		HWND hwnd = (HWND)wParam;
		GetClassNameA(hwnd, pszClassA, MAX_CLASS_NAME);
		if (!lstrcmpA(pszClassA, "#32770")) {
			RemoveWindowSubclass(hwnd, TEDlgProc, (UINT_PTR)TEDlgProc);
		} else if (!lstrcmpA(pszClassA, TOOLTIPS_CLASSA)) {
			RemoveWindowSubclass(hwnd, TETTProc, (UINT_PTR)TETTProc);
		}
		/*	} else if (nCode == HCBT_CLICKSKIPPED) {
		WCHAR pszNum[99];
		swprintf_s(pszNum, 99, L"%x %x\n", wParam, lParam);
		::OutputDebugString(pszNum);
		if (wParam == WM_MOUSEWHEEL) {
		MOUSEHOOKSTRUCTEX *pMHS = (MOUSEHOOKSTRUCTEX *)lParam;
		Sleep(0);
		}*/
	}
	auto itr = g_umCBTHook.find(GetCurrentThreadId());
	return itr != g_umCBTHook.end() ? CallNextHookEx(itr->second, nCode, wParam, lParam) : 0;
}

#endif
