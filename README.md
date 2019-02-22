## optional 

A fast and simple c++ interface to the TD Ameritrade APIs for stock and options trading.

#### Build Requirements
* boost
* curl
* ncurses

#### Building
* Clone and cd into `optional`.
* `mkdir build && cd build`
* `cmake ../ && make`

#### Dev TODO
* add gtest and switch to tdd. COME ON, TEGAN ._.
* uhh, maybe use curl instead of boost.beast? (if I only need get/put)

***

#### What this is. (Or will be. It's in progress.)
It's really two main components:
1. A c++ back-end for algorithmic trading through TD Ameritrade (paper money or live trading).
  * Goal is a modular & fast interface that allows for quick backtesting and algorithm setup.
2. A simple ncurses frontend to provide a basic terminal GUI for order placement/status, account stats, etc.
  * Display list of current positions. 
  * Display list of current orders. 
  * Display balances (Cash & Sweep, Net Liq, Buying Power).
  * Sell and buy options/stock through single line input.

These will become more distinct as the project grows, right now I'll be happy getting a post to the api with the correct oauth token.

#### More Info
User guide (just a text dump at this point tbh) [is on the wiki](https://github.com/tegan-lamoureux/optional/wiki).
