#include "framework.h"
#include "Device.h"

CDevice g_Device;

CDevice::CDevice(void)
{
	m_pd3d = NULL;
	m_pDevice = NULL;
	m_pFont = NULL;
	m_pSprite = NULL;
	m_bWindowed = true;

	QueryPerformanceFrequency(&m_MiniteTime);
	QueryPerformanceCounter(&m_SecondTime);
	QueryPerformanceCounter(&m_LastTime);
	QueryPerformanceCounter(&m_FirstTime);
}

CDevice::~CDevice(void)
{
	ReleaseAll();
}

void CDevice::ReleaseAll(void)
{
	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pd3d);
}

void CDevice::SetTimeDelta(void)
{
	QueryPerformanceCounter(&m_SecondTime);

	if (m_SecondTime.QuadPart - m_LastTime.QuadPart
		>= m_MiniteTime.QuadPart)
	{
		QueryPerformanceFrequency(&m_MiniteTime);
		m_LastTime = m_SecondTime;
	}

	m_fTimeDelta = (m_SecondTime.QuadPart - m_FirstTime.QuadPart) /
		static_cast<float>(m_MiniteTime.QuadPart);

	m_FirstTime = m_SecondTime;
}

HRESULT CDevice::ResetDevice(void)
{
	if (m_pd3d)
	{
		D3DDISPLAYMODE	d3dmode;

		if (FAILED(m_pd3d->GetAdapterDisplayMode(
			D3DADAPTER_DEFAULT, &d3dmode)))
		{
			MessageBox(g_hWnd, L"디스플레이 모드 실패",
				L"실패", MB_OK);
			return E_FAIL;
		}

		D3DPRESENT_PARAMETERS	d3dpp;
		ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

		SAFE_RELEASE(m_pSprite);
		SAFE_RELEASE(m_pFont);

		if (m_bWindowed)
		{
			// 창모드로 전환시
			// 윈도우의 위치를 잡아준다.
			RECT		rc = { 0, 0, g_iWinSizeX, g_iWinSizeY };

			AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);
			SetWindowPos(g_hWnd, HWND_TOPMOST, 0, 0, rc.right - rc.left,
				rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);
		}

		SetParameters(d3dpp);

		if (FAILED(m_pDevice->Reset(&d3dpp)))
		{
			MessageBox(g_hWnd, L"디바이스 리셋실패",
				L"실패", MB_OK);
			return E_FAIL;
		}

		DirectionLight(D3DXVECTOR3(-1, -1, 0));

		m_pDevice->LightEnable(0, TRUE);

		// 스프라이트를 생성한다.
		D3DXCreateSprite(m_pDevice, &m_pSprite);

		if (FAILED(InitFont(14, 25, FW_HEAVY, false, L"굴림")))
		{
			MessageBox(g_hWnd, L"폰트 생성실패", L"실패", MB_OK);
			return E_FAIL;
		}
	}

	return S_OK;
}

void CDevice::SetParameters(D3DPRESENT_PARAMETERS& d3dpp)
{
	RECT	rc;

	GetClientRect(g_hWnd, &rc);

	d3dpp.BackBufferWidth = rc.right - rc.left;
	d3dpp.BackBufferHeight = rc.bottom - rc.top;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.Flags = 0;
	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.Windowed = m_bWindowed;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
}

HRESULT CDevice::Init(void)
{
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pd3d);

	m_pd3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9		caps;

	if (FAILED(m_pd3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
	{
		MessageBox(g_hWnd, L"캡스 얻어오기 실패", L"실패", MB_OK);
		return E_FAIL;
	}

	DWORD		vp = 0;

	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS		d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	SetParameters(d3dpp);

	if (FAILED(m_pd3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		g_hWnd, vp | D3DCREATE_MULTITHREADED,
		&d3dpp, &m_pDevice)))
	{
		MessageBox(g_hWnd, L"디바이스 생성 실패", L"실패", MB_OK);
		return E_FAIL;
	}

	m_pDevice->SetRenderState(D3DRS_CULLMODE,
		D3DCULL_CCW);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, true);

	m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER,
		D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER,
		D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER,
		D3DTEXF_LINEAR);

	DirectionLight(D3DXVECTOR3(-1, -1, 0));

	m_pDevice->LightEnable(0, TRUE);

	// 스프라이트를 생성한다.
	D3DXCreateSprite(m_pDevice, &m_pSprite);

	if (FAILED(InitFont(14, 25, FW_HEAVY, false, L"굴림")))
	{
		MessageBox(g_hWnd, L"폰트 생성실패", L"실패", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void CDevice::DirectionLight(D3DXVECTOR3 vDir)
{
	D3DLIGHT9	light;
	ZeroMemory(&light, sizeof(light));

	D3DCOLORVALUE	value;

	value.r = value.g = value.b = value.a = 1.0f;

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Direction = vDir;
	light.Diffuse = value;
	light.Ambient = value;

	m_pDevice->SetLight(0, &light);
}

HRESULT CDevice::InitFont(UINT Width, UINT Height, UINT Weight,
	BOOL Italic, const TCHAR* pName)
{
	SAFE_RELEASE(m_pFont);

	D3DXFONT_DESC		df;
	ZeroMemory(&df, sizeof(df));
	df.Width = Width;
	df.Height = Height;
	df.Weight = Weight;
	df.Italic = Italic;
	df.CharSet = DEFAULT_CHARSET;
	df.MipLevels = 1;
	lstrcpyW(df.FaceName, pName);

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &df, &m_pFont)))
	{
		MessageBox(g_hWnd, L"폰트 생성실패", L"실패", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}