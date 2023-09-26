#include <string>
#include <string_view>
#include <toml++/toml.h>

#ifndef PROJCREATOR_TOMLPLUSPLUS
#define PROJCREATOR_TOMLPLUSPLUS

class ProjDoc {
public:
  using FileData = std::string_view;

public:
  ProjDoc();
  ProjDoc &init(std::string_view proj_name);


  bool is_directory(std::string_view directory) const;
  bool is_file(std::string_view file) const;
  // std::string append_string(std::string_view str1, std::string_view str2);
  // static std::string s_append_string(std::string_view str1,
   //                                  std::string_view str2);


  void set_proj_name(std::string_view proj_name);
  // std::string get_root();
  std::string get_directory_name() const;

private:
  bool create_file(std::string_view filename, FileData data);
  bool create_directory(std::string_view directory_name);

  void create_cmake_file();
  void create_cxx_file();
  // make functions to append to a string and take out file extensions

  std::string projName_;
  std::string rootFile_{"CMakeLists.txt"};
  std::string rootFileDir_;
  std::string cmake_file;
  std::string cxx_file;
};

#endif
