#include "../common/main.h"
#include "../common/manager.h"
#include "../common/input.h"
#include "../common/renderer.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_sdl.h"
#include "../imgui/imgui_impl_dx11.h"

#include "DebugUI.h"

#include "../common/Game_Object.h"
#include "../common/model.h"

#include "../common/Scene.h"

bool show_another_window = false;

void CDebugUI::Initialize()
{
#if defined(_DEBUG) || defined(DEBUG)
	ImGui_ImplDX11_Init(CRenderer::GetDevice(), CRenderer::GetDeviceContext());
#endif
}

void CDebugUI::Finalize()
{
#if defined(_DEBUG) || defined(DEBUG)
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
#endif
}

void CDebugUI::Update()
{
#if defined(_DEBUG) || defined(DEBUG)
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
#endif
}

void CDebugUI::Draw()
{
#if defined(_DEBUG) || defined(DEBUG)
	CScene* scene = CManager::GetScene();
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	XMFLOAT3 pos(0,0,0);
	//if(scene != nullptr) pos = scene->GetGameObject<CPlayer>(2)->GetPosition();

	{
		static float f = 0.0f;
		static int counter = 0;
		ImGui::Begin("DebugWindow");

		ImGui::Text("Scene : %s", CManager::GetNowScene());
		
		if (strcmp(CManager::GetNowScene(), "Title") == 0)
		{
			ImGui::SetNextTreeNodeOpen(true, ImGuiCond_Once);
			if (ImGui::TreeNode("Title")) {


				ImGui::TreePop();
			}
		}

		if (strcmp(CManager::GetNowScene(), "Game") == 0)
		{
			ImGui::SetNextTreeNodeOpen(true, ImGuiCond_Once);
			if (ImGui::TreeNode("Game")) {


				ImGui::TreePop();
			}
		}

		if (strcmp(CManager::GetNowScene(), "Result") == 0)
		{
			ImGui::SetNextTreeNodeOpen(true, ImGuiCond_Once);
			if (ImGui::TreeNode("Result")) {


				ImGui::TreePop();
			}
		}

		//ImGui::Text("This is some useful text.");
		//ImGui::Checkbox("Another Window", &show_another_window);
		//
		//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		//ImGui::ColorEdit3("clear color", (float*)&clear_color);

		if (ImGui::Button("Button"))
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}

	// Rendering
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif
}