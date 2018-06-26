#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>
namespace fs = std::filesystem;
 
void demo_exists(const fs::path& p, fs::file_status s = fs::file_status{})
{
    std::cout << p;
    if(fs::status_known(s) ? fs::exists(s) : fs::exists(p))
        std::cout << " exists\n";
    else
        std::cout << " does not exist\n";
}

int main()
{
    fs::create_directory("sandbox");
    std::ofstream("sandbox/file"); // create regular file
    fs::create_symlink("non-existing", "sandbox/symlink");
 
    demo_exists("sandbox");
    for(auto it = fs::directory_iterator("sandbox"); it != fs::directory_iterator(); ++it)
        demo_exists(*it, it->status()); // use cached status from directory entry
    fs::remove_all("sandbox");
}

/*
"sandbox" exists
"sandbox/file" exists
"sandbox/symlink" does not exist
*/
