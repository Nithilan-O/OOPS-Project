#include "Regular.h"
#include <cmath>
using namespace std;
Regular::Regular():Metro()
{
}
Regular::Regular(int no):Metro(no)
{
}
string Regular::get_features() const
{
	return "Stops at A, B, and C;\nFare is 10 (+ 2 per km)";
}
double Regular::calculate_fare(double distance) const
{
	if(not isfinite(distance)  or  distance<=0)
	{
		return-1;
	}
	return round((10.0+2.0*distance)*100.0)/100.0;
}
ostream& operator<<(ostream& output,const Regular& regular)
{
	output<<"Regular | Train "<<regular.get_train_no()<<" | "<<(regular.is_operating()?"Operating":"Out of service")<<endl<<regular.get_features()<<endl;
	return output;
}
