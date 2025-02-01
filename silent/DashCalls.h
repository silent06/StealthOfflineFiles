#include "stdafx.h"
namespace Dashboard_Calls {
	extern HRESULT(*XuiElementGetId)(HXUIOBJ hObj, LPCWSTR *pszId);
	extern HRESULT(*XuiElementGetChildById)(HXUIOBJ hObj, LPCWSTR szId, HXUIOBJ *phChild);
	extern HRESULT(*XuiElementAddChild)(HXUIOBJ hObj, HXUIOBJ hChild);
	extern HRESULT(*XuiElementGetParent)(HXUIOBJ hObj, HXUIOBJ* phParent);
	extern HRESULT(*XuiFigureSetFill)(HXUIOBJ hObj, XUI_FILL_TYPE nFillType, DWORD dwFillColor, XUIGradientStop *pStops, int nNumStops, float fGradientAngle, const D3DXVECTOR2 *pvScale, const D3DXVECTOR2 *pvTrans);
	extern HRESULT(*XuiFigureSetFillRainbow)(HXUIOBJ hObj, XUI_FILL_TYPE nFillType, DWORD dwFillColor, XUIGradientStop *pStops, int nNumStops, float fGradientAngle, const D3DXVECTOR2 *pvScale, const D3DXVECTOR2 *pvTrans);
	extern HRESULT(*XuiCreateObject)(LPCWSTR szClassName, HXUIOBJ *phObj);
	extern HRESULT(*XuiElementSetBounds)(HXUIOBJ hObj, float fWidth, float fHeight);
	extern HRESULT(*XuiElementSetPosition)(HXUIOBJ hObj, const D3DXVECTOR3 *pvPos);
	extern HRESULT(*XuiObjectGetPropertyId)(HXUIOBJ hObj, LPCWSTR szPropName, DWORD *pdwId);
}