#include "oauth.h"
#include <curl/curl.h>

// FIXME: Change these namespaces to split the frontend and backend? Maybe. Check.

Optional::OAuth::OAuth(std::string oauth_uid_in, std::string redirect_uri_in)
    : authorization_status(Unauthenticated)
    , oauth_uid(oauth_uid_in)
    , redirect_uri(redirect_uri_in)
    , authentication_code("")
    , refresh_token("")
    , access_token("")
{
    curl_global_init(CURL_GLOBAL_ALL);
    
    if (this->redirect_uri.empty()) {
        this->redirect_uri = "https://null_value";
    }
    if (this->oauth_uid.empty()) {
        this->oauth_uid = "null_value";
    }
}

Optional::OAuth::~OAuth() {
    /* always cleanup */ 
    curl_easy_cleanup(curl);
}

std::string Optional::OAuth::generate_authentication_url() {
    return std::string("https://auth.tdameritrade.com/auth?response_type=code&redirect_uri=")
            + this->redirect_uri
            + std::string("&client_id=")
            + this->oauth_uid
            + std::string("@AMER.OAUTHAP");
}

bool Optional::OAuth::accept_authentication_code(std::string code) {
    bool valid = false;
    const std::string search_term = "?code=";

    if (code.empty() == false) {
        auto location = code.find(search_term);

        if (location != std::string::npos && (location + search_term.length()) < code.length()) {
            this->authentication_code = code.substr(location + search_term.length());
            valid = true;
        }
    }

    return valid;
}

std::string Optional::get_authentication_code() {
    return this->authentication_code;
}

std::string Optional::OAuth::generate_refresh_token() {
    // left off here. post to this->access_token_post_url with the given
    // authentication code and user info. same for access token.
	
    CURL *curl = curl_easy_init();
    CURLcode res;
	
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, this->access_token_post_url);
	
        /* Now specify the POST data */ 
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "field1=datahere&field2=moredata"); // FIXME with real data
 
        /* Perform the request, res will get the return code */ 
        res = curl_easy_perform(curl);
	    
        /* Check for errors */ 
        if(res != CURLE_OK) {
            //fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res)); // FIXME: err here, probs with status enum
	}
	    
	// TODO: Figure out how to get resulting code back? Does a post return anything? Or do I need to do a corresponding get? HOW DOES THIS WORK
    }
}

std::string Optional::OAuth::generate_access_token() {

}

std::string Optional::OAuth::debug()
{
    return this->authentication_code;
}
