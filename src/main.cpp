#include "webhook.hpp"

int main()
{
    curl_global_init(CURL_GLOBAL_ALL);

    // nuke_webhook(
    // webhook_url, 
    // webhook_name,
    // nuke_string,
    // message_count,    - OPTIONAL  
    // populate_string,  - OPTIONAL  send message_count messages of duplicated nuke_string ((2000 / nuke_string.length()) * message_count) times
    // avatar_url,       - OPTIONAL  a nuke image has been hardcoded haha
    // )

    nuke_webhook("URL", "NUKED_BY_YURTRIMU", "nukedNUKED", true, 5);

    curl_global_cleanup();
}