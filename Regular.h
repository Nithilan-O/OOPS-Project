#ifndef REGULAR_H
#define REGULAR_H
#include "Metro.h"
using namespace std;
class Regular:public Metro
{
	public:
		Regular();
		Regular(int no);
		string get_features() const;
		double calculate_fare(double distance) const;
};
ostream& operator<<(ostream& output,const Regular& regular);
#endif
