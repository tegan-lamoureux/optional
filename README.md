## optional 

A fast and simple c++ interface to the TD Ameritrade APIs for stock and options trading.

***

#### What this is. (It's in progress.)
Two main components:
1. A c++ back-end for algorithmic trading through TD Ameritrade (paper money or live trading).
  * Goal is a simple interface that allows for quick backtesting and algorithm setup.
2. A simple ncurses frontend to provide a basic terminal GUI for order placement/status, account stats, etc.
  * Display list of current positions. 
  * Display list of current orders. 
  * Display balances (Cash & Sweep, Net Liq, Buying Power).
  * Sell and buy options/stock through simple form input.
  * Display trades/ticks for symbol.

Backend implemented as a static library. Main app links against it, as an example of how an automated trading program could do the same.

***

#### Build Requirements
* cmake
* curl
* ncurses

#### Building
* Clone and cd into `optional`.
* `mkdir build && cd build`
* `cmake ../ && make`

***

#### More Info
User guide (empty, tbd) [is on the wiki](https://github.com/tegan-lamoureux/optional/wiki).
