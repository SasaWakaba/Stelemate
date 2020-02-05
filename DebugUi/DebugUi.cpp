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
#include "../GameSystem/WorldManager.h"

bool show_another_window = false;

bool CDebugUI::bAI_Window = true;

void CDebugUI::Initialize()
{

	ImGui_ImplDX11_Init(CRenderer::GetDevice(), CRenderer::GetDeviceContext());

	const ImVec4 kColorPrimaryBase = { 0.109f, 0.996f, 1.000f , 1.0f };
	const ImVec4 kColorPrimary =	{ kColorPrimaryBase.x, kColorPrimaryBase.y, kColorPrimaryBase.z, 0.933f };
	const ImVec4 kColorPrimaryA99 = { kColorPrimaryBase.x, kColorPrimaryBase.y, kColorPrimaryBase.z, 0.600f };
	const ImVec4 kColorPrimaryA66 = { kColorPrimaryBase.x, kColorPrimaryBase.y, kColorPrimaryBase.z, 0.4f };
	const ImVec4 kColorPrimaryA33 = { kColorPrimaryBase.x, kColorPrimaryBase.y, kColorPrimaryBase.z, 0.2f };
	const ImVec4 kColorPrimaryDark = { 0.011f, 0.098f, 0.101f, 0.733f };
		  
	const ImVec4 kColorAccentBase = { 1.000f , 0.631f , 0.000f , 1.0f};
	const ImVec4 kColorAccent =		{ kColorAccentBase.x , kColorAccentBase.y , kColorAccentBase.z , 0.933f };
	const ImVec4 kColorAccentAcc =	{ kColorAccentBase.x , kColorAccentBase.y , kColorAccentBase.z , 0.800f };
	const ImVec4 kColorAccentA99 =	{ kColorAccentBase.x , kColorAccentBase.y , kColorAccentBase.z , 0.600f };

	const ImVec4 kColorWhite = { 0.866f , 0.866f , 0.866f , 0.800f };
	const ImVec4 kColorBlackA55 = { 0.066f, 0.066f, 0.066f, 0.333f};

	ImVec4 Base = { 0.031f,0.098f, 0.168f, 0.8f };
	ImVec4 Line = { 0.427f,0.796f, 0.854f,1.000f };
	ImVec4 Text = { 0.968f,0.933f, 0.396f,1.0f };
	ImVec4 sub = { 0.427f,0.796f, 0.854f,1.000f };

	ImGui::GetStyle().Colors[ImGuiCol_MenuBarBg] = kColorPrimaryA33;
	ImGui::GetStyle().Colors[ImGuiCol_TitleBg] = kColorPrimaryDark;
	ImGui::GetStyle().Colors[ImGuiCol_TitleBgCollapsed] = kColorPrimaryDark;
	ImGui::GetStyle().Colors[ImGuiCol_TitleBgActive] = kColorPrimaryA99;
	ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = kColorPrimaryDark;
	ImGui::GetStyle().Colors[ImGuiCol_Border] = kColorPrimaryA99;
	ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = kColorPrimaryA33;
	ImGui::GetStyle().Colors[ImGuiCol_FrameBgHovered] = kColorAccentAcc;
	ImGui::GetStyle().Colors[ImGuiCol_FrameBgActive] = kColorAccent;
	ImGui::GetStyle().Colors[ImGuiCol_ScrollbarBg] = kColorPrimaryA33;
	ImGui::GetStyle().Colors[ImGuiCol_ScrollbarGrab] = kColorPrimaryA99;
	ImGui::GetStyle().Colors[ImGuiCol_ScrollbarGrabHovered] = kColorPrimaryA99;
	ImGui::GetStyle().Colors[ImGuiCol_ScrollbarGrabActive] = kColorPrimary;
	ImGui::GetStyle().Colors[ImGuiCol_CheckMark] = kColorAccent;
	ImGui::GetStyle().Colors[ImGuiCol_SliderGrab] = kColorPrimaryA99;
	ImGui::GetStyle().Colors[ImGuiCol_SliderGrabActive] = kColorPrimary;
	ImGui::GetStyle().Colors[ImGuiCol_Button] = kColorPrimaryA33;
	ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = kColorAccentAcc;
	ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = kColorAccent;
	ImGui::GetStyle().Colors[ImGuiCol_Header] = kColorPrimaryA99;
	ImGui::GetStyle().Colors[ImGuiCol_HeaderHovered] = kColorAccentAcc;
	ImGui::GetStyle().Colors[ImGuiCol_HeaderActive] = kColorAccent;
	ImGui::GetStyle().Colors[ImGuiCol_PlotLines] = kColorPrimaryA99;
	ImGui::GetStyle().Colors[ImGuiCol_PlotLinesHovered] = kColorPrimary;
	ImGui::GetStyle().Colors[ImGuiCol_PlotHistogram] = kColorPrimaryA99;
	ImGui::GetStyle().Colors[ImGuiCol_PlotHistogramHovered] = kColorPrimary;
	ImGui::GetStyle().Colors[ImGuiCol_Text] = kColorPrimary;
	ImGui::GetStyle().Colors[ImGuiCol_TextDisabled] = kColorPrimaryA66;
	ImGui::GetStyle().Colors[ImGuiCol_TextSelectedBg] = kColorAccent;
	ImGui::GetStyle().Colors[ImGuiCol_PopupBg] = kColorPrimaryDark;

	ImGui::GetStyle().AntiAliasedLines = true;
	ImGui::GetStyle().WindowRounding = 0.0f;
	ImGui::GetStyle().FrameRounding = 0.0f;


}

void CDebugUI::Finalize()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void CDebugUI::Update()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void CDebugUI::Draw()
{
	CScene* scene = CManager::GetScene();
	static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	XMFLOAT3 pos(0,0,0);
	//if(scene != nullptr) pos = scene->GetGameObject<CPlayer>(2)->GetPosition();

	{
		static float f = 0.0f;
		static int counter = 0;
		ImGui::Begin("DebugWindow");

		ImGui::Text("Scene : %s", CManager::GetNowScene());

		switch (WorldManager::GetGameMode())
		{
		case Casual:
			ImGui::Text("GameMode:Casual");
			break;
		case Classic:
			ImGui::Text("GameMode:Classic");
			break;
		}
		
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
				ImGui::Text("NowStage : %d", WorldManager::GetNowStageNum());
				ImGui::Text("Turn : %d", WorldManager::GetTurn());
				switch (WorldManager::GetActionTurn())
				{
				case 0:
				case 2:
					ImGui::Text("ActionTurn : Player");
					break;
				case 1:
				case 3:
					ImGui::Text("ActionTurn : Enemy");
					break;
				}


				ImGui::Checkbox("AI Window", &bAI_Window);
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
		
		if (strcmp(CManager::GetNowScene(), "Preparation") == 0)
		{
			ImGui::SetNextTreeNodeOpen(true, ImGuiCond_Once);
			if (ImGui::TreeNode("Preparation")) {
				ImGui::Text("NextStage : %d", WorldManager::GetNowStageNum());

				ImGui::TreePop();
			}
		}


		
		
		ImGui::Checkbox("Another Window", &show_another_window);
		
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::ColorEdit3("clear color", (float*)&clear_color);

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
		ImGui::Begin("Another Window", &show_another_window);
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}

	if (bAI_Window)
	{
		ImGui::Begin("AI Window", &show_another_window);

		switch (WorldManager::GetEnemyAction())
		{
		case wait:
			ImGui::Text("EnemySelectAction : wait");
			break;
		case move:
			ImGui::Text("EnemySelectAction : Move");
			break;
		case attack:
			ImGui::Text("EnemySelectAction : Attack");
			break;
		case heal:
			ImGui::Text("EnemySelectAction : Heal");
			break;
		case end:
			ImGui::Text("EnemySelectAction : end");
			break;
		}
		


		ImVec2 pos = { ImGui::GetWindowPos().x + 50, ImGui::GetWindowPos().y + 100 };
		float width = ImGui::GetWindowWidth() - 100;
		float height = ImGui::GetWindowHeight() - 100;
		if (width > height)
		{
			width = height;
		}
		else if (height > width)
		{
			height = width;
		}

		StageState nowStage = WorldManager::GetNowStage();
		ImColor color = {0.968f, 0.933f, 0.396f};
		for (int i = 0; i < nowStage.numZ + 1; i++)
		{
			ImVec2 linePosA = { pos.x,			pos.y + (height / (nowStage.numZ) * i) };
			ImVec2 linePosB = { pos.x + width,	pos.y + (height / (nowStage.numZ) * i) };
			ImGui::GetWindowDrawList()->AddLine(linePosA, linePosB, color, 1.0f);
		}

		for (int i = 0; i < nowStage.numX + 1; i++)
		{
			ImVec2 linePosA = { pos.x + width / (nowStage.numX) * i, pos.y };
			ImVec2 linePosB = { pos.x + width / (nowStage.numX) * i, pos.y + height };
			ImGui::GetWindowDrawList()->AddLine(linePosA, linePosB, color, 1.0f);
		}

		for (int z = 0; z < nowStage.numZ; z++)
		{
			for (int x = 0; x < nowStage.numX; x++)
			{
				if (nowStage.Stage[z * nowStage.numX + x].bChar)
				{
					float w = width - width / nowStage.numX;
					float h = height - height / nowStage.numZ;
					ImVec2 Diffpos = { pos.x + (width / nowStage.numX / 2), pos.y + (height / nowStage.numZ / 2) };
					ImVec2 Pos2 = { Diffpos.x + w / (nowStage.numX - 1) * x, Diffpos.y + h / (nowStage.numZ - 1) * (nowStage.numZ - 1 - z) };
					if (!nowStage.Stage[z * nowStage.numX + x].Charcter->GetAlly())
					{
						color = {1.0f, 0.0f, 0.0f};
					}
					else
					{
						color = { 0.109f, 0.996f, 1.000f };
					}
					ImGui::GetWindowDrawList()->AddCircleFilled(Pos2, (width / (nowStage.numX)) / 3, color, 12);
				}
			}
		}
		

		if (ImGui::Button("Close Me"))
			bAI_Window = false;
		ImGui::End();
	}

	// Rendering
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}