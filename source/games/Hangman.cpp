#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <thread>
#include <vector>

#include "games/Hangman.hpp"
#include "helpers/Globals.hpp"
#include "helpers/PageBuilder.hpp"
#include "helpers/Terminal.hpp"

namespace TerminalGames
{
    Hangman::Hangman(const bool& p_useAnsiEscapeCodes) :
        m_computerSpeed(0),
        m_errorCount(0),
        m_turnCount(0),
        m_currentGuess(0),
        m_hasSavedGameSettings(false),
        m_hasWinner(false),
        m_saveGameSettings(false),
        m_userIsGuesser(false)
    {
        m_pageBuilder.SetProperties(Pages::HANGMAN, p_useAnsiEscapeCodes);
        m_randomNumberGenerator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    }

    void Hangman::SetupGame()
    {
        m_commandsRemaining.reserve(Globals::G_HANGMAN_NUMBER_OF_LETTERS_IN_THE_ALPHABET);
        m_commandsRemaining = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        m_currentGuess = 'A';
        m_incorrectGuesses.clear();
        m_currentGuessOfWord = "";
        m_wordToBeGuessed = "";
        m_errorCount = 0;
        m_turnCount = 0;
        m_hasWinner = false;
    }

    void Hangman::GetUserOptions()
    {
        if (m_saveGameSettings && m_hasSavedGameSettings)
            return;

        m_computerSpeedName = "N/A";
        m_playerCount = "N/A";

        GetPlayerCount();

        if (m_playerCount == "0  ")
        {
            m_userIsGuesser = false;
            GetComputerSpeed();
            GetWordFromComputer();
        }

        else if (m_playerCount == "1  ")
        {
            GetUserPlayerChoice();
            GetComputerSpeed();

            if (!m_userIsGuesser)
            {
                GetWordFromUser();
            }

            else
            {
                GetWordFromComputer();
            }
        }

        else if (m_playerCount == "2  ")
        {
            m_userIsGuesser = true;
            GetWordFromUser();
        }

        for (uint32_t i = 0; i < m_wordToBeGuessed.size(); i++)
        {
            m_currentGuessOfWord.push_back('_');
        }

        UpdateGameInfo();
    }

    void Hangman::UpdateGameInfo()
    {
        m_gameInfo.m_hangmanGameInfo = {
            .m_incorrectGuesses = m_incorrectGuesses,
            .m_computerSpeedName = m_computerSpeedName,
            .m_currentGuessOfWord = m_currentGuessOfWord,
            .m_playerCount = m_playerCount,
            .m_wordToBeGuessed = m_wordToBeGuessed,
            .m_errorCount = m_errorCount,
            .m_turnCount = m_turnCount,
            .m_currentGuess = m_currentGuess};
    }

    bool Hangman::IsGameOver()
    {
        if (m_errorCount == Globals::G_HANGMAN_MAXIMUM_ERROR_COUNT)
        {
            m_hasWinner = true;
            return m_hasWinner;
        }

        for (uint32_t i = 0; i < m_wordToBeGuessed.size(); i++)
        {
            if (m_wordToBeGuessed[i] != m_currentGuessOfWord[i])
            {
                return false;
            }
        }

        m_hasWinner = true;
        return m_hasWinner;
    }

    void Hangman::ToggleCurrentPlayer() {}

    bool Hangman::IsCurrentTurnUsers()
    {
        return m_userIsGuesser;
    }

    void Hangman::ExecuteUserCommand()
    {
        uint32_t keyPress = 0;
        uint32_t currentSelection = 0;

        while (true)
        {
            m_gameInfo.m_hangmanGameInfo.m_currentGuess = m_commandsRemaining[currentSelection];

            Terminal::PrintOutput(m_pageBuilder.GetUserCommandPage(m_gameInfo));

            keyPress = Terminal::GetNextKeyPress();

            if (keyPress == Globals::G_QUIT_KEY)
            {
                Terminal::GetUserChoiceFromQuitMenus(m_pageBuilder.GetQuitOptionSelectionPage());
                continue;
            }

            if (keyPress == Globals::G_ENTER_KEY)
            {
                ExecuteGeneralCommand(m_commandsRemaining[currentSelection]);
                return;
            }

            if (keyPress == Globals::G_UP_ARROW_KEY)
            {
                currentSelection == 0 ? currentSelection = m_commandsRemaining.size() - 1 : --currentSelection;
            }

            else if (keyPress == Globals::G_DOWN_ARROW_KEY)
            {
                currentSelection == (m_commandsRemaining.size() - 1) ? currentSelection = 0 : ++currentSelection;
            }

            else
            {
                auto commandFindLocation = Globals::ImplementStdRangesFind(m_commandsRemaining.begin(), m_commandsRemaining.end(), keyPress - Globals::G_HANGMAN_KEY_PRESS_CHAR_OFFSET);

                if (commandFindLocation != m_commandsRemaining.end())
                {
                    currentSelection = static_cast<uint32_t>(std::distance(m_commandsRemaining.begin(), commandFindLocation));
                }
            }
        }
    }

    void Hangman::ExecuteComputerCommand()
    {
        Terminal::PrintOutput(m_pageBuilder.GetComputerCommandPage(m_gameInfo));

        if (m_computerSpeed != 0)
        {
            std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(m_computerSpeed));
        }

        const char COMPUTER_COMMAND = m_commandsRemaining[m_randomNumberGenerator() % m_commandsRemaining.size()];

        ExecuteGeneralCommand(COMPUTER_COMMAND);
    }

    void Hangman::GameOver()
    {
        Terminal::GetUserChoiceFromGameOverMenu(m_pageBuilder.GetGameOverPage(m_gameInfo), m_pageBuilder.GetQuitOptionSelectionPage());
    }

    void Hangman::RestartGame()
    {
        m_saveGameSettings = true;
    }

    void Hangman::ResetGame()
    {
        m_saveGameSettings = false;
        m_hasSavedGameSettings = false;
    }

    void Hangman::GetPlayerCount()
    {
        UpdateGameInfo();

        const std::vector<std::string> MENUS = m_pageBuilder.GetPlayerCountOptionSelectionGamePages(m_gameInfo);
        const std::vector<std::string> QUIT_MENUS = m_pageBuilder.GetQuitOptionSelectionPage();
        m_playerCount = std::to_string(Terminal::GetUserChoiceFromGameMenus(MENUS, QUIT_MENUS)) + "  ";
    }

    void Hangman::GetUserPlayerChoice()
    {
        UpdateGameInfo();

        const std::vector<std::string> MENUS = m_pageBuilder.GetUserPlayerChoiceOptionSelectionGamePages(m_gameInfo);
        const std::vector<std::string> QUIT_MENUS = m_pageBuilder.GetQuitOptionSelectionPage();
        Terminal::GetUserChoiceFromGameMenus(MENUS, QUIT_MENUS) == 0 ? m_userIsGuesser = true : m_userIsGuesser = false;
    }

    void Hangman::GetComputerSpeed()
    {
        UpdateGameInfo();

        const std::vector<std::string> MENUS = m_pageBuilder.GetComputerSpeedOptionSelectionGamePages(m_gameInfo);
        const std::vector<std::string> QUIT_MENUS = m_pageBuilder.GetQuitOptionSelectionPage();
        m_computerSpeed = Terminal::GetUserChoiceFromGameMenus(MENUS, QUIT_MENUS);

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

    void Hangman::GetWordFromUser()
    {
        UpdateGameInfo();

        const std::string OUTPUT = m_pageBuilder.GetPageWithMessage(m_gameInfo, "Please enter the word to be guessed:");

        std::string input;

        while (true)
        {
            Terminal::PrintOutput(OUTPUT);

            Terminal::SetCursorPosition({Globals::G_HANGMAN_GET_WORD_FROM_USER_COLUMN, Globals::G_HANGMAN_USER_INPUT_ROW});

            std::getline(std::cin, input);

            if (input[0] == Globals::G_QUIT_KEY)
            {
                Terminal::GetUserChoiceFromQuitMenus(m_pageBuilder.GetQuitOptionSelectionPage());
                continue;
            }

            if (input.size() < Globals::G_HANGMAN_MINIMUM_WORD_SIZE || input.size() > Globals::G_HANGMAN_MAXIMUM_WORD_SIZE)
            {
                continue;
            }

            // Capitalise word
            std::ranges::transform(input.begin(), input.end(), input.begin(), ::toupper, {});

            if (std::regex_match(input, std::regex("^[A-Za-z]+$")))
            {
                m_wordToBeGuessed = input;
                return;
            }
        }
    }

    void Hangman::GetWordFromComputer()
    {
        m_wordToBeGuessed = Globals::G_HANGMAN_COMPUTER_WORDS.at(m_randomNumberGenerator() % Globals::G_HANGMAN_COMPUTER_WORDS.size());
    }

    void Hangman::ExecuteGeneralCommand(const char& p_guess)
    {
        bool isGuessCorrect = false;
        for (uint32_t i = 0; i < m_wordToBeGuessed.size(); i++)
        {
            if (m_wordToBeGuessed[i] == p_guess)
            {
                isGuessCorrect = true;
                m_currentGuessOfWord[i] = p_guess;
            }
        }

        if (!isGuessCorrect)
        {
            m_incorrectGuesses.push_back(p_guess);
            m_errorCount++;
        }

        m_commandsRemaining.erase(Globals::ImplementStdRangesFind(m_commandsRemaining.begin(), m_commandsRemaining.end(), p_guess));
        m_turnCount++;
    }
}
