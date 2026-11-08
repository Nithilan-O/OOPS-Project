#ifndef METROLINE_H
#define METROLINE_H
#include "Route.h"
using namespace std;
class MetroLine
{
	private:
		Route route;
	protected:
		MetroLine(const string& line_name,int maximum_stations);
		void add_station(Station& station);
	public:
		virtual ~MetroLine();
		virtual string get_line_name() const=0;
		virtual void configure_route(Station* stations)=0;
		const Route& get_route() const;
};
ostream& operator<<(ostream& output,const MetroLine& line);
#endif
