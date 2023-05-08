#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#include <shellapi.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#endif

#include "php.h"
#include "script_php_content.h"

int main(int argc, char* argv[]) {
    std::string output_dir = "php";
    std::string executable_name = "php.exe";

#ifdef _WIN32
    std::string exe_path = ".\\" + output_dir + "\\" + executable_name;
#else
    std::string exe_path = output_dir + "/" + executable_name;
#endif

    std::ofstream output_file(exe_path, std::ios::binary);
    if (!output_file.is_open()) {
        std::cerr << "Error opening output file: " << exe_path << std::endl;
        return 1;
    }

    output_file.write(reinterpret_cast<const char*>(embedded_executable), embedded_executable_size);
    output_file.close();

    std::stringstream file_content(script_php_content);

    std::string content_arg = "-r \"" + file_content.str() + "\"";

    for (int i = 1; i < argc; ++i) {
        content_arg += " ";
        content_arg += argv[i];
    }

#ifdef _WIN32
    SHELLEXECUTEINFO shell_exec_info = {0};
    shell_exec_info.cbSize = sizeof(SHELLEXECUTEINFO);
    shell_exec_info.fMask = SEE_MASK_NOCLOSEPROCESS;
    shell_exec_info.hwnd = NULL;
    shell_exec_info.lpVerb = "open";
    shell_exec_info.lpFile = exe_path.c_str();
    shell_exec_info.lpParameters = content_arg.c_str();
    shell_exec_info.lpDirectory = NULL;
    shell_exec_info.nShow = SW_SHOW;
    shell_exec_info.hInstApp = NULL;

    if (!ShellExecuteEx(&shell_exec_info)) {
        std::cerr << "Error executing the embedded executable: " << GetLastError() << std::endl;
        return 1;
    }

    WaitForSingleObject(shell_exec_info.hProcess, INFINITE);

    CloseHandle(shell_exec_info.hProcess);

    std::filesystem::remove(exe_path);
#else
    pid_t pid = fork();

    if (pid == 0) {
        std::vector<std::string> args;
        args.push_back(exe_path.string());
        args.push_back(content_arg);
        args.push_back("");

        std::vector<char*> args_pointers(args.size(), nullptr);
        for (std::size_t i = 0; i < args.size(); ++i) {
            args_pointers[i] = &args[i][0];
        }

        if (execv(exe_path.c_str(), args_pointers.data()) == -1) {
            std::cerr << "Error executing the embedded executable: " << strerror(errno) << std::endl;
            return 1;
        }
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            std::filesystem::remove(exe_path);
        }
    } else {
        std::cerr << "Error forking process" << std::endl;
        return 1;
    }
#endif
    
    return 0;
}
