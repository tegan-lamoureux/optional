## optional 

A fast and simple c++ interface to the TD Ameritrade APIs for stock and options trading.

![here you can see some awful trades i made](https://raw.githubusercontent.com/tegan-lamoureux/tegan-lamoureux.github.io/master/images/static_hosting/optional.png)

***

#### What this is.
Two main components:
1. A c++ back-end for algorithmic trading through TD Ameritrade (paper money or live trading).
  * Goal is a simple interface that allows for quick backtesting and algorithm setup.
  * Note: It's mostly there, although there are likely bugs, and I've continued some development offline. If you're keen on anything not here contact me and let me know.
  
2. A simple ncurses frontend to provide a basic terminal GUI for order placement/status, account stats, etc.
  * Display list of current positions. 
  * Display list of current orders. 
  * Display balances (Cash & Sweep, Net Liq, Buying Power).
  * Show option chains for a symbol.
  * Note: This has largely just turned into a monitoring service for an account. The functionality is mostly in the backend.

Backend implemented as a static library. Main app links against it, as an example of how an automated trading program could do the same.

***

#### Build Requirements
* cmake
* curl development libraries
* ncurses development libraries

#### Building App and Unit Tests (On Linux)
* Clone and cd into `optional`.
* Make a build directory in `optional` folder: `mkdir build && cd build`
* Prepare build files: `cmake ../`
* Build: `make`

***

#### More Info
User guide (empty, tbd) [is on the wiki](https://github.com/tegan-lamoureux/optional/wiki).
