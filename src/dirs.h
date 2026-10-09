#pragma once
#include <filesystem>

namespace fs = std::filesystem;
class dirs_s {
 public:
  fs::directory_entry* entry = nullptr;
  bool is_open = 0;
  bool should_recurse = 0;
  unsigned long num_sub = 0;
  dirs_s* sub_entries = nullptr;

  void get();
  void refresh();
  void sort();
  void del();

};
/*
void sort_dir_items(dirs_s* dir);
void get_dir_items(dirs_s* dir);
void get_dir_items_recursive(dirs_s* dir);
void sort_dir_items_recursive(dirs_s* dir);
void refresh_dir_items(dirs_s* dir);

void sort_dirs(dirs_s* entries, unsigned long num_entries) ;
*/

void print_dir_items(dirs_s* dir);
void print_dir_items_recursive(dirs_s* dir);
