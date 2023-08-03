//
// Created by pierr on 25/07/2023.
//

#include "main.hpp"

#include "include/SaveFile/WebUtils.h"
#include "libcurl/shared/curl.h"
#include "libcurl/shared/easy.h"

namespace WebUtils {

    //https://stackoverflow.com/a/55660581
    string query_encode(string s)
    {
        string ret;

        #define IS_BETWEEN(ch, low, high) ((ch) >= (low) && (ch) <= (high))
        #define IS_ALPHA(ch) (IS_BETWEEN(ch, 'A', 'Z') || IS_BETWEEN(ch, 'a', 'z'))
        #define IS_DIGIT(ch) IS_BETWEEN(ch, '0', '9')
        #define IS_HEXDIG(ch) (IS_DIGIT(ch) || IS_BETWEEN(ch, 'A', 'F') || IS_BETWEEN(ch, 'a', 'f'))

        for(size_t i = 0; i < s.size();)
        {
            char ch = s[i++];

            if (IS_ALPHA(ch) || IS_DIGIT(ch))
            {
                ret += ch;
            }
            else if ((ch == '%') && IS_HEXDIG(s[i+0]) && IS_HEXDIG(s[i+1]))
            {
                ret += s.substr(i-1, 3);
                i += 2;
            }
            else
            {
                switch (ch)
                {
                    case '-':
                    case '.':
                    case '_':
                    case '~':
                    case '!':
                    case '$':
                    case '&':
                    case '\'':
                    case '(':
                    case ')':
                    case '*':
                    case '+':
                    case ',':
                    case ';':
                    case '=':
                    case ':':
                    case '@':
                    case '/':
                    case '?':
                    case '[':
                    case ']':
                        ret += ch;
                        break;

                    default:
                    {
                        static const char hex[] = "0123456789ABCDEF";
                        char pct[] = "%  ";
                        pct[1] = hex[(ch >> 4) & 0xF];
                        pct[2] = hex[ch & 0xF];
                        ret.append(pct, 3);
                        break;
                    }
                }
            }
        }

        return ret;
    }



    /*std::size_t CurlWrite_CallbackFunc_File(void *ptr, size_t size, size_t nmemb, void *stream)
    {
        size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
        return written;
    }*/

    size_t CurlWrite_CallbackFunc_StdString(void* contents, size_t size, size_t nmemb, string* s)
    {
        size_t newLength = size * nmemb;
        try
        {
            s->append((char*)contents, newLength);
        }
        catch (std::bad_alloc& e)
        {
            //handle memory problem
            getLogger().critical("Reponse Bad Allocation");
            return 0;
        }
        //getLogger().info("response function : %s", s->c_str());
        return newLength;
    }

    int Ping(string url) {
        CURL *curl;
        CURLcode res;
        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();
        if(curl)
        {
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
            curl_easy_setopt(curl, CURLOPT_URL, query_encode(url).c_str());
            curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
            curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            return res;
        }
        return -1;
    }

    bool isWifiOn() {
        return Ping(GOOGLE_URL) == CURLE_OK;
    }

    bool canFindServer() {
        return Ping(API_URL) == CURLE_OK;
    }

    int PostJSonDrive(string token, string data) {
        CURLcode cc;

        getLogger().info("Buffer : %s", data.c_str());
        std::string authorization = "Authorization: Bearer " + token;

        std::string response;
        std::string header;
        curl_off_t postsize = (curl_off_t) strlen(data.c_str());

        curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: */*");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, authorization.c_str());

        CURL *pcurl = curl_easy_init();
        curl_easy_setopt(pcurl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(pcurl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(pcurl, CURLOPT_URL, "https://www.googleapis.com/upload/drive/v3/files?uploadType=media");
        curl_easy_setopt(pcurl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(pcurl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(pcurl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(pcurl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(pcurl, CURLOPT_POSTFIELDSIZE_LARGE, postsize);
        curl_easy_setopt(pcurl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(pcurl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(pcurl, CURLOPT_HEADER, 1);
        curl_easy_setopt(pcurl, CURLOPT_HEADERDATA, &header);
        curl_easy_setopt(pcurl, CURLOPT_TIMEOUT, TIMEOUT);

        cc = curl_easy_perform(pcurl);
        /* Check for errors */
        if (cc != CURLE_OK) {
            getLogger().critical("curl_easy_perform() failed: %u: %s", cc, curl_easy_strerror(cc));
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(pcurl);

        return cc;
    }


    string extractInformation(size_t p, string key, const string& theEntireString)
    {
        string s = "\"" + key +"\":\"";
        auto p1 = theEntireString.find(s);
        if (string::npos != p1)
            p1 += s.size();
        auto p2 = theEntireString.find_first_of('\"',p1);
        if (string::npos != p2)
            return theEntireString.substr(p1,p2-p1);
        return "";
    }

    string ConnectServer(bool& connected, string url, string OTP, bool debug)
    {
        CURLcode cc;

        string body = "{\"query\":\"query {externalTasksByOtp(otp: \\\"" + OTP + "\\\"){id otp result_step_id}}\"}";
        std::string response;
        std::string header;
        curl_off_t postsize = (curl_off_t) strlen(body.c_str());

        curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: */*");
        headers = curl_slist_append(headers, "Content-Type: application/json");

        CURL *pcurl = curl_easy_init();
        curl_easy_setopt(pcurl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(pcurl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(pcurl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(pcurl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(pcurl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(pcurl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(pcurl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(pcurl, CURLOPT_POSTFIELDSIZE_LARGE, postsize);
        curl_easy_setopt(pcurl, CURLOPT_POSTFIELDS, body.c_str());
        curl_easy_setopt(pcurl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(pcurl, CURLOPT_HEADER, 1);
        curl_easy_setopt(pcurl, CURLOPT_HEADERDATA, &header);
        curl_easy_setopt(pcurl, CURLOPT_TIMEOUT, TIMEOUT);

        cc = curl_easy_perform(pcurl);
        /* Check for errors */
        if (cc != CURLE_OK) {
            getLogger().critical("curl_easy_perform() failed: %u: %s", cc, curl_easy_strerror(cc));
        }
        if(debug) {
            getLogger().info("Query sent : %s", body.c_str());
            getLogger().info("Server connexion response : %s", response.c_str());
        }

        connected = cc == CURLE_OK;

        // {"data":{"externalTasksByOtp":[{"id":"ed4b05d7-95f4-46d5-9d74-b4485e92bc9b","otp":"708735","result_step_id":"403529e7-f5a0-43cf-8fda-42fe76c12786"}]}}

        curl_slist_free_all(headers);
        curl_easy_cleanup(pcurl);

        return extractInformation(0,"result_step_id", response);
    }

    std::thread PostJSONAsync(string url, string result_step_id, string data, function<void(long, string)> const &finished, bool debug) {
        return PostJSONAsync(string(url), string(result_step_id), string(data), TIMEOUT, finished, debug);
    }

    std::thread PostJSONAsync(const string &url, string result_step_id, string data, long timeout, function<void(long, string)> const &finished, bool debug) {
        std::thread t(
                [url, timeout, result_step_id, data, finished, debug] {
                    string response;

                    string body = "{\"query\":\"mutation updateExternalTask {updateExternalTask(input: { id: \\\"" + result_step_id + "\\\", data: \\\"" + data + "\\\" }) {id}}\"}";
                    curl_off_t postSize = (curl_off_t) strlen(body.c_str());

                    struct curl_slist *headers = NULL;
                    headers = curl_slist_append(headers, "Accept: */*");
                    headers = curl_slist_append(headers, "Content-Type: application/json");

                    CURL *curl = curl_easy_init();
                    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
                    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
                    curl_easy_setopt(curl, CURLOPT_URL, query_encode(url).c_str());
                    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
                    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
                    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE, postSize);
                    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);


                    curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);

                    // Follow HTTP redirects if necessary.
                    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);


                    CURLcode res = curl_easy_perform(curl);
                    /* Check for errors */
                    if (res != CURLE_OK) {
                        getLogger().critical("curl_easy_perform() failed: %u: %s", res, curl_easy_strerror(res));
                    }
                    long httpCode(0);
                    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);


                    if(debug) {
                        getLogger().info("Query sent : %s", body.c_str());
                        getLogger().info("Data sending response : %s", response.c_str());
                    }

                    curl_slist_free_all(headers);
                    curl_easy_cleanup(curl);

                    finished(httpCode, response);
                }
        );
        t.detach();
        return t;
    }
}
