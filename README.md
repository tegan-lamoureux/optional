## optional 

A fast and simple terminal interface to the TD Ameritrade APIs for stock and options trading, written in ncurses and c++. 

#### Features (TODO, at this point). 
* Display a chart for a given symbol, input box for days wide and minutes per candlestick. 
* Display list of current positions. 
* Display list of current orders. 
* Display balances (Cash & Sweep, Net Liq, Buying Power).
* Sell and buy options/stock through single line input.

#### Longer term goals:
* Interface for auto-trading a custom algorithm / backtesting strategies.
* Auto-sell/buy at defined limits.
* Quick spreads.
* Alerts.

#### Start of User Guide (OAUTH IS A PAIN):
1. In order to use this application, you'll need a TD Ameritrade Developer Account. 
  * This is free. [Register here.](https://developer.tdameritrade.com/)
2. Once registered, you'll need to make an app. 
  * Under your username in the top right corner, go to 'My Apps' and then '+ Add a New App'.
  * Fill out the App Name. `Optional` works great. ;)
  * Callback URL should be `https://localhost`
  * For OAuth User ID, enter some alphanumeric ID. I've been using `APP0001`.
  * Put a description. Anything. It doesn't matter.
