#include "catch.hpp"
#include "../Smoother/Smoother.h"

int HISTORY_LENGTH = 10;

TEST_CASE("Smoother should be created with a history capicity of historyLength", "[Smoother]") {
  Smoother smooth(HISTORY_LENGTH);
  REQUIRE(smooth.getHistoryCapacity() == HISTORY_LENGTH);
}

TEST_CASE("Smoother should add value into history","[Smoother]") {
  Smoother smooth(HISTORY_LENGTH);
  smooth.addToHistory(42);
  REQUIRE(smooth.getHistorySize() == 1);
}

TEST_CASE("Smoother should restrict size to initial history size", "[Smoother]") {
  Smoother smooth(HISTORY_LENGTH);
  for(int i = 0; i < HISTORY_LENGTH + 2; i++) {
    smooth.addToHistory(42);
  }
  REQUIRE(smooth.getHistorySize() == HISTORY_LENGTH);
}

TEST_CASE("Smoother should return smallest value in Smoother", "[Smoother]") {
  Smoother smooth(HISTORY_LENGTH);
  for(int i = 0; i < HISTORY_LENGTH + 2; i++) {
    smooth.addToHistory(42);
  }
  smooth.addToHistory(2);
  REQUIRE(smooth.smallestValueInHistory() == 2);
}

TEST_CASE("Smoother should return average of added values", "[Smoother]") {
  Smoother smooth(HISTORY_LENGTH);
  for(int i = 0; i < HISTORY_LENGTH; i++) {
    smooth.addToHistory(i);
  }
  REQUIRE(smooth.averageHistory() == 4);
}
