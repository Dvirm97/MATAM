#include "Game.h"
#include "test_utilities.h"

using namespace std;

void GameAddPlayerTest() {
  _print_mode_name("Testing GameAddPlayer function");
  Game game(3);
  test(game.addPlayer("Censor", "integral", LIFE, 3) != SUCCESS,
       "GameAddPlayer doesn't return SUCCESS on successful addition",
       __LINE__);
  test(game.addPlayer("Censor", "integral", LIFE, 3) != NAME_ALREADY_EXISTS,
       "GameAddPlayer doesn't return NAME_ALREADY_EXISTS error",
       __LINE__);
  game.addPlayer("Alex", "derivative", LIFE, 3);
  //Checking whether addPlayer adds a non-rider warrior..
  game.addWarrior("Anubis", "Claw", LIFE, 1, false);
  game.makeStep("Anubis");
  game.makeStep("Alex");
  game.fight("Anubis", "Alex"); // both should be in same cell.
  silient_test_passed();
  game.addWarrior("Anubis", "Claw", LIFE, 1, false);
  test(game.addPlayer("Aliza", "Matrix", LIFE, 5) != GAME_FULL,
       "GameAddPlayer doesn't return GAME_FULL on error",
       __LINE__);
}

void GameNextLevelTest() {
  _print_mode_name("Testing GameNextLevel function");
  Game game(1);
  game.addPlayer("Linoy", "lazer gun", LIFE, 5);
  test(game.nextLevel("Linoy") != SUCCESS,
       "GameNextLevel doesn't return SUCCESS on successful increase of lvl",
       __LINE__);
  test(game.nextLevel("Moshe") != NAME_DOES_NOT_EXIST,
       "GameNextLevel doesn't return NAME_DOES_NOT_EXIST on player which doesn't exists.",
       __LINE__);
}

void GameMakeStepTest() {
  _print_mode_name("Testing GameMakeStep function");
  Game game(1);
  game.addPlayer("Linoy", "lazer gun", LIFE, 5);
  test(game.makeStep("Linoy") != SUCCESS,
       "GameMakeStep doesn't return SUCCESS on successful step.",
       __LINE__);
  test(game.makeStep("Chris") != NAME_DOES_NOT_EXIST,
       "GameMakeStep doesn't return NAME_DOES_NOT_EXISTS on player which doesn't exists.",
       __LINE__);
}

void GameAddLifeTest() {
  _print_mode_name("Testing GameAddLife function");
  Game game(1);
  game.addPlayer("Linoy", "lazer gun", LIFE, 5);
  test(game.addLife("Linoy") != SUCCESS,
       "GameAddLife doesn't return SUCCESS on successful step.",
       __LINE__);
  test(game.addLife("Chris") != NAME_DOES_NOT_EXIST,
       "GameAddLife doesn't return NAME_DOES_NOT_EXISTS on player which doesn't exists.",
       __LINE__);
}

void GameAddStrengthTest() {
  _print_mode_name("Testing GameAddStrength function");
  Game game(1);
  game.addPlayer("Linoy", "lazer gun", LIFE, 5);
  test(game.addStrength("Linoy", 5) != SUCCESS,
       "GameAddLife doesn't return SUCCESS on successful step.",
       __LINE__);
  test(game.addStrength("Chris", 5) != NAME_DOES_NOT_EXIST,
       "GameAddStrength doesn't return NAME_DOES_NOT_EXISTS on player which doesn't exists.",
       __LINE__);
  test(game.addStrength("Linoy", -1) != INVALID_PARAM,
       "GameAddStrength doesn't return INVALID_PARAM on negative strength input.",
       __LINE__);
}

void GameRemoveAllPlayersWIthWeakWeaponTest() {
  _print_mode_name("Testing GameRemoveAllPlayersWIthWeakWeapon function");
  Game game(6);
  game.addPlayer("Linoy", "lazer gun", LIFE, 1);
  game.addPlayer("Nazar", "lazer gun", LIFE, 7);
  game.addPlayer("Max", "lazer gun", LIFE, 3);
  game.addPlayer("Guy", "lazer gun", STRENGTH, 4);
  game.removeAllPlayersWithWeakWeapon(6);
  test(game.addPlayer("Linoy", "lazer gun", LIFE, 5) != SUCCESS,
       "GameRemoveAllPlayersWIthWeakWeapon didn't remove the player correctly.",
       __LINE__);
  test(game.addPlayer("Nazar", "lazer gun", LIFE, 5) != NAME_ALREADY_EXISTS,
       "GameRemoveAllPlayersWIthWeakWeapon removes players with weapon value higher than required.",
       __LINE__);
  test(game.addPlayer("Max", "lazer gun", LIFE, 5) != NAME_ALREADY_EXISTS,
       "GameRemoveAllPlayersWIthWeakWeapon removes players with weapon value higher than required.",
       __LINE__);
  test(game.addPlayer("Guy", "lazer gun", LIFE, 5) != NAME_ALREADY_EXISTS,
       "GameRemoveAllPlayersWIthWeakWeapon removes players with weapon value higher than required.",
       __LINE__);
}

void GameAddWarriorTest() {
  _print_mode_name("Testing GameAddWarrior function");
  Game game(2);
  game.addWarrior("Thrall", "Mace", LIFE, 100500, false);
  try {
    game.addWarrior("Thrall", "Mace", LIFE, 100500, false);
  }
  catch (mtm::NameAlreadyExists& a) {
    test(false, "NOERROR", __LINE__);
  }
  try {
    game.addWarrior("Illidan Stormrage", "Warglaives of Azzinoth",
                    LEVEL, 70, false);
  }
  catch (mtm::IllegalWeapon& a) {
    test(false, "NOERROR", __LINE__);
  }
  game.addWarrior("Garrosh Hellscream", "2H-Mace", LIFE, 9001, false);
  try {
    game.addWarrior("Grom Hellscream", "Axe", LIFE, 1000, false);
  }
  catch (mtm::GameFull& a) {
    test(false, "NOERROR", __LINE__);
  }
}

void GameAddWizardTest() {
  _print_mode_name("Testing GameWizard function");
  Game game(2);
  game.addWizard("Gandalf", "StafF", LEVEL, 100500, 5);
  try {
    game.addWizard("Gandalf", "Staff", LEVEL, 100500, 5);
  }
  catch (mtm::NameAlreadyExists& a) {
    test(false, "NOERROR", __LINE__);
  }
  try {
    game.addWizard("Saruman", "Staff", LIFE, 100500, 5);
  }
  catch (mtm::IllegalWeapon& a) {
    test(false, "NOERROR", __LINE__);
  }
  try {
    game.addWizard("Saruman", "Staff", LEVEL, 9001, -1);
  }
  catch (mtm::InvalidParam& a) {
    test(false, "NOERROR", __LINE__);
  }
  game.addWizard("Saruman", "Staff", LEVEL, 9001, 5);
  try {
    game.addWizard("Galadriel", "Telepathy", LEVEL, 9000, 5);
  }
  catch (mtm::GameFull& a) {
    test(false, "NOERROR", __LINE__);
  }
}

void GameAddTrollTest() {
  _print_mode_name("Testing GameTroll function");
  Game game(2);
  game.addTroll("Grendel", "LongLongMace", LIFE, 100500, 5);
  try {
    game.addTroll("Grendel", "LongLongMace", LIFE, 100500, 5);
  }
  catch (mtm::NameAlreadyExists& a) {
    test(false, "NOERROR", __LINE__);
  }
  try {
    game.addTroll("Dunker", "Fists", LIFE, 9001, 0);
  }
  catch (mtm::InvalidParam& a) {
    test(false, "NOERROR", __LINE__);
  }
  try {
    game.addTroll("Dunker", "Fists", LIFE, 9001, -1);
  }
  catch (mtm::InvalidParam& a) {
    test(false, "NOERROR", __LINE__);
  }
  game.addTroll("Hrungnir", "Mace", LIFE, 9001, 5);
  try {
    game.addTroll("Dovregubben", "Fists", LIFE, 9000, 5);
  }
  catch (mtm::GameFull& a) {
    test(false, "NOERROR", __LINE__);
  }
}

void GameFightPart1Test() {
  _print_mode_name("Testing GameFight function part 1");
  Game game(10);
  game.addPlayer("Roi", "lazer gun", LIFE, 2);
  game.addPlayer("Guy", "lazer gun", STRENGTH, 2);
  game.addPlayer("Kevin", "lazer gun", STRENGTH, 2);
  game.addPlayer("Linoy", "lazer gun", LIFE, 1);
  game.addPlayer("Markus", "lazer gun", STRENGTH, 1);
  game.addPlayer("Max", "lazer gun", LIFE, 2);
  game.addPlayer("Nazar", "lazer gun", LIFE, 2);
  game.addPlayer("Terry", "lazer gun", LIFE, 1);
  game.addPlayer("Alex", "sword", STRENGTH, 9);
  game.makeStep("Markus");
  game.makeStep("Linoy");
  game.makeStep("Nazar");
  game.makeStep("Kevin");
  game.makeStep("Terry");
  game.makeStep("Roi");
  game.makeStep("Max");
  game.makeStep("Max");
  game.fight("Terry", "Roi");
  game.fight("Markus", "Kevin");
  test(game.fight("Linoy", "Nazar") != SUCCESS,
       "GameFight didn't return SUCCESS on valid fight.",
       __LINE__);
  try { //Linoy died in previous fight.
    game.fight("Linoy", "Nazar");
  } catch (mtm::NameDoesNotExist& a) {
    test(false, "NOERROR", __LINE__);
  }
  test(game.addPlayer("Linoy", "lazer gun", LIFE, 1) != SUCCESS,
       "GameFight didn't remove dead player after fight(Linoy) died due to Level = 0.",
       __LINE__);
  test(game.addPlayer("Terry", "lazer gun", LIFE, 1) != SUCCESS,
       "GameFight didn't remove dead player after fight(Terry) died due to Life = 0.",
       __LINE__);
  test(game.addPlayer("Markus", "lazer gun", LIFE, 1) != SUCCESS,
       "GameFight didn't remove dead player after fight(Markus) died due to Strength = 0.",
       __LINE__);
  test(game.fight("Nazar", "Max") != FIGHT_FAILED,
       "GameFight didn't return FIGHT_FAILED when 2 players were in different cells.",
       __LINE__);
  try { //Player1 doesn't exists
    game.fight("Player1", "Max");
  } catch (mtm::NameDoesNotExist& a) {
    test(false, "NOERROR", __LINE__);
  }
  try { //Player1 doesn't exists
    game.fight("Max", "Player1");
  } catch (mtm::NameDoesNotExist& a) {
    test(false, "NOERROR", __LINE__);
  }
  game.addStrength("Max", 10);
  game.fight("Max", "Alex");
  try { // "GameFight calculates hitStrength wrong(Max died, he had 10 strength and alex hits for 9)."
    game.addPlayer("Max", "lazer gun", LIFE, 2);
  } catch (mtm::NameAlreadyExists& a) {
    test(false, "NOERROR", __LINE__);
  }
  game.nextLevel("Linoy");
  game.nextLevel("Linoy"); // Linoy level should be 3 now
  game.fight("Linoy", "Nazar");
  try { //Linoy shouldn't die.
    game.addPlayer("Linoy", "lazer gun", LIFE, 2);
  } catch (mtm::NameAlreadyExists& a) {
    test(false, "NOERROR", __LINE__);
  }
  game.addLife("Linoy");
  game.addLife("Linoy"); // Linoy life is now 3
  game.fight("Linoy", "Roi");
  try { //Linoy shouldn't die.
    game.addPlayer("Linoy", "lazer gun", LIFE, 2);
  } catch (mtm::NameAlreadyExists& a) {
    test(false, "NOERROR", __LINE__);
  }
}

void GameFightPart2Test() {
  _print_mode_name("Testing GameFight function part 2");
  Game game(10);
  game.addWarrior("Varian Wrynn", "Sword", LIFE, 1, true);
  game.addWarrior("Thrall", "Mace", LIFE, 2, false);
  game.addWizard("Gandalf", "Staff", LEVEL, 4, 6);
  game.addWizard("Saruman", "Staff", LEVEL, 4, 2);
  game.addTroll("Dovregubben", "Fists", LIFE, 1, 5);
  game.makeStep("Varian Wrynn");
  game.makeStep("Thrall");
  for (int i = 0; i < 10; i++) {
    game.nextLevel("Varian Wrynn");
    game.addLife("Gandalf");
  }
  test(game.fight("Varian Wrynn", "Thrall") != FIGHT_FAILED,
       "GameFight didn't return FIGHT_FAILED when warriors were in different cells",
       __LINE__);
  test(game.fight("Varian Wrynn", "Saruman") != FIGHT_FAILED,
       "GameFight didn't return FIGHT_FAILED when wizard had not enough range to attack.",
       __LINE__);
  test(game.fight("Varian Wrynn", "Gandalf") != SUCCESS,
       "GameFight didn't return SUCCESS when wizard had enough range to attack.",
       __LINE__);
  test(game.fight("Gandalf", "Dovregubben")
           != FIGHT_FAILED, //https://moodle.technion.ac.il/mod/hsuforum/discuss.php?d=612 link with the clarification.
       "GameFight didn't return FIGHT_FAILED when wizard had better so the troll couldn't attack him even when they are in same cell",
       __LINE__);
  game.addLife("Dovregubben");
  game.makeStep("Thrall");
  game.makeStep("Dovregubben"); //he should have 3 life now due to regeneration
  game.fight("Dovregubben", "Thrall");
  try { //Dovregubben shouldn't die he has 3 life's and Thrall hits for 2.
    game.addTroll("Dovregubben", "Fists", LIFE, 1, 5);
  } catch (mtm::NameAlreadyExists& a) {
    test(false, "NOERROR", __LINE__);
  }
  game.addWarrior("Geralt of Rivia", "Sword", LIFE, 5, true);
  game.addTroll("Hrungnir", "Mace", LIFE, 1, 4);
  game.makeStep("Geralt of Rivia");
  game.makeStep("Geralt of Rivia"); // position = 10 (rider).
  for (int j = 0; j < 5; ++j) {
    game.makeStep("Hrungnir");
  } // position = troll (+=2 each step).
  test(game.fight("Hrungnir", "Geralt of Rivia") != SUCCESS,
       "GameFight didn't return SUCCESS on valid fight(either troll ain't walking properly or rider).",
       __LINE__);
  //After this fight troll should die, he could regen his HP only to 4(which is max) and Geralt hits for 5)
  //Next line shouldn't throw an exception.
  game.addTroll("Hrungnir", "Mace", LIFE, 1, 4);
  game.addWarrior("Konnan", "Axe", LIFE, 50000, true);
  game.makeStep("Konnan");
  test(game.fight("Gandalf", "Konnan") != FIGHT_FAILED,
       "GameFight didn't return FIGHT_FAILED when wizard had worse weapon but warrior couldn't attack him due to range.",
       __LINE__);
  silient_test_passed();
}


class ifLowerName {
  Wizard w;
 public:
  explicit ifLowerName(string s) : w(s, Weapon("Staff", LEVEL, 1), 1) {}
  bool operator()(Player const& player) const {
    return w > player;
  }
};

void GameRemovePlayerIfTest() {
  Game game(5);
  game.addWarrior("l", "", LIFE, 10, false);
  game.addWizard("k", "", LEVEL, 10, 1);
  game.addTroll("a", "", LIFE, 10, 50);
  game.addWarrior("b", "", LIFE, 10, false);
  game.addWarrior("z", "", LIFE, 10, false);
  string s("k");
  string s2("z");
  string s3("~"); //Should remove every player cuz of its ascii value.
  ifLowerName Lower(s);
  ifLowerName Lower2(s2);
  ifLowerName Lower3(s3);
  test(!game.removePlayersIf(Lower),
       "Function should remove players A,B,L",
       __LINE__);
  test(!game.removePlayersIf(Lower2),
       "Function should remove player K",
       __LINE__);
  test(game.removePlayersIf(Lower2),
       "Player shouldn't be removed, player with the name \"Z\" could'nt be removed by Z itself.",
       __LINE__);
  test(!game.removePlayersIf(Lower3),
       "Removing all players",
       __LINE__);
  test(game.removePlayersIf(Lower3),
       "There are no players, shouldn't remove anything.",
       __LINE__);
}

int main() {
  cout <<
       "\nWelcome to the homework MTM 5 Call of Matam Duties tests"
       "\nThe tests were written by: Vova Parakhin."
       "\n\n------Passing those tests won't"
       " guarantee you a good grade------\nBut they might get you closer"
       ",make some tests yourself to be sure.\n\n";
  cout << "You can change w/e you want in the file itself"
          " but make sure \nto contact me if you want to upload";
  cout << " \'upgraded version\' of the file.\n" << endl;
  getEnter();
  GameAddPlayerTest();
  GameNextLevelTest();
  GameMakeStepTest();
  GameAddLifeTest();
  GameAddStrengthTest();
  GameRemoveAllPlayersWIthWeakWeaponTest();
  GameAddTrollTest();
  GameAddWizardTest();
  GameAddWarriorTest();
  GameFightPart1Test();
  GameFightPart2Test();
  GameRemovePlayerIfTest();
  print_grade();
  return 0;
}
