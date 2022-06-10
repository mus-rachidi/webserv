#include "request.hpp"

/// utils
bool existfile(std::string &f)
{	
	std::string filename =  f;
	std::ifstream file(filename.c_str());
	return (file.good());
}

Request::Request(){
}

Request::Request(std::string req_path, int _fd)
{
	this->fd = _fd;
    this->PathOfReq = req_path;
	this->ROOTDIR = "."; // repl
	this->Content_length = 0;
	this->IsPhpFile = false;
	this->IsReqBody = 0;
	this->AutoindexOn = false;
    start_parsing();
	this->path_info = this->RequestFile;
}


void Request::start_parsing()
{
	std::string f = this->PathOfReq;
	std::ifstream file(f);

    if (file.good())
    {
        std::string     line;
        std::ifstream   myfile;

        myfile.open(this->PathOfReq);
        std::getline(myfile, line);
        this->parse_firstline(line);
        line = this->ParseHeaderReq(line);
        this->PrepareMsgBody(line);
    }
}

bool IsPhpFileFunc(std::string filename)
{
	std::size_t found = filename.find(".php");
	if (found!=std::string::npos)
		return (true);
	return (false);
}

void Request::parse_firstline(std::string fline)
{
	std::stringstream   inputfile(fline);
	std::string         str;
	int                 i;

	i = 0;
	while (std::getline(inputfile, str, ' '))
	{
		if (i == 0)
			this->method = str;
		else if (i == 1)
		{
			std::size_t found = str.find("?");
			if (found!=std::string::npos)
			{
				this->RequestFile = str.substr(0, found);
				this->QueryString = str.substr(found+1);
			}
			else
				this->RequestFile = str;
            break;
		}
		i++;
	}
	this->IsPhpFile = IsPhpFileFunc(this->RequestFile);
}

std::string Request::ParseHeaderReq(std::string line)
{
    std::ifstream myfile;
	myfile.open(this->PathOfReq);

	std::getline(myfile, line);
    while (std::getline(myfile, line)) 
	{
        if (line == "\r")
			break;
        getvalue(line);
    }
    return (line);
}

void Request::getvalue(std::string line)
{
	std::stringstream   inputfile(line);
	std::string         str;

	std::getline(inputfile, str, ':');
	if (str == "Host")
	{
		for (int j = 0; j < 2; j++)
			std::getline(inputfile, str, ' ');
        std::size_t found = str.find(":");
        if (found!=std::string::npos)
		{
            getHost_Port(str);
        }
        else
		{
            this->host = str;
			this->port = "80";
		}
	}
	else if (str == "Content-Type") 
		this->Content_type = line.substr(line.find(' ') + 1);
	else if (str == "Content-Length")
	{
		std::getline(inputfile, str, ':');
		this->Content_length = std::stoi(str);
	}
    else if (str == "Connection") 
		this->Connection = line.substr(line.find(' ') + 1);
}

void Request::getHost_Port(std::string line)
{
	std::stringstream   inputfile(line);
	std::string         str;

	std::getline(inputfile, str, ':');
	this->host = str;

	std::getline(inputfile, str, ':');
	this->port = str;
}

void Request::PrepareMsgBody(std::string line)
{
    if (this->method == "POST")
    {
        std::ifstream myfile;
        this->body_content = concat("/tmp/.REQ_NO_", this->fd) + "_BODY";
        std::ofstream reqBody(body_content);

        myfile.open(this->PathOfReq, std::fstream::binary);
        while (std::getline(myfile, line) && line != "\r")
        {
            if (line.length() == 0)
                break;
        }

        while (std::getline(myfile, line))
        {
            reqBody << line << "\n";
        }
        this->IsReqBody = true;
    }
}
