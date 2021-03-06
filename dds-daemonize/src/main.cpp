// Copyright 2014 GSI, Inc. All rights reserved.
//
//
//
// API
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
// STD
#include <iostream>
#include <string>
// DDS
#include "version.h"
#include "Res.h"
#include "SysHelper.h"

using namespace std;
using namespace MiscCommon;

void printVersion()
{
    cout << PROJECT_NAME << " v" << PROJECT_VERSION_STRING << "\n"
         << "DDS configuration"
         << " v" << USER_DEFAULTS_CFG_VERSION << "\n" << g_cszReportBugsAddr << endl;
}

int main(int argc, char* argv[])
{

    // process ID and Session ID
    pid_t pid;
    pid_t sid;

    // Fork off the parent process
    pid = ::fork();
    if (pid < 0)
        return EXIT_FAILURE;

    // If we got a good PID, then we can exit the parent process.
    if (pid > 0)
        return EXIT_SUCCESS;

    // Change the file mode mask
    ::umask(0);

    // Create a new SID for the child process
    sid = ::setsid();
    if (sid < 0) // TODO:  Log the failure
        return EXIT_FAILURE;

    // Change the current working directory
    // chdir("/") to ensure that our process doesn't keep any directory
    // in use. Failure to do this could make it so that an administrator
    // couldn't unmount a file system, because it was our current directory.
    if (::chdir("/") < 0) // TODO: Log the failure
        return EXIT_FAILURE;

    string sStdOut(argv[1]);
    smart_append(&sStdOut, '/');
    sStdOut += argv[2];
    sStdOut += ".out.log";

    // child
    int fd_out = open(sStdOut.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd_out < 0)
        cerr << "Can't open file for user's process stdout: " << sStdOut;

    dup2(fd_out, 1); // make stdout go to file
    dup2(fd_out, 2); // make stderr go to file
    close(fd_out);   // fd no longer needed - the dup'ed handles are sufficient

    char** cmd_arg = &argv[2];
    if (argc > 3)
        execvp(argv[2], cmd_arg);

    return 0;
}