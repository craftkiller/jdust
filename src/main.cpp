/**
 * Copyright (c) 2014 Tom Alexander; Released under the ISC License
 * https://github.com/craftkiller/jdust
 */
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "dust_renderer.h"
#include "result_store.h"

std::string load_file(const char* file_name)
{
    std::ifstream t(file_name);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

int main(int argc, char **argv) 
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <script file>\n";
        return 0;
    }

    // Load file(s)
    std::string script_contents;
    for (int i = 1; i < argc; ++i)
    {
        std::string file_contents = load_file(argv[i]);
        script_contents += file_contents;
    }

    result_store state;

    int ret = execute_js(state, script_contents.c_str());
    if (ret != 0)
    {
        std::cerr << "Return code: " << ret << "\n";
    }
    std::cout << state.get_result() << "\n";
    return ret;
}
