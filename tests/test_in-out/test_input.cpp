#include <gtest/gtest.h>
#include "../../src/in-out/in_out.h"



//Test to verify the correct input of components for each of their shapes
TEST(InputTest, ValidInput) {
  std::istringstream input_stream("2\n 3\n 1 2\n 3 4\n 5 6\n "
                                  "4\n 0 0\n 1 1\n 2 2\n 3 3\n");

  std::streambuf* old_cin = std::cin.rdbuf(input_stream.rdbuf());

  std::vector<std::vector<Point>> shapes = input();

  ASSERT_EQ(shapes.size(), 2);
  ASSERT_EQ(shapes[0].size(), 3);
  ASSERT_EQ(shapes[1].size(), 4);

  std::cin.rdbuf(old_cin);
}



//Test for entering a letter instead of the number of shapes
TEST(InputTest, LetterInput) {
  std::istringstream input_stream("letter)\n");

  std::streambuf* old_cin = std::cin.rdbuf(input_stream.rdbuf());

  std::vector<std::vector<Point>> shapes = input();
  ASSERT_TRUE(shapes.empty());

  std::cin.rdbuf(old_cin);
}



//Test for entering a letter instead of vertices count
TEST(InputTest, LetterIncteadCount) {
  std::istringstream input_stream("1\n abc");

  std::streambuf* old_cin = std::cin.rdbuf(input_stream.rdbuf());

  std::vector<std::vector<Point>> shapes = input();
  ASSERT_TRUE(shapes.empty());

  std::cin.rdbuf(old_cin);
}



//Test for entering a letter instead of a coordinates of vertex
TEST(InputTest, LetterInsteadVertex) {
  std::istringstream input_stream("2\n 3\n -1 0\n -10 10\n abba cabac"
                                  "3\n 5 6\n 7 8\n 9 10\n");

  std::streambuf* old_cin = std::cin.rdbuf(input_stream.rdbuf());

  std::vector<std::vector<Point>> shapes = input();
  std::cin.rdbuf(old_cin);

  ASSERT_TRUE(shapes.empty());
}



//Test for fully correct input of each component of shapes
TEST(InputTest, FullyCorrectInput) {
    std::istringstream input_stream("2\n 4\n -1 0\n -10 10\n 3 4\n 5 6\n"
                                  "5\n 5 6\n -7 -8\n 0 10\n 1.2 3.4 \n 0.0 0.0");

  std::streambuf* old_cin = std::cin.rdbuf(input_stream.rdbuf());

  std::vector<std::vector<Point>> shapes = input();

  std::cin.rdbuf(old_cin);

  ASSERT_EQ(shapes.size(), 2);
  ASSERT_EQ(shapes[0].size(), 4);
  ASSERT_EQ(shapes[1].size(), 5);

  ASSERT_EQ(shapes[0][0].x, -1);
  ASSERT_EQ(shapes[0][1].x, -10);
  ASSERT_EQ(shapes[0][1].y, 10);

  ASSERT_EQ(shapes[1][3].x, 1.2);
  ASSERT_EQ(shapes[1][3].y, 3.4);
  ASSERT_EQ(shapes[1][4].x, 0.0);
}