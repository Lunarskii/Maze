#include "test_core.h"

TEST(Cave, CorrectFile) {
  Cave cave = Cave::GetInstance();

  EXPECT_NO_THROW(cave.UploadCaveFromFile("caves/cave1.txt"));

  EXPECT_EQ(cave.GetCave().rows, 4);
  EXPECT_EQ(cave.GetCave().cols, 4);
}

TEST(Cave, IncorrectFile) {
  Cave cave = Cave::GetInstance();

  EXPECT_ANY_THROW(cave.UploadCaveFromFile("somepath"));
}

TEST(Cave, Generation) {
  Cave cave = Cave::GetInstance();

  cave.setSize(20);
  cave.GenerateCave();

  EXPECT_EQ(cave.GetCave().cols, 20);
  EXPECT_EQ(cave.GetCave().rows, 20);
  EXPECT_EQ(cave.GetCave().cave_data.size(), 20);
  EXPECT_TRUE(cave.HasNextGeneration());

  while (cave.HasNextGeneration()) cave.CellularAutomation();

  EXPECT_FALSE(cave.HasNextGeneration());
}