#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include <fmt/format.h>
#include <fmt/core.h>


#include "ProjDoc.hpp"

/**
 * I have the toml file which has the different attrubutes etc and
 * and the program runs that toml and converts it into a cmake file which is
 * called so its a wrapper for cmake and make essentially
 */

constexpr ProjDoc::FileData BASIC_CONFIG_FILE[]{"[Meta-data]\n"
                                              "name = \"test\"\n"
                                              "project-version = \"0.0.1\"\n"
                                              "cxx-version = 17\n"
                                              "cxx-standard-required = true\n\n"
                                              "[files]\n"
                                              "main = \"./src/main.cpp\"\n"};

void ProjDoc::create_cmake_file(){
 this->cmake_file =  "cmake_minimum_required(VERSION 3.12 FATAL_ERROR)\n\n"
    + fmt::format("project({})\n\n", projName_) + 
    "set(CMAKE_CXX_STANDARD 17)\n"
    "set(CMAKE_CXX_EXTENSIONS OFF)\n"
    "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n"
    "set(CMAKE_EXPORT_COMPILE_COMMANDS ON)\n\n"
    "add_definitions(\"-Wall\" \"-g\")\n\n"
    "include_directories(${CMAKE_SOURCE_DIR}/include)\n"
    "file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)\n\n"
    "file(GLOB HEADER_FILES ${CMAKE_SOURCE_DIR}/include/*.hpp)\n\n"
    "add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})\n";
}

void ProjDoc::create_cxx_file(){
  this->cxx_file = 
    "#include <iostream>\n\n"
    "template<typename ...T>\n"
    "void print(T ...args){\n"
    "\tauto printArg{\n"
    "\t\t[](const auto &arg){std::cout << arg;}\n"
    "\t};\n"
    "\t(printArg(args), ...);\n"
    "}\n"
    "int main(){\n"
    "\tprint(\"Hello, World!\");\n"
    "\treturn 0;\n}"
  ;
}

ProjDoc::ProjDoc(){}

ProjDoc &ProjDoc::init(std::string_view proj_name) {
  projName_ = proj_name;
  create_directory(projName_);
  create_directory(fmt::format("{}/include", projName_)); // convert the other format strings to fmt
  create_cmake_file();
  create_cxx_file();

  // std::string proj_dir{fmt::format(projName_, "/")};
  std::string build_dir{fmt::format("{}/build/", projName_)};
  std::string src_dir{fmt::format("{}/src/", projName_)};
  rootFileDir_ = fmt::format("{}/{}",projName_, rootFile_); 
  fmt::print("\n{}\n", rootFile_);

  if(!create_directory(src_dir))   {fmt::print(stderr, "CANNOT MAKE src_dir\n"); exit(-1);};
  if(!create_directory(build_dir)) {fmt::print(stderr, "CANNOT MAKE build-dir\n"); exit(-1);};
  if(!create_file(fmt::format("{}/CMakeLists.txt", proj_name), cmake_file)) {fmt::print(stderr,"CANNOT MAKE CMAKE FILE\n"); exit(-1);};
  if(!create_file(fmt::format("{}/main.cpp", src_dir),cxx_file))            {fmt::print(stderr, "CANNOT MAKE MAIN FILE\n"); exit(-1);};

  return *this;
}

// ProjDoc &ProjDoc::init(std::string_view proj_name) {
//   this->projName_ = proj_name;
//   this->init();
//   return *this;
// }

// look through directories for a CXX.toml file
// std::string ProjDoc::get_root() {
// std::vector<std::string> dir_paths;
// std::string tmp{""};
// int count{0};
// for (auto elem : (std::string)std::filesystem::current_path()) {
// if (elem == '/' || elem == '\\') {
// dir_paths.emplace_back(tmp);
// tmp.clear();
// } else {
// tmp += elem;
// }
// }

// for (size_t i{dir_paths.size()}; i != -1; i--) {
//   std::cout << dir_paths[i] << '\n';
//   if (dir_paths[i] != this->projName_) {
//     dir_paths.pop_back();
//     count++;
//   } else
//     break;
// }

// // std::for_each(dir_paths.rbegin(), dir_paths.rend(),
// // [](auto val) { std::cout << val << '\n'; });
// return this->rootFile_;
// }

bool ProjDoc::create_file(std::string_view filename,
                              ProjDoc::FileData data) {

  if (std::filesystem::exists(filename)) {
    std::ofstream newfile{filename.data()};
    newfile << data.data();
    newfile.close();
    return true;
  }
  // file does not exist so do write stuff here
  std::ofstream new_file{filename.data()};

  // return false if new_file cannot be made
  if(!new_file) return false;
  
  new_file << data.data();
  new_file.close();
  return true;
}

bool ProjDoc::create_directory(std::string_view directory_name) {
  if (is_directory(directory_name)){
    std::cout << directory_name << "already exists\n";
    return false;
  }
  std::filesystem::create_directory(directory_name);
  return true;
}

bool ProjDoc::is_directory(std::string_view directory) const {
  return std::filesystem::is_directory(directory) ? true : false;
}

bool ProjDoc::is_file(std::string_view file) const{
  return std::filesystem::is_regular_file(file) ? true : false;
}

// std::string ProjDoc::append_string(std::string_view str1,
//                                    std::string_view str2) {
//   return {std::string(str1).append(str2)};
// }

// std::string ProjDoc::s_append_string(std::string_view str1,
//                                      std::string_view str2) {
//   return {std::string(str1).append(str2)};
// }

std::string ProjDoc::get_directory_name() const { return this->projName_; }

void ProjDoc::set_proj_name(std::string_view proj_name){ this->projName_ = proj_name;}
