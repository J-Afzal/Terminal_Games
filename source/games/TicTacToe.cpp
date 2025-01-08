#include <chrono>
#include <cstdint>
#include <string>
#include <thread>
#include <tuple>
#include <vector>

#include "games/TicTacToe.hpp"
#include "helpers/Constants.hpp"
#include "helpers/Exceptions.hpp"
#include "helpers/Functions.hpp"
#include "helpers/PageBuilder.hpp"
#include "helpers/Terminal.hpp"

namespace TerminalGames
{
    TicTacToe::TicTacToe(const bool& p_useAnsiEscapeCodes) :
        m_computerSpeed(0),
        m_turnCount(0),
        m_hasWinner(false)
    {
        m_pageBuilder.SetProperties(Pages::TICTACTOE, p_useAnsiEscapeCodes);
        m_randomNumberGenerator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    }

    void TicTacToe::SetupGame()
    {
        m_randomNumberGenerator() % 2 == 0 ? m_currentPlayer = "Player X" : m_currentPlayer = "Player O";
        m_commandsRemaining.clear();
        m_previousCommand = {0, 0};
        m_computerSpeedName = "N/A";
        m_playerCount = "N/A";
        m_userPlayerChoice = " ";
        m_turnCount = 0;
        m_hasWinner = false;

        for (uint32_t i = 0; i < G_TICTACTOE_BOARD_HEIGHT; i++)
        {
            for (uint32_t j = 0; j < G_TICTACTOE_BOARD_WIDTH; j++)
            {
                m_gameGrid.at(i).at(j) = "   ";
                m_commandsRemaining.emplace_back(i, j);
            }
        }
    }

    void TicTacToe::UpdateGameInfo()
    {
        m_gameInfo.m_ticTacToeGameInfo = {
            .m_gameGrid = m_gameGrid,
            .m_computerSpeedName = m_computerSpeedName,
            .m_currentPlayer = m_currentPlayer,
            .m_playerCount = m_playerCount,
            .m_turnCount = m_turnCount,
            .m_hasWinner = m_hasWinner};
    }

    void TicTacToe::GetUserOptions()
    {
        GetPlayerCount();

        // If only one human user, then ask them which player they want to be (X or O)
        if (m_playerCount == "1  ")
        {
            GetUserPlayerChoice();
        }

        // If computer involved get computer difficulty and speed
        if (m_playerCount != "2  ") // i.e. = 0 or = 1
        {
            GetComputerSpeed();
        }

        UpdateGameInfo();
    }

    bool TicTacToe::IsGameOver()
    {
        // Check horizontals
        if ((m_gameGrid[0][0] != "   " && m_gameGrid[0][0] == m_gameGrid[0][1] && m_gameGrid[0][1] == m_gameGrid[0][2]) ||
            (m_gameGrid[1][0] != "   " && m_gameGrid[1][0] == m_gameGrid[1][1] && m_gameGrid[1][1] == m_gameGrid[1][2]) ||
            (m_gameGrid[2][0] != "   " && m_gameGrid[2][0] == m_gameGrid[2][1] && m_gameGrid[2][1] == m_gameGrid[2][2]) ||

            // Check verticals
            (m_gameGrid[0][0] != "   " && m_gameGrid[0][0] == m_gameGrid[1][0] && m_gameGrid[1][0] == m_gameGrid[2][0]) ||
            (m_gameGrid[0][1] != "   " && m_gameGrid[0][1] == m_gameGrid[1][1] && m_gameGrid[1][1] == m_gameGrid[2][1]) ||
            (m_gameGrid[0][2] != "   " && m_gameGrid[0][2] == m_gameGrid[1][2] && m_gameGrid[1][2] == m_gameGrid[2][2]) ||

            // Check diagonals
            (m_gameGrid[0][0] != "   " && m_gameGrid[0][0] == m_gameGrid[1][1] && m_gameGrid[1][1] == m_gameGrid[2][2]) ||
            (m_gameGrid[2][0] != "   " && m_gameGrid[2][0] == m_gameGrid[1][1] && m_gameGrid[1][1] == m_gameGrid[0][2]))
        {
            m_hasWinner = true;
            return m_hasWinner;
        }

        return m_turnCount == G_TICTACTOE_MAXIMUM_ERROR_COUNT;
    }

    void TicTacToe::ToggleCurrentPlayer()
    {
        m_currentPlayer == "Player X" ? m_currentPlayer = "Player O" : m_currentPlayer = "Player X";
    }

    bool TicTacToe::IsCurrentTurnUsers()
    {
        // If it is two player game then next turn will always be the user's turn, if not then
        // check if the current player is the same as the user's choice. For a zero player game
        // m_UserPlayerChoice = ' ' and so this will always return false.
        return m_playerCount == "2  " || m_currentPlayer == m_userPlayerChoice;
    }

    void TicTacToe::ExecuteUserCommand()
    {
        while (true)
        {
            const std::tuple<uint32_t, uint32_t> SELECTED_COMMAND = Terminal::GetUserCommandFromGameGrid(m_previousCommand, m_pageBuilder, m_gameInfo, true);

            if (ValidateCommand(SELECTED_COMMAND))
            {
                ExecuteGeneralCommand(SELECTED_COMMAND);
                m_previousCommand = SELECTED_COMMAND;
                return;
            }
        }
    }

    void TicTacToe::ExecuteComputerCommand()
    {
        Terminal::PrintOutput(m_pageBuilder.GetComputerCommandPage(m_gameInfo));

        if (m_computerSpeed != 0)
        {
            std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(m_computerSpeed));
        }

        const std::tuple<uint32_t, uint32_t> SELECTED_COMMAND = m_commandsRemaining[m_randomNumberGenerator() % m_commandsRemaining.size()];

        if (ValidateCommand(SELECTED_COMMAND))
        {
            ExecuteGeneralCommand(SELECTED_COMMAND);
            return;
        }
    }

    void TicTacToe::GameOver()
    {
        Terminal::PrintOutput(m_pageBuilder.GetGameOverPage(m_gameInfo));

        if (Terminal::GetNextKeyPress() == G_QUIT_KEY)
        {
            throw Exceptions::QuitGame();
        }
    }

    void TicTacToe::GetPlayerCount()
    {
        UpdateGameInfo();

        const std::vector<std::string> MENUS = m_pageBuilder.GetPlayerCountOptionSelectionGamePages(m_gameInfo);
        m_playerCount = std::to_string(Terminal::GetUserChoiceFromGameMenus(MENUS)) + "  ";
    }

    void TicTacToe::GetUserPlayerChoice()
    {
        UpdateGameInfo();

        const std::vector<std::string> MENUS = m_pageBuilder.GetUserPlayerChoiceOptionSelectionGamePages(m_gameInfo);
        Terminal::GetUserChoiceFromGameMenus(MENUS) == 0 ? m_userPlayerChoice = "Player X" : m_userPlayerChoice = "Player O";
    }

    void TicTacToe::GetComputerSpeed()
    {
        UpdateGameInfo();

        const std::vector<std::string> MENUS = m_pageBuilder.GetComputerSpeedOptionSelectionGamePages(m_gameInfo);
        m_computerSpeed = Terminal::GetUserChoiceFromGameMenus(MENUS);

        if (m_computerSpeed == 0)
        {
            m_computerSpeedName = "INSTANT";
        }

        else if (m_computerSpeed == 1)
        {
            m_computerSpeedName = "FAST";
        }

        else // == 2
        {
            m_computerSpeedName = "SLOW";
        }
    }

    bool TicTacToe::ValidateCommand(const std::tuple<uint32_t, uint32_t>& p_command)
    {
        const auto COMMAND_FIND_LOCATION = ImplementStdRangesFind(m_commandsRemaining.begin(), m_commandsRemaining.end(), p_command);

        return COMMAND_FIND_LOCATION != m_commandsRemaining.end();
    }

    void TicTacToe::ExecuteGeneralCommand(const std::tuple<uint32_t, uint32_t>& p_command)
    {
        const auto COMMAND_FIND_LOCATION = ImplementStdRangesFind(m_commandsRemaining.begin(), m_commandsRemaining.end(), p_command);

        m_gameGrid.at(std::get<0>(p_command)).at(std::get<1>(p_command)) = std::string(" ") + m_currentPlayer.back() + std::string(" ");
        m_commandsRemaining.erase(COMMAND_FIND_LOCATION);
        m_turnCount++;
    }
}
