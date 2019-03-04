#ifndef OPTIONAL_REST_H
#define OPTIONAL_REST_H

#include <mutex>
#include <string>

namespace Optional {

class Rest
{
public:
    Rest();
    ~Rest();

    std::string post(std::string post_url, std::string header, std::string post_data, bool& valid_data_out);

private:
    std::mutex curl_lock;

    static size_t curl_post_callback(void* contents, size_t size, size_t nmemb, void* return_data);
};

}

#endif // REST_H
