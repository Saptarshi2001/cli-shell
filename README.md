# cli-shell
This is a command line shell program written in C. It provides a basic shell interface where users can execute various commands and perform operations such as changing directories, creating directories, searching files, and more.

## Features

- Change directory: Use the `cd` command to navigate through directories.
- Create directory: Use the `mkdir` command to create new directories.
- Help: Use the `help` command to display a list of available commands.
- Exit: Use the `exit` command to exit the shell.
- Echo: Use the `echo` command to print text to the console.
- Clear: Use the `cls` command to clear the console screen.
- Color: Use the `color` command to change the console text and background color.
- Grep: Use the `grp` command to search for a pattern in a file.

## Getting Started

To compile and run the program, follow these steps:

1. Clone the repository: `git clone https://github.com/your-username/your-repo.git`
2. Navigate to the project directory: `cd your-repo`
3. If you want to compile the main file ,run the following the command : `gcc  shell.c`
4. Run the .exe file -`a.exe`
5. If you want to compile both the main file and the test file,remove the /* and */ and run the following command: 
   `gcc -c shell.c test.c`
6. After compiling the files, link them together:`gcc shell.o test.o -o output`   
7. Run the program: `output.exe`

## Usage

Once the program is running, you can enter commands in the shell prompt. Here are some examples:

- Change directory: `cd directory_name`
- Create directory: `mkdir directory_name`
- Help: `help`
- Exit: `exit`
- Echo: `echo text`
- Clear: `cls`
- Color: `color`
- Grep: `grp pattern file_name`
  
## System requirements
- Windows 7 or higher
- Linux- Will be released soon
- Gcc compiler
- MinGW

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
