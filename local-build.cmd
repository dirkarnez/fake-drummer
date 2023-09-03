REM run as Administrator
@echo off

cd /d %~dp0
set DOWNLOADS_DIR=%USERPROFILE%\Downloads
set DOWNLOAD_DIRS_LINUX=%DOWNLOADS_DIR:\=/%

SET PATH=^
%DOWNLOADS_DIR%\PortableGit\bin;^
%DOWNLOADS_DIR%\winlibs-x86_64-posix-seh-gcc-11.2.0-mingw-w64-9.0.0-r1\mingw64;^
%DOWNLOADS_DIR%\winlibs-x86_64-posix-seh-gcc-11.2.0-mingw-w64-9.0.0-r1\mingw64\bin;^
%DOWNLOADS_DIR%\cmake-3.26.1-windows-x86_64\bin;^

@REM set PATH=^
@REM D:\Softwares\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64;^
@REM D:\Softwares\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\mingw64\bin;^
@REM D:\Softwares\cmake-3.23.0-rc1-windows-x86_64\bin;

cmake.exe -G"MinGW Makefiles" ^
-DMIDIFILE_ROOT="%DOWNLOAD_DIRS_LINUX%/midifile-c78a85f51f92b7f57904c2d14f1813f5a6f7e7318-winlibs-x86_64-posix-seh-gcc-11.2.0-mingw-w64-9.0.0-r1" ^
-DCMAKE_BUILD_TYPE=Debug ^
-B./cmake-build &&^
cd cmake-build &&^
cmake --build . &&^
echo "Successful build"
pause