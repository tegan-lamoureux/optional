#include "oauth.h"
#include <curl/curl.h>
#include <cstring>

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
    curl_global_cleanup();

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

std::string Optional::OAuth::get_authentication_code() {
    return this->authentication_code;
}

std::string Optional::OAuth::generate_refresh_token() {
    CURL *curl = curl_easy_init();
    CURLcode res;
	
    if(curl && this->authentication_code.empty() == false) { // FIXME: Change to enum unauthenticated.
        struct WriteThis wt;
        struct weird_string ws;

        std::string post_data = std::string("grant_type=authorization_code")
                + std::string("&refresh_token=")
                + std::string("&access_type=offline")
                + std::string("&code=")
                + this->authentication_code
                + std::string("&client_id=")
                + this->oauth_uid
                + std::string("&redirect_uri=")
                + this->redirect_uri;

        wt.readptr = post_data.c_str();
        wt.sizeleft = post_data.length();

        curl_easy_setopt(curl, CURLOPT_URL, this->access_token_post_url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, this->read_callback);
        curl_easy_setopt(curl, CURLOPT_READDATA, &wt);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ws);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)wt.sizeleft);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
          fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else {
            fprintf(stderr, "success! : %s\n");
        }

        /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str()); // FIXME with real data
 
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
	    
        /* Check for errors */
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else {
            fprintf(stderr, "OMG IT WORKED\n", curl_easy_strerror(res));
            fprintf(stderr, "data: %s\n", ws.ptr);
        }

        // TODO: Figure out how to get resulting code back? Does a post return anything? Or do I need to do a corresponding get? HOW DOES THIS WORK

        curl_easy_cleanup(curl);
    }

    return this->refresh_token;
}

std::string Optional::OAuth::generate_access_token() {

}

std::string Optional::OAuth::debug()
{
    return this->authentication_code;
}

size_t Optional::OAuth::read_callback(void *dest, size_t size, size_t nmemb, void *userp)
{
  struct WriteThis *wt = (struct WriteThis *)userp;
  size_t buffer_size = size*nmemb;

  if(wt->sizeleft) {
    /* copy as much as possible from the source to the destination */
    size_t copy_this_much = wt->sizeleft;
    if(copy_this_much > buffer_size)
      copy_this_much = buffer_size;
    memcpy(dest, wt->readptr, copy_this_much);

    wt->readptr += copy_this_much;
    wt->sizeleft -= copy_this_much;
    return copy_this_much; /* we copied this many bytes */
  }

  return 0; /* no more data left to deliver */
}

size_t Optional::OAuth::writefunc(void *ptr, size_t size, size_t nmemb, struct weird_string *s)
{
  size_t new_len = s->len + size*nmemb;
  s->ptr = static_cast<char*>(realloc(s->ptr, new_len+1));
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}
