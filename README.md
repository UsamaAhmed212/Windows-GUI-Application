# **Windows GUI Application**

## **Overview**

This guide explains how to compile a C program into an executable (`.exe`) with a custom icon.

## **Compilation Steps**

### 1. Compile the Resource File

Run the following command:

```bash
windres resources.rc -o resources.o && gcc main.c resources.o -o main.exe -lgdi32 -mwindows
```
#### Behavior of Flags
> **`-mwindows:`** Tells GCC to create a Windows GUI application. This means that the application will not have a console window attached to it when run.

> **`-lgdi32:`** Links against the GDI32 library for graphical operations (drawing, fonts, images, etc.).

## Expected Result:

- **`main.exe`**: Executable File (.exe)

### 3. Run Executable File (.exe)

```bash
main.exe
```
OR
```bash
./main.exe
```

## **Compilation Steps 02**

### Run the following command : => (if you want Monitors changes and automatically recompiles and runs your application when changes are detected.)
```bash
watch_main.bat
```
OR
```bash
./watch_main.bat
```
