#include "MetroService.h"
#include <exception>
#include <iostream>
#include <new>
using namespace std;
int main()
{
	try
	{
		MetroService service;
		service.run_service();
	}
	catch(const bad_alloc&)
	{
		cerr<<"Error: not enough memory to run On Track."<<endl;
		return 1;
	}
	catch(const exception& error)
	{
		cerr<<"Application error: "<<error.what()<<endl;
		return 1;
	}
	catch(...)
	{
		cerr<<"Unknown application error."<<endl;
		return 1;
	}
	return 0;
}
