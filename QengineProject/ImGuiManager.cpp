#include "ImGuiManager.h"

ImGuiManager::ImGuiManager(Window& window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true); // Use your actual window variable here
    ImGui_ImplOpenGL3_Init("#version 330");
}

void ImGuiManager::BasicText(const std::string& stringA, const std::string& stringB)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Your UI code here
    ImGui::Begin(stringA.c_str());
    ImGui::Text("%s", stringB.c_str());
    ImGui::End();

    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
