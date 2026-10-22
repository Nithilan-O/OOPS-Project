#ifndef STATION_H
#define STATION_H
#include <iostream>
#include <string>
using namespace std;
class Station
{
	private:
		int id;
		string name;
		double position_km;
	public:
		Station();
		Station(int station_id,const string& station_name,double position);
		int get_id() const;
		const string& get_name() const;
		double get_position_km() const;
		bool set_id(int station_id);
		bool set_name(const string& station_name);
		bool set_position_km(double position);
		friend istream& operator>>(istream& input,Station& station);
};
ostream& operator<<(ostream& output,const Station& station);
istream& operator>>(istream& input,Station& station);
#endif
