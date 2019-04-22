#pragma once

class Smoother {
private:
  int* history;
  int historyLength;
  int index = 0;

public:
  Smoother(int historyLength);
  void addToHistory(int value);
  int getHistoryCapacity();
  int getHistorySize();
  int averageHistory();
  int smallestValueInHistory();
};
