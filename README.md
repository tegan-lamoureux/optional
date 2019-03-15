## optional 

A fast and simple c++ interface to the TD Ameritrade APIs for stock and options trading.

#### Build Requirements
* curl
* ncurses

#### Building
* Clone and cd into `optional`.
* `mkdir build && cd build`
* `cmake ../ && make`

#### Dev Notes
* doxygen comments.

***

#### What this is. (It's in progress.)
Two main components:
1. A c++ back-end for algorithmic trading through TD Ameritrade (paper money or live trading).
  * Goal is a modular & fast interface that allows for quick backtesting and algorithm setup.
2. A simple ncurses frontend to provide a basic terminal GUI for order placement/status, account stats, etc.
  * Display list of current positions. 
  * Display list of current orders. 
  * Display balances (Cash & Sweep, Net Liq, Buying Power).
  * Sell and buy options/stock through single line input.

Backend implemented as a static library. Main app links against it, as an example of how an automated trading program could do the same.

#### More Info
User guide (emtpy, tbd) [is on the wiki](https://github.com/tegan-lamoureux/optional/wiki).
