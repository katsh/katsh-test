//ヘッダーファイルのインクルード
#include <windows.h>
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>
//必要なライブラリファイルのロード
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dCompiler.lib")
//警告非表示
#pragma warning(disable : 4305)
//定数定義
#define WINDOW_WIDTH 640 //ウィンドウ幅
#define WINDOW_HEIGHT 480 //ウィンドウ高さ
#define APP_NAME L"シェーディング　陰影を付ける D3d11"
//マクロ
#define SAFE_RELEASE(x) if(x){x->Release(); x;}

//頂点の構造体
struct SimpleVertex
{
    D3DXVECTOR3 Pos;//位置
	D3DXVECTOR3 Normal;//法線　シェーディング（陰影計算）には法線は必須
};
//Simpleシェーダー用のコンスタントバッファーのアプリ側構造体 もちろんシェーダー内のコンスタントバッファーと一致している必要あり
struct SIMPLESHADER_CONSTANT_BUFFER
{
	D3DXMATRIX mW;//ワールド行列
	D3DXMATRIX mWVP;//ワールドから射影までの変換行列
	D3DXVECTOR4 vLightDir;//ライト方向
	D3DXVECTOR4 vColor;//ディフューズ色	
};
//
//
//
class MAIN
{
public:
	MAIN();
	~MAIN();
	HRESULT InitWindow(HINSTANCE,INT,INT,INT,INT,LPCWSTR);
	LRESULT MsgProc(HWND,UINT,WPARAM,LPARAM);
	HRESULT InitD3D();
	HRESULT InitPolygon();
	HRESULT InitShader();
	void Loop();
	void App();
	void Render();
	void DestroyD3D();
	//↓アプリにひとつ
	HWND m_hWnd;
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
	IDXGISwapChain* m_pSwapChain;
	ID3D11RenderTargetView* m_pRenderTargetView;
	ID3D11DepthStencilView* m_pDepthStencilView;
	ID3D11Texture2D* m_pDepthStencil;
	D3DXVECTOR3 m_vLight;
	//↓モデルの種類ごと(モデルの構造が全て同一ならアプリにひとつ）
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11Buffer* m_pConstantBuffer;
	//↓モデルごと	
	ID3D11Buffer* m_pVertexBuffer;
};
