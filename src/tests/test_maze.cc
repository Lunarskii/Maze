#include "test_core.h"

TEST(Maze, CorrectFile) {
  Maze maze = Maze::GetInstance();
  maze.UploadMazeFromFile("mazes/maze1.txt");

  EXPECT_EQ(maze.GetMaze().rows, 10);
  EXPECT_EQ(maze.GetMaze().cols, 10);
  EXPECT_TRUE(maze.GetMaze().IsValid());
}

TEST(Maze, IncorrectFile) {
  Maze maze = Maze::GetInstance();
  EXPECT_ANY_THROW(maze.UploadMazeFromFile("somepath"));
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

  maze.SaveMaze("saved_cave_test.txt");
  std::ifstream fs("saved_cave_test.txt");

  EXPECT_TRUE(fs.good());
}