#ifndef TEST_UTILITIES_H_
#define TEST_UTILITIES_H_

#include <cstdio>
#include <cmath>

using std::endl;
using std::cout;
using std::printf;

int test_number = 0;
int tests_passed = 0;

void _print_error(const char *errorName, int lineNumber) {
  printf("\t\t\tTest %2d failed\n", test_number + 1);
  printf(
      "\n***************************************************************************");
  printf("\nError Line: %d\nError description:\n%-80s", lineNumber, errorName);
  printf(
      "\n***************************************************************************\n");
}

void _print_test_number(int line_num) {
  printf("Running test %2d at line number: %3d.", test_number + 1,
         line_num);
}

void _print_test_success(int test_number) {
  printf("\t\t\tTest %2d passed successfully\n", test_number + 1);
}

void _print_mode_name(const char *name) {
  printf(
      "---------------------------------------------------------------------------");
  printf("\n\t\t    %s", name);
  printf(
      "\n---------------------------------------------------------------------------\n");
}

void test(bool expression, const char *error_code, int line) {
  _print_test_number(line);
  if (expression)
    _print_error(error_code, line);
  else {
    _print_test_success(test_number);
    tests_passed += 1;
  }
  test_number += 1;

}
void silient_test_passed() {
  test_number++;
  tests_passed++;
}

void getEnter() {
  cout << "              _                                                \n"
          "             | |                                               \n"
          "             | |===( )   //////                                \n"
          "             |_|   |||  | o o|                                 \n"
          "                    ||| ( c  )                  ____           \n"
          "                     ||| \\= /                  ||   \\_       \n"
          "                      ||||||                   ||     |        \n"
          "                      ||||||                ...||__/|-\"       \n"
          "                      ||||||             __|________|__        \n"
          "                        |||             |______________|       \n"
          "                        |||             || ||      || ||       \n"
          "                        |||             || ||      || ||       \n"
          "------------------------|||-------------||-||------||-||-------\n"
          "                        |__>            || ||      || ||       \n"
          "                                                               \n"
          "                                                               \n"
          "     hit ENTER to continue                                     \n";
  getchar();
}

void print_grade() {
  auto grade = (int) (((double) tests_passed / test_number) * 100);
  if (grade == 100) {
    cout
        << "             ________________________________________________               \n"
           "            /                                                \\             \n"
           "           |    _________________________________________     |             \n"
           "           |   |                                         |    |             \n"
           "           |   |    Congratulations, You've done it!     |    |             \n"
           "           |   |                                         |    |             \n"
           "           |   |       Good luck with the Exams,         |    |             \n"
           "           |   |                                         |    |             \n"
           "           |   |    See you on Data Structures course!   |    |             \n"
           "           |   |                                         |    |             \n"
           "           |   |_________________________________________|    |             \n"
           "           |                                                  |             \n"
           "            \\_________________________________________________/            \n"
           "                   \\___________________________________/                   \n"
           "                              -Vova Parakhin-                               \n";
  }
  if (grade <= 99 && grade > 55) {
    cout << "      .--..--..--..--..--..--.            \n"
            "    .' \\  (`._   (_)     _   \\            \n"
            "  .'    |  '._)         (_)  |            \n"
            "  \\ _.')\\      .----..---.   /            \n"
            "  |(_.'  |    /    .-\\-.  \\  |            \n"
            "  \\     0|    |   ( O| O) | o|            \n"
            "   |  _  |  .--.____.'._.-.  |            \n"
            "   \\ (_) | o         -` .-`  |            \n"
            "    |    \\   |`-._ _ _ _ _\\ /             \n"
            "    \\    |   |  `. |_||_|   |             \n"
            "    | o  |    \\_      \\     |     -.   .-.\n"
            "    |.-.  \\     `--..-'   O |     `.`-' .'\n"
            "  _.'  .' |     `-.-'      /-.__   ' .-'  \n"
            ".' `-.` '.|='=.='=.='=.='=|._/_ `-'.'     \n"
            "`-._  `.  |________/\\_____|    `-.'       \n"
            "   .'   ).| '=' '='\\/ '=' |               \n"
            "   `._.`  '---------------'               \n"
            "           //___\\   //___\\                \n"
            "             ||       ||                  \n"
            "    LGB      ||_.-.   ||_.-.              \n"
            "            (_.--__) (_.--__)             \n"
            "         Not that much left!              \n";
  }
  if (grade <= 55) {
    cout << "                             __           \n"
            "                   _ ,___,-'\",-=-.        \n"
            "       __,-- _ _,-'_)_  (\"\"`'-._\\ `.      \n"
            "    _,'  __ |,' ,-' __)  ,-     /. |      \n"
            "  ,'_,--'   |     -'  _)/         `\\      \n"
            ",','      ,'       ,-'_,`           :     \n"
            ",'     ,-'       ,(,-(              :     \n"
            "     ,'       ,-' ,    _            ;     \n"
            "    /        ,-._/`---'            /      \n"
            "   /        (____)(----. )       ,'       \n"
            "  /         (      `.__,     /\\ /,        \n"
            " :           ;-.___         /__\\/|        \n"
            " |         ,'      `--.      -,\\ |        \n"
            " :        /            \\    .__/          \n"
            "  \\      (__            \\    |_           \n"
            "   \\       ,`-, *       /   _|,\\          \n"
            "    \\    ,'   `-.     ,'_,-'    \\         \n"
            "   (_\\,-'    ,'\")--,'-'       __\\        \n"
            "    \\       /  // ,'|      ,--'  `-.      \n"
            "     `-.    `-/ \'  |   _,'         `.    \n"
            "        `-._ /      `--'/             \\   \n"
            "-OMG-      ,'           |              \\  \n"
            "          /             |               \\ \n"
            "       ,-'              |               / \n"
            "      /                 |             -'  \n"
            "         What are you doing here?...      \n";
  }
  printf("\nYour grade is: %d", grade);
  printf("\nYou've passed %d tests out of %d\n", tests_passed, test_number);
}

#endif /* TEST_UTILITIES_H_ */
