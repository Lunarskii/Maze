#include "test_core.h"

TEST(Cave, CorrectFile) {
  Cave cave = Cave::GetInstance();

  EXPECT_NO_THROW(cave.UploadCaveFromFile("./tests/materials/caves/cave1.txt"));

  EXPECT_EQ(cave.GetCave().rows, 4);
  EXPECT_EQ(cave.GetCave().cols, 4);
}

TEST(Cave, IncorrectFile) {
  Cave cave = Cave::GetInstance();

  EXPECT_ANY_THROW(cave.UploadCaveFromFile("somepath"));
}

TEST(Cave, EmptyFile)
{
  Cave cave = Cave::GetInstance();
  EXPECT_ANY_THROW(cave.UploadCaveFromFile("./tests/materials/mazes/0.txt"));
}

TEST(Cave, NegativeRows)
{
  Cave cave = Cave::GetInstance();
  EXPECT_ANY_THROW(cave.UploadCaveFromFile("./tests/materials/caves/negative_rows.txt"));
}

TEST(Cave, NegativeColumns)
{
  Cave cave = Cave::GetInstance();
  EXPECT_ANY_THROW(cave.UploadCaveFromFile("./tests/materials/caves/negative_cols.txt"));
}

TEST(Cave, BadData)
{
  Cave cave = Cave::GetInstance();
  EXPECT_ANY_THROW(cave.UploadCaveFromFile("./tests/materials/caves/bad_data.txt"));
}

TEST(Cave, Generation) {
  Cave cave = Cave::GetInstance();

  cave.SetRows(20);
  cave.SetCols(20);
  cave.SetInitialChance(10);
  cave.GenerateCave();

  EXPECT_EQ(cave.GetCave().cols, 20);
  EXPECT_EQ(cave.GetCave().rows, 20);
  EXPECT_EQ(cave.GetCave().cave_data.size(), 20);
  EXPECT_TRUE(cave.HasNextGeneration());

  cave.SetLimitBirth(5);
  cave.SetLimitDeath(3);
  while (cave.HasNextGeneration()) cave.CellularAutomation();

  EXPECT_FALSE(cave.HasNextGeneration());
}