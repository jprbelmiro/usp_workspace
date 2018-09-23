#ifndef _INTERFACE_H_
#define _INTERFACE_H_

typedef enum{
  INVALID = -1,
  EXIT,
  INSERT,
  REMOVE,
  INDEX_STAT,
  DATA_STAT
}operations;

void printOperations();
void printInvalidOp();
void printSelectOp();
void printBye();
void printWelcome();

int readOperation();

#endif
