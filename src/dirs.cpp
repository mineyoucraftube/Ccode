#include "dirs.h"
#include <iostream>
/*
void recursive_dir_delete(dirs_s* entry);
unsigned long get_dirs(char* path, dirs_s** entries, unsigned long* num_entries);
void sort_dirs(dirs_s* entries, unsigned long num_entries);
void refresh_dirs(dirs_s** entries, unsigned long* num_entries);

void recursive_dir_delete(dirs_s* entry) {
  for (unsigned long i = 0; i < entry->num_sub; i++) {
    if (entry->sub_entries[i].sub_entries != nullptr) {
      recursive_dir_delete(&entry->sub_entries[i]);
    }
    delete[] entry->sub_entries;
    entry->sub_entries = nullptr;
  }
}

void recursive_dir_refresh(dirs_s* entries, unsigned long num_entries) {
  for (unsigned long i = 0; i < num_entries; i++) {
    entries[i].entry.refresh();
  }
}

unsigned long get_dirs(char* path, dirs_s** entries, unsigned long* num_entries) {
  std::error_code fserror;
  unsigned long num_paths = 0;
  unsigned long pathi = 0;
  for (fs::directory_iterator entry(path, fserror); begin(entry) != end(entry); entry.increment(fserror), num_paths++);  // if(fserror.value() !=0) entry.disable_recursion_pending();
  if ((*entries) != nullptr) {
    unsigned long old_num_paths = (*num_entries);
    dirs_s* tempentries = new dirs_s[num_paths];

    for (fs::directory_iterator entry(path, fserror); pathi < num_paths; entry.increment(fserror)) {  // if(fserror.value() !=0) entry.disable_recursion_pending();
      tempentries[pathi++].entry = *entry;
    }
    sort_dirs(tempentries, num_paths);
    for (unsigned long i = 0; i < old_num_paths; i++) {
      (*entries)[i].should_delete = 1;
      (*entries)[i].entry.refresh();
    }

    for (unsigned long i = 0; i < num_paths; i++) {
      for (unsigned long j = 0; j < old_num_paths; j++) {
        if ((*entries)[j].entry == tempentries[i].entry) {
          tempentries[i] = (*entries)[j];
          (*entries)[j].should_delete = !(*entries)[j].entry.exists();
        }
      }
    }
    for (unsigned long i = 0; i < old_num_paths; i++) {
      if ((*entries)[i].should_delete) {
        if ((*entries[i]).sub_entries != nullptr) {
          recursive_dir_delete(&(*entries)[i]);
        }
      }
    }
    delete[] (*entries);
    (*entries) = tempentries;
  } else {
    (*entries) = new dirs_s[num_paths];

    for (fs::directory_iterator entry(path, fserror); pathi < num_paths; entry.increment(fserror)) {  // if(fserror.value() !=0) entry.disable_recursion_pending();
      (*entries)[pathi++].entry = *entry;
    }
  }

  sort_dirs((*entries), num_paths);
  (*num_entries) = num_paths;
  return num_paths;
}

void sort_dirs(dirs_s* entries, unsigned long num_entries) {
  dirs_s tempdir;
  for (unsigned long i = 1; i < num_entries; i++) {
    for (unsigned long j = 1; j < num_entries + 1 - i; j++) {
      if (entries[j - 1].entry.exists() < entries[j].entry.exists()) {
        tempdir = entries[j - 1];
        entries[j - 1] = entries[j];
        entries[j] = tempdir;
      } else if (entries[j - 1].entry.is_directory() < entries[j].entry.is_directory()) {
        tempdir = entries[j - 1];
        entries[j - 1] = entries[j];
        entries[j] = tempdir;
      } else if (entries[j - 1].entry.is_directory() == entries[j].entry.is_directory()) {
        unsigned long k = 0;
        while (entries[j - 1].entry.path().filename().c_str()[k] == entries[j].entry.path().filename().c_str()[k]) k++;
        if ((entries[j - 1].entry.path().filename().c_str()[k] > entries[j].entry.path().filename().c_str()[k])) {
          tempdir = entries[j - 1];
          entries[j - 1] = entries[j];
          entries[j] = tempdir;
        }
      }
    }
  }
}

void refresh_dirs(dirs_s** entries, unsigned long* num_entries) {
  //  dirs_s* entries = nullptr;
  //  unsigned long num_entry = 0;
  get_dirs(".", entries, num_entries);
  for (int i = 0; i < (*num_entries); i++) {
    std::cout << (*entries)[i].entry.is_directory() << " " << (*entries)[i].entry.is_symlink() << " " << (*entries)[i].entry.path().filename().c_str() << '\n';
  }
  int a;
  std::cout << ((*entries)[0].entry == (*entries)[1].entry) << "\n";
  std::cout << ((*entries)[1].entry == (*entries)[1].entry) << "\n";
  std::cout << (*entries)[17].entry.path().filename().c_str() << "\n";
  std::cout << (*entries)[17].entry.exists() << "\n";
  std::cin >> a;
  std::cout << (*entries)[17].entry.path().filename().c_str() << "\n";
  std::cout << (*entries)[17].entry.exists() << "\n";
  std::cin >> a;
  (*entries)[17].entry.refresh();
  std::cout << (*entries)[17].entry.path().filename().c_str() << "\n";
  std::cout << (*entries)[17].entry.exists() << "\n";
}
*/
/*
void sort_dirs(dirs_s* entries, unsigned long num_entries) {
  dirs_s tempdir;
  for (unsigned long i = 1; i < num_entries; i++) {
    for (unsigned long j = 1; j < num_entries + 1 - i; j++) {
      if (entries[j - 1].entry->exists() < entries[j].entry->exists()) {
        tempdir = entries[j - 1];
        entries[j - 1] = entries[j];
        entries[j] = tempdir;
      } else if (entries[j - 1].entry->is_directory() < entries[j].entry->is_directory()) {
        tempdir = entries[j - 1];
        entries[j - 1] = entries[j];
        entries[j] = tempdir;
      } else if (entries[j - 1].entry->is_directory() == entries[j].entry->is_directory()) {
        unsigned long k = 0;
        while (entries[j - 1].entry->path().filename().c_str()[k] == entries[j].entry->path().filename().c_str()[k]) k++;
        if ((entries[j - 1].entry->path().filename().c_str()[k] > entries[j].entry->path().filename().c_str()[k])) {
          tempdir = entries[j - 1];
          entries[j - 1] = entries[j];
          entries[j] = tempdir;
        }
      }
    }
  }
}
*/
/*











workspace
*/

/*
void sort_dir_items(dirs_s* dir) {
  dirs_s tempdir;
  for (unsigned long i = 1; i < dir->num_sub; i++) {
    for (unsigned long j = 1; j < dir->num_sub + 1 - i; j++) {
      if (dir->sub_entries[j - 1].entry->exists() < dir->sub_entries[j].entry->exists()) {
        tempdir = dir->sub_entries[j - 1];
        dir->sub_entries[j - 1] = dir->sub_entries[j];
        dir->sub_entries[j] = tempdir;

      } else if (dir->sub_entries[j - 1].entry->is_directory() < dir->sub_entries[j].entry->is_directory()) {
        tempdir = dir->sub_entries[j - 1];
        dir->sub_entries[j - 1] = dir->sub_entries[j];
        dir->sub_entries[j] = tempdir;

      } else if (dir->sub_entries[j - 1].entry->is_directory() == dir->sub_entries[j].entry->is_directory()) {
        unsigned long k = 0;
        while (dir->sub_entries[j - 1].entry->path().filename().c_str()[k] == dir->sub_entries[j].entry->path().filename().c_str()[k]) k++;  // known bug/FIXME/TODO: if both file names are the same this will segfault, this isn't an issue unless manual fuckery is involved
        if ((dir->sub_entries[j - 1].entry->path().filename().c_str()[k] > dir->sub_entries[j].entry->path().filename().c_str()[k])) {
          tempdir = dir->sub_entries[j - 1];
          dir->sub_entries[j - 1] = dir->sub_entries[j];
          dir->sub_entries[j] = tempdir;
        }
      }
    }
  }
}

void sort_dir_items_recursive(dirs_s* dir) {
  sort_dir_items(dir);
  if (dir->sub_entries != nullptr) {
    for (unsigned long i = 0; i < dir->num_sub; i++) {
      if (dir->sub_entries[i].entry->is_directory()) {
        sort_dir_items_recursive(&dir->sub_entries[i]);
      }
    }
  }
}

void get_dir_items(dirs_s* dir) {
  std::error_code fserror;
  unsigned long num_items = 0;
  for (fs::directory_iterator entry(dir->entry->path(), fserror); begin(entry) != end(entry); entry.increment(fserror), num_items++);  // if(fserror.value() !=0) entry->disable_recursion_pending();
  if (dir->sub_entries != nullptr) {
    for (unsigned long i = 0; i < dir->num_sub; i++) {
      dir->sub_entries[i].del();
    }
    // std::cout << "get_dir_items(dirs_s* dir): dir.sub_entries should be nullptr. if dir.sub_entries[].sub_entries isn't nullptr, a memory leak will happen";
    delete[] dir->sub_entries;
    dir->sub_entries = nullptr;
    dir->num_sub = 0;
  }
  dir->num_sub = num_items;
  dir->sub_entries = new dirs_s[dir->num_sub];
  num_items = 0;
  for (fs::directory_iterator entry(dir->entry->path(), fserror); num_items < dir->num_sub && begin(entry) != end(entry); entry.increment(fserror)) {  // if(fserror.value() !=0) entry->disable_recursion_pending();
    dir->sub_entries[num_items++].entry = new fs::directory_entry(entry->path());
  }

  //  (*num_entries) = num_items;
  // return num_items;
}

void get_dir_items_recursive(dirs_s* dir) {
  if (dir->should_recurse) {
    get_dir_items(dir);
    for (unsigned long i = 0; i < dir->num_sub; i++) {
      // if (dir->sub_entries[i].entry->is_directory() && dir->sub_entries[i].should_recurse) {
      if (dir->sub_entries[i].entry->is_directory()) {
        get_dir_items_recursive(&dir->sub_entries[i]);
      }
    }
  }
}

void refresh_dir_items(dirs_s* dir) {
  dirs_s tempdir;
  tempdir.entry = dir->entry;
  get_dir_items(&tempdir);

  for (unsigned long i = 0; i < dir->num_sub; i++) {
    dir->sub_entries[i].entry->refresh();
    if (!dir->sub_entries[i].entry->exists()) {
      dir->sub_entries[i].del();
      continue;
    }
    for (unsigned long j = 0; j < tempdir.num_sub; j++) {
      if (dir->sub_entries[i].entry == tempdir.sub_entries[j].entry) {
        tempdir.sub_entries[j].del();
        tempdir.sub_entries[j] = dir->sub_entries[i];
        goto skipdel;
      }
    }
    dir->sub_entries[i].del();
  skipdel:;
  }
}

void refresh_dir_items_recursive(dirs_s* dir) {
  dir->entry->refresh();
  if (!dir->entry->exists()) {
    dir->del();
    return;
  }
  if (dir->sub_entries != nullptr) {
    for (unsigned long i = 0; i < dir->num_sub; i++) {
      refresh_dir_items(dir);
    }
  }
}
*/

void print_dir_items(dirs_s* dir) {
  std::cout << dir->entry->path().c_str() << '\n';
  if (dir->sub_entries != nullptr) {
    for (unsigned long i = 0; i < dir->num_sub; i++) {
      std::cout << dir->sub_entries[i].entry->path().c_str() << '\n';
    }
  }
}

void print_dir_items_recursive(dirs_s* dir) {
  std::cout << dir->entry->path().c_str() << '\n';
  if (dir->sub_entries != nullptr) {
    for (unsigned long i = 0; i < dir->num_sub; i++) {
      print_dir_items_recursive(&dir->sub_entries[i]);
    }
  }
}

dirs_s* getr(dirs_s* dir) {
  std::error_code fserror;
  unsigned long num_items = 0;
  unsigned long itemi = 0;
  for (fs::directory_iterator entry(dir->entry->path(), fserror); begin(entry) != end(entry); entry.increment(fserror), num_items++);

  dirs_s* newdir = new dirs_s;
  newdir->sub_entries = new dirs_s[num_items];
  newdir->num_sub = num_items;
  for (fs::directory_iterator entry(dir->entry->path(), fserror); itemi < dir->num_sub && begin(entry) != end(entry); entry.increment(fserror)) {  // if(fserror.value() !=0) entry->disable_recursion_pending();
    newdir->sub_entries[itemi++].entry = new fs::directory_entry(entry->path());
  }
  return newdir;
}

void dirs_s::get() {
  if (sub_entries != nullptr) {
    return;
  }
  std::error_code fserror;
  unsigned long num_items = 0;
  unsigned long itemi = 0;
  for (fs::directory_iterator entryi(entry->path(), fserror); begin(entryi) != end(entryi); entryi.increment(fserror), num_items++)
    if (fserror.value() != 0) std::cout << fserror.message() << '\n';

  num_sub = num_items;
  sub_entries = new dirs_s[num_sub];

  for (fs::directory_iterator entryi(entry->path(), fserror); itemi < num_sub && begin(entryi) != end(entryi); entryi.increment(fserror)) {  // if(fserror.value() !=0) entry->disable_recursion_pending();
    sub_entries[itemi++].entry = new fs::directory_entry(entryi->path());
  }
}

void dirs_s::refresh() {
  entry->refresh();
  if (!entry->exists()) {
    this->del();
    return;
  }
  if (sub_entries != nullptr) {
    if (should_recurse) {
      dirs_s* newdir = getr(this);
      for (unsigned long i = 0; i < num_sub; i++) {
        sub_entries[i].refresh();
        bool should_delete = 1;
        for (unsigned long j = 0; j < newdir->num_sub; j++) {
          if (sub_entries[i].entry == newdir->sub_entries[j].entry) {
            delete newdir->sub_entries[j].entry;
            newdir->sub_entries[j] = sub_entries[i];
            should_delete = 0;
          }
        }
        if (should_delete) {
          sub_entries[i].del();
        }
      }
      delete[] sub_entries;
      sub_entries = newdir->sub_entries;
      newdir->sub_entries = nullptr;
      num_sub = newdir->num_sub;
      newdir->num_sub = 0;
      delete newdir;
      newdir = nullptr;

    } else {
      for (unsigned long i = 0; i < num_sub; i++) {
        sub_entries[i].del();
      }
      delete[] sub_entries;
      sub_entries = nullptr;
    }
  } else if (entry->is_directory() && should_recurse) {
    get();
  }
}

void dirs_s::sort() {
  if (sub_entries != nullptr) {
    dirs_s tempdir;
    for (unsigned long i = 1; i < num_sub; i++) {
      for (unsigned long j = 1; j < num_sub + 1 - i; j++) {
        if (sub_entries[j - 1].entry->exists() < sub_entries[j].entry->exists()) {
          tempdir = sub_entries[j - 1];
          sub_entries[j - 1] = sub_entries[j];
          sub_entries[j] = tempdir;

        } else if (sub_entries[j - 1].entry->is_directory() < sub_entries[j].entry->is_directory()) {
          tempdir = sub_entries[j - 1];
          sub_entries[j - 1] = sub_entries[j];
          sub_entries[j] = tempdir;

        } else if (sub_entries[j - 1].entry->is_directory() == sub_entries[j].entry->is_directory()) {
          unsigned long k = 0;
          while (sub_entries[j - 1].entry->path().filename().c_str()[k] == sub_entries[j].entry->path().filename().c_str()[k]) k++;  // known bug/FIXME/TODO: if both file names are the same this will segfault, this isn't an issue unless manual fuckery is involved
          if ((sub_entries[j - 1].entry->path().filename().c_str()[k] > sub_entries[j].entry->path().filename().c_str()[k])) {
            tempdir = sub_entries[j - 1];
            sub_entries[j - 1] = sub_entries[j];
            sub_entries[j] = tempdir;
          }
        }
      }
    }
    for (unsigned long i = 0; i < num_sub; i++) {
      if (sub_entries[i].entry->is_directory()) {
        sub_entries[i].sort();
      }
    }
  }
}

void dirs_s::del() {
  if (entry != nullptr) {
    delete entry;
    entry = nullptr;
  }
  if (sub_entries != nullptr) {
    for (unsigned long i = 0; i < num_sub; i++) {
      sub_entries[i].del();
    }
    delete[] sub_entries;
    sub_entries = nullptr;
  }
}

/*

void sort_dir_items(dirs_s* dir) {
  dirs_s tempdir;
  for (unsigned long i = 1; i < dir->num_sub; i++) {
    for (unsigned long j = 1; j < dir->num_sub + 1 - i; j++) {
      if (dir->sub_entries[j - 1].entry.exists() < dir->sub_entries[j].entry.exists()) {
        tempdir = dir->sub_entries[j - 1];
        dir->sub_entries[j - 1] = dir->sub_entries[j];
        dir->sub_entries[j] = tempdir;

      } else if (dir->sub_entries[j - 1].entry.is_directory() < dir->sub_entries[j].entry.is_directory()) {
        tempdir = dir->sub_entries[j - 1];
        dir->sub_entries[j - 1] = dir->sub_entries[j];
        dir->sub_entries[j] = tempdir;

      } else if (dir->sub_entries[j - 1].entry.is_directory() == dir->sub_entries[j].entry.is_directory()) {
        unsigned long k = 0;
        while (dir->sub_entries[j - 1].entry.path().filename().c_str()[k] == dir->sub_entries[j].entry.path().filename().c_str()[k]) k++;  // known bug/FIXME/TODO: if both file names are the same this will segfault, this isn't an issue unless manual fuckery is involved
        if ((dir->sub_entries[j - 1].entry.path().filename().c_str()[k] > dir->sub_entries[j].entry.path().filename().c_str()[k])) {
          tempdir = dir->sub_entries[j - 1];
          dir->sub_entries[j - 1] = dir->sub_entries[j];
          dir->sub_entries[j] = tempdir;
        }
      }
    }
  }
}

void get_dir_items(dirs_s* dir) {
  std::error_code fserror;
  unsigned long num_items = 0;
  for (fs::directory_iterator entry(dir->entry.path(), fserror); begin(entry) != end(entry); entry.increment(fserror), num_items++);  // if(fserror.value() !=0) entry.disable_recursion_pending();
  if (dir->sub_entries != nullptr) {
    std::cout << "get_dir_items(dirs_s* dir): dir.sub_entries should be nullptr. if dir.sub_entries[].sub_entries isn't nullptr, a memory leak will happen";
    delete[] dir->sub_entries;
    dir->sub_entries = nullptr;
    dir->num_sub = 0;
  }
  dir->num_sub = num_items;
  dir->sub_entries = new dirs_s[dir->num_sub];
  num_items = 0;
  for (fs::directory_iterator entry(dir->entry.path(), fserror); num_items < dir->num_sub && begin(entry) != end(entry); entry.increment(fserror)) {  // if(fserror.value() !=0) entry.disable_recursion_pending();
    dir->sub_entries[num_items++].entry = *entry;
  }

  //  (*num_entries) = num_items;
  // return num_items;
}

// dir->entry.assign(workspace_path);
// dir->entry.refresh();
// void get_dir_items_recursive(dirs_s* dir, char* workspace_path) {
void get_dir_items_recursive(dirs_s* dir) {
  get_dir_items(dir);
  for (unsigned long i = 0; i < dir->num_sub; i++) {
    if (dir->sub_entries[i].entry.is_directory()) {  //} && !dir->sub_entries[i].entry.is_symlink()) {
      get_dir_items_recursive(&dir->sub_entries[i]);
    }
  }
}

void sort_dir_items_recursive(dirs_s* dir) {
  sort_dir_items(dir);
  for (unsigned long i = 0; i < dir->num_sub; i++) {
    if (dir->sub_entries[i].entry.is_directory()) {
      sort_dir_items_recursive(&dir->sub_entries[i]);
    }
  }
}

void refresh_dir_items(dirs_s* dir) {
  dir->entry.refresh();
  if (!dir->entry.exists()) {
    dir->del();
    return;
  }
  dirs_s tempdir;
  tempdir.entry.assign(dir->entry.path());
  tempdir.entry.refresh();
  get_dir_items(&tempdir);

  for (unsigned long i = 0; i < dir->num_sub; i++) {
    dir->sub_entries[i].entry.refresh();
    if (!dir->sub_entries[i].entry.exists()) {
      dir->sub_entries[i].del();
      continue;
    }
    for (unsigned long j = 0; j < tempdir.num_sub; j++) {
      if (dir->sub_entries[i].entry == tempdir.sub_entries[j].entry) {
        tempdir.sub_entries[j] = dir->sub_entries[i];
        goto skipdel;
      }
    }
    dir->sub_entries[i].del();
  skipdel:;
  }
}

void print_dir_items(dirs_s* dir) {
  std::cout << dir->entry.path().c_str() << '\n';
  if (dir->sub_entries != nullptr) {
    for (unsigned long i = 0; i < dir->num_sub; i++) {
      std::cout << dir->sub_entries[i].entry.path().c_str() << '\n';
    }
  }
}

void print_dir_items_recursive(dirs_s* dir) {
  std::cout << dir->entry.path().c_str() << '\n';
  if (dir->sub_entries != nullptr) {
    for (unsigned long i = 0; i < dir->num_sub; i++) {
      print_dir_items_recursive(&dir->sub_entries[i]);
    }
  }
}

dirs_s::~dirs_s() {
  if (sub_entries != nullptr) {
    for (unsigned long i = 0; i < num_sub; i++) {
      sub_entries[i].~dirs_s();
    }
  }
}
*/