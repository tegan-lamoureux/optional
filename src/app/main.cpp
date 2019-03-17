#include "account.h"
#include "display.h"

#include <iostream>
#include <string>

using namespace std;

void handle_failed_authentication(Optional::Account& account, std::string oauth_uid);

int main(int argc, char* argv[]){
    string account_number;
    string oauth_uid;

    if (argc < 3) {
        cout << "Please enter your account number: ";
        cin >> account_number;
        cout << "Please enter your oauth user id: ";
        cin >> oauth_uid;
    }
    else {
        account_number = argv[1];
        oauth_uid = argv[2];
    }

    Optional::Account account(account_number, oauth_uid);

    if (account.get_authorization_status() != Optional::OAuthStatus::Valid) {
        handle_failed_authentication(account, oauth_uid);
    }

    Optional::Display display(account);

    display.run_loop();

    return 0;
}

void handle_failed_authentication(Optional::Account& account, std::string oauth_uid) {
    // Loading refresh from disk failed, we need to manually get a new token.
    Optional::OAuth oauth(oauth_uid, "https://localhost", account.get_rest_interface());
    std::string code = "";

    cout << "Failed to load valid refresh token from disk. Please manually reauthenticate." << endl;
    cout << "Steps:" << endl;
    cout << "1. Go to this url: " << oauth.generate_authentication_url() << endl;
    cout << "2. Authenticate with your TD Ameritrade account to approve the app." << endl;
    cout << "3. The result will be a code in your address bar and a failed page load @ https://localhost. Paste entire address bar contents below: " << endl;
    cout << ": ";

    cin >> code;

    bool code_accepted = oauth.accept_authentication_code(code);
    Optional::OAuthStatus token_generation_status = oauth.generate_tokens();

    if (code_accepted && token_generation_status == Optional::OAuthStatus::Valid) {
        cout << endl << "Successfully validated account! Please restart application." << endl;
    }
    else {
        cout << endl << "Error loading account. Please check credentials and developer application authentication and try again." << endl;
    }

    cout << " Press enter to quit.";
    cin.ignore();
}
