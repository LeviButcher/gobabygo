#pragma once


class DistanceBuzzerControl {

  private:
      int buzzerPin;
      int intermittentDistance;
      int constantDistance;
      enum DB_STATES {START, INTERMITTENT, CONSTANT, OFF};
      DB_STATES DB_STATE;

  public:
    DistanceBuzzerControl(int buzzerPin, int intermittentDistance, int constantDistance);
    void update(int distance);
};
