# hello_world
## hello_world_log_file
- a simple cpp code that outputs time and the text "hello_world" to a file specified in the command line arg. useful for testing script or code that runs another binary
- usage
  - `exe_file <path_to_log_file>`

## hello_world_msgbox
- a simple cpp code that outputs a MessageBox
- usage
  - `exe_file`

# compile
## Windows 
- download MSYS2 and gcc
- set the env variable to the gcc downloaded by MSYS2
- `g++ hello_world.cpp -o hello_world.exe -static`
- for `hello_world_minimal.cpp`, use `gcc -o hello_world_minimal.exe hello_world_minimal.cpp -Wl,-e,MyCustomStart -nostdlib -lkernel32 -Wl,--dynamicbase -Wl,--subsystem,windows`
  - `-e,MyCustomStart` - set the entry point to this function

## Linux
- install gcc
- `g++ file.cpp -o file -static`

# usage
- `hello_world <path_to_log_file>`



