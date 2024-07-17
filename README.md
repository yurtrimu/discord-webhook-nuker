# 🟩 Discord Webhook Nuker 🟩 <a href="https://github.com/yurtrimu/discord-webhook-nuker/actions/workflows/main.yml"><img src="https://github.com/yurtrimu/discord-webhook-nuker/actions/workflows/main.yml/badge.svg" alt="Working"></a>

## **Discord Webhook Nuker is for nuking a webhook.**

# Questions?
### - **I gladly answer your questions on the [discord server](https://discord.gg/QBhFd2aK4r).**

## Usage

```c++
#include "webhook.hpp"

int main()
{
    curl_global_init(CURL_GLOBAL_ALL);

    // nuke_webhook(
    // webhook_url, 
    // webhook_name,
    // nuke_string,
    // message_count,    - OPTIONAL  
    // populate_string,  - OPTIONAL  send message_count messages of duplicated nuke_string
    //                                       ((2000 / nuke_string.length()) * message_count) times
    // avatar_url,       - OPTIONAL  a nuke image has been hardcoded haha
    // )

    nuke_webhook("URL", "NUKED_BY_YURTRIMU", "nukedNUKED", true, 5);

    curl_global_cleanup();
}
```

## Example.png
![alt text](https://github.com/yurtrimu/discord-webhook-nuker/blob/main/Example.png?raw=true)

## Operating System
- **Below Windows 7 - 🟦 Untested**
- **Windows 7 - 🟦 Untested**
- **Windows 10 - 🟩 Working**
- **Windows 11 - 🟦 Untested**
- **Mac OS - 🟦 Untested**
- **Linux - 🟦 Untested**

## Requirements

**You need to have the OpenSSL library installed and linked to your compiler.**

- You could download the OpenSSL library from [OpenSSL website](https://www.openssl.org/source/).

**You need to have the CURL library installed and linked to your compiler ( _ STATIC _).**

- You could download the CURL library from [CURL website](https://curl.se/download.html).

## Linker

- **libcrypto.lib**
- **libssl.lib**
- **openssl.lib**
- **libcurl_a.lib**
- **crypt32.lib**
- **ws2_32.lib**
- **wldap32.lib**
- **normaliz.lib**

## Compiling

- **Build - 🟦 Untested**
- **Release - 🟩 Working**
- **C++11  - 🟦 Untested**
- **C++14  - 🟩 Working**
- **C++17 - 🟩 Working**
- **C++20 - 🟩 Working**

## Contributing

**Pull requests are welcome.**

## Legal Disclaimer
🟥 **The content provided is for educational and informational purposes only.** 🟥

