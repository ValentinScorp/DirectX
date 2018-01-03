#include "Precompiled.h"

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

Renderer *renderer = nullptr;
Scene *scene = nullptr;
UserInput *userInput = nullptr;
GuiSystem *guiSystem = nullptr;

Camera camera(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
//Clock clock;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	//wcex.style = WS_EX_TOPMOST | WS_POPUP;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"My DirectX Project";
	wcex.hIconSm = NULL;
	RegisterClassExW(&wcex);

	HWND hWnd = CreateWindowEx(WS_EX_TOPMOST, "My DirectX Project", "DirectX Project", WS_POPUP, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr, nullptr, hInstance, nullptr);

	if (hWnd == NULL) {
		return -1;
	}

	SetWindowLong(hWnd, GWL_STYLE, WS_BORDER);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	userInput = new UserInput();

	renderer = new Renderer(&camera);

	renderer->Initialize(hWnd);

//	renderer->SetUserInput(userInput);

	scene = new Scene();
	scene->Initialize(renderer);

	renderer->SetCamera(scene->GetActiveCamera());

	guiSystem = new GuiSystem(renderer->GetDevice());
	guiSystem->CreateButton(D3DXVECTOR2(800, 50), "rock.png", 0);
	guiSystem->CreateButton(D3DXVECTOR2(800, 100), "grass.png", 1);
	guiSystem->CreateButton(D3DXVECTOR2(800, 150), "sand.png", 2);

    // added line

	userInput->RegisterListener(scene->GetActiveCamera());
	userInput->RegisterListener(scene);
	userInput->RegisterListener(renderer);

	userInput->RegisterGuiReceiver(guiSystem);

	guiSystem->RegisterListener(scene);

	renderer->InitializeLightAndMaterials();

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//clock.Update();
			scene->UpdateUnits(1.0f);
			renderer->BeginScene();
			renderer->Draw();
			guiSystem->Draw();
			renderer->EndScene();
		}
	}

	if (scene != nullptr) {
		scene->Destroy();
		delete scene;
		scene = nullptr;
	}

	if (guiSystem != nullptr) {
        guiSystem->Destroy();
        delete guiSystem;
        guiSystem = nullptr;
	}

	if (renderer != nullptr) {
		renderer->Destroy();
		delete renderer;
		renderer = nullptr;
	}

	if (userInput != nullptr) {
		delete userInput;
		userInput = nullptr;
	}
	UnregisterClass("My DirectX Project", hInstance);

    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	short delta = 0;
	int xPos = GET_X_LPARAM(lParam);
	int yPos = GET_Y_LPARAM(lParam);

	POINT mMousePos;
	GetCursorPos(&mMousePos);
	ScreenToClient(hWnd, &mMousePos);
	RECT windowRect;

	GetWindowRect(hWnd, &windowRect);

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case 'A':
			userInput->SendMessage(Message("user_input", "a", xPos, yPos, 0));
			break;
		}
		break;
	case WM_MOUSEWHEEL:
		delta = GET_WHEEL_DELTA_WPARAM(wParam);
		if (delta != 0) {
			userInput->SendMessage(Message("user_input", "mouse_wheel", xPos, yPos, delta));
		}
		break;
	case WM_LBUTTONDOWN:
		userInput->SendMessage(Message("user_input", "left_mouse_button_down", xPos, yPos, 0));
		break;
	case WM_LBUTTONUP:
		userInput->SendMessage(Message("user_input", "left_mouse_button_up", xPos, yPos, 0));
		break;
	case WM_RBUTTONDOWN:
		userInput->SendMessage(Message("user_input", "right_mouse_button_down", xPos, yPos, 0));
		break;
	case WM_RBUTTONUP:
		userInput->SendMessage(Message("user_input", "right_mouse_button_up", xPos, yPos, 0));
		break;
	case WM_MOUSEMOVE:
		//userInput->PlaceMessage(UserMessage(xPos, yPos, MouseMove, MouseMove, delta));
		userInput->SendMessage(Message("user_input", "mouse_move", xPos, yPos, 0));
		break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
