#ifndef STRING_PARSER_H
#define STRING_PARSER_H

#include <string>
#include <Python.h>
#include <vector>

#include <iostream>

//aka the Python Whisperer
class StringParser {
private:
	std::string m_scommand;

	//Py Objects
	PyObject *m_POname, *m_POmodule, *m_POfunctionName, *m_POvalues, *m_POstring, *m_POlist, *m_POints, *m_POparams, *m_POerrors;
	//gil state
	PyGILState_STATE m_gstate;

public:
	StringParser();
	~StringParser();

	//init and close python c api
	void init();
	void close();
	
	//sanitize string before sending it to being drawn and if it is the case 
	//get commands from string
	std::string parseString(std::vector < int > &f_icommands, std::string s_command, std::vector < std::string > &params, std::vector < int > &errors);
};

#endif