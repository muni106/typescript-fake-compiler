# typescript-fake-compiler
A simple tool to compile directly one typescript file for unix based systems.

I apologize in advance if something does not work, in case let me know that I try to fix it as soon as possible.

## Prerequisites
You need to be in a UNIX based system and having installed:
- nodejs
- any c compiler, preferably gcc
- typescript

## Installation
I tried to make it super-easy to install:
```bash
cd "folder of the repository"
make
./tscf.exe
```

## Usage
After the installation you'll need just to use the command tsfc (TypeScriptFakeCompiler) followed by the file you want to run like the following example:
```bash
tsfc "your_file.ts"
```