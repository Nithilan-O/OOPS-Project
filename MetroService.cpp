#include "MetroService.h"
#include <iostream>
#include <cmath>
using namespace std;
MetroService::MetroService()
: route("Metro Line",3),regular(101),ticket_count(0),next_ticket_id(1001)
{
	route.add_station(Station(1,"A",0));
	route.add_station(Station(2,"B",5));
	route.add_station(Station(3,"C",10));
}
void MetroService::read_no(const string& prompt,int& value) const
{
	cout<<prompt;
	cin>>value;
	cin.ignore();
}
void MetroService::display_stations() const
{
	for(int i=0;i<route.get_count();++i)
	{
		Station station;
		route.get_station(i,station);
		cout<<station<<endl;
	}
}
void MetroService::display_metros() const
{
	cout<<"1. "<<regular;
	cout<<"Stops: A; B; C"<<endl;
}
void MetroService::book_ticket()
{
	if(ticket_count==100)
	{
		cout<<"Ticket storage is full."<<endl;
		return;
	}
	display_stations();
	int source_id,destination_id;
	read_no("Source station ID (1-3): ",source_id);
	read_no("Destination station ID (1-3): ",destination_id);
	int source_index=route.find_station(source_id);
	int destination_index=route.find_station(destination_id);
	Station from,to;
	route.get_station(source_index,from);
	route.get_station(destination_index,to);
	double distance=fabs(from.get_position_km()-to.get_position_km());
	int intervals=abs(destination_index-source_index);
	cout<<"Journey: "<<distance<<" km, "<<intervals<<" station intervals."<<endl<<"Fare: INR "<<regular.calculate_fare(distance)<<endl<<"Passenger name: ";
	string passenger;
	getline(cin,passenger);
	Ticket ticket(next_ticket_id,passenger,from,to,distance,regular.calculate_fare(distance),intervals);
	tickets[ticket_count++]=ticket;
	++next_ticket_id;
	cout<<"Ticket generated."<<endl<<ticket;
}
void MetroService::display_ticket() const
{
	if(ticket_count==0)
	{
		cout<<"No tickets booked."<<endl;
		return;
	}
	cout<<"Stored tickets:"<<endl;
	for(int i=0;i<ticket_count;++i)
	{
		cout<<tickets[i];
	}
}
void MetroService::run_service()
{
	cout<<"Welcome to Metro Rail Service"<<endl;
	while(true)
	{
		cout<<endl<<"1. Stations\n2. Metro line\n3. Metro service\n4. Book ticket\n5. Display tickets\n0. Exit\n";
		int choice;
		read_no("Choice: ",choice);
		if(choice==0)
		{
			break;
		}
		if(choice==1)
		{
			display_stations();
		}
		else if(choice==2)
		{
			cout<<route;
		}
		else if(choice==3)
		{
			display_metros();
		}
		else if(choice==4)
		{
			book_ticket();
		}
		else if(choice==5)
		{
			display_ticket();
		}
	}
	cout<<"Goodbye."<<endl;
}
