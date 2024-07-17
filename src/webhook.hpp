#pragma once

#include "utils//curlpost.hpp"

#include "json/json.hpp"

using json = nlohmann::json;

struct discord_webhook {
    std::string url;
    std::string name;
    std::string avatar;
    std::string message;
};

static bool delete_webhook(std::string &url) {

    if (curl_delete(url, std::vector<std::string>())) {
        printf("Webhook successfully deleted.\n");
    }
}

static bool send_webhook(struct discord_webhook &webhook, std::string &response) {
    std::vector<std::string> chunks;

    size_t length = webhook.message.length();
    for (size_t i = 0; i < length; i += 2000) {
        chunks.push_back(webhook.message.substr(i, 2000));
    }

    json original_json;

    if (!webhook.avatar.empty()) {
        original_json["avatar_url"] = webhook.avatar;
    }

    if (!webhook.name.empty()) {
        original_json["username"] = webhook.name;
    }

    if (chunks.size() == 0) {
        return false;
    }

    std::vector<int> return_codes;

    for (const std::string &message : chunks) {

        json copied_json = original_json;
        copied_json["content"] = message;

        std::string post_data = copied_json.dump();

        std::vector<std::string> headers = { "Content-Type: application/json" };

        if (curl_post(webhook.url, headers, post_data, response)) {
            return_codes.push_back(true);
        }
        else {
            return_codes.push_back(false);
        }
    }

    for (const int &code : return_codes) {
        if (code != true) {
            return false;
        }
    }

    return true;
}

static bool nuke_webhook(std::string nuke_url, std::string nuke_name, std::string nuke_string, bool generate_str = true, int nuke_message_count = 5, std::string avatar_url = "") {
    struct discord_webhook webhook;
    webhook.name = nuke_name;
    webhook.url = nuke_url;

    if (!avatar_url.empty()) {
        webhook.avatar = "https://cdn.discordapp.com/attachments/1262789409917632522/1263251066653511840/2734864.png?ex=66998dbc&is=66983c3c&hm=938f74fbc7f6484ee59ba46c97acf8d398fdbedb87a2e992e8ef163e82618bf6&";
    }
    else {
        webhook.avatar = avatar_url;
    }

    std::string nuke_string_new = nuke_string;
    if (generate_str) {

        nuke_string_new.clear();
        for (int i = 0; i < (2000 / nuke_string.length()) * nuke_message_count; i++) {

            nuke_string_new += nuke_string;
        }
    }

    webhook.message = nuke_string_new;

    std::string response;

    if (send_webhook(webhook, response)) {
        printf("Webhook successfully sent %zu length of data.\n", webhook.message.length());
    }

    delete_webhook(nuke_url);
}