#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

// if first command in pipeline has input redirection
if (hasInputFile && is1stCommand) { 
  int fdin = open(inputFile, O_RDONLY, 0644);
  dup2(fdin, STDIN_FILENO);
  close(fdin);
}

// if last command in pipeline has output redirection
if (hasOutputFile && isLastCommand) { 
  int fdout = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  dup2(fdout, STDOUT_FILENO);
  close(fdout);
}



}
