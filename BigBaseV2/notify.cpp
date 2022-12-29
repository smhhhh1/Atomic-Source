#include "notify.h"
#include <imgui.h>
#include <imgui_internal.h>
namespace big
{
	void notify::tick()
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);
		if (ImGui::Begin("##notifications", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize))
		{


		}
		ImGui::End();


		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImU32(ImColor(20, 20, 31, 180)));

		ImGui::RenderNotifications();


		ImGui::PopStyleColor(1);
	}
	
}