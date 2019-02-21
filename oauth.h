#ifndef OPTIONAL_OAUTH_H
#define OPTIONAL_OAUTH_H

#include <string>

namespace Optional {

/**
 * @brief Handles OAuth credentials for logging into app and accessing trading account.
 */
class OAuth
{
public:
    OAuth(std::string oauth_uid, std::string redirect_uri);

private:
    OAuth() = delete;
};

}

#endif // OAUTH_H
