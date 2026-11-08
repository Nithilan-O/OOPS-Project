#ifndef GREENLINE_H
#define GREENLINE_H
#include "MetroLine.h"
class GreenLine:public MetroLine
{
	public:
		GreenLine();
		string get_line_name() const override;
		void configure_route(Station* stations) override;
};
#endif
