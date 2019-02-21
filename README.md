## optional 

A fast and simple terminal interface to the TD Ameritrade APIs for stock and options trading, written in ncurses and c++. 

#### Building
* Clone and cd into `optional`.
* `mkdir build && cd build`
* `cmake ../ && make`

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
  * For OAuth User ID, enter some unique alphanumeric ID. Ex: `APP0001`.
  * Put a description. Anything. It doesn't matter.
3. Once your app is created, go to the following URL to authenticate the app with your trading account.
  * `https://auth.tdameritrade.com/auth?response_type=code&redirect_uri=https%3A%2F%2Flocalhost&client_id=OAUTH_USER_ID@AMER.OAUTHAP`
  * **NOTE:** You'll need to change OAUTH_USER_ID to whatever you set your OAuth User ID to in step 2. For example, if you used APP0001, [you'll go to this url](https://auth.tdameritrade.com/auth?response_type=code&redirect_uri=https%3A%2F%2Flocalhost&client_id=APP0001@AMER.OAUTHAP).
  * Sign in with your trading account login. **Not the Developer account we just made.**
  * You'll be redirected to a dead page. This is fine. You need to copy what is in the address bar. This is your OAuth key. Save it somewhere safe in a text file. It should look like `https://localhost/?code=<a whole lot of characters here>`
  
bleh from there just follow the rest of: https://developer.tdameritrade.com/content/simple-auth-local-apps, I'm going to automate this as part of the startup anyway.
