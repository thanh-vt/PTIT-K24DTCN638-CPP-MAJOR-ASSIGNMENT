@echo off

:: Check if the user provided a program name
if "%1"=="" (
    echo Please provide the program name as a parameter.
    exit /b
)

:: Extract the program name without extension
for %%F in (%1) do set "program_name=%%~nF"

:: Generate input and output file names based on the program name
set "input_file=%program_name%_in.txt"
set "output_file=%program_name%_out.txt"

pushd cmake-build-debug
:: Check if the input file exists
if not exist "%input_file%" (
    echo Input file "%input_file%" does not exist.
    exit /b
)
:: Run the program with input redirection and capture stdout, ignore stderr
"%1" < "%input_file%" > "%output_file%" 2>nul

:: Inform the user that the process has completed
echo Program has finished. Output is in "%output_file%".
