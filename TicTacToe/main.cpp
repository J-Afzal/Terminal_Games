//
//  main.cpp
//  TicTacToe
//
//  Created by Main on 09/12/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//

#include "TicTacToe.hpp"
#include <iostream>
#include <vector>

int main(void) {
    
    std::cout << "--------------------TicTacToe V1.0 by Junaid Afzal--------------------" << std::endl;
    
    unsigned int CurrentPlayer;
    std::srand(std::time(0));
    if (std::rand() % 2 == 0)
        CurrentPlayer = 'X'; //88
    else
        CurrentPlayer = 'O'; //79
    
    unsigned int NumberOfTurns = 0;

    std::vector< std::vector<int> > GameData = Get_Size_Of_Grid();
    
    unsigned int NumberOfPlayers = Get_Number_Of_players();
    
    unsigned int UserXO;
    
    if(NumberOfPlayers == 1)
        UserXO = Get_User_X_O();
    
    
    while (!Game_Over(GameData) && !Winning_Conditions_Met(GameData))
    {
        Display_Current_Game(GameData);

        CurrentPlayer = Toggle_Player(CurrentPlayer);

        GameData = Ask_User_For_Next_Input(GameData, CurrentPlayer);

        NumberOfTurns++;

        std::cout << "\n\n" << std::endl;
     }

    
    
     if (Winning_Conditions_Met(GameData))
     {
        Display_Current_Game(GameData);
        std::cout << "Congratulations on Player " << (char)CurrentPlayer << " for winning!\nOnly took you " << NumberOfTurns << " turns" << std::endl;
        std::cout << "--------------------TicTacToe V2.0 by Junaid Afzal--------------------\n\n" << std::endl;
     }

     else
     {
        Display_Current_Game(GameData);
        std::cout << "Game is a draw\nOnly took you " << NumberOfTurns << " turns" << std::endl;
        std::cout << "--------------------TicTacToe V2.0 by Junaid Afzal--------------------\n\n" << std::endl;
     }
    
    return 0;
}





/*
 - std::cout << "Two player? (y or n) ";
 - formatting {} and spacing and functions
 */
