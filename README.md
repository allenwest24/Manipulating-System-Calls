# Manipulating-System-Calls
A demo on how you can manipulate PATH to run malicious versions of syscalls.

## Overview
Manipulation of system calls so that they would reference our versions of basic commands.
We did this with cat, less, and signal.
Further explanation below.

## Storyline

After your last assignment, your new boss is not impressed yet. However, she thinks 
that you might have what it takes to be a good security engineer. Your next 
assignment takes you to Bostom University. Apparently, they have been hacked, once
again and have contacted your company for help. You logon to the Linux server and see
a number of applications that look like they may have vulnerabilities. These programs 
are written in C, so you first use grep to search for known insecure library 
functions such as gets(), strcpy(), or system(). After a brief search, you find three
simple programs that use the system() function. You immediately bring them to the 
attention of your boss. Unfortunately, after a brief check, she cannot find anything 
wrong with these programs. She claims that the calls to system() and dlopen() were
performed in a safe manner, and she orders you to continue working and stop bothering 
you without having something real. However, you know that these programs all have 
flaws. Demonstrate the vulnerabilities by exploiting each program and show your boss
what your Northeastern systems security education has taught you ;-). But wait ...
there is something strange going on ... why can't you create all the files that you
want? Darn quotas ....

## Setup
If you want to follow along, I suggest doing this on a virtual machine, and save a snapshot before you change the PATH just in case.
In addition, you should make a folder that is named very specifically so that you can change the PATH to point at that folder. I will 
explain this later.

### Prog1 (cat.c): 
In prog1 we see that the sole call is just a 
- system("cat ...");

Because of this we know we can maniuplate a system call by modifying the PATH. 
To find the environment settings,  type:
- printenv

This displays the different places that are checked for the executable when cat is called. 
We can change this by calling:
- export PATH=~/newFunctions:PATH$

***Now we want to add a malicious version of cat.c to the directory newFunctions so when we add it to the PATH it will find ours first and 
execute the malicious version!***

This essentially adds our folder of altered functions to the path to be checked and then we add the original $PATH so we don't have to write 
every single function.
Now we can have our new version call:
- system("/bin/grade"); *guid enabled*

### Prog3 (less.c):
Similar process as before with prog1, except now we have to read the function more carefully. You can see that it only uses a system call in 
the case that it can't open all 4 files. The way of fixing this is typing:
- ulimit -n 5

This will limit the processes to only 5 and not leave enough for the files to all open, now we can trigger the vulnerable system call 
like last time.

### Prog2 (signal.c):
Hardest of all (and kind of a shit show).
By reading the source code we see that a system call only occurs when it is given a signal alarm.
To do this, we have to kill the process while it's running.
Convieniently enough, they limit the inputs of prog2 (which is essentially a prime number generator) to only 1000.
This means we can't delay it very long. 
Control + c isn't the right kill signal. 
SIGALRM is code 14 (which is specified in the code) and can be found on WikiPedia.
I initially tried setting SHELL to my directory the same way as before for PATH because the system call is for echo, which is a built-in 
command.
This didn't work even though I think it shouldve. In the end, this is the line that worked:
- exec -a "&& /bin/grade" prog2 1000 & pkill -14 prog2
