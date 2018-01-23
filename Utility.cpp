#include "Precompiled.h"

std::string GetCurrentExeDirectory()
{
    std::string directory;
    directory.resize(260);

    HMODULE hModule = GetModuleHandle(NULL);
    //WCHAR path[MAX_PATH];

    GetModuleFileName(hModule, &directory.at(0), MAX_PATH);


    const std::string pattern = "\\";
    return directory.substr(0, directory.find_last_of(pattern));

}

void GetFilesInDirectory(std::vector<std::string> &fileNames, std::string dirPath)
{
    HANDLE dir;
    WIN32_FIND_DATA file_data;

    if ((dir = FindFirstFile((dirPath + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE) {
        return; /* No files found */
    }
    do {
        const std::string file_name = file_data.cFileName;
        const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

        if (file_name[0] == '.')
            continue;

        if (is_directory)
            continue;

        fileNames.push_back(file_name);
    } while (FindNextFile(dir, &file_data));

    FindClose(dir);
}
