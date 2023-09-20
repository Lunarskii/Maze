#include "test_core.h"

TEST(Maze, CorrectFile) {
  Maze maze = Maze::GetInstance();
  maze.UploadMazeFromFile("./tests/materials/mazes/maze1.txt");

  EXPECT_EQ(maze.GetMaze().rows, 10);
  EXPECT_EQ(maze.GetMaze().cols, 10);
  EXPECT_TRUE(maze.GetMaze().IsValid());
}

TEST(Maze, NoFile) {
  Maze maze = Maze::GetInstance();
  EXPECT_ANY_THROW(maze.UploadMazeFromFile("somepath"));
}

TEST(Maze, EmptyFile)
{
  Maze maze = Maze::GetInstance();
  EXPECT_ANY_THROW(maze.UploadMazeFromFile("./tests/materials/mazes/0.txt"));
}

TEST(Maze, NegativeRows)
{
  Maze maze = Maze::GetInstance();
  EXPECT_ANY_THROW(maze.UploadMazeFromFile("./tests/materials/mazes/negative_rows.txt"));
}

TEST(Maze, NegativeColumns)
{
  Maze maze = Maze::GetInstance();
  EXPECT_ANY_THROW(maze.UploadMazeFromFile("./tests/materials/mazes/negative_cols.txt"));
}

TEST(Maze, BadRightWalls)
{
  Maze maze = Maze::GetInstance();
  EXPECT_ANY_THROW(maze.UploadMazeFromFile("./tests/materials/mazes/bad_right_walls.txt"));
}

TEST(Maze, BadBottomWalls)
{
  Maze maze = Maze::GetInstance();
  EXPECT_ANY_THROW(maze.UploadMazeFromFile("./tests/materials/mazes/bad_bottom_walls.txt"));
}

TEST(Maze, Generation) {
  Maze maze = Maze::GetInstance();
  maze.GenerateMaze(20, 20);

  EXPECT_EQ(maze.GetMaze().rows, 20);
  EXPECT_EQ(maze.GetMaze().cols, 20);
  EXPECT_TRUE(maze.GetMaze().IsValid());
}

TEST(Maze, Saving) {
  Maze maze = Maze::GetInstance();
  maze.GenerateMaze(4, 4);

  maze.SaveMaze("./tests/materials/mazes/saved_cave_test.txt");
  std::ifstream fs("./tests/materials/mazes/saved_cave_test.txt");

  EXPECT_TRUE(fs.good());
}

TEST(Maze, Pathfinder1)
{
  Maze maze = Maze::GetInstance();
  maze.UploadMazeFromFile("./tests/materials/mazes/test_pathfinder.txt");
  std::vector<Point> path_ = maze.FindPath({7, 1}, {2, 6});
  EXPECT_EQ(path_.size(), 15);
}

TEST(Maze, Pathfinder2)
{
  Maze maze = Maze::GetInstance();
  maze.UploadMazeFromFile("./tests/materials/mazes/test_pathfinder.txt");
  EXPECT_EQ(maze.FindPath({7, 1}, {-1, 0}).empty(), std::vector<Point>{}.empty());
}
