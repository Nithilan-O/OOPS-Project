#include "Metro.h"
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
string Metro::get_service_name() const
{
	return "Regular";
}
string Metro::get_features() const
{
	return "Blue, Green, and Yellow Lines;\nFare is INR 20 plus INR 5 per extra stop";
}
double Metro::calculate_fare(int extra_stops,bool digital) const
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
ostream& operator<<(ostream& output,const Metro& metro)
{
	output<<metro.get_service_name()<<" | Train "<<metro.get_train_no()<<" | "<<(metro.is_operating()?"Operating":"Out of service")<<endl<<metro.get_features()<<endl;
	return output;
}
