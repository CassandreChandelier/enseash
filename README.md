# enseash


## Question 1


The message of welcome appears without any problem

## Question 2

We have an input for the user, it is executed. After the execution, we print
the prompt enseash % and wait for new command. 
We created a fonction prompt to print each time "enseash %"

```bash
# define PROMPT "enseash % "
write(1,PROMPT,sizeof(PROMPT));
```

## Question 3

We had to quit the shell output with the command "exit" when the user wrote this,
or with <ctrl>+d
We did some modifications in the code. We had first a while(1) loop in the main
code, and delete the one in the executionCommand code. Then we could retrieve the
input data and if it was "exit", quit the code.
Moreover, we had an instruction to quit the shell in the case where the user
pressed the key "<ctrl>+d"


## Question 4

We use the functions WIFEXITED which returns a boolean (true if the son finished or 
false if it didn't). Then, we use WEXITSTATUS which returns the exit code only if 
WIFEXITED returns true. For returning the signal, we do the same with two others 
functions. WIFSIGNALED returns true if the son end because of a signal and WTERMSIG 
returns the number of the signal that caused the end of the son.


## Question 5

We want to add the time in the function return. So by using the function clock_gettime, we 
can use the variable CLOCK_REALTIME which is the time at the moment.
To use this function, we had to define a structure:

```bash
struct timespec start, end;
```

We use at the beginning of the function executionCommand by calling the structure (&start),
and at the end of the execution (in the parent process) by calling the structure a last 
time (&end). Then, we calculate the time elapsed.

Moreover, we can see that we have the same code two times, so we create another function: 

```bash
wifReturn(int status, const char *type, int value, struct timespec *start, struct 
timespec *end);
```

Then it can return WIFEXITED or WIFSIGNAL.
