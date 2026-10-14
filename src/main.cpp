#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>
#include <imgui_stdlib.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include "dirs.h"

#ifdef _WIN32
std::chrono::steady_clock::time_point start;
void start_timer() {
  start = std::chrono::high_resolution_clock::now();
}
void print_timer(char* i) {
  int a = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
  std::cout << i << "\t" << a << "\n";
}
#endif
#ifdef __gnu_linux__
std::chrono::_V2::system_clock::time_point start = std::chrono::high_resolution_clock::now();
// std::filesystem::__file_clock::time_point started = std::chrono::high_resolution_clock::now();
void start_timer() {
  start = std::chrono::high_resolution_clock::now();
}
void print_timer(char* i) {
  int a = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
  std::cout << i << "\t" << (long double)a / 1000000.0f << "\n";
}
unsigned long time() {
  return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
}
long time(std::filesystem::file_time_type a) {
  return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::file_clock::to_sys(a) - start).count();
}
// std::chrono::file_clock::to_sys(ftime));
// std::chrono::time_point<std::filesystem::__file_clock, std::chrono::duration<signed long, std::nano>>
// std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<signed long, std::nano>>
#endif

static void glfw_error_callback(int error, const char* description) {
  fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

const int vsync_interval = 2;

#define ImCol4(R, G, B, A) ImVec4((float)R / 255, (float)G / 255, (float)B / 255, (float)A / 255)
void layout();
void sync_files();
void fileexplorer();
void editor();

dirs_s workspacedir;
unsigned long last_dirs_refresh = 0;
int main() {
#pragma region init
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit()) return 1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  GLFWwindow* window = glfwCreateWindow(1280, 800, "Ccode", nullptr, nullptr);
  if (window == nullptr) return 1;
  glfwMakeContextCurrent(window);
  gladLoadGL();
  glfwSwapInterval(vsync_interval);  // Enable vsync (when set to 1)
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330 core");
#pragma endregion
#pragma region setup

  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad;
  ImGui::StyleColorsDark();
  ImGuiStyle& style = ImGui::GetStyle();
  style.ScaleAllSizes(1);   // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
  style.FontScaleMain = 1;  // Set initial font scale. (in docking branch: using io.ConfigDpiScaleFonts=true automatically overrides this for every window depending on the current monitor)
  style.WindowPadding = ImVec2(0, 0);
  style.ItemSpacing = ImVec2(0, 0);
  style.WindowMinSize = ImVec2(1, 1);
  style.WindowBorderSize = 0;
  style.Colors[ImGuiCol_WindowBg] = ImCol4(0, 0, 0, 255);
  style.Colors[ImGuiCol_ChildBg] = ImCol4(0, 0, 0, 0);
  style.Colors[ImGuiCol_PopupBg] = ImCol4(0, 0, 0, 0);
  style.Colors[ImGuiCol_Border] = ImCol4(255, 255, 255, 255);

  char filename[1024];
  FILE* f = popen("zenity --file-selection --directory", "r");
  fgets(filename, 1024, f);
  filename[strcspn(filename, "\n")] = 0;
  std::cout << filename << "\n";

  workspacedir.entry = new fs::directory_entry(filename);
  workspacedir.entry->refresh();
  workspacedir.should_recurse = 1;
  workspacedir.is_open = 1;

  workspacedir.refresh();
  workspacedir.sort();
  print_dir_items_recursive(&workspacedir);
  //  get_dir_items_recursive(&workspacedir);
  //  print_dir_items_recursive(&workspacedir);
  //  std::cout << "\n";
  //  sort_dir_items_recursive(&workspacedir);
  // sort_dirs(workspacedir.sub_entries, workspacedir.num_sub);
  //  print_dir_items_recursive(&workspacedir);
  // refresh_dirs(&entries, &num_entry);
  // return 0;
  // return 0;

#pragma endregion
  while (!glfwWindowShouldClose(window)) {
#pragma region preloop
    glfwPollEvents();
    if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0) {
      ImGui_ImplGlfw_Sleep(10);
      continue;
    }
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
#pragma endregion
#pragma region loop
    ImGui::GetWindowDrawList()->AddCallback(ImGui::GetPlatformIO().DrawCallback_SetSamplerNearest);

    if (time() - last_dirs_refresh >= 500000) {
      last_dirs_refresh = time();
      workspacedir.refresh();
      workspacedir.sort();
      sync_files();
    }
    // ImGui::ShowStyleEditor();
    layout();
#pragma endregion
#pragma region postloop
    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#pragma endregion
    glfwSwapBuffers(window);
  }
#pragma region deinit
  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
#pragma endregion
  return 0;
}
using namespace ImGui;

bool main_open = 1, file_explorer_open = 1;
void layout() {
  ImGuiStyle& style = GetStyle();
  const ImGuiViewport* viewport = GetMainViewport();
  SetNextWindowPos(viewport->WorkPos);
  SetNextWindowSize(viewport->WorkSize);
  if (Begin("main", &main_open, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings)) {
    fileexplorer();
    SameLine();
    SeparatorEx(ImGuiSeparatorFlags_Vertical);
    SameLine();
    editor();
  }
  End();
}

template <typename T>
void resize_array(T** array, unsigned long size, unsigned long new_size) {
  T* temp = new T[new_size];
  for (unsigned long i = 0; i < new_size; i++) {
    if (i < size) {
      temp[i] = (*array)[i];
    }
  }
  if ((*array) != nullptr) {
    delete[] (*array);
    (*array) = nullptr;
  }
  (*array) = temp;
}

void get_file_contents(const char* filename, std::string* contents) {
  std::ifstream in(filename, std::ios::binary);
  if (in) {
    in.seekg(0, std::ios::end);
    contents->resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&(*contents)[0], contents->size());
    in.close();
    return;
  }
  throw(errno);
}

void set_file_contents(const char* filename, std::string* contents) {
  std::ofstream out(filename, std::ios::binary | std::ios::trunc);
  if (out) {
    out.write(&(*contents)[0], contents->size());
    out.close();
    return;
  }
  throw(errno);
}

unsigned long num_open_files = 0;
struct editorfiles_s {
  fs::directory_entry file;
  std::string content;
  std::filesystem::file_time_type drive_time;
  unsigned long last_edit = 0;
  bool edited = 0;
  bool conflict = 0;
};

void force_load_file(editorfiles_s* file) {
  file->file.refresh();
  get_file_contents(file->file.path().c_str(), &file->content);
  file->drive_time = file->file.last_write_time();
  file->conflict = 0;
  file->edited = 0;
}
void force_save_file(editorfiles_s* file) {
  file->file.refresh();
  set_file_contents(file->file.path().c_str(), &file->content);
  file->file.refresh();
  file->drive_time = file->file.last_write_time();
  file->conflict = 0;
  file->edited = 0;
}
void sync_file(editorfiles_s* file) {
  file->file.refresh();
  if (file->file.last_write_time() > file->drive_time && file->edited) {
    file->conflict = 1;
  } else if (file->file.last_write_time() > file->drive_time) {
    get_file_contents(file->file.path().c_str(), &file->content);
    file->drive_time = file->file.last_write_time();
  } else if (file->edited) {
    set_file_contents(file->file.path().c_str(), &file->content);
    file->file.refresh();
    file->drive_time = file->file.last_write_time();
    file->edited = 0;
  }
}

editorfiles_s* open_files;
void editor_add_file(fs::directory_entry file) {
  file.refresh();
  for (unsigned long i = 0; i < num_open_files; i++) {
    open_files[i].file.refresh();
    if ((file) == (open_files[i].file)) return;
  }
  resize_array(&open_files, num_open_files, num_open_files + 1);
  open_files[num_open_files].file = file;
  get_file_contents(open_files[num_open_files].file.path().c_str(), &open_files[num_open_files].content);
  open_files[num_open_files].drive_time = open_files[num_open_files].file.last_write_time();
  open_files[num_open_files].conflict = 0;
  open_files[num_open_files].edited = 0;
  open_files[num_open_files].last_edit = 0;
  num_open_files++;
}

void editor_remove_file(unsigned long filei) {
  if (open_files[filei].edited) {
    sync_file(&open_files[filei]);
    if (open_files[filei].conflict || open_files[filei].edited) {
      return;
    }
  }
  if (num_open_files == 1) {
    delete[] open_files;
    open_files = nullptr;
    num_open_files = 0;
  } else {
    editorfiles_s* temp = new editorfiles_s[num_open_files - 1];
    for (unsigned long i = 0; i < num_open_files - 1; i++) {
      temp[i] = open_files[i < filei ? i : i + 1];
    }
    delete[] open_files;
    open_files = temp;
    num_open_files--;
  }
}

unsigned long last_file_sync = 0;
void sync_files() {
  if (time() - last_file_sync >= 500000) {
    last_file_sync = time();
    for (unsigned long i = 0; i < num_open_files; i++) {
      sync_file(&open_files[i]);
    }
  }
}

void display_dir_items_recursive(dirs_s* dir) {
  if (dir->entry->is_directory()) {
    if (TreeNode(dir->entry->path().filename().c_str())) {
      if (dir->should_recurse == 0) {
        dir->should_recurse = 1;
        dir->is_open = 1;
        dir->refresh();  // FIXME: that... is gonna refresh every frame
        dir->sort();
      }
      dir->should_recurse = 1;
      dir->is_open = 1;
      if (dir->sub_entries != nullptr) {
        for (unsigned long i = 0; i < dir->num_sub; i++) {
          display_dir_items_recursive(&dir->sub_entries[i]);
        }
      }
      TreePop();
    } else {
      dir->is_open = 0;
    }
  } else if (dir->entry->is_regular_file()) {
    if (Selectable(dir->entry->path().filename().c_str())) {
      editor_add_file(*dir->entry);
    }
  } else {
    Text(dir->entry->path().filename().c_str());
  }
}

void fileexplorer() {
  if (BeginChild("file_explorer", ImVec2(150, 0), ImGuiChildFlags_ResizeX)) {
    display_dir_items_recursive(&workspacedir);
    Text("files");
  }
  EndChild();
}

void editor() {
  if (BeginChild("editor", ImVec2(0, 0), ImGuiChildFlags_None, ImGuiWindowFlags_None)) {
    bool conflics = 0;
    for (unsigned long i = 0; i < num_open_files; i++) {
      if (open_files[i].conflict) {
        if (!conflics) {
          Text("you have unsaved changes and the file on disk was modified for these files:");
          conflics = 1;
        }
        if (Button("overwrite")) {
          force_save_file(&open_files[i]);
        }
        SameLine();
        if (Button("reload")) {
          force_load_file(&open_files[i]);
        }
        SameLine();
        Text(open_files[i].file.path().c_str());
      }
    }
    if (BeginTabBar("open files", ImGuiTabBarFlags_Reorderable)) {
      for (unsigned long i = 0; i < num_open_files; i++) {
        bool open = 1;
        PushID(open_files[i].file.path().c_str());
        if (BeginTabItem(open_files[i].file.path().filename().c_str(), &open, (ImGuiTabItemFlags_UnsavedDocument * open_files[i].edited))) {
          Text(open_files[i].file.path().c_str());
          if (InputTextMultiline("##source", &open_files[i].content, ImVec2(-FLT_MIN, -FLT_MIN), ImGuiInputTextFlags_AllowTabInput)) {  //-FLT_MIN, GetTextLineHeight() * 16
            open_files[i].edited = 1;
            open_files[i].last_edit = time();
          }
          EndTabItem();
        }
        if (!open) {
          editor_remove_file(i--);
        }
        PopID();
      }
      EndTabBar();
    }

    // Text("editor");
  }
  EndChild();
}

/*
if (open_files[i].conflict == 1) {
  SetNextWindowPos(GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
  if (BeginPopupModal("conflict", nullptr, ImGuiWindowFlags_None)) {
    EndPopup();
  } else {
    OpenPopup("conflict");
  }
}
*/
