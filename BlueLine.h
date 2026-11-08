#ifndef BLUELINE_H
#define BLUELINE_H
#include "MetroLine.h"
class BlueLine:public MetroLine
{
	public:
		BlueLine();
		string get_line_name() const override;
		void configure_route(Station* stations) override;
};
#endif
