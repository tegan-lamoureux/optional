#include "account.h"
#include "display.h"
#include "oauth.h"

#include <string>
#include <iostream>

using namespace std;
int main(){
    // I should be writing unit tests.
    Optional::OAuth oauth("ASD123", "https://localhost");
    std::string test = "https://localhost/?code=asdasd12312332";

    oauth.accept_authentication_code(test);

    cout << oauth.debug();

	return 0;
}
