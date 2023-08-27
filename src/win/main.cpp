

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <windows.h>

bool show_main_window = true;

 void showOrHideMainWindow()
{
    show_main_window = !show_main_window;
}

// Main code
int main(int, char**)
{
    if (!glfwInit())
        return 1;

    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";

    // 关掉主窗体（step 1）
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "clipboard-note", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    IMGUI_CHECKVERSION();
    // Setup Dear ImGui context
    ImGui::CreateContext();
    ImGui::StyleColorsLight();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // 关掉主窗体（step 2）
    io.ConfigViewportsNoAutoMerge = true;


    io.Fonts->AddFontFromFileTTF("c:/windows/fonts/simhei.ttf", 13.0f, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    if (RegisterHotKey(NULL, 1, MOD_ALT,
                   0x42))
    {

    }





    // Main loop
    while (!glfwWindowShouldClose(window))
    {

        // Poll and handle events (inputs, window resize, etc.)
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ************ GUI **************
//#ifdef IMGUI_HAS_VIEWPORT
        ImGuiViewport* viewport = ImGui::GetMainViewport();
//ImGui::SetNextWindowPos(viewport->ImGuiViewport::WorkPos);
ImGui::SetNextWindowSize(viewport->ImGuiViewport::WorkSize);
//ImGui::SetNextWindowViewport(viewport->ID);
//#else
//        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
//        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
//#endif


if (show_main_window)
{


        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::Begin("clipboard-note", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysUseWindowPadding);
        ImGui::PopStyleVar();


        ImGui::BeginChild("header", ImVec2(0.0f, 60.0f), true);
        ImGui::Text("我是头部");
        ImGui::EndChild();

        ImGui::BeginChild("left", ImVec2(400.0f, 0.0f), true);
        ImGui::Text("分类");
        ImVec2 leftPos = ImGui::GetWindowPos();
        ImVec2 leftSize = ImGui::GetWindowSize();
        ImGui::EndChild();


        ImGui::SetNextWindowPos(ImVec2(leftPos.x + leftSize.x + 4.0f, leftPos.y));

        ImGui::BeginChild("content", ImVec2(0.0f, leftSize.y), true);
        ImGui::Text("内容");
        ImGui::EndChild();

        ImGui::End();

}

        // ************ GUI **************

        // Rendering
        ImGui::Render();
        // Update and Render additional Platform Windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);


        // 热键
        MSG msg;
        if (GetMessage(&msg, NULL, 0, 0))
        {
            if (msg.message == WM_HOTKEY)
            {
                wprintf(L"WM_HOTKEY received\n");
                showOrHideMainWindow();
            }
        }
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}