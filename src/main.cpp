#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <filesystem>
#include <fstream>

#include <fmt/core.h>

#include "ProjDoc.hpp"



void show_commands() {
  std::string help_cmd{
    "Usage: make-proj <cmd> (optional-value)\n"
    "cmd:\n"
    "\t - help -> used to print this help menu\n\n"
    "\t - new (project-name), example: make-proj new temp\n"
    "\t   -> creates a new project with build and source folders and default cmake and main file\n\n"
    "\t - run -> runs the executable if it exists otherwise builds and runs it\n\n"
    "\t - build -> builds the project to an executable\n"
  };
  fmt::print(help_cmd);
}

void run(ProjDoc& doc){
  if(doc.is_directory("build")){
    fmt::print("In top level directory wiht build and src folders\n");
    std::fstream cmake_file{"CMakeLists.txt", std::ios::in};
    std::string lines;
    while(std::getline(cmake_file, lines)){
      if(lines.substr(0, 7) == "project"){
        lines.erase(0, 7); // gets rid of project leaving only the brackets
        lines.erase(0,1); // gets rid of first bracket
        lines.pop_back(); // gets rid of final bracket
        doc.set_proj_name(lines);
//        fmt::print(lines);
      }// TODO: sort case where we not in top_level dir
    }
    std::string val{fmt::format("cd build/; {}",fmt::format("./{}", doc.get_directory_name().c_str() ))};
  //  fmt::print(val);
    std::system(val.c_str());
  }
}

void build_program(const ProjDoc& doc){
  if(doc.is_file("CMakeLists.txt")){
    std::system("cmake -B build/");
    std::system("cmake --build build/");
  }
}

int main(int argc, char *argv[]) {

  std::vector<std::string> cmd_args(argv, argv+argc);
  cmd_args.erase(cmd_args.begin());

  // for(const auto& elem: cmd_args){
    // fmt::print(elem << '\n');
  // }

  ProjDoc project{};

  switch(cmd_args.size()){
    case 0:
      {
        show_commands();
        break;
      }
    case 1:
      {
        if(cmd_args[0] == "build"){
          build_program(project);
          break;
        }
        else if (cmd_args[0] == "run"){
          run(project);
          break;
        }
        else if (cmd_args[0] == "help")
          show_commands();
        break;
      }
    case 2:
      {
        if(cmd_args[0] == "new"){
          project.init(cmd_args[1]);
        }
        break;
      }
  }

  return 0;
}
