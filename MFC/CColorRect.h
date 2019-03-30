#pragma once
#include <atltypes.h>

class CColorRect :	public CRect
{
public:
	CColorRect();
	~CColorRect();

	inline
		void CColorRect::newAttr(int penWidth/*=0*/, COLORREF penColor/*=BLACK*/,
			COLORREF);
};

