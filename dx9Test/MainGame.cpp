#include "framework.h"
#include "MainGame.h"
#include "Device.h"

MainGame g_MainGame;


struct CUSTOMVERTEX_TEX
{
	FLOAT x, y, z, rhw;
	FLOAT u, v;
};

struct INDEX
{
	DWORD	_0, _1, _2;
};

class CustomTryAngle
{
public:
	LPDIRECT3DTEXTURE9			ptexture;
	LPDIRECT3DVERTEXBUFFER9		pVB;
	LPDIRECT3DINDEXBUFFER9		pIB;

	int vertexCnt = 3;
	int indexCnt = 3;
	int triangleNum = 1;

	DWORD fvf = D3DFVF_XYZRHW | D3DFVF_TEX1;

public:
	void init()
	{
		if (FAILED(D3DXCreateTextureFromFile(g_Device.GetDev(), L"C:\\Users\\pcwmp\\Desktop\\DX9 Test\\circle.png", &ptexture)))
		{
			return;
		}

		if (FAILED(g_Device.GetDev()->CreateVertexBuffer(vertexCnt * sizeof(CUSTOMVERTEX_TEX), 0, fvf, D3DPOOL_DEFAULT, &pVB, 0)))
		{
			return;
		}

		if (FAILED(g_Device.GetDev()->CreateIndexBuffer(triangleNum * sizeof(INDEX), 0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &pIB, 0)))
		{
			return;
		}

		CUSTOMVERTEX_TEX* pV;

		float x = 200;
		float y = 200;
		float width = 200;
		float height = 200;

		pVB->Lock(0, 0, (void**)&pV, 0);

		pV[0] = CUSTOMVERTEX_TEX{ x + width, y,						0.5f, 1.0f, 0,0 };
		pV[1] = CUSTOMVERTEX_TEX{ x, y + height,					0.5f, 1.0f, 0,1 };
		pV[2] = CUSTOMVERTEX_TEX{ x + width, y + height,			0.5f, 1.0f, 1,0 };
		
		pVB->Unlock();

		INDEX* pI;

		pIB->Lock(0, 0, (void**)&pI, 0);

		pI->_0 = 0;
		pI->_1 = 1;
		pI->_2 = 2;

		pIB->Unlock();
	}

	void render(float elpasedTime)
	{
		g_Device.GetDev()->SetTexture(0, ptexture);
		g_Device.GetDev()->SetStreamSource(0, pVB, 0, sizeof(CUSTOMVERTEX_TEX));
		g_Device.GetDev()->SetFVF(fvf);
		g_Device.GetDev()->SetIndices(pIB);
		g_Device.GetDev()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCnt, 0, triangleNum);
	}
};

class CustomRect
{
public:
	LPDIRECT3DTEXTURE9			ptexture;
	LPDIRECT3DVERTEXBUFFER9		pVB;
	LPDIRECT3DINDEXBUFFER9		pIB;

	int vertexCnt = 4;
	int indexCnt = 6;
	int triangleNum = 2;

	DWORD fvf = D3DFVF_XYZRHW | D3DFVF_TEX1;

public:
	void init()
	{
		if (FAILED(D3DXCreateTextureFromFile(g_Device.GetDev(), L"C:\\Users\\pcwmp\\Desktop\\DX9 Test\\circle.png", &ptexture)))
		{
			return;
		}

		if (FAILED(g_Device.GetDev()->CreateVertexBuffer(vertexCnt * sizeof(CUSTOMVERTEX_TEX), 0, fvf, D3DPOOL_DEFAULT, &pVB, 0)))
		{
			return;
		}

		if (FAILED(g_Device.GetDev()->CreateIndexBuffer(triangleNum * sizeof(INDEX), 0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &pIB, 0)))
		{
			return;
		}

		CUSTOMVERTEX_TEX* pV;

		float x = 500;
		float y = 500;
		float width = 200;
		float height = 200;

		pVB->Lock(0, 0, (void**)&pV, 0);

		pV[0] = CUSTOMVERTEX_TEX{ x, y,						0.5f, 1.0f, 0,0 };
		pV[1] = CUSTOMVERTEX_TEX{ x + width, y,				0.5f, 1.0f, 1,0 };
		pV[2] = CUSTOMVERTEX_TEX{ x, y + height,			0.5f, 1.0f, 0,1 };
		pV[3] = CUSTOMVERTEX_TEX{ x + width, y + height,	0.5f, 1.0f, 1,1 };

		pVB->Unlock();

		INDEX* pI;

		pIB->Lock(0, 0, (void**)&pI, 0);

		pI->_0 = 0;
		pI->_1 = 1;
		pI->_2 = 3;
		++pI;

		pI->_0 = 0;
		pI->_1 = 3;
		pI->_2 = 2;

		pIB->Unlock();
	}

	void render(float elpasedTime)
	{
		CUSTOMVERTEX_TEX* pV;

		float x = 500;
		float y = 300;
		float width = 200;
		float height = 200;

		static float c = 0.f;

		c = c + (5.f * elpasedTime);
		
		//0도 일때 
		float sinthe = sin(c); //0 ->  1 -> -1
		float costhe = cos(c); //1 -> -1 ->  1

		sinthe = max(min(sinthe, 1), 0);
		sinthe = max(min(costhe, 1), 0);


		pVB->Lock(0, 0, (void**)&pV, 0);

		pV[0] = CUSTOMVERTEX_TEX{ x, y,						0.5f, 1.0f, 0,0 };
		pV[1] = CUSTOMVERTEX_TEX{ x + width, y,				0.5f, 1.0f, 1,0 };
		pV[2] = CUSTOMVERTEX_TEX{ x, y + height,			0.5f, 1.0f, 0,1 };
		pV[3] = CUSTOMVERTEX_TEX{ x + width, y + height,	0.5f, 1.0f, 1,1 };
		
		pVB->Unlock();

		g_Device.GetDev()->SetTexture(0, ptexture);
		//g_Device.GetDev()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		//g_Device.GetDev()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

		g_Device.GetDev()->SetStreamSource(0, pVB, 0, sizeof(CUSTOMVERTEX_TEX));
		g_Device.GetDev()->SetFVF(fvf);
		g_Device.GetDev()->SetIndices(pIB);
		g_Device.GetDev()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCnt, 0, triangleNum);
	}
};

class CustomRotateRect
{
public:
	LPDIRECT3DTEXTURE9			ptexture;
	LPDIRECT3DVERTEXBUFFER9		pVB;

	int vertexCnt = 24;
	int triangleNum = 8;

	DWORD fvf = D3DFVF_XYZRHW | D3DFVF_TEX1;
public:
	void init()
	{
		if (FAILED(D3DXCreateTextureFromFile(g_Device.GetDev(), L"C:\\Users\\pcwmp\\Desktop\\DX9 Test\\circle.png", &ptexture)))
		{
			return;
		}

		if (FAILED(g_Device.GetDev()->CreateVertexBuffer(vertexCnt * sizeof(CUSTOMVERTEX_TEX), 0, fvf, D3DPOOL_DEFAULT, &pVB, 0)))
		{
			return;
		}
	}

	void render(float elpasedTime)
	{
		CUSTOMVERTEX_TEX* pV;

		float width = 50;
		float height = 50;

		float centerX = 100;
		float centerY = 100;

		static float p = 0;

		p += 60 * elpasedTime;
		//float pecent = 0.5f;
		//p = 400 * pecent;
		//float sinthe = sin(c); //0 ->  1 -> -1
		//float costhe = cos(c); //1 -> -1 ->  1

		pVB->Lock(0, 0, (void**)&pV, 0);
		//0 1 2 순서의 2번만 증가 or 감소. -x -y -y x , x y y -x
		if (p <= 50.f)
		{
			pV[0] = CUSTOMVERTEX_TEX{ centerX,		   centerY,								0.5f, 1.0f, 0.5f , 0.5f };
			pV[1] = CUSTOMVERTEX_TEX{ centerX,		   centerY + height,					0.5f, 1.0f, 0.5    , 1 };
			pV[2] = CUSTOMVERTEX_TEX{ centerX - p,	   centerY + height,					0.5f, 1.0f, 0.5f - (p / 100.f) , 1 };
		}
		else if (p <= 100.f)
		{
			pV[3] = CUSTOMVERTEX_TEX{ centerX,		   centerY,								0.5f, 1.0f, 0.5f , 0.5f };
			pV[4] = CUSTOMVERTEX_TEX{ centerX - width, centerY + height,					0.5f, 1.0f, 0    , 1 };
			pV[5] = CUSTOMVERTEX_TEX{ centerX - width, (centerY + height) - (p - 50.f),		0.5f, 1.0f, 0    , 1.f - ((p - 50.f) / 100.f) };
		}
		else if (p <= 150.f)
		{
			pV[6] = CUSTOMVERTEX_TEX{ centerX,		   centerY,								0.5f, 1.0f, 0.5f , 0.5f };
			pV[7] = CUSTOMVERTEX_TEX{ centerX - width, centerY,								0.5f, 1.0f, 0    , 0.5f };
			pV[8] = CUSTOMVERTEX_TEX{ centerX - width, centerY - (p - 100.f),				0.5f, 1.0f, 0    , 0.5f - ((p - 100.f) / 100.f) };
		}
		else if (p <= 200.f)
		{
			pV[9] = CUSTOMVERTEX_TEX{ centerX,		   centerY,								0.5f, 1.0f, 0.5f , 0.5f };
			pV[10] = CUSTOMVERTEX_TEX{ centerX - width, centerY - height,					0.5f, 1.0f, 0    , 0 };
			pV[11] = CUSTOMVERTEX_TEX{ (centerX - width) + (p - 150.f), centerY - height,	0.5f, 1.0f, 0.0f + ((p - 150.f) / 100.f) , 0 };
		}
		//
		else if (p <= 250.f)
		{
			pV[12] = CUSTOMVERTEX_TEX{ centerX,		   centerY,								0.5f, 1.0f, 0.5f , 0.5f };
			pV[13] = CUSTOMVERTEX_TEX{ centerX,		   centerY - height,					0.5f, 1.0f, 0.5    , 0 };
			pV[14] = CUSTOMVERTEX_TEX{ centerX + (p - 200.f),	   centerY - height,		0.5f, 1.0f, 0.5f + ((p - 200.f) / 100.f)  , 0 };
		}
		else if (p <= 300.f)
		{
			pV[15] = CUSTOMVERTEX_TEX{ centerX,		   centerY,								0.5f, 1.0f, 0.5f , 0.5f };
			pV[16] = CUSTOMVERTEX_TEX{ centerX + width, centerY - height,					0.5f, 1.0f, 1    , 0 };
			pV[17] = CUSTOMVERTEX_TEX{ centerX + width, (centerY - height) + (p - 250.f),	0.5f, 1.0f, 1    , 0.0f + ((p - 250.f) / 100.f) };
		}
		else if (p <= 350.f)
		{
			pV[18] = CUSTOMVERTEX_TEX{ centerX,		   centerY,								0.5f, 1.0f, 0.5f , 0.5f };
			pV[19] = CUSTOMVERTEX_TEX{ centerX + width, centerY,							0.5f, 1.0f, 1    , 0.5f };
			pV[20] = CUSTOMVERTEX_TEX{ centerX + width, centerY + (p - 300.f),				0.5f, 1.0f, 1    , 0.5f + ((p - 300.f) / 100.f) };
		}
		else if (p <= 400.f)
		{
			pV[21] = CUSTOMVERTEX_TEX{ centerX,		   centerY,								0.5f, 1.0f, 0.5f , 0.5f };
			pV[22] = CUSTOMVERTEX_TEX{ centerX + width, centerY + height,					0.5f, 1.0f, 1    , 1 };
			pV[23] = CUSTOMVERTEX_TEX{ (centerX + width) - (p - 350.f), centerY + height,	0.5f, 1.0f, 1.f - ((p - 350.f) / 100.f) , 1 };
		}

		pVB->Unlock();

		g_Device.GetDev()->SetStreamSource(0, pVB, 0, sizeof(CUSTOMVERTEX_TEX));
		g_Device.GetDev()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_Device.GetDev()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_Device.GetDev()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		//g_Device.GetDev()->SetRenderState(D3DRS_ALPHAREF, 0.5);
		g_Device.GetDev()->SetTexture(0, ptexture);
		g_Device.GetDev()->SetFVF(fvf);
		g_Device.GetDev()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 8);
	}
};

class CustomCircle
{
public:
	LPDIRECT3DTEXTURE9			ptexture;
	LPDIRECT3DVERTEXBUFFER9		pVB;

	int vertexCnt = 0;
	int triangleNum = 0;

	DWORD fvf = D3DFVF_XYZRHW | D3DFVF_TEX1;
public:
	void init()
	{
		if (FAILED(D3DXCreateTextureFromFile(g_Device.GetDev(), L"C:\\Users\\pcwmp\\Desktop\\DX9 Test\\circle.png", &ptexture)))
		{
			return;
		}

		if (FAILED(g_Device.GetDev()->CreateVertexBuffer(vertexCnt * sizeof(CUSTOMVERTEX_TEX), 0, fvf, D3DPOOL_DEFAULT, &pVB, 0)))
		{
			return;
		}
	}

	void render(float elpasedTime)
	{
		CUSTOMVERTEX_TEX* pV;

		float radius = 30;
		float r = 5;
		float centerX = 300;
		float centerY = 300;

		static float p = 0;
		p += 30 * elpasedTime;
		//float sinthe = sin(c); //0 ->  1 -> -1
		//float costhe = cos(c); //1 -> -1 ->  1

		pVB->Lock(0, 0, (void**)&pV, 0);
	
		pV[0] = CUSTOMVERTEX_TEX{ centerX,		   centerY,		0.5f, 1.0f, 0.5f , 0.5f };
		pV[1] = CUSTOMVERTEX_TEX{ centerX,		   centerY,		0.5f, 1.0f, 0.5    , 1 };
		pV[2] = CUSTOMVERTEX_TEX{ centerX - p,	   centerY,		0.5f, 1.0f, 0  , 1 };

		pVB->Unlock();

		g_Device.GetDev()->SetStreamSource(0, pVB, 0, sizeof(CUSTOMVERTEX_TEX));
		g_Device.GetDev()->SetTexture(0, ptexture);
		g_Device.GetDev()->SetFVF(fvf);
		g_Device.GetDev()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 8);
	}
};

CustomRect rect;
CustomTryAngle angle;
CustomRotateRect roRect;
CustomCircle circle;

MainGame::MainGame()
{
}

MainGame::~MainGame()
{

}

float MainGame::GetElapsedTime()
{
	static LARGE_INTEGER prevTime = {0, 0};
	LARGE_INTEGER Time = { 0, 0 };
	LARGE_INTEGER frequency = { 0, 0 };

	//cpu 클럭수를 얻는다.
	QueryPerformanceCounter(&Time);

	if (prevTime.QuadPart == 0)
	{
		prevTime = Time;
		return 0.f;
	}

	//1초당 (주파수)진동수를 반환한다.
	QueryPerformanceFrequency(&frequency);

	auto elapsedTime = (Time.QuadPart - prevTime.QuadPart) / static_cast<float>(frequency.QuadPart);

	prevTime = Time;

	return elapsedTime;
}

bool MainGame::init()
{
	if (FAILED(g_Device.Init()))
	{
		return false;
	}

	
	//rect.init();
	//angle.init();
	roRect.init();
	//circle.init();
}

void MainGame::update()
{
	elapsedTime = GetElapsedTime();
}

void MainGame::render()
{
	g_Device.GetDev()->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	g_Device.GetDev()->BeginScene();

	{
		//rect.render(elapsedTime);
		//angle.render(elapsedTime);
		roRect.render(elapsedTime);
		//circle.render(elapsedTime);
	}

	g_Device.GetDev()->EndScene();

	g_Device.GetDev()->Present(0, 0, 0, 0);
}