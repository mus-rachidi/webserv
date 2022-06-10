#include "ServerRoutes.hpp"

ServerRoutes::ServerRoutes( void )
{
	this->_redirection_code = 301;
	this->_redirection_url = "";
	this->_route = "/";
	this->_root = "/tmp/www";
	this->_dir_list = false;
	this->_phpcgi = "";
	this->_upload_dir = "";
}

ServerRoutes::ServerRoutes( ServerRoutes const & src )
{
	*this = src;
}

ServerRoutes & ServerRoutes::operator=( ServerRoutes const & src )
{
	this->_redirection_code = src._redirection_code;
	this->_redirection_url = src._redirection_url;
	this->_route = src._route;
	this->_root = src._root;
	this->_dir_list = src._dir_list;
	this->_indexes = src._indexes;
	this->_methods = src._methods;
	this->_phpcgi = src._phpcgi;
	this->_upload_dir = src._upload_dir;

	return *this;
}

ServerRoutes::~ServerRoutes( void )
{}

int ServerRoutes::getRedirectionCode( void ) const
{
	return this->_redirection_code;
}

std::string ServerRoutes::getRedirectionUrl( void ) const
{
	return this->_redirection_url;
}

std::string ServerRoutes::getRoute( void ) const
{
	return this->_route;
}

std::string ServerRoutes::getRoot( void ) const
{
	return this->_root;
}

bool ServerRoutes::getDirListing( void ) const
{
	return this->_dir_list;
}

std::vector<std::string> ServerRoutes::getIndexes( void ) const
{
	return this->_indexes;
}

std::string ServerRoutes::getPhpCgi( void ) const
{
	return this->_phpcgi;
}

std::vector<std::string> ServerRoutes::getAllMethods( void ) const
{
	return this->_methods;
}

int ServerRoutes::getMethodsCount( void ) const
{
	return this->_methods.size();
}

std::string ServerRoutes::getUploadDir( void ) const
{
	return this->_upload_dir;
}

bool ServerRoutes::isMethodAllowed( std::string const & method ) const
{
	return (
		find(this->_methods.begin(), this->_methods.end(), method)
		!=
		this->_methods.end()
	);
}

void ServerRoutes::setRedirectionCode( int const & redirection )
{
	this->_redirection_code = redirection;
}

void ServerRoutes::setRedirectionUrl( std::string const & redirection )
{
	this->_redirection_url = redirection;
}

void ServerRoutes::setRoute( std::string const & route )
{
	this->_route = route;
}

void ServerRoutes::setRoot( std::string const & root )
{
	this->_root = root;
}

void ServerRoutes::setDirListing( bool dir_list )
{
	this->_dir_list = dir_list;
}

void ServerRoutes::addIndex( std::string const & index )
{
	this->_indexes.push_back(index);
}

void ServerRoutes::setPhpCgi( std::string const & cgi )
{
	this->_phpcgi = cgi;
}

bool ServerRoutes::addMethod( std::string const & method )
{
	if ( !this->isMethodAllowed( method ) )
	{
		this->_methods.push_back(method);
		return true;
	}
	return false;
}

void ServerRoutes::setUploadDir( std::string const & upload )
{
	this->_upload_dir = upload;
}