#pragma once

class CDevice
{
private:
	LPDIRECT3D9				m_pd3d;
	LPDIRECT3DDEVICE9		m_pDevice;
	LPD3DXSPRITE			m_pSprite;
	LPD3DXFONT				m_pFont;
	bool		m_bWindowed;
	LARGE_INTEGER		m_FirstTime;
	LARGE_INTEGER		m_SecondTime;
	LARGE_INTEGER		m_MiniteTime;
	LARGE_INTEGER		m_LastTime;
	float		m_fTimeDelta;

public:		// Á¢±ÙÀÚ
	LPDIRECT3DDEVICE9 GetDev(void) { return m_pDevice; }
	LPD3DXSPRITE GetSprite(void) { return m_pSprite; }
	LPD3DXFONT GetFont(void) { return m_pFont; }
	void SetMode(void) { m_bWindowed = !m_bWindowed; }
	float GetTimeDelta(void)
	{
		return m_fTimeDelta;
	}

public:
	HRESULT Init(void);
	void SetParameters(D3DPRESENT_PARAMETERS& d3dpp);
	HRESULT InitFont(UINT Width, UINT Height, UINT Weight,
		BOOL Italic, const TCHAR* pName);
	HRESULT ResetDevice(void);
	void DirectionLight(D3DXVECTOR3 vDir);
	void ReleaseAll(void);
	void SetTimeDelta(void);

public:
	CDevice(void);
	~CDevice(void);
};

extern CDevice g_Device;
