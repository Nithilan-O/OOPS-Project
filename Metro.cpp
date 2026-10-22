#include "Metro.h"
#include <cmath>
using namespace std;
Metro::Metro()
{
	train_no=1;
	operating=true;
}
Metro::Metro(int no)
{
	train_no=1;
	operating=true;
	set_train_no(no);
}
int Metro::get_train_no() const
{
	return train_no;
}
bool Metro::is_operating() const
{
	return operating;
}
bool Metro::set_train_no(int no)
{
	if(no<=0)
	{
		return false;
	}
	train_no=no;
	return true;
}
void Metro::set_operating(bool status)
{
	operating=status;
}
string Metro::get_features() const
{
	return "Stops at A, B, and C;\nFare is 10 (+ 2 per km)";
}
double Metro::calculate_fare(double distance) const
{
	if(not isfinite(distance)  or  distance<=0)
	{
		return-1;
	}
	return round((10.0+2.0*distance)*100.0)/100.0;
}
ostream& operator<<(ostream& output,const Metro& metro)
{
	output<<"Regular | Train "<<metro.get_train_no()<<" | "<<(metro.is_operating()?"Operating":"Out of service")<<endl<<metro.get_features()<<endl;
	return output;
}
