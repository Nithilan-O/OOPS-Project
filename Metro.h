#ifndef METRO_H
#define METRO_H
#include "Route.h"
using namespace std;
class Metro
{
	private:
		int train_no;
		bool operating;
	public:
		Metro();
		Metro(int no);
		int get_train_no() const;
		bool is_operating() const;
		bool set_train_no(int no);
		void set_operating(bool status);
		string get_features() const;
		double calculate_fare(double distance) const;
};
ostream& operator<<(ostream& output,const Metro& metro);
#endif
