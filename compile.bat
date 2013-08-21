@echo off
rmdir temp /S /Q
del TempProjectFile.sln
bin\premake4.exe --os=windows --platform=x32 vs2010
"C:\Windows\Microsoft.NET\Framework\v4.0.30319\msbuild.exe" TempProjectFile.sln
rmdir temp /S /Q
del TempProjectFile.sln
pause