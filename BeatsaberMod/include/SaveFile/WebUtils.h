//
// Created by pierr on 25/07/2023.
//

#ifndef BEATSABER_ANALYSIS_MOD_WEBUTILS_H
#define BEATSABER_ANALYSIS_MOD_WEBUTILS_H

#include "beatsaber-hook/shared/config/rapidjson-utils.hpp"

using namespace std;

#define TIMEOUT 60

#define API_URL "https://projet-staps.cleverapps.io/graphql"
#define GOOGLE_URL "https://www.google.com/"

namespace WebUtils {

    int Ping(string url);
    bool isWifiOn();
    bool canFindServer();


    int PostJSonDrive(string token, string data);
    string ConnectServer(bool& connected, string url, string OTP, bool debug=false);
    std::thread PostJSONAsync(string url, string result_step_id, string data, function<void(long, string)> const& finished, bool debug=false);
    std::thread PostJSONAsync(const string& url, string result_step_id, string data, long timeout, function<void(long, string)> const& finished, bool debug=false);
};


#endif //BEATSABER_ANALYSIS_MOD_WEBUTILS_H
