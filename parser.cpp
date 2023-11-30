#include "parser.h"
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <map>

using namespace std;


#pragma region constructor
// constructor
Parser::Parser(string str){
    regex pattern("^[0-9a-zA-Z]+:/{0,2}[^ ~`]+");
    this->_url = trim_url(str);

    // validation
    if (this->_url == "")
    {
        Parser::info_struct structure;
        structure.part = "Message";
        structure.description = "string is empty";
        info_vect.push_back(structure);

        this->_protocol = "none";
        this->_user = "none";
        this->_password = "none";
        this->_host = "none";
        this->_port = "none";
        this->_path = "none";
    }
    // if not empty
    else if (!regex_match(this->_url, pattern))     // not a url
    {
        Parser::info_struct structure;
        structure.part = "Message";
        structure.description = "string is not a URL";
        info_vect.push_back(structure);

        this->_protocol = "undefined";
        this->_user = "none";
        this->_password = "none";
        this->_host = "none";
        this->_port = "none";
        this->_path = "none";
    }
    // if url
    else
    {
        parseWithDetails();
    }
}
#pragma endregion

#pragma region helpful_tools
string Parser::trim_url(string& str)
{
    if (str == "")
    {
        return str;
    }
    else
    {
        size_t startPos = str.find_first_not_of(WHITESPACE);
        size_t endPos = str.find_last_not_of(WHITESPACE);

        size_t start = (startPos == std::string::npos) ? 0 : startPos;
        size_t end = (endPos == std::string::npos) ? str.length()-1 : endPos;
        return str.substr(start, end-start+1);
    }    
}
#pragma endregion

#pragma region get_methods
vector<Parser::info_struct> Parser::GetInfoVect()
{
    return this->info_vect;
}

string Parser::GetParamValues()
{
    string str = "";
    str += this->_url + ", " + this->_protocol + ", " + this->_user + ", " + this->_password + ", " + this->_host + ", " + this->_port + ", " + this->_path;
    return str;
}

std::string Parser::GetStoredURL()
{
    return this->_url;
}
#pragma endregion


#pragma region parsers
size_t Parser::defaultParse()
{
    // main url format: protocol://user:password@host:port/path_or_other
    size_t pos1, pos2, pos3;
    size_t offset = 0;
    string url = this->_url;
    
    pos1 = url.find(':');
    this->_protocol = url.substr(offset, pos1);
    offset = url.find("//", pos1)==(pos1+1) ? pos1+3 : pos1+1;

    // exceptions for mailto and news
    if ((this->_protocol == "mailto") || (this->_protocol == "news"))
    {
        this->_user = "none";
        this->_password = "none";
        this->_host = "none";
        this->_port = "none";
        this->_path = (offset < url.length()) ? url.substr(offset) : "empty";

        return offset;
    }

    pos2 = url.find('@');
    if (pos2 == std::string::npos)   // no "@"
    {
        this->_user = "none";
        this->_password = "none";
    }
    else if (pos2 == offset)    // no info behind offset and "@"
    {
        this->_user = "empty";
        this->_password = "empty";
        offset += 1; 
    }
    else
    {
        pos1 = url.find(':', offset);
        if (pos1 != std::string::npos)
        {
            this->_user = ((pos1 < pos2) && (pos1 != offset)) ? url.substr(offset, pos1-offset) : "empty";
            this->_password = (pos1 < pos2-1) ? url.substr(pos1+1, pos2-pos1-1) : "empty";            
        }
        else    // no ":", only name
        {
            this->_user = url.substr(offset, pos2-offset);
            this->_password = "empty";
        }
        offset = pos2 + 1;
    }

    pos2 = url.find('/', offset);
    if (pos2 == std::string::npos)   // url only with domain
    {
        pos2 = url.length();
    }
    if (pos2 == offset)    // no info about domain
    {
        this->_host = "empty";
        this->_port = "empty";
    }
    else
    {
        pos1 = url.find(':', offset);
        if (pos1 != std::string::npos)
        {
            this->_host = ((pos1 < pos2) && (pos1 != offset)) ? url.substr(offset, pos1-offset) : "empty";
            this->_port = (pos1 < pos2-1) ? url.substr(pos1+1, pos2-pos1-1) : "empty";            
        }
        else    // only host name
        {
            this->_host = url.substr(offset, pos2-offset);
            this->_port = "empty";
        }
    }

    offset = pos2+1;
    this->_path = (offset < url.length()) ? url.substr(offset) : "none";
    
    return offset;  // start position of path or parameters of particular protocol
}

void Parser::parseWithDetails()
{
    string url = this->_url;
    size_t path_offset = defaultParse();

    std::map<std::string, int> protocols
    {
        {"ftp", 1}, {"http", 2}, {"https", 2}, {"gopher", 3}, 
        {"mailto", 4}, {"news", 5}, {"nntp", 6}, {"telnet", 7}, 
        {"wais", 8}, {"file", 9}, {"prosfero", 10}
    };
    int protocol = protocols[this->_protocol];
    // define type of protocol
    switch(protocol)
    {
        case 1: // ftp
            ftp_parse();
            break;

        case 2: // http or httpd
            http_parse(path_offset);
            break;

        case 3: // gopher
            gopher_parse();
            break;

        case 4: //mailto
            mailto_parse();
            break;

        case 5: //news
            news_parse(path_offset);
            break;

        case 6: //nntp
            nntp_parse(path_offset);
            break;

        case 7: //telnet
            telnet_parse();
            break;

        case 8: // wais
            Parser::wais_parse(path_offset);
            break;

        case 9: // file
            file_parse();
            break;
            
        case 10: //prospero
            Parser::prospero_parse(path_offset);
            break;

        default:    // unknown protocol
            Parser::info_struct structure;

            structure.part = "protocol";
            structure.description = this->_protocol + " (unknown)";
            info_vect.push_back(structure);

            structure.part = "username";
            structure.description = this->_user;
            info_vect.push_back(structure);

            structure.part = "password";
            structure.description = this->_password;
            info_vect.push_back(structure);

            structure.part = "host";
            structure.description = this->_host;
            info_vect.push_back(structure);

            structure.part = "port";
            structure.description = this->_port;
            info_vect.push_back(structure);

            structure.part = "path or other parameters";
            structure.description = this->_path;
            info_vect.push_back(structure);
            break;
    }   
}
#pragma endregion

#pragma region protocol_functions
void Parser::ftp_parse()
{
    // ftp
    // ftp://name:password@host:port/path
    // path = cwd1/cwd2/.../cwdN/name;type=typecode
    // port: 20, 21

    Parser::info_struct structure;

    structure.part = "protocol";
    structure.description = this->_protocol;
    info_vect.push_back(structure);

    structure.part = "username";
    structure.description = this->_user;
    info_vect.push_back(structure);

    structure.part = "password";
    structure.description = this->_password;
    info_vect.push_back(structure);

    structure.part = "host";
    structure.description = this->_host;
    info_vect.push_back(structure);

    structure.part = "port";
    structure.description = (this->_port == "empty") ? "20 and 21 (default)" : this->_port;
    info_vect.push_back(structure);

    structure.part = "path";
    structure.description = this->_path;
    info_vect.push_back(structure);

}

void Parser::http_parse(size_t offset)
{
    // http / https
    // http://host:port/path?searchpart
    // port: 80

    Parser::info_struct structure;
    size_t pos1;
    string url = this->_url;

    structure.part = "protocol";
    structure.description = this->_protocol;
    info_vect.push_back(structure);

    structure.part = "host";
    structure.description = this->_host;
    info_vect.push_back(structure);

    structure.part = "port";
    structure.description = (this->_port == "empty") ? "80 (default)" : this->_port;
    info_vect.push_back(structure);

    if (offset < url.length())
    {
        pos1 = url.find('?', offset);
        if (pos1 == std::string::npos)
        {
            structure.part = "path";
            structure.description = this->_path;
            info_vect.push_back(structure);
        }
        else if (pos1 == offset)
        {
            structure.part = "path";
            structure.description = "empty";
            info_vect.push_back(structure);

            structure.part = "query";
            structure.description = (pos1 == url.length()-1) ? "empty" : url.substr(pos1+1);
            info_vect.push_back(structure);
        }
        else
        {
            structure.part = "path";
            structure.description = url.substr(offset, pos1-offset);
            info_vect.push_back(structure);

            structure.part = "query";
            structure.description = (pos1 == url.length()-1) ? "empty" : url.substr(pos1+1);
            info_vect.push_back(structure);
        }
    }
    else    //offset over the length of string
    {
        structure.part = "path";
        structure.description = "empty";
        info_vect.push_back(structure);

        structure.part = "query";
        structure.description = "empty";
        info_vect.push_back(structure);
    }
    
}

void Parser::gopher_parse()
{
    // gopher
    // gopher://host:port/path
    // port: 70

    Parser::info_struct structure;

    structure.part = "protocol";
    structure.description = this->_protocol;
    info_vect.push_back(structure);

    structure.part = "host";
    structure.description = this->_host;
    info_vect.push_back(structure);

    structure.part = "port";
    structure.description = (this->_port == "empty") ? "70 (default)" : this->_port;
    info_vect.push_back(structure);

    structure.part = "path";
    structure.description = this->_path;
    info_vect.push_back(structure);

}

void Parser::mailto_parse()
{
    // mailto
    //mailto:address

    Parser::info_struct structure;

    structure.part = "protocol";
    structure.description = this->_protocol;
    info_vect.push_back(structure);

    structure.part = "address";
    structure.description = this->_path;
    info_vect.push_back(structure);

}

void Parser::news_parse(size_t offset)
{
    // news
    // news:group-name  news:message-id
    // with "."         with "@"

    Parser::info_struct structure;
    string url = this->_url;

    structure.part = "protocol";
    structure.description = this->_protocol;
    info_vect.push_back(structure);

    if (offset < url.length())
    {
        regex group("(w+)\\.(w+)");
        regex id("[0-9a-zA-Z]+@[0-9a-zA-Z]");
        if (regex_match(this->_path, group))
        {
            structure.part = "group-name";
            structure.description = this->_path;
            info_vect.push_back(structure);
        }
        else if (regex_match(this->_path, id))
        {
            structure.part = "message-id";
            structure.description = this->_path;
            info_vect.push_back(structure);
        }
        else
        {
            structure.part = "uncnown field";
            structure.description = this->_path;
            info_vect.push_back(structure);
        }
    }
    else
    {
        structure.part = "message";
        structure.description = "empty field";
        info_vect.push_back(structure);
    }
    
}

void Parser::nntp_parse(size_t offset)
{
    // nntp
    // ntp://host:port/newgroup/article-number
    // port: 119

    Parser::info_struct structure;
    string url = this->_url;

    structure.part = "protocol";
    structure.description = this->_protocol;
    info_vect.push_back(structure);

    structure.part = "host";
    structure.description = this->_host;
    info_vect.push_back(structure);

    structure.part = "port";
    structure.description = (this->_port=="empty") ? "119 (default)" : this->_port;
    info_vect.push_back(structure);


    if (offset < url.length())
    {
        size_t pos1 = url.find('/', offset);
        if (pos1 == std::string::npos)   // only with newgroup
        {
            structure.part = "newgroup";
            structure.description = this->_path;
            info_vect.push_back(structure);

            structure.part = "number of article";
            structure.description = "empty";
            info_vect.push_back(structure);
        }
        else if (pos1 == offset)    // only with number of article
        {
            structure.part = "newgroup";
            structure.description = "empty";
            info_vect.push_back(structure);

            structure.part = "number of article";
            structure.description = (pos1 < url.length()-1) ? url.substr(pos1+1) : "empty";
            info_vect.push_back(structure);
        }
        else
        {
            structure.part = "newgroup";
            structure.description = url.substr(offset, pos1-offset);
            info_vect.push_back(structure);

            structure.part = "number of article";
            structure.description = (pos1 < url.length()-1) ? url.substr(pos1+1) : "empty";
            info_vect.push_back(structure);
        }
    }
    else
    {
        structure.part = "newgroup";
        structure.description = "empty";
        info_vect.push_back(structure);

        structure.part = "number of article";
        structure.description = "empty";
        info_vect.push_back(structure);
    }
    
}

void Parser::telnet_parse()
{
    // telnet
    // telnet://user:password@host:port/
    // port: 23

    Parser::info_struct structure;

    structure.part = "protocol";
    structure.description = this->_protocol;
    info_vect.push_back(structure);

    structure.part = "username";
    structure.description = this->_user;
    info_vect.push_back(structure);

    structure.part = "password";
    structure.description = this->_password;
    info_vect.push_back(structure);

    structure.part = "host";
    structure.description = this->_host;
    info_vect.push_back(structure);

    structure.part = "port";
    structure.description = (this->_port == "empty") ? "23 (default)" : this->_port;
    info_vect.push_back(structure);

}

void Parser::wais_parse(size_t offset)
{
    // wais
    // wais://host:port/database?search     wais://host:port/database/wtype/wpath
    // port: 210

    Parser::info_struct structure;
    string url = this->_url;
    size_t pos;

    structure.part = "protocol";
    structure.description = this->_protocol;
    info_vect.push_back(structure);

    structure.part = "host";
    structure.description = this->_host;
    info_vect.push_back(structure);

    structure.part = "port";
    structure.description = (this->_port == "empty") ? "210 (default)" : this->_port;
    info_vect.push_back(structure);

    if (offset < url.length())
    {
        regex wsearch("[0-9a-zA-Z]+\\?[0-9a-zA-Z]+");
        regex wpath("[0-9a-zA-Z]+/[0-9a-zA-Z]+/[0-9a-zA-Z]+");
        if (regex_match(this->_path, wsearch))
        {
            pos = url.find('?', offset);
            structure.part = "database";
            structure.description = url.substr(offset, pos-offset);
            info_vect.push_back(structure);

            structure.part = "search";
            structure.description = url.substr(pos+1);
            info_vect.push_back(structure);
        }
        else if (regex_match(this->_path, wpath))
        {
            size_t pos2;

            pos = url.find('/', offset);
            pos2 = url.find('/', pos+1);
            structure.part = "database";
            structure.description = url.substr(offset, pos-offset);
            info_vect.push_back(structure);

            structure.part = "wtype";
            structure.description = url.substr(pos+1, pos2-pos-1);
            info_vect.push_back(structure);

            structure.part = "wpath";
            structure.description = url.substr(pos2+1);
            info_vect.push_back(structure);
        }
        else
        {
            structure.part = "uncnown field";
            structure.description = this->_path;
            info_vect.push_back(structure);
        }
    }
    else
    {
        structure.part = "message";
        structure.description = "empty field";
        info_vect.push_back(structure);
    }

    structure.part = "path";
    structure.description = this->_path;
    info_vect.push_back(structure);

}

void Parser::file_parse()
{
    // file
    // file://host/path     host may be empty (localhost)

    Parser::info_struct structure;

    structure.part = "protocol";
    structure.description = this->_protocol;
    info_vect.push_back(structure);

    structure.part = "host";
    structure.description = this->_host;
    info_vect.push_back(structure);

    structure.part = "path";
    structure.description = this->_path;
    info_vect.push_back(structure);

}

void Parser::prospero_parse(size_t offset)
{
    // prospero
    // prospero://host:port/hsoname;field=value
    // port: 1525

    Parser::info_struct structure;
    string url = this->_url;

    structure.part = "protocol";
    structure.description = this->_protocol;
    info_vect.push_back(structure);

    structure.part = "host";
    structure.description = this->_host;
    info_vect.push_back(structure);

    structure.part = "port";
    structure.description = (this->_port == "empty") ? "1525 (default)" : this->_port;
    info_vect.push_back(structure);

    if (offset < url.length())
    {
        size_t pos1 = url.find(';', offset);
        if (pos1 == std::string::npos)   // only with hsoname
        {
            structure.part = "hsoname";
            structure.description = this->_path;
            info_vect.push_back(structure);

            structure.part = "fields";
            structure.description = "empty";
            info_vect.push_back(structure);
        }
        else if (pos1 == offset)    // only with fields
        {
            structure.part = "hsoname";
            structure.description = "empty";
            info_vect.push_back(structure);

            structure.part = "fields";
            structure.description = (pos1 < url.length()-1) ? url.substr(pos1+1) : "empty";
            info_vect.push_back(structure);
        }
        else
        {
            structure.part = "hsoname";
            structure.description = url.substr(offset, pos1-offset);
            info_vect.push_back(structure);

            structure.part = "fields";
            structure.description = (pos1 < url.length()-1) ? url.substr(pos1+1) : "empty";
            info_vect.push_back(structure);
        }
    }
    else
    {
        structure.part = "hsoname";
        structure.description = "empty";
        info_vect.push_back(structure);

        structure.part = "fields";
        structure.description = "empty";
        info_vect.push_back(structure);
    }

}
#pragma endregion

#pragma region print_functions
void Parser::outlineInfo()
{
    if(!this->info_vect.empty())
    {        
        cout << "url string: " << this->_url << endl;
        int vSize = info_vect.size();
        for (int i = 0; i < vSize; i++)
        {
            cout << "\t" << info_vect[i].part << ": " << info_vect[i].description << endl;
        }
        cout << "\n\n";
    }
    else
    {
        cout << "No info about this object" << endl;
    }
}

void Parser::outlineDefaultInfo()
{
    cout << "url string: " << this->_url << endl;
    cout << "\t" << "protocol: " << this->_protocol << endl;
    cout << "\t" << "username: " << this->_user << endl;
    cout << "\t" << "password: " << this->_password << endl;
    cout << "\t" << "host: " << this->_host << endl;
    cout << "\t" << "port: " << this->_port << endl;
    cout << "\t" << "path or other info: " << this->_path << endl;
    cout << "\n\n";
}
#pragma endregion