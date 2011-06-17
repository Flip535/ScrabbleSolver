#pragma once

class CGdiPlusBitmap
{
public:
	Gdiplus::Bitmap* m_pBitmap;

public:
	CGdiPlusBitmap(LPCWSTR pFile=NULL)			{ m_pBitmap = NULL; if(pFile)Load(pFile); }
	CGdiPlusBitmap(UINT id, LPCTSTR pType = RT_RCDATA, HMODULE hInst = NULL)
												{  Load(id, pType, hInst); }
	virtual ~CGdiPlusBitmap()					{ Empty(); }

	void Empty()								{ if (m_pBitmap) delete m_pBitmap; m_pBitmap = NULL; }

	BOOL Load(UINT id, LPCTSTR pType = RT_RCDATA, HMODULE hInst = NULL);

	BOOL Load(LPCWSTR pFile)
	{
		Empty();
		m_pBitmap = Gdiplus::Bitmap::FromFile(pFile);
		return m_pBitmap->GetLastStatus() == Gdiplus::Ok;
	}

	void    CreateMem( int xExtent, int yExtent )
	{
		if(m_pBitmap)
			DEL(m_pBitmap);
		m_pBitmap = new Gdiplus::Bitmap(xExtent, yExtent, PixelFormat32bppARGB);
	}

	int GetWidth(){if(m_pBitmap)return this->m_pBitmap->GetWidth(); else return 0;}
	int GetHeight(){if(m_pBitmap)return this->m_pBitmap->GetHeight(); else return 0;}

	operator Gdiplus::Bitmap*() const			{ return m_pBitmap; }
	operator BOOL() const			{ return m_pBitmap!=NULL; 	}
};

inline
BOOL CGdiPlusBitmap::Load(UINT id, LPCTSTR type, HMODULE hInst)
{
	BOOL bRC = FALSE;   

	HRSRC hRRes = FindResource( hInst, MAKEINTRESOURCE(id), MAKEINTRESOURCE(type));
    if( !hRRes )
    {
        CString str;
        str.Format( IDS_ERR_RESIDNOTFOUND, id );
        AfxMessageBox( str );
        
		return bRC;
    }

    int resSize = SizeofResource( hInst, hRRes );

    HGLOBAL hRes = LoadResource( hInst, hRRes );
    if( hRes )
	{
		BYTE *pRes = (BYTE *) LockResource( hRes );
		HGLOBAL hImg = NULL; 
		BYTE *pImg = NULL;
		if( pRes )
			hImg = ::GlobalAlloc(GMEM_MOVEABLE, resSize);
		if(hImg)
			pImg = (BYTE *)::GlobalLock(hImg);
		if( pImg )
		{
			memcpy(pImg, pRes, resSize);
			::GlobalUnlock(hImg);
			
			CComPtr<IStream> spStream;

			if ( ::CreateStreamOnHGlobal(hImg, FALSE, &spStream) == S_OK )
			{
				Gdiplus::Bitmap* temp = Gdiplus::Bitmap::FromStream(spStream, TRUE);
				m_pBitmap = new Gdiplus::Bitmap(temp->GetWidth(),temp->GetHeight(),PixelFormat32bppARGB);
				m_pBitmap->SetResolution(96,96);
				Gdiplus::Graphics g(m_pBitmap);
				g.DrawImage(temp,0,0);
				delete temp;
				if(m_pBitmap == NULL)
					bRC = FALSE;
				else
					bRC = TRUE;
			}
		}
		if(hImg)
			::GlobalFree(hImg);
		FreeResource( hRes );
	}
    
	return bRC;

}

inline
void TileImage( CGdiPlusBitmap* img, const CRect& rect, Gdiplus::Graphics& g, BOOL bVerticallyStretchToFitRect = FALSE)
{
	Gdiplus::RectF imgRect(rect.left,rect.top,img->GetWidth(),bVerticallyStretchToFitRect?rect.Height():img->GetHeight());
	float widthToDraw = rect.right;

	while(imgRect.X < widthToDraw)
	{
		g.DrawImage(*img,imgRect,0,0,img->GetWidth(),img->GetHeight(),Gdiplus::UnitPixel);
		imgRect.X+=imgRect.Width;
	}
}

//inline bool GdiPlusConvertImage(LPCTSTR fileIn, LPCTSTR fileOut, LPCTSTR outFormat = _T("image/jpeg"), ULONG nQuality = 0, BOOL bResize = FALSE, int newWidth = 0, int newHeight = 0, BOOL bKeepAspectRation = TRUE )
//{
//	
//	CGdiPlusBitmap bmpTemp( fileIn );
//	int nWidth  = (int) bmpTemp.GetWidth();
//	int nHeight = (int) bmpTemp.GetHeight();
//	if( bResize )
//	{
//		nWidth  = newWidth;
//		nHeight = newHeight;
//
//		if( bKeepAspectRation )
//		{
//			//Create the image at the proper size and aspect ratio
//			double xMultiplier = ((double)(newWidth))/((double)bmpTemp.GetWidth());
//			double yMultiplier = ((double)(newHeight))/((double)bmpTemp.GetHeight());
//			double multiplier = xMultiplier > yMultiplier ? yMultiplier : xMultiplier;
//			nWidth  = (int) (multiplier * (double)bmpTemp.GetWidth() );
//			nHeight = (int) (multiplier * (double)bmpTemp.GetHeight() );
//		}
//	}
//
//	Gdiplus::Bitmap bitmap(nWidth, nHeight); 
//	Gdiplus::Graphics graphics(&bitmap);
//	graphics.DrawImage(bmpTemp.m_pBitmap, 0, 0, nWidth, nHeight);
//
//	CLSID pngClsid;
//	GetEncoderClsid( outFormat, &pngClsid );
//
//	Gdiplus::EncoderParameters param;
//	param.Count						  = 1;
//	param.Parameter[0].Guid			  = Gdiplus::EncoderQuality;
//	param.Parameter[0].Type           = Gdiplus::EncoderParameterValueTypeLong;
//	param.Parameter[0].NumberOfValues = 1;
//	param.Parameter[0].Value          = &nQuality; 
//
//	Gdiplus::Status status;
//
//	status = bitmap.Save( fileOut, &pngClsid, &param );
//
//	return (Gdiplus::Ok == status );
//}