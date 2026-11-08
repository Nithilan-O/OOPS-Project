#include "Regular.h"
using namespace std;

Regular::Regular():Metro()
{
}
Regular::Regular(int no):Metro(no)
{
}
string Regular::get_service_name() const
{
	return "Regular";
}
string Regular::get_features() const
{
	return "Blue, Green, and Yellow Lines;\nFare is INR 20 plus INR 5 per extra stop";
}
double Regular::calculate_fare(int extra_stops,bool digital) const
{
	if(extra_stops<0)
	{
		return-1;
	}
	int fare=20+5*extra_stops;
	if(digital)
	{
		fare=fare*8/10;
	}
	return fare;
}
ostream& operator<<(ostream& output,const Regular& regular)
{
	const Metro& metro=regular;
	return output<<metro;
}
