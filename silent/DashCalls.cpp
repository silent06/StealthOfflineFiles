#include "stdafx.h"
namespace Dashboard_Calls {

	HRESULT(*XuiElementGetId)(HXUIOBJ hObj, LPCWSTR *pszId);
	HRESULT(*XuiElementGetChildById)(HXUIOBJ hObj, LPCWSTR szId, HXUIOBJ *phChild);
	HRESULT(*XuiElementAddChild)(HXUIOBJ hObj, HXUIOBJ hChild);
	HRESULT(*XuiElementGetParent)(HXUIOBJ hObj, HXUIOBJ* phParent);
	HRESULT(*XuiFigureSetFill)(HXUIOBJ hObj, XUI_FILL_TYPE nFillType, DWORD dwFillColor, XUIGradientStop *pStops, int nNumStops, float fGradientAngle, const D3DXVECTOR2 *pvScale, const D3DXVECTOR2 *pvTrans);
	HRESULT(*XuiFigureSetFillRainbow)(HXUIOBJ hObj, XUI_FILL_TYPE nFillType, DWORD dwFillColor, XUIGradientStop *pStops, int nNumStops, float fGradientAngle, const D3DXVECTOR2 *pvScale, const D3DXVECTOR2 *pvTrans);
	HRESULT(*XuiCreateObject)(LPCWSTR szClassName, HXUIOBJ *phObj);
	HRESULT(*XuiElementSetBounds)(HXUIOBJ hObj, float fWidth, float fHeight);
	HRESULT(*XuiElementSetPosition)(HXUIOBJ hObj, const D3DXVECTOR3 *pvPos);
	HRESULT(*XuiObjectGetPropertyId)(HXUIOBJ hObj, LPCWSTR szPropName, DWORD *pdwId);

	VOID ResolveFunctions() {

	}
}