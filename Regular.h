#ifndef REGULAR_H
#define REGULAR_H
#include "Metro.h"
using namespace std;
class Regular:public Metro
{
	public:
		Regular();
		Regular(int no);
		string get_service_name() const override;
		string get_features() const override;
		double calculate_fare(int extra_stops,bool digital) const override;
};
ostream& operator<<(ostream& output,const Regular& regular);
#endif
