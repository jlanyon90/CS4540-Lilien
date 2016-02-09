INCLUDED:
- a4_lanyon.c
- Makefile -produces the a4_lanyon.ko when run
- CS_4540_a4_SLC.docx - the SLC report for this assignment

hw4_part1 folder contains:
	-part1.c
	-Makefile - produces part1.ko when run
	-a4_lanyon_I1 a script file showing the output of dmesg when part1.ko is inserted and removed

TO RUN:
- make (creates kernel object)
- sudo insmod a4_lanyon.ko (inserts kernel object)
- dmesg (shows message from init)
- sudo rmmod a4_lanyon (removes kernel object)
- sudo dmesg -c	(shows message from exit)

