#include "MetroService.h"
#include <iostream>
#include <limits>
using namespace std;
MetroService::MetroService()
: regular(101),ticket_count(0),next_ticket_id(1001)
{
	const string station_names[station_capacity]=
	{
		"Airport","Alandur","Guindy",
		"Saidapet","Nandanam","Thousand Lights",
		"Chennai Central","Washermenpet",
		"Tondiarpet","Tollgate","Thiruvottriyur","Wimco Nagar Depot",
		"St. Thomas Mount","Ashok Nagar","Vadapalani",
		"CMBT","Anna Nagar Tower","Kilpauk",
		"Egmore","Porur Junction","Porur Bypass","Iyyappanthangal",
		"Kumananchavadi","Poonamallee Bus Stand","Poonamallee Bypass"
	};
	for(int i=0;i<station_capacity;++i)
	{
		stations[i]=Station(i+1,station_names[i],0);
	}
	lines[0]=&blue_line;
	lines[1]=&green_line;
	lines[2]=&yellow_line;
	for(int i=0;i<line_count;++i)
	{
		lines[i]->configure_route(stations);
	}
}
bool MetroService::read_no(const string& prompt,int& value) const
{
	cout<<prompt;
	if(not (cin>>value))
	{
		if(cin.eof() or cin.bad())
		{
			return false;
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		return false;
	}
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	return true;
}
int MetroService::find_station_index(int station_id) const
{
	if(station_id<1 or station_id>station_capacity)
	{
		return-1;
	}
	return station_id-1;
}
void MetroService::display_stations() const
{
	cout<<endl<<"Stations (IDs are used when booking):"<<endl;
	for(int i=0;i<station_capacity;++i)
	{
		int station_id=stations[i].get_id();
		cout<<station_id<<". "<<stations[i].get_name()<<" | Lines: ";
		bool first=true;
		for(int line=0;line<line_count;++line)
		{
			if(lines[line]->get_route().find_station(station_id)>=0)
			{
				if(not first)
				{
					cout<<", ";
				}
				cout<<lines[line]->get_line_name();
				first=false;
			}
		}
		cout<<endl;
	}
	cout<<endl;
}
void MetroService::display_routes() const
{
	for(int i=0;i<line_count;++i)
	{
		cout<<*lines[i];
		cout<<endl;
	}
}
void MetroService::display_metros() const
{
	cout<<"1. "<<regular;
	cout<<"Lines: Blue Line; Green Line; Yellow Line"<<endl;
}
bool MetroService::determine_route(int source_id,int destination_id,string& route_details,
	int& extra_stops) const
{
	int parent[station_capacity+1];
	int parent_line[station_capacity+1];
	bool visited[station_capacity+1]={false};
	int queue[station_capacity];
	for(int i=0;i<=station_capacity;++i)
	{
		parent[i]=-1;
		parent_line[i]=-1;
	}
	int first=0,last=0;
	if(find_station_index(source_id)<0 or find_station_index(destination_id)<0)
	{
		return false;
	}
	visited[source_id]=true;
	queue[last++]=source_id;
	while(first<last and not visited[destination_id])
	{
		int current_station=queue[first++];
		for(int next=0;next<line_count;++next)
		{
			const Route& route=lines[next]->get_route();
			int station_index=route.find_station(current_station);
			if(station_index<0)
			{
				continue;
			}
			for(int direction=-1;direction<=1;direction+=2)
			{
				int next_index=station_index+direction;
				Station station;
				if(next_index>=0 and next_index<route.get_count() and
					route.get_station(next_index,station) and not visited[station.get_id()])
				{
					visited[station.get_id()]=true;
					parent[station.get_id()]=current_station;
				parent_line[station.get_id()]=next;
					queue[last++]=station.get_id();
				}
			}
		}
	}
	if(not visited[destination_id])
	{
		return false;
	}
	int path[station_capacity];
	int path_lines[station_capacity];
	int path_count=0;
	int current_station=destination_id;
	while(current_station!=source_id)
	{
		path[path_count]=current_station;
		path_lines[path_count]=parent_line[current_station];
		++path_count;
		current_station=parent[current_station];
	}
	if(path_count==0)
	{
		extra_stops=0;
		for(int line=0;line<line_count;++line)
		{
			if(lines[line]->get_route().find_station(source_id)>=0)
			{
				route_details=lines[line]->get_line_name();
				return true;
			}
		}
		return false;
	}
	for(int i=path_count-1;i>=0;--i)
	{
		int line=path_lines[i];
		if(i==path_count-1 or line!=path_lines[i+1])
		{
			if(not route_details.empty())
			{
				route_details+=" via "+stations[path[i+1]-1].get_name()+" -> ";
			}
			route_details+=lines[line]->get_line_name();
		}
	}
	extra_stops=path_count>1?path_count-1:0;
	return true;
}
void MetroService::book_ticket()
{
	if(ticket_count==100)
	{
		cout<<"Ticket storage is full."<<endl;
		return;
	}
	display_stations();
	int source_id,destination_id,ticket_type;
	if(not read_no("Source station ID: ",source_id) or
		not read_no("Destination station ID: ",destination_id))
	{
		if(cin.eof() or cin.bad())
		{
			return;
		}
		cout<<"Invalid station selection."<<endl;
		return;
	}
	int source_index=find_station_index(source_id);
	int destination_index=find_station_index(destination_id);
	string route_details;
	int extra_stops;
	if(source_index<0 or destination_index<0 or
		not determine_route(source_id,destination_id,route_details,extra_stops))
	{
		cout<<"Invalid source or destination station ID."<<endl;
		return;
	}
	if(not read_no("Ticket type (1. Counter paper, 2. Eligible digital): ",ticket_type) or
		(ticket_type!=1 and ticket_type!=2))
	{
		if(cin.eof() or cin.bad())
		{
			return;
		}
		cout<<"Invalid ticket type."<<endl;
		return;
	}
	bool digital=ticket_type==2;
	double fare=regular.calculate_fare(extra_stops,digital);
	if(fare<0)
	{
		cout<<"Unable to calculate fare."<<endl;
		return;
	}
	cout<<endl<<"Passenger name: ";
	string passenger;
	if(not getline(cin,passenger) or
		passenger.find_first_not_of(" \t\r\n")==string::npos)
	{
		cout<<"Passenger name cannot be empty. Ticket was not generated."<<endl;
		return;
	}
	Station from=stations[source_index];
	Station to=stations[destination_index];
	Ticket ticket(next_ticket_id,passenger,from,to,fare,route_details,extra_stops,digital);
	tickets[ticket_count++]=ticket;
	++next_ticket_id;
	cout<<endl<<"Ticket generated."<<endl<<ticket<<endl;
}
void MetroService::display_ticket() const
{
	if(ticket_count==0)
	{
		cout<<"No tickets booked."<<endl;
		return;
	}
	cout<<endl<<"Stored tickets:"<<endl;
	for(int i=0;i<ticket_count;++i)
	{
		cout<<tickets[i]<<endl;
	}
}
void MetroService::run_service()
{
	cout<<"Welcome to On Track"<<endl;
	while(true)
	{
		cout<<endl<<"===== On Track ====="<<endl;
		cout<<"1. View stations"<<endl;
		cout<<"2. View metro lines"<<endl;
		cout<<"3. View metro service"<<endl;
		cout<<"4. Book a ticket"<<endl;
		cout<<"5. Display booked tickets"<<endl;
		cout<<"0. Exit"<<endl;
		cout<<endl;
		int choice;
		bool valid_choice=read_no("Choice: ",choice);
		cout<<endl;
		if(not valid_choice)
		{
			if(cin.eof() or cin.bad())
			{
				break;
			}
			cout<<"Invalid menu choice."<<endl;
			continue;
		}
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
			display_routes();
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
		else
		{
			cout<<"Invalid menu choice."<<endl;
		}
	}
	cout<<"Goodbye."<<endl;
}
