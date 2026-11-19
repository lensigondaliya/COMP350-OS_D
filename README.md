# COMP 350 - Project D: Writing and Deleting Files

Team: Lensi Gondaliya, Nina Aubourg, Ying Lu

## How to build and run
1. On the class server run `./compileOS.sh`. It builds the bootloader, kernel, and shell and puts kernel, message.txt, tstpr1, tstpr2 and shell onto diskc.img.
2. Open simulator.jar, tick Hard Drive C, choose diskc.img, set Cylinders 28, Heads 2, Sectors 18, and click Boot Disk C.

## Step 1 - writeSector (interrupt 0x21, AX=6)
**What we did:** writeSector(buffer, sector) is a copy of readSector that calls BIOS interrupt 0x13 with AH=3 (write) instead of AH=2 (read).
**How to verify:** It is used by deleteFile and writeFile below. If those work, writeSector works.

## Step 2 - dir command
**What we did:** The shell reads the directory (sector 2) and prints the 6-character name of every 32-byte entry whose first byte is not '\0'.
**How to verify:** Type `dir`. You see kernel, messag, tstpr1, tstpr2, shell.

## Step 3 - deleteFile (interrupt 0x21, AX=7) and del command
**What we did:** deleteFile(name) loads the Map (sector 1) and Directory (sector 2), finds the file, sets the first byte of its name to '\0', sets each of its sectors to 0 in the Map, and writes both back.
**How to verify:** Type `type messag` (it prints), then `del messag`, then `dir` (messag is gone) and `type messag` (File not found!). In hexedit, the Map bytes for messag become 00 and its directory entry starts with 00.

## Step 4 - writeFile (interrupt 0x21, AX=8)
**What we did:** writeFile(buffer, name, numberOfSectors) loads the Map and Directory, finds a free directory entry, copies the name (padding with '\0'), then for each sector finds a free Map entry starting at 3, marks it 0xFF, records it in the directory entry, and writes 512 bytes there. The rest of the entry is filled with 0 and the Map and Directory are written back. It returns if there is no free entry or sector.
**How to verify:** We tested it with `interrupt(0x21, 8, "this is a test message", "testmg", 3);` in main() (now commented out). `dir` showed testmg and `type testmg` printed "this is a test message".

## Step 5 - copy command
**What we did:** `copy file1 file2` reads file1 with the readFile system call (AX=3) and writes it as file2 with the writeFile system call (AX=8).
**How to verify:** Type `copy messag mess2`, then `type mess2` (same text as messag). Also `copy shell shell2` and `exec shell2` gives a working SHELL> prompt.

## Step 6 - create command
**What we did:** `create filename` prompts with "> " for lines of text until an empty line is entered, adds each line to a buffer, and writes the buffer to a file with writeFile.
**How to verify:** Type `create textfl`, enter a few lines, press Enter on an empty line, then `type textfl`. The lines print back and `dir` lists textfl.
