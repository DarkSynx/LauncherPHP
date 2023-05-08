@echo off
rem exeTobin\exeTobin.exe exeTobin\php.exe php.h php.cpp
(
echo const char *script_php_content = R"(
setlocal EnableDelayedExpansion
for /f "usebackq delims=" %%a in ("script.php") do (
    set "line=%%a"
    echo(!line:"=\"!
)
echo ^)";
) > script_php_content.h