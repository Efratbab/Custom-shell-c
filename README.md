# 🖥️ Custom Shell in C (`myshell`)

A simple command-line interpreter written in C that demonstrates **system programming, process control, and custom shell design**.  
This project implements a miniature shell (`myshell.c`) that executes basic Linux commands using `fork()` and `exec()`, along with custom implementations of built-in commands (`history`, `cd`, `pwd`, `exit`).  

---

## 📂 Project Contents

- **`myshell.c`** – main source code of the custom shell.   
---

## ⚡ Quick Start

1. **Clone the repository**
   ```bash
   git clone https://github.com/<your-username>/custom-shell-c.git
   cd custom-shell-c
2. **Compile the program**
   ```bash
   gcc myshell.c -o myshell
3. **Run the shell**
      The shell accepts optional directories where executables can be found. For example:
   ```bash
   ./myshell /bin /usr/bin /home/user/custom_bin
4. **Use the shell**
   Once running, you’ll see a prompt:$

## Features
**Built-in Commands (implemented without exec)**
history – prints all commands entered in the session (FIFO order, includes history itself).
cd <dir> – changes the current directory using chdir().
pwd – prints the current working directory using getcwd().
exit – exits the shell.

## Concepts Demonstrated
Process management with fork(), exec(), and wait().
Custom command parsing with strtok().
Built-in commands implemented directly with system calls.
Error handling using perror().
Environment isolation – modifications inside the shell do not affect the host environment once it exits.

