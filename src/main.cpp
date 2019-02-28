#include "oauth.h"
#include "account.h"
#include "display.h"

#include <iostream>
#include <string>

using namespace std;

int main(){
    Optional::OAuth oauth("TEUX0001", "https%3A%2F%2Flocalhost");
    string result;

    cout << "Go to this url, authenticate, and paste result below: " << oauth.generate_authentication_url() << endl;
    cout << ": ";
    cin >> result;

    oauth.accept_authentication_code(result);
    oauth.generate_refresh_token();

    return 0;
}
