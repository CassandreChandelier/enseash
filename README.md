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
