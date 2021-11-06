//
//  @File: Hangman.cpp
//  @Author: Junaid Afzal
//

// to prevent max error with windows.h redefining it
// https://stackoverflow.com/questions/7035023/stdmax-expected-an-identifier/7035078
#define NOMINMAX
#include <windows.h>

#include "hangman.hpp"
#include "functions.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <conio.h>

void Setup_Game(unsigned int &NumberOfPlayers,
                std::string &PlayerThatIsGuessing,
                std::string &AIDifficulty,
                std::string &WordToBeGuessed,
                std::string &CurrentGuessOfWord,
                std::vector<unsigned char> &ValidMovesRemaining,
                const std::vector<unsigned char> &IncorrectGuesses)
{
  // Set seed of srand to time(0) so pseudo random
  std::srand((unsigned int)std::time(0));

  do
  {
    Display_Game(0, "N/A", AIDifficulty, IncorrectGuesses, "");
    std::cout << "\n\n\n\n\nPlease enter the number of players: ";
  }
  while(Get_Number_Of_Players(NumberOfPlayers, 0, 2));

  if (NumberOfPlayers == 0)
    PlayerThatIsGuessing = "AI";

  else if (NumberOfPlayers == 1)
  {
    do
    {
      Display_Game(0, std::to_string(NumberOfPlayers), AIDifficulty, IncorrectGuesses, "");
      std::cout << "\n\n\n\n\nWhat player would you like to be? (Player One = Guesser and Player Two = Set the word): ";
    }
    while(Get_User_Player_Choice(PlayerThatIsGuessing));

    if (PlayerThatIsGuessing == "PLAYER ONE")
      PlayerThatIsGuessing = "HUMAN";
    else
      PlayerThatIsGuessing = "AI";
  }

  if (NumberOfPlayers == 0 || NumberOfPlayers == 1)
  {
    do
    {
      Display_Game(0, std::to_string(NumberOfPlayers), AIDifficulty, IncorrectGuesses, "");
      std::cout << "\n\n\n\n\nPlease enter the AI difficulty (EASY or HARD): ";
    }
    while(Get_AI_Difficulty(AIDifficulty));
  }



  if (PlayerThatIsGuessing == "AI" || NumberOfPlayers == 2)
    WordToBeGuessed = Get_Word_To_Be_Guessed_From_User(IncorrectGuesses, NumberOfPlayers, AIDifficulty);
  else
    WordToBeGuessed = Get_Word_To_Be_Guessed_From_AI();

  // Create the current guess to be the same size as the word to be guessed but only containing underscores
  for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
    CurrentGuessOfWord.push_back('_');

  for (unsigned int i = 0; i < 26; i++)
    ValidMovesRemaining.push_back(65+i);
}

std::string Get_Word_To_Be_Guessed_From_User(const std::vector<unsigned char> &IncorrectGuesses,
                                             const unsigned int &NumberOfPlayers,
                                             const std::string &AIDifficulty)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  std::string Input; // No spaces or - allowed

  while (!IsValueCorrect)
  {
    // Set flag to true by default as difficult to continue to to next iteration of while loop
    // within a nested if statements within nested for loops
    IsValueCorrect = true;

    Display_Game(0, std::to_string(NumberOfPlayers), AIDifficulty, IncorrectGuesses, "");
    std::cout << "\n\n\n\n\nEnter the word to be guessed: ";

    std::getline(std::cin, Input);

    // Capitalise all letters so that only capital letter need to be dealt with
    Capitalise_Word(Input);

    // Only accept chars that are either capital or lowercase letters
    for (unsigned int i = 0; i < Input.size(); i++)
    {
      if (Input[i] < 'A' || Input[i] > 'Z')
      {
        IsValueCorrect = false;
        break;
      }
    }
  }

  return Input;
}

std::string Get_Word_To_Be_Guessed_From_AI(void)
{
  std::vector<std::string> Words = Generate_Word_List();
  return Words[std::rand() % Words.size()];
}

void Display_Game(const unsigned int &NumberOfErrors,
                  const std::string &NumberOfPlayers,
                  const std::string &AIDifficulty,
                  const std::vector<unsigned char> &IncorrectGuesses,
                  const std::string &CurrentGuessOfWord)
{
  // Start from blank terminal
  Clear_Terminal();

  // Draw the hangman drawing
  switch (NumberOfErrors)
  {
  case 0:
    std::cout << "\n\t\t\t\t\t       Hangman"
              << "\n\n\t\t\t\t\t   # of Players = " << NumberOfPlayers
              << "\n\n\t\t\t\t\t AI Difficulty = " << AIDifficulty
              << "\n\n\n";
    break;

  case 1:
    std::cout << "\n\t\t   Incorrect Guesses\t       Hangman"
              << "\n\n\t\t   " << IncorrectGuesses[0] << "\t\t\t   # of Players = " << NumberOfPlayers
              << "\n\n\t\t\t\t\t AI Difficulty = " << AIDifficulty
              << "\n" << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
              << "\n\n";
    break;

  case 2:
    std::cout << "\n    " << (char)179 << "\t\t   Incorrect Guesses\t       Hangman"
              << "\n    " << (char)179
              << "\n    " << (char)179 << "\t\t   " << IncorrectGuesses[0] << "   " << IncorrectGuesses[1] << "\t\t   # of Players = " << NumberOfPlayers
              << "\n    " << (char)179
              << "\n    " << (char)179 << "\t\t\t\t\t AI Difficulty = " << AIDifficulty
              << "\n" << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
    break;

  case 3:
    std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196
              << "\n    " << (char)179 << "\t\t   Incorrect Guesses\t       Hangman"
              << "\n    " << (char)179
              << "\n    " << (char)179 << "\t\t   " << IncorrectGuesses[0] << "   " << IncorrectGuesses[1] << "   " << IncorrectGuesses[2] << "\t\t   # of Players = " << NumberOfPlayers
              << "\n    " << (char)179
              << "\n    " << (char)179 << "\t\t\t\t\t AI Difficulty = " << AIDifficulty
              << "\n" << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
    break;

  case 4:
    std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191
              << "\n    " << (char)179 << "       " << (char)179 << "\t   Incorrect Guesses\t       Hangman"
              << "\n    " << (char)179
              << "\n    " << (char)179 << "\t\t   " << IncorrectGuesses[0] << "   " << IncorrectGuesses[1] << "   " << IncorrectGuesses[2] << "   " << IncorrectGuesses[3] << "\t   # of Players = " << NumberOfPlayers
              << "\n    " << (char)179
              << "\n    " << (char)179 << "\t\t\t\t\t AI Difficulty = " << AIDifficulty
              << "\n" << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
    break;

  case 5:
    std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196  << (char)196 << (char)196 << (char)196 << (char)196 << (char)191
              << "\n    " << (char)179 << "       " << (char)179 << "\t   Incorrect Guesses\t       Hangman"
              << "\n    " << (char)179 << "       O"
              << "\n    " << (char)179 << "\t\t   " << IncorrectGuesses[0] << "   " << IncorrectGuesses[1] << "   " << IncorrectGuesses[2] << "   " << IncorrectGuesses[3] << "   " << IncorrectGuesses[4] << "\t   # of Players = " << NumberOfPlayers
              << "\n    " << (char)179
              << "\n    " << (char)179 << "\t\t\t\t\t AI Difficulty = " << AIDifficulty
              << "\n" << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
    break;

  case 6:
    std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191
              << "\n    " << (char)179 << "       " << (char)179 << "\t   Incorrect Guesses\t       Hangman"
              << "\n    " << (char)179 << "       O"
              << "\n    " << (char)179 << "       " << (char)179 << "\t   " << IncorrectGuesses[0] << "   " << IncorrectGuesses[1] << "   " << IncorrectGuesses[2] << "   " << IncorrectGuesses[3] << "   " << IncorrectGuesses[4] << "\t   # of Players = " << NumberOfPlayers
              << "\n    " << (char)179
              << "\n    " << (char)179 << "\t\t   " << IncorrectGuesses[5] << "\t\t\t AI Difficulty = " << AIDifficulty
              << "\n" << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
    break;

  case 7:
    std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191
              << "\n    " << (char)179 << "       " << (char)179 << "\t   Incorrect Guesses\t       Hangman"
              << "\n    " << (char)179 << "       O"
              << "\n    " << (char)179 << "       " << (char)179 << "\t   " << IncorrectGuesses[0] << "   " << IncorrectGuesses[1] << "   " << IncorrectGuesses[2] << "   " << IncorrectGuesses[3] << "   " << IncorrectGuesses[4] << "\t   # of Players = " << NumberOfPlayers
              << "\n    " << (char)179 << "      /"
              << "\n    " << (char)179 << "\t\t   " << IncorrectGuesses[5] << "   " << IncorrectGuesses[6] << "\t\t AI Difficulty = " << AIDifficulty
              << "\n" << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
    break;

  case 8:
    std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191
              << "\n    " << (char)179 << "       " << (char)179 << "\t   Incorrect Guesses\t       Hangman"
              << "\n    " << (char)179 << "       O"
              << "\n    " << (char)179 << "       " << (char)179 << "\t   " << IncorrectGuesses[0] << "   " << IncorrectGuesses[1] << "   " << IncorrectGuesses[2] << "   " << IncorrectGuesses[3] << "   " << IncorrectGuesses[4] << "\t   # of Players = " << NumberOfPlayers
              << "\n    " << (char)179 << "      / \\"
              << "\n    " << (char)179 << "\t\t   " << IncorrectGuesses[5] << "   " << IncorrectGuesses[6] << "   " << IncorrectGuesses[7] << "\t\t AI Difficulty = " << AIDifficulty
              << "\n" << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
    break;

  case 9:
    std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191
              << "\n    " << (char)179 << "       " << (char)179 << "\t   Incorrect Guesses\t       Hangman"
              << "\n    " << (char)179 << "       O"
              << "\n    " << (char)179 << "      /" << (char)179 << "\t   " << IncorrectGuesses[0] << "   " << IncorrectGuesses[1] << "   " << IncorrectGuesses[2] << "   " << IncorrectGuesses[3] << "   " << IncorrectGuesses[4] << "\t   # of Players = " << NumberOfPlayers
              << "\n    " << (char)179 << "      / \\"
              << "\n    " << (char)179 << "\t\t   " << IncorrectGuesses[5] << "   " << IncorrectGuesses[6] << "   " << IncorrectGuesses[7] << "   " << IncorrectGuesses[8] << "\t AI Difficulty = " << AIDifficulty
              << "\n" << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
    break;

  case 10:
    std::cout << "    " << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191
              << "\n    " << (char)179 << "       " << (char)179 << "\t   Incorrect Guesses\t       Hangman"
              << "\n    " << (char)179 << "       O"
              << "\n    " << (char)179 << "      /" << (char)179 << "\\" << "\t   " << IncorrectGuesses[0] << "   " << IncorrectGuesses[1] << "   " << IncorrectGuesses[2] << "   " << IncorrectGuesses[3] << "   " << IncorrectGuesses[4] << "\t   # of Players = " << NumberOfPlayers
              << "\n    " << (char)179 << "      / \\"
              << "\n    " << (char)179 << "\t\t   " << IncorrectGuesses[5] << "   " << IncorrectGuesses[6] << "   " << IncorrectGuesses[7] << "   " << IncorrectGuesses[8] << "   " << IncorrectGuesses[9] << "\t AI Difficulty = " << AIDifficulty
              << "\n" << (char)196 << (char)196 << (char)196 << (char)196 << (char)193 << (char)196 << (char)196 << (char)196 << (char)196 << "\n\n";
    break;

  default:
    std::cout << "Error in Display_Game() switch statement\n";
    break;
  }

  // Current guess of word
  for (unsigned int i = 0; i < CurrentGuessOfWord.size(); i++)
    std::cout << CurrentGuessOfWord[i] << " ";
}

bool Winning_Conditions_Met(const unsigned int &NumberOfErrors,
                            const std::string &WordToBeGuessed,
                            const std::string &CurrentGuessOfWord)
{
  // 10 errors mean that the final state of the hangman drawing has been reached
  if (NumberOfErrors == 10)
    return true;

  else
  {
    // If there is any difference then winning condition not met
    for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
      if (WordToBeGuessed[i] != CurrentGuessOfWord[i])
        return false;

    return true;
  }
}

void Get_Next_User_Guess(unsigned int &NumberOfErrors,
                         const unsigned int &NumberOfPlayers,
                         const std::string &AIDifficulty,
                         std::vector<unsigned char> &IncorrectGuesses,
                         std::vector<unsigned char> &CorrectGuesses,
                         std::vector<unsigned char> &ValidMovesRemaining,
                         std::string &CurrentGuessOfWord,
                         const std::string &WordToBeGuessed)
{
  bool IsValueCorrect = false; // Flag for if input value is valid
  std::string Input;

  while (!IsValueCorrect)
  {
    Display_Game(NumberOfErrors, std::to_string(NumberOfPlayers), AIDifficulty, IncorrectGuesses, CurrentGuessOfWord);
    std::cout << "\n\nEnter your guess: ";

    std::getline(std::cin, Input);

    if (Input.size() != 1)
      continue;

    Capitalise_Word(Input);

    auto CommandPosition = std::find(ValidMovesRemaining.begin(), ValidMovesRemaining.end(), Input[0]);

    if (CommandPosition != ValidMovesRemaining.end())
    {
      IsValueCorrect = true;
      ValidMovesRemaining.erase(CommandPosition);
    }
  }

  if (!Check_Guess_Against_Word_To_Be_Guessed(WordToBeGuessed, Input[0], CurrentGuessOfWord))
  {
    IncorrectGuesses.push_back(Input[0]);
    NumberOfErrors++;
  }
  else
    CorrectGuesses.push_back(Input[0]);
}

void Get_Next_AI_Guess(unsigned int &NumberOfErrors,
                       const unsigned int &NumberOfPlayers,
                       const std::string &AIDifficulty,
                       std::vector<unsigned char> &IncorrectGuesses,
                       std::vector<unsigned char> &CorrectGuesses,
                       std::vector<unsigned char> &ValidMovesRemaining,
                       std::string &CurrentGuessOfWord,
                       const std::string &WordToBeGuessed)
{
  Display_Game(NumberOfErrors, std::to_string(NumberOfPlayers), AIDifficulty, IncorrectGuesses, CurrentGuessOfWord);

  unsigned char Guess = ValidMovesRemaining[std::rand() % ValidMovesRemaining.size()];
  auto CommandPosition = std::find(ValidMovesRemaining.begin(), ValidMovesRemaining.end(), Guess);
  ValidMovesRemaining.erase(CommandPosition);

  if (!Check_Guess_Against_Word_To_Be_Guessed(WordToBeGuessed, Guess, CurrentGuessOfWord))
  {
    IncorrectGuesses.push_back(Guess);
    NumberOfErrors++;
  }
  else
    CorrectGuesses.push_back(Guess);
}

bool Check_Guess_Against_Word_To_Be_Guessed(const std::string &WordToBeGuessed,
                                            const unsigned char &Guess,
                                            std::string &CurrentGuessOfWord)
{
  bool IsGuessCorrect = false;

  // If below is true then guess is a letter and every occurrence of this letter
  // needs to be deposited is the current guess of word
  for (unsigned int i = 0; i < WordToBeGuessed.size(); i++)
    if (WordToBeGuessed[i] == Guess)
    {
      IsGuessCorrect = true;
      CurrentGuessOfWord[i] = Guess;
    }

  return IsGuessCorrect;
}

void Display_Game_Over_Message(const unsigned int &NumberOfErrors,
                               const unsigned int &NumberOfPlayers,
                               const std::string &AIDifficulty,
                               const std::vector<unsigned char> &IncorrectGuesses,
                               const std::string &CurrentGuessOfWord,
                               const std::string &WordToBeGuessed,
                               const unsigned int &NumberOfTurns,
                               bool &GameIsRunning)
{
  Display_Game(NumberOfErrors, std::to_string(NumberOfPlayers), AIDifficulty, IncorrectGuesses, CurrentGuessOfWord);
  // If the below is true then hangman has reached its final state and thus user has lost
  if (NumberOfErrors == 10)
    std::cout << "  (The word was " << WordToBeGuessed << ")\n\n\n\t\t\tGAME OVER\n\n       The guesser has lost but lasted for " << NumberOfTurns << " turns!";

  else
    std::cout << "\n\n\n\t\t\tGAME OVER\n\n       The guesser has won! The game lasted " << NumberOfTurns << " turns.";

  std::cout << "\n\n     Press 'Q' to quit OR any other key to play again...";

  // Gets key pressed and then checks and clears terminal window if replaying
  if (_getch() == 'q')
    GameIsRunning = false;

  else
    // Start from blank terminal
    Clear_Terminal();
}
