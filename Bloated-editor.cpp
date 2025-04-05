// main.cpp

// created by Georgiy Chipunov using prompt
// and got stuck , in bard
// Code in c a editor like unity ue5 with imgui and node graph and map editor with OpenGL

#include <glad/glad.h> // Must be included before GLFW
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imnodes.h" // Include your chosen node editor library

#include <iostream>
#include <vector>

// --- Simple Placeholder Data Structures ---
struct Node {
    int id;
    ImVec2 pos;
    // Add other node data (type, inputs, outputs, etc.)
};

struct Link {
    int id;
    int start_node, start_attr;
    int end_node, end_attr;
};

struct MapObject {
    int id;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    // Add mesh, material references etc.
};

// --- Global State (Simplified) ---
std::vector<Node> nodes;
std::vector<Link> links;
std::vector<MapObject> mapObjects;
int nextNodeId = 1;
int nextLinkId = 1;
int nextObjectId = 1;
// --- Framebuffer for Map Viewport ---
GLuint fbo = 0;
GLuint fboTexture = 0;
GLuint rboDepth = 0;
ImVec2 viewportSize = ImVec2(0, 0);

// --- Basic Camera (Placeholder) ---
glm::vec3 cameraPos = glm::vec3(0.0f, 2.0f, 5.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// --- Function Prototypes ---
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void renderSceneToFBO(int width, int height); // Renders your 3D map content
void createFramebuffer(int width, int height);
void deleteFramebuffer();

int main() {
    // --- GLFW Initialization ---
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    const char* glsl_version = "#version 330 core";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // --- GLFW Window Creation ---
    GLFWwindow* window = glfwCreateWindow(1600, 900, "C Game Editor", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1); // Enable vsync

    // --- GLAD Initialization ---
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // --- Setup Dear ImGui context ---
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImNodes::CreateContext(); // Initialize imnodes context
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows (Optional)

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // --- Initial FBO Creation (dummy size) ---
    createFramebuffer(800, 600);

    // --- Editor State Init ---
    // Add some initial nodes/objects if desired

    // --- Main Loop ---
    while (!glfwWindowShouldClose(window)) {
        // --- Input ---
        glfwPollEvents();
        processInput(window);

        // --- Start the Dear ImGui frame ---
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // --- Enable Dockspace ---
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        // --- Menu Bar ---
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New Scene")) { /* TODO */ }
                if (ImGui::MenuItem("Open Scene")) { /* TODO */ }
                if (ImGui::MenuItem("Save Scene")) { /* TODO */ }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit")) { glfwSetWindowShouldClose(window, true); }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit")) { /* TODO */ ImGui::EndMenu(); }
            if (ImGui::BeginMenu("View")) { /* TODO */ ImGui::EndMenu(); }
             if (ImGui::BeginMenu("Create")) {
                 if (ImGui::MenuItem("Add Node")) {
                      Node newNode;
                      newNode.id = nextNodeId++;
                      newNode.pos = ImVec2(100, 100); // Or spawn at mouse cursor
                      nodes.push_back(newNode);
                 }
                 if (ImGui::MenuItem("Add Cube")) {
                     MapObject newObj;
                     newObj.id = nextObjectId++;
                     newObj.position = glm::vec3(0.0f);
                     newObj.rotation = glm::vec3(0.0f);
                     newObj.scale = glm::vec3(1.0f);
                     mapObjects.push_back(newObj);
                 }
                 ImGui::EndMenu();
             }
            ImGui::EndMainMenuBar();
        }

        // --- Node Editor Window ---
        ImGui::Begin("Node Editor");
        ImNodes::BeginNodeEditor();

        // Example: Add Node button within the editor window
        if (ImGui::Button("Add Node Inside")) {
             Node newNode;
             newNode.id = nextNodeId++;
             // Get position from imnodes or center of view
             ImVec2 click_pos = ImGui::GetMousePos(); // Example position
             imnodes::SetNodeScreenSpacePos(newNode.id, click_pos);
             nodes.push_back(newNode);
        }
        ImGui::SameLine();
        if (ImGui::Button("Save Graph State")) {
            // TODO: Save node positions and links (e.g., to JSON or binary)
             ImNodes::SaveCurrentEditorStateToIniFile("my_editor.ini"); // Basic imnodes save
        }
         ImGui::SameLine();
         if (ImGui::Button("Load Graph State")) {
             // TODO: Load node positions and links
              ImNodes::LoadCurrentEditorStateFromIniFile("my_editor.ini"); // Basic imnodes load
         }


        // Draw Nodes
        for (Node& node : nodes) {
            ImNodes::BeginNode(node.id);
            ImNodes::BeginNodeTitleBar();
            ImGui::TextUnformatted(("Node " + std::to_string(node.id)).c_str());
            ImNodes::EndNodeTitleBar();

            // Input Attributes
            ImNodes::BeginInputAttribute(node.id << 8); // Unique ID for attribute
            ImGui::Text("Input");
            ImNodes::EndInputAttribute();

            // Output Attributes
            ImNodes::BeginOutputAttribute(node.id << 16); // Unique ID
             ImGui::Indent(40); // Push output to the right
             ImGui::Text("Output");
             ImGui::Unindent(40);
            ImNodes::EndOutputAttribute();


            // TODO: Add node content widgets here (sliders, text fields, etc.)

            ImNodes::EndNode();

             // Update node position if moved (imnodes handles dragging internally)
             // You might want to store the position back into your `Node` struct if needed
             // node.pos = imnodes::GetNodeScreenSpacePos(node.id); // Check imnodes API
        }

        // Draw Links
        for (const Link& link : links) {
            ImNodes::Link(link.id, link.start_attr, link.end_attr);
        }

        ImNodes::EndNodeEditor();

        // Handle creating new links
        int start_attr, end_attr;
        if (ImNodes::IsLinkCreated(&start_attr, &end_attr)) {
             // Check if start_attr and end_attr are valid outputs/inputs
             // Extract node IDs from attribute IDs (depends on how you generate attr IDs)
             int start_node_id = start_attr >> 16; // Example if output ID was (node.id << 16)
             int end_node_id = end_attr >> 8;   // Example if input ID was (node.id << 8)

             // TODO: Add validation (e.g., don't link output to output)
             std::cout << "Linking " << start_node_id << " (" << start_attr << ") to "
                       << end_node_id << " (" << end_attr << ")" << std::endl;

             Link newLink;
             newLink.id = nextLinkId++;
             newLink.start_attr = start_attr;
             newLink.end_attr = end_attr;
             // Extract node IDs if needed for your data structure
             // newLink.start_node = ...;
             // newLink.end_node = ...;
             links.push_back(newLink);
        }

        // Handle deleting links/nodes
        int link_id;
        if (ImNodes::IsLinkDestroyed(&link_id)) {
            auto iter = std::remove_if(links.begin(), links.end(),
                [link_id](const Link& link){ return link.id == link_id; });
            if (iter != links.end()) {
                links.erase(iter, links.end());
                 std::cout << "Deleted Link: " << link_id << std::endl;
            }
        }
        const int num_selected_nodes = ImNodes::NumSelectedNodes();
        if (num_selected_nodes > 0 && ImGui::IsKeyReleased(ImGuiKey_Delete)) {
            std::vector<int> selected_nodes_ids(num_selected_nodes);
            ImNodes::GetSelectedNodes(selected_nodes_ids.data());
            for (int node_id_to_delete : selected_nodes_ids) {
                // Remove node
                auto node_iter = std::remove_if(nodes.begin(), nodes.end(),
                    [node_id_to_delete](const Node& node){ return node.id == node_id_to_delete; });
                 if (node_iter != nodes.end()) {
                    nodes.erase(node_iter, nodes.end());
                    std::cout << "Deleted Node: " << node_id_to_delete << std::endl;

                    // Remove associated links
                     links.erase(std::remove_if(links.begin(), links.end(),
                        [node_id_to_delete](const Link& link) {
                             // Simple check, assumes attribute IDs store node ID
                             int start_node_id = link.start_attr >> 16; // Adjust shifts based on your ID scheme
                             int end_node_id = link.end_attr >> 8;    // Adjust shifts based on your ID scheme
                             return start_node_id == node_id_to_delete || end_node_id == node_id_to_delete;
                         }), links.end());
                 }
            }
        }


        ImGui::End(); // Node Editor Window

        // --- Map/Level Editor Viewport ---
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0)); // Remove padding for viewport
        ImGui::Begin("Map Editor Viewport");
        {
            ImVec2 currentViewportSize = ImGui::GetContentRegionAvail();
            if (viewportSize.x != currentViewportSize.x || viewportSize.y != currentViewportSize.y) {
                viewportSize = currentViewportSize;
                // Resize Framebuffer
                deleteFramebuffer(); // Delete old one first
                createFramebuffer((int)viewportSize.x, (int)viewportSize.y);
                 std::cout << "Resized FBO to " << viewportSize.x << "x" << viewportSize.y << std::endl;
            }

            // Render 3D scene to our FBO
            if (fbo != 0 && viewportSize.x > 0 && viewportSize.y > 0) {
                renderSceneToFBO((int)viewportSize.x, (int)viewportSize.y);

                // Display FBO texture in ImGui window
                // Flip texture vertically because OpenGL origin is bottom-left, ImGui is top-left
                ImGui::Image((void*)(intptr_t)fboTexture, viewportSize, ImVec2(0, 1), ImVec2(1, 0));
            } else {
                 ImGui::Text("Viewport size is invalid or FBO not created.");
            }


            // TODO: Handle mouse input within this window for camera control, object selection etc.
            // Use ImGui::IsWindowHovered(), ImGui::GetMousePosInWindow(), ImGui::IsMouseDown() etc.
            if(ImGui::IsWindowFocused() && ImGui::IsWindowHovered()) {
                // Handle camera panning, orbiting, zooming based on mouse delta, scroll wheel
                 // Example: Simple camera movement
                 float cameraSpeed = 0.05f;
                 if (ImGui::IsKeyDown(ImGuiKey_W)) cameraPos += cameraSpeed * cameraFront;
                 if (ImGui::IsKeyDown(ImGuiKey_S)) cameraPos -= cameraSpeed * cameraFront;
                 if (ImGui::IsKeyDown(ImGuiKey_A)) cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
                 if (ImGui::IsKeyDown(ImGuiKey_D)) cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
                 // Add mouse look, orbit etc.
            }
        }
        ImGui::End();
        ImGui::PopStyleVar(); // Restore padding

        // --- Properties Window ---
        ImGui::Begin("Properties");
        // TODO: Show properties of selected node or map object
        ImGui::Text("Select an item to see properties.");
        // Example: If a node is selected in imnodes...
        if (ImNodes::NumSelectedNodes() > 0) {
            std::vector<int> selected_node_ids(ImNodes::NumSelectedNodes());
            ImNodes::GetSelectedNodes(selected_node_ids.data());
             ImGui::Text("Selected Node ID: %d", selected_node_ids[0]);
             // Find the node in your `nodes` vector and display its properties (pos, custom data...)
        }
         // Example: If a map object is selected (implement selection logic first)...
        // if (selectedMapObjectId != -1) { ... }

        ImGui::End();

        // --- Scene Hierarchy Window ---
        ImGui::Begin("Scene Hierarchy");
        // TODO: List map objects, allow selection
         for(const auto& obj : mapObjects) {
             std::string label = "Object " + std::to_string(obj.id);
             if (ImGui::Selectable(label.c_str() /*, is_selected */)) {
                 // Handle selection logic
                 std::cout << "Selected map object: " << obj.id << std::endl;
             }
         }
        ImGui::End();

        // --- Rendering ---
        // Clear the main window (important if using viewports or if background is visible)
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render ImGui draw data
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows (if viewports enabled)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        // --- Swap Buffers ---
        glfwSwapBuffers(window);
    }

    // --- Cleanup ---
    deleteFramebuffer();
    ImNodes::DestroyContext();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
