/* shell.c - Project D - Lensi Gondaliya, Nina Aubourg, Ying Lu */
main()
{
    char line[80];
    char buffer[13312];
    int sectorsRead;
    char dirBuf[512];
    char fileName[7];
    int i, j;

    while (1) {
        syscall(0, "SHELL> ");
        syscall(1, line);

        /* Step 5: type filename - print a file */
        if (line[0] == 't' && line[1] == 'y' && line[2] == 'p' && line[3] == 'e' && line[4] == ' ') {
            syscall(3, line + 5, buffer, &sectorsRead);
            if (sectorsRead > 0) {
                syscall(0, buffer);
                syscall(0, "\r\n");
            } else {
                syscall(0, "File not found!\r\n");
            }
        }
        /* Step 6: exec filename - load and run a program */
        else if (line[0] == 'e' && line[1] == 'x' && line[2] == 'e' && line[3] == 'c' && line[4] == ' ') {
            syscall(3, line + 5, buffer, &sectorsRead);
            if (sectorsRead > 0) {
                syscall(4, line + 5);
            } else {
                syscall(0, "Program not found!\r\n");
            }
        }
        /* Project D Step 2: dir - list files in the directory */
        else if (line[0] == 'd' && line[1] == 'i' && line[2] == 'r') {
            syscall(2, dirBuf, 2);
            for (i = 0; i < 512; i = i + 32) {
                if (dirBuf[i] != '\0') {
                    for (j = 0; j < 6; j++) {
                        fileName[j] = dirBuf[i + j];
                    }
                    fileName[6] = '\0';
                    syscall(0, fileName);
                    syscall(0, "\r\n");
                }
            }
        }
               /* Project D Step 3: del filename - delete a file */
        else if (line[0] == 'd' && line[1] == 'e' && line[2] == 'l' && line[3] == ' ') {
            syscall(7, line + 4);
        }
 else {
            syscall(0, "Bad Command!\r\n");
        }

    }
}
