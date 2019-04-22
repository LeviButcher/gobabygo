#include "Smoother.h"


Smoother::Smoother(int historyLength) {
  this -> historyLength = historyLength;
  history = new int[historyLength];
  for(int i = 0; i< historyLength; i++) {
    history[i] = -1;
  }
}

int Smoother::getHistoryCapacity() {
  return historyLength;
}

int Smoother::getHistorySize() {
  int count = 0;
  for(int i = 0; i< historyLength; i++) {
    if(history[i] != -1) {
      count++;
    }
  }
  return count;
}

void Smoother::addToHistory(int value) {
  history[index] = value;
  index = (index + 1) % historyLength;
}

int Smoother::smallestValueInHistory() {
  int smallest = history[0];
  for(int i = 1; i < historyLength; i++) {
    if(history[i] < smallest) {
      smallest = history[i];
    }
  }
  return smallest;
}

int Smoother::averageHistory() {
  int total = 0;
  int count = 0;
  for(int i = 0; i < historyLength; i++) {
   if(history[i] != -1) {
      total = total + history[i];
      count++;
    }
   }
   return total / count;
}
