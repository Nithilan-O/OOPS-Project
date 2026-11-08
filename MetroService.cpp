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
	routes[0]=Route("Blue Line",12);
	routes[1]=Route("Green Line",9);
	routes[2]=Route("Yellow Line",7);
	const int blue_line[12]={12,11,10,9,8,7,6,5,4,3,2,1};
	const int green_line[9]={7,19,18,17,16,15,14,2,13};
	const int yellow_line[7]={25,24,23,22,21,20,15};
	for(int i=0;i<12;++i)
	{
		routes[0].add_station(stations[blue_line[i]-1]);
	}
	for(int i=0;i<9;++i)
	{
		routes[1].add_station(stations[green_line[i]-1]);
	}
	for(int i=0;i<7;++i)
	{
		routes[2].add_station(stations[yellow_line[i]-1]);
	}
}
bool MetroService::read_no(const string& prompt,int& value) const
{
	cout<<prompt;
	if(not (cin>>value))
	{
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
			if(routes[line].find_station(station_id)>=0)
			{
				if(not first)
				{
					cout<<", ";
				}
				cout<<routes[line].get_name();
				first=false;
			}
		}
		cout<<endl;
	}
}
void MetroService::display_routes() const
{
	for(int i=0;i<line_count;++i)
	{
		cout<<routes[i];
		cout<<endl;
	}
}
void MetroService::display_metros() const
{
	const Metro& metro=regular;
	cout<<"1. "<<metro;
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
			int station_index=routes[next].find_station(current_station);
			if(station_index<0)
			{
				continue;
			}
			for(int direction=-1;direction<=1;direction+=2)
			{
				int next_index=station_index+direction;
				Station station;
				if(next_index>=0 and next_index<routes[next].get_count() and
					routes[next].get_station(next_index,station) and not visited[station.get_id()])
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
			if(routes[line].find_station(source_id)>=0)
			{
				route_details=routes[line].get_name();
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
			route_details+=routes[line].get_name();
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
		cout<<"Invalid ticket type."<<endl;
		return;
	}
	bool digital=ticket_type==2;
	const Metro& metro=regular;
	double fare=metro.calculate_fare(extra_stops,digital);
	if(fare<0)
	{
		cout<<"Unable to calculate fare."<<endl;
		return;
	}
	cout<<endl<<"Journey route: "<<route_details<<endl;
	cout<<"Extra stops: "<<extra_stops<<endl;
	cout<<"Fare: INR "<<fare<<endl<<"Passenger name: ";
	string passenger;
	getline(cin,passenger);
	Station from=stations[source_index];
	Station to=stations[destination_index];
	Ticket ticket(next_ticket_id,passenger,from,to,fare,route_details,extra_stops,digital);
	tickets[ticket_count++]=ticket;
	++next_ticket_id;
	cout<<"Ticket generated."<<endl<<ticket<<endl;
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
	cout<<"Welcome to Chennai Metro Rail Service"<<endl;
	while(true)
	{
		cout<<endl<<"===== Main Menu ====="<<endl;
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
