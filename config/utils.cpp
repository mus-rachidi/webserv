#include "utils.h"

/**
 * @brief Trims leading whitespace from a string
 * 
 * @param s std::string const &
 * @return std::string 
 */
std::string w_ltrim(std::string const & s)
{
	return std::regex_replace(s, std::regex("^\\s+"), "");
}

/**
 * @brief Trims the ending whitespace from a string
 * 
 * @param s std::string const &
 * @return std::string 
 */
std::string w_rtrim(std::string const & s)
{
	return std::regex_replace(s, std::regex("\\s+$"), "");
}

/**
 * @brief Trims the leading and ending whitespaces from a string.
 * 
 * @param s std::string const & 
 * @return std::string 
 */
std::string w_trim(std::string const & s)
{
	return w_ltrim(w_rtrim(s));
}

/**
 * @brief Splits a string into a vector of strings based on a delimiter.
 * 
 * @param s std::string const &
 * @param c char
 * @return std::vector<std::string> A vector of strings
 */
std::vector<std::string> s_split(std::string const & s, char c)
{
	std::vector<std::string> result;

	std::string::const_iterator it = s.begin();
	while (it != s.end())
	{
		std::string::const_iterator it_next = std::find(it, s.end(), c);
		result.push_back(std::string(it, it_next));
		it = it_next;
		if (it != s.end())
			it++;
	}
	return (result);
}

std::string concat(std::string const & s, int i)
{
	std::stringstream ss;
	ss << i;
	return (s + ss.str());
}

long long int calculateSize(std::string filename)
{

	FILE* fp = fopen(filename.c_str(), "r");
	if (fp == NULL) {
		return 0;
	}
	fseek(fp, 0L, SEEK_END);
	long int ans = ftell(fp);
	fclose(fp);
	return ans;
}

bool file_exists(std::string const & name)
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0) && (S_ISREG(buffer.st_mode));
}

bool directory_exists(std::string const & name)
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0) && (S_ISDIR(buffer.st_mode));
}

/**
 * @brief 
 * 
 * @param filename 
 * @return int : returns 0 if success, -1 if error 
 */
int hasAccess(std::string const & filename)
{
	return access(filename.c_str(), R_OK);
}

std::string preparehref(std::string const & filename, std::string const & req)
{
	return ("<a href='" + req + (req.size()>1?"/":"") + filename + "'>" + filename + "</a>");
}

void generate_dirlist(std::string const & o_file, std::string full_path, std::string const & req)
{
	DIR				*dir;
	struct dirent	*ent;
	std::ofstream	myfile;

	myfile.open(o_file);
	myfile << "<html><head><title>Index of " + full_path + " </title></head><body>" << std::endl;
	myfile << "<h1>Index of  " + full_path + " </h1><hr><pre>" << std::endl;
	if ((dir = opendir(full_path.c_str())) != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			if (ent->d_name[0] == '.')
				continue;

			std::string		filename(ent->d_name);
			std::string		tmp;
			struct stat		sb;

			if (full_path[full_path.size()-1] != '/')
				full_path += "/";
			tmp = full_path;
			tmp += ent->d_name;

			stat(tmp.c_str(), &sb);
			myfile
				<< preparehref(filename, req)
				<< std::setw(60 - (preparehref(filename, req).length() / 2))
				<< sb.st_size << " bytes"<< std::setw(40) << ctime(&sb.st_ctime) ;
		}
		closedir(dir);
	}
	myfile << "</pre><hr></body></html>" << std::endl;
	myfile.close();
}

std::string getStatusByCode(int sCode)
{
    std::map<int, std::string> status;
    status[200] = "200 OK";
	status[201] = "201 Created";
	status[202] = "202 Accepted";
	status[204] = "204 No Content";
	status[206] = "206 Partial Content";
	status[301] = "301 Moved Permanently";
	status[302] = "302 Found";
	status[304] = "304 Not Modified";
    status[400] = "400 Bad Request";
    status[401] = "401 Unauthorized";
    status[403] = "403 Forbidden";
    status[404] = "404 Not Found";
    status[405] = "405 Method Not Allowed";
    status[406] = "406 Not Acceptable";
    status[408] = "408 Request Timeout";
    status[411] = "411 Length Required";
    status[413] = "413 Payload Too Large";
    status[414] = "414 URI Too Long";
    status[415] = "415 Unsupported Media Type";
    status[429] = "429 Too Many Requests";
    status[431] = "431 Request Header Fields Too Large";
    status[500] = "500 Internal Server Error";
    status[502] = "502 Bad Gateway";
    status[503] = "503 Service Unavailable";
    status[504] = "504 Gateway Timeout";
    status[505] = "505 HTTP Version Not Supported";
    status[508] = "508 Loop Detected";

    return (status[sCode]);
}

std::string searchByExtension(std::string const & extention)
{
    std::map<std::string, std::string> types;
	types["aac"] = "audio/aac";
	types["abw"] = "application/x-abiword";
	types["ai"] = "application/postscript";
	types["arc"] = "application/octet-stream";
	types["avi"] = "video/x-msvideo";
	types["azw"] = "application/vnd.amazon.ebook";
	types["bin"] = "application/octet-stream";
	types["bz"] = "application/x-bzip";
	types["bz2"] = "application/x-bzip2";
	types["csh"] = "application/x-csh";
	types["css"] = "text/css";
	types["csv"] = "text/csv";
	types["doc"] = "application/msword";
	types["dll"] = "application/octet-stream";
	types["eot"] = "application/vnd.ms-fontobject";
	types["epub"] = "application/epub+zip";
	types["gif"] = "image/gif";
	types["htm"] = "text/html";
	types["html"] = "text/html";
	types["ico"] = "image/x-icon";
	types["ics"] = "text/calendar";
	types["jar"] = "application/java-archive";
	types["jpeg"] = "image/jpeg";
	types["jpg"] = "image/jpeg";
	types["js"] = "application/javascript";
	types["json"] = "application/json";
	types["mid"] = "audio/midi";
	types["midi"] = "audio/midi";
	types["mp2"] = "audio/mpeg";
	types["mp3"] = "audio/mpeg";
	types["mp4"] = "video/mp4";
	types["mpa"] = "video/mpeg";
	types["mpe"] = "video/mpeg";
	types["mpeg"] = "video/mpeg";
	types["mpkg"] = "application/vnd.apple.installer+xml";
	types["odp"] = "application/vnd.oasis.opendocument.presentation";
	types["ods"] = "application/vnd.oasis.opendocument.spreadsheet";
	types["odt"] = "application/vnd.oasis.opendocument.text";
	types["oga"] = "audio/ogg";
	types["ogv"] = "video/ogg";
	types["ogx"] = "application/ogg";
	types["otf"] = "font/otf";
	types["png"] = "image/png";
	types["php"] = "application/x-httpd-php";
	types["pdf"] = "application/pdf";
	types["ppt"] = "application/vnd.ms-powerpoint";
	types["rar"] = "application/x-rar-compressed";
	types["rtf"] = "application/rtf";
	types["sh"] = "application/x-sh";
	types["svg"] = "image/svg+xml";
	types["swf"] = "application/x-shockwave-flash";
	types["tar"] = "application/x-tar";
	types["tif"] = "image/tiff";
	types["tiff"] = "image/tiff";
	types["ts"] = "application/typescript";
	types["ttf"] = "font/ttf";
	types["txt"] = "text/plain";
	types["vsd"] = "application/vnd.visio";
	types["wav"] = "audio/x-wav";
	types["weba"] = "audio/webm";
	types["webm"] = "video/webm";
	types["webp"] = "image/webp";
	types["woff"] = "font/woff";
	types["woff2"] = "font/woff2";
	types["xhtml"] = "application/xhtml+xml";
	types["xls"] = "application/vnd.ms-excel";
	types["xlsx"] = "application/vnd.ms-excel";
	types["xlsx_OLD"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
	types["xml"] = "application/xml";
	types["xul"] = "application/vnd.mozilla.xul+xml";
	types["zip"] = "application/zip";
	types["3gp"] = "video/3gpp";
	types["3gp_DOES_NOT_CONTAIN_VIDEO"] = "audio/3gpp";
	types["3gp2"] = "video/3gpp2";
	types["3gp2_DOES_NOT_CONTAIN_VIDEO"] = "audio/3gpp2";
	types["7z"] = "application/x-7z-compressed";

    if (types[extention].length() == 0)
        return ("application/octet-stream");
    return (types[extention]);
}