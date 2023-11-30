#include <string>
#include <vector>
#include <map>

#pragma once

class Parser
{
private:
    const std::string WHITESPACE = " \n\t\r\f\v";

    std::string _url;

    std::string _protocol;
    std::string _user;
    std::string _password;
    std::string _host;
    std::string _port;
    std::string _path;

    struct info_struct {
            std::string part;
            std::string description;
        };
    std::vector<info_struct> info_vect;


    std::string trim_url(std::string& str);
    size_t defaultParse();
    void parseWithDetails();

    void ftp_parse();
    void http_parse(size_t offset);
    void gopher_parse();
    void mailto_parse();
    void news_parse(size_t offset);
    void nntp_parse(size_t offset);
    void telnet_parse();
    void wais_parse(size_t offset);
    void file_parse();
    void prospero_parse(size_t offset);


public:
    Parser(std::string str);
    void outlineInfo();
    void outlineDefaultInfo();

    std::vector<info_struct> GetInfoVect();
    std::string GetParamValues();
    std::string GetStoredURL();
};