@echo off
pushd %~dp0\..\
call Vendor\Premake\premake5.exe vs2022
popd
PAUSE