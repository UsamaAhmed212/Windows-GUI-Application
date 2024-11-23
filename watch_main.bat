:loop
fswatch -1 main.c
windres resources.rc -o resources.o && gcc main.c resources.o -o main.exe -lgdi32 && main.exe
goto loop
