# Hangman Test Plan

## Inital Page

1. Starting from the main menu with coloured output (i.e. step 1 from
   [Toggling ANSI Colour Escape Codes](./Main-Menu-Test-Plan.md#toggling-ansi-colour-escape-codes) section in the
   [Main Menu Test Plan](./Main-Menu-Test-Plan.md)). Select the `Hangman` option and press `Enter` on Windows or enter "e" on
   macOS/Linux:

    ```text
    ╔══════════════════════════════════════════════════════════════╗
    ║                            Hangman                           ║
    ╚══════════════════════════════════════════════════════════════╝
    ╔══════════════════════════════════════════════════════════════╗
    ║                                                              ║
    ║                                                              ║
    ║                    # of Players = N/A                        ║
    ║                                                              ║
    ║                    Computer Speed = N/A                      ║
    ║                                                              ║
    ║                                                              ║
    ║                                                              ║
    ║                                                              ║
    ║ Please select the number of players:                         ║
    ║ > 0                                                          ║
    ║   1                                                          ║
    ║   2                                                          ║
    ║                                                              ║
    ╚══════════════════════════════════════════════════════════════╝
    ╔══════════════════════════════════════════════════════════════╗
    ║                     q = to show quit menu                    ║
    ╚══════════════════════════════════════════════════════════════╝
    ```

    > [!NOTE]
    > The output should be coloured.

## Zero Players

player count - confirm option selection wraps up and down
zero player

computer speed - confirm option selection wraps up and down
with speed instant

repeat with fast and slow options

## One Player

player count - confirm option selection wraps up and down
one player

player choice - confirm option selection wraps up and down
Do with as guesser

computer speed - confirm option selection wraps up and down
with speed instant

Repeat with fast and slow options

Repeat all as word setter

## Two Players

player count - confirm option selection wraps up and down
two player

## Restart and Reset Game

finish game (zero player game?) and hit restart button

finish game (zero player game?) and hit reset button and finish game

## Quit Menu

restart game

reset game

quit game goes to main menu (and return to game resets it)

quit to homepage (and return to game resets it)

quit program

### Player Count Option Screen

Do above templated options on first time running game (different outputs)

Do above templated options after playing games once

### Player Choice Option Screen

Do above templated options on first time running game (different outputs)

Do above templated options after playing games once

### Computer Speed Option Screen

Do above templated options on first time running game (different outputs)

Do above templated options after playing games once

### User Word To Be Guessed Screen

Do above templated options

### User Guess Screen

Do above templated options

### Game Over Screen

Do above templated options

## Toggled ANSI Colour Escape Codes

Toggle to "no" on homepage and repeat all previous steps

<!-- TODO: reference to macOS/Linux controls on all steps -->