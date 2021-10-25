//
//  @File: main.cpp for Battleships
//  @Author: Junaid Afzal
//

#include "Battleships.hpp"

int main(void) {
  bool GameIsRunning = true;

    while (GameIsRunning)
    {
      // Variables needed for the game
      std::vector< std::vector<std::string> > PlayerOneBoard, PlayerOneOpponentBoard, PlayerTwoBoard, PlayerTwoOpponentBoard;
      std::string CurrentPlayer;
      unsigned int NumberOfPlayers, NumberOfTurns = 0;

      // Setups all the variables so that game can be played
      Setup_Game(PlayerOneBoard, PlayerOneOpponentBoard, PlayerTwoBoard, PlayerTwoOpponentBoard, NumberOfPlayers, CurrentPlayer);

      // Loop until a winning condition on either board exists
      while (!Winning_Conditions_Met(PlayerOneBoard, PlayerTwoBoard))
      {
        Toggle_Player(CurrentPlayer);

        // One human player and one computer player
        if (NumberOfPlayers == 1)
        {
          // Human player is PLAYER_ONE by default
          if (CurrentPlayer == "PLAYER_ONE")
          {
            // Ask human user for a grid position that they want to attack
            unsigned int Command = Ask_User_For_Next_Command(PlayerOneBoard, PlayerOneOpponentBoard);

            // Carry out the attack and update the corresponding boards
            Execute_Next_Turn(PlayerOneBoard, PlayerOneOpponentBoard, PlayerTwoBoard, PlayerTwoOpponentBoard, CurrentPlayer, Command);
          }

          // Player is the computer
          else
          {
            // Ask computer for a grid position that they want to attack
            unsigned int Command = Ask_Computer_For_Next_Command(PlayerTwoOpponentBoard);

            // Carry out the attack and update the corresponding boards
            Execute_Next_Turn(PlayerOneBoard, PlayerOneOpponentBoard, PlayerTwoBoard, PlayerTwoOpponentBoard, CurrentPlayer, Command);
          }
        }

        // computer vs computer
        else
        {
          if (CurrentPlayer == "PLAYER_ONE")
          {
            //Ask computer for a grid position that they want to attack
            unsigned int Command = Ask_Computer_For_Next_Command(PlayerOneOpponentBoard);

            // Carry out the attack and update the corresponding boards
            Execute_Next_Turn(PlayerOneBoard, PlayerOneOpponentBoard, PlayerTwoBoard, PlayerTwoOpponentBoard, CurrentPlayer, Command);
          }

          else
          {
            // Ask computer for a grid position that they want to attack
            unsigned int Command = Ask_Computer_For_Next_Command(PlayerTwoOpponentBoard);

            // Carry out the attack and update the corresponding boards
            Execute_Next_Turn(PlayerOneBoard, PlayerOneOpponentBoard, PlayerTwoBoard, PlayerTwoOpponentBoard, CurrentPlayer, Command);
          }

          Display_Game_For_Computers(PlayerOneBoard, PlayerTwoBoard);
        }

        // Increment the number of turns
        NumberOfTurns++;
      }

      // Display the winning message as game is now over
      Display_Game_Over_Message(CurrentPlayer, NumberOfTurns, GameIsRunning);
    }

  return 0;
}