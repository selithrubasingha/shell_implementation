## 🐚 Shell in C

### Overview

A simple unix shell written in C . It supports a REPL (Read-Eval-Print Loop) lifecycle, parses user input, and executes commands . contains the few built-in commands including `cd` , `exit` and `help` . There is still room for improvement by adding some more built-ins and more features . 

---
### 🧠 What I Learned 

- __Inner Workings:__ The main aim of doing this project is to understand how a shell works under the hood .


- __process Management:__  Got an understanding about how starting processes worked in Unix-like operating systems. Things like the `Init` process (Main process) , and how `fork()` , `exec()` and `wait()` function collectively work to start processes

- __Memory Management:__ Got better at using `malloc` , `realloc` , and pointers in C

- __Built-ins vs. External Commands:__ Learned why certain commands (like cd) must be shell built-ins due to process isolation (a child process cannot modify the parent's current working directory).

---
### 🛠️ Run this file 

Sadly , functions like `fork()` won't work if you are using Native Windows . I recommend using WSL (windows subsystem for linux) . 

There is no problem for Linux and macOS though .

Once that's done you could clone the repo . and compile it and run the file . 

### 1. compile
```Bash
gcc -o shell shell.c
```

### 2. run
```Bash
./shell
```

