#include <iostream>
#include <filesystem>
#include<string>
#include <fstream>
#include "date.hpp"
#include "menus.hpp"

/*if (la date de fin est inf date debut ou inferieur 2023)
{
	refaire une dmd de date
}
sinon si c'est la meme' année comparé les mois
sinon si l annee de la date de fin est plus grande alors on fait pas les autres conditions*/
void maxday(Date & date, int& MAX)
{
	if(date.month==1 || date.month==3||date.month==5 ||date.month==7 || date.month==8 ||date.month==10||date.month==12)
		{
			MAX=31;
		}
	else if(date.month==4 || date.month==6 ||date.month==9 || date.month==11)
		{
			MAX=30;
		}
	else 
	{
		if (date.year%400==0 || (date.year%4==0  && date.year%100!=0))
		{
			MAX=29;
		}
		else
		{
			MAX=28;
		}
					
	}	
}
void ChooseDateEnd(Date& dateend, Date& datebegin)
{
	int max=0;
	std::cout<<"Choisissez une date de fin pour l'évenement"<<std::endl
	<<"Rentrez une année :"<<std::endl;
	std::cin>>dateend.year;
	while(dateend.year<datebegin.year)
		{
			std::cout<<"l'évenement ne peut pas se terminer avant qu'il ne commences !"<<std::endl;
			std::cin>>dateend.year;
		}

	if(dateend.year==datebegin.year)
	{
		std::cout<<"mois: "<<std::endl;
		std::cin>>dateend.month;
		while((dateend.month<datebegin.month) || (dateend.month>12))
		{
			std::cout<<"l'évenement ne peut pas se terminer avant qu'il ne commences !"<<std::endl;
			std::cin>>dateend.month;
		}
		maxday(dateend, max);
		if(dateend.month==datebegin.month)
		{
			std::cout<<"jour: "<<std::endl;
			std::cin>>dateend.day;
			while((dateend.day<datebegin.day)|| (dateend.day>max))
			{
				std::cout<<"l'événement ne peut pas se terminer avant qu'il ne commences !"<<std::endl;
				std::cin>>dateend.day;
			}
			if (dateend.day==datebegin.day)
			{
				std::cout<<"heure: "<<std::endl;
				std::cin>>dateend.temps.hour;
				while((dateend.temps.hour<datebegin.temps.hour)||(dateend.temps.hour >=24))
				{
					std::cout<<"l'événement ne peut pas se terminer avant qu'il ne commences !"<<std::endl;
					std::cin>>dateend.temps.hour;
				}
				if (dateend.temps.hour== datebegin.temps.hour)
				{
					std::cout<<"minute: "<<std::endl;
					std::cin>>dateend.temps.minute;
					while((dateend.temps.minute<datebegin.temps.minute)||(dateend.temps.minute>=60))
					{
						std::cout<<"l'évenement ne peut pas se terminer avant qu'il ne commences !"<<std::endl;
						std::cin>>dateend.temps.minute;
					}
				}
				else if (dateend.temps.hour>=datebegin.temps.hour)
				{
					std::cout<<"minute: "<<std::endl;
					std::cin>>dateend.temps.minute;
					while (datebegin.temps.minute >=60)
					{
						std::cout<<"Rentrez la durée d'une minute entre 0 et 59 !"<<std::endl;
						std::cin>>datebegin.temps.minute;
					}
				}
			}
			else if (dateend.day>datebegin.day)
			{
				std::cout<<"heure: "<<std::endl;
				std::cin>>dateend.temps.hour;
				while (dateend.temps.hour>=24)
				{
					std::cout<<"Une journée dure 23h59!"<<std::endl;
					std::cin>>dateend.temps.hour;
				}
					std::cout<<"minute: "<<std::endl;
					std::cin>>dateend.temps.minute;
					while (datebegin.temps.minute >=60)
				{
					std::cout<<"Rentrez la durée d'une minute entre 0 et 59 !"<<std::endl;
					std::cin>>datebegin.temps.minute;
				}
			}
			}
		else if(dateend.month>datebegin.month)
		{
			std::cout<<"jour: "<<std::endl;
			std::cin>>dateend.day;
			while (dateend.day >max ||dateend.day<1)
			{
				std::cout<<"Le mois "<<dateend.month<<" comporte "<<max<<" jours, ressaisissez le jour de l'évenement"<<std::endl;
				std::cin>>dateend.day;
			}
			std::cout<<"heure: "<<std::endl;
			std::cin>>dateend.temps.hour;
			while (dateend.temps.hour>=24)
			{
				std::cout<<"Une journée dure 23h59!"<<std::endl;
				std::cin>>dateend.temps.hour;
			}
			std::cout<<"minute: "<<std::endl;
			std::cin>>dateend.temps.minute;
			while (datebegin.temps.minute >=60)
			{
				std::cout<<"Rentrez la durée d'une minute entre 0 et 59 !"<<std::endl;
				std::cin>>datebegin.temps.minute;
			}
		}
	}
	else if(dateend.year>datebegin.year)
	{
		std::cout<<"mois: "<<std::endl;
		std::cin>>dateend.month;
		while(dateend.month>12 ||dateend.month<1 )
		{
			std::cout<<"Il n'y a que 12 mois dans l'année !"<<std::endl;
			std::cin>>dateend.month;
		}
		maxday(dateend, max);
		std::cout<<"jour: "<<std::endl;
		std::cin>>dateend.day;
		while (dateend.day >max ||dateend.day<1)
		{
			std::cout<<"Le mois "<<dateend.month<<" comporte "<<max<<" jours, ressaisissez le jour de l'évenement"<<std::endl;
			std::cin>>dateend.day;
		}
		std::cout<<"heure: "<<std::endl;
		std::cin>>dateend.temps.hour;
		while (dateend.temps.hour>=24)
		{
			std::cout<<"Une journée dure 23h59!"<<std::endl;
			std::cin>>dateend.temps.hour;
		}
		std::cout<<"minute: "<<std::endl;
		std::cin>>dateend.temps.minute;
		while (dateend.temps.minute >=60)
		{
			std::cout<<"Rentrez la durée d'une minute entre 0 et 59 !"<<std::endl;
			std::cin>>datebegin.temps.minute;
		}
	}
}

void ChooseDateBegin(Date& datebegin)
{

	std::cout<<"Choisissez une date de début pour l'évenement"<<std::endl
	<<"Rentrez une année :"<<std::endl;
	std::cin>>datebegin.year;
	while(datebegin.year<2023)
		{
			std::cout<<"L'année doit être au minimum 2023 !"<<std::endl;
			std::cin>>datebegin.year;
		}
	std::cout<<"mois: "<<std::endl;
	std::cin>>datebegin.month;
	while(datebegin.month>12 || datebegin.month <1)
		{
			std::cout<<"Il n'y a que 12 mois dans l'année !"<<std::endl;
			std::cin>>datebegin.month;
		}
		int max=0;
		maxday(datebegin, max);
	std::cout<<"jour: "<<std::endl;
	std::cin>>datebegin.day;
	while (datebegin.day >max ||datebegin.day<1)
	{
		std::cout<<"Le mois "<<datebegin.month<<" comporte "<<max<<" jours, ressaisissez le jour de l'évenement"<<std::endl;
		std::cin>>datebegin.day;
	}

	std::cout<<"heure:"<<std::endl;
	std::cin>>datebegin.temps.hour;
	while (datebegin.temps.hour>=24)
	{
		std::cout<<"Une journée dure 23h59!"<<std::endl;
		std::cin>>datebegin.temps.hour;
	}
	std::cout<<"minute:"<<std::endl;
	std::cin>>datebegin.temps.minute;
	while (datebegin.temps.minute >=60)
	{
		std::cout<<"Rentrez la durée d'une minute entre 0 et 59 !"<<std::endl;
		std::cin>>datebegin.temps.minute;
	}
}