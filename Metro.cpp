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
Metro::~Metro()
{
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
ostream& operator<<(ostream& output,const Metro& metro)
{
	output<<metro.get_service_name()<<" | Train "<<metro.get_train_no()<<" | "<<(metro.is_operating()?"Operating":"Out of service")<<endl<<metro.get_features()<<endl;
	return output;
}
