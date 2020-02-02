# shellfile - WIP

Shellfile is a different take on displaying folder contents in the terminal.  
It is very early in development but the goals are:  
Same level of detail as standard 'ls'  
Easily read formatting  
Color coding  
Keyboard file navigation  
# It is not 'ls'
Shellfile will be a program that not only outputs to the terminal,  
but also runs with user input. (arrow keys, command interpreter, et.c.)  
In contrast to running ls, Shellfile might not leave usable info on screen,  
as it is meant to be a file explorer more than a directory lister,  
and during navigation it will redraw neccessary parts of the terminal.  

# Disclaimer:
This is a WIP - goals might change  
Currently it only aims to be *mostly* unix-like compliant, will not work under Windows yet  
PROJECT NAME AND PROGRAM NAME ARE LIKELY TO CHANGE - this is only the internal working title.  
When the program is usable, a suitable and available name will be picked.  
Credit to inspriations/modified code snippets are in the respectable files - due to change.  

# Update 1:
First working version, where the program can be used to explore the filesystem.
No files can be selected, so no actual usability.
Folder max depth is 10 right now.
Looks weird on small terminal sizes.

Tested on Terminal.app in macOS 10.14

# Controls: (WIP)
Navigation: h(left, go "up" a directory), j(down, select next item in folder), k(up, select previous item in folder), l(right, enter a directory/folder).
