#ifndef YELLOWLINE_H
#define YELLOWLINE_H
#include "MetroLine.h"
class YellowLine:public MetroLine
{
	public:
		YellowLine();
		string get_line_name() const override;
		void configure_route(Station* stations) override;
};
#endif
