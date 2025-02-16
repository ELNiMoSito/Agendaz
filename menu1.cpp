#include <iostream>
#include <filesystem>
#include<string>
#include <fstream>
#include <random>
#include <vector>
#include "menus.hpp"

void LoadAgenda()
{
	ClearScreen();
	fs::path rep_courant = fs::current_path();
	fs::path AgendasRep= rep_courant/"Agendas";
	fs::directory_entry de (AgendasRep);
	if((!de.exists())|| (is_empty(AgendasRep)))

	{
		std::cout<<"Aucun agenda n'existe, veuillez créer un agenda (appuyez sur n'importe quelle touche afin de revenir au menu principale)"<<std::endl;
		std::string choice="X";
		std::cin>>choice;
		menu1();
	}

	else 
	{
		std::cout<<"Quel agenda voulez-vous ouvrir parmis vos agendas ci-dessous."<<std::endl;
		unsigned short int num=0;
		short int choice;
		std::vector<fs::path> pathvec ={};
		fs::directory_iterator agendas(AgendasRep);
		for (const fs::directory_entry& de: agendas)
		{
			num+=1;
			fs::path element = de.path();
			std::cout<<element.filename()<<"("<<num<<")"<<std::endl;
			pathvec.push_back(element);
		}
		std::cin>>choice;
		while (choice > num || choice< 0)
		{
			std::cout<<"Choisissez un numéro valable"<<std::endl;
			std::cin>>choice;
		}
		fs::path agendachoice= pathvec[choice-1];
		menu2(agendachoice);
	}
}
void LeaveApp()
{
	return;
}

void DeleteAgenda()
{
	ClearScreen();
	fs::path rep_courant = fs::current_path();
	fs::path AgendasRep= rep_courant/"Agendas";
	fs::directory_entry de (AgendasRep);
	if((!de.exists())|| (is_empty(AgendasRep)))
	{
		std::cout<<"Aucun agenda n'existe, veuillez créer un agenda (appuyez sur n'importe quelle touche afin de revenir au menu principale)"<<std::endl;
		std::string choice="X";
		std::cin>>choice;
		menu1();
	}
	else 
	{
		std::cout<<"Quel agenda voulez-vous supprimer parmis vos agendas ci-dessous."<<std::endl;
		unsigned short int num=0;
		short int choice;
		std::vector<fs::path> pathvec ={};
		fs::directory_iterator agendas(AgendasRep);
		for (const fs::directory_entry& de: agendas)
		{
			num+=1;
			fs::path element = de.path();
			std::cout<<element.filename()<<"("<<num<<")"<<std::endl;
			pathvec.push_back(element);
		}
		std::cin>>choice;
		while (choice > num || choice< 0)
		{
			std::cout<<"Choississez un numéro valable"<<std::endl;
			std::cin>>choice;
		}
		fs::path agendachoice= pathvec[choice-1];
		std::cout<<"Etes vous bien sûr de vouloir supprimer cet Agenda ?[O/N]"<<std::endl;
		char deletechoice = 'Z';
		std::cin>>deletechoice;
		while ((deletechoice != 'O') && (deletechoice !='N'))
			{
				std::cout<<"Choix invalide, veuillez taper O pour Oui ou N pour non."<<std::endl;
				std::cin>>deletechoice;
			}
			std::string ToMenu="z";
		if (deletechoice == 'O')
			{
				fs::remove_all(agendachoice);
				std::cout<<"Agenda supprimé"<<std::endl
			 	<<"Appuyez sur n'importe quelle touche afin de revenir au menu principal"<<std::endl;
			 	std::cin>>ToMenu;
				menu1();
			}
		else 
			{
			 	std::cout<<"L'agenda n'est pas supprimé."<<std::endl
			 	<<"Appuyez sur n'importe quelle touche afin de revenir au menu principal"<<std::endl;
				std::cin>>ToMenu;
			 	menu1();
			}
	}
}

std::filesystem::path NewAgenda(information &agenda)
{
	fs::path rep_courant=fs::current_path();
	fs::path AgendasRep=rep_courant / "Agendas";
	fs::path new_agenda = AgendasRep / agenda.name;
	fs::directory_entry de(new_agenda);
	if(de.exists())
	{
		std::string paused;
		std::cout<<"L'agenda "<<agenda.name<<" existe déjà, appuyez sur une touche afin de revenir au menu de création d'agenda"<<std::endl;
		std::cin>>paused;
		AskMakeAgenda();
	}
	else
	{
	fs::create_directory(new_agenda);
	fs::path agendainfo = new_agenda /"Agenda_Information";
	std::ofstream ofs (agendainfo);
	ofs<<"INFORMATION SUR L'AGENDA :"<<std::endl;
	ofs<<"Nom de l'agenda: "<<agenda.name<<std::endl;
	ofs<<"ID de l'agenda -> "<<agenda.id<<std::endl;
	ofs<<"Description de l'agenda :"<<agenda.description<<std::endl;
	}
	return new_agenda;
}
void AskMakeAgenda()
{
	ClearScreen();
	std::cout<<"Vous voici dans le menu de création d'agenda."<<std::endl;
	information agenda;
	std::cin.ignore();
	std::cout<<"Saisissez un nom pour votre agenda.(Minimum trois lettres)"<<std::endl;
	std::getline(std::cin, agenda.name);

	while(agenda.name.size()<3)
	{
		ClearScreen();
		std::cout<<"Le nom donné à votre agenda dois faire un minimum de trois lettres"<<std::endl;
		std::getline(std::cin, agenda.name);
	}
	int len=agenda.name.size();
	agenda.id = getUID(len);
	std::cout<<"Ecrivez une description pour votre nouvel agenda"<<std::endl;
	std::getline(std::cin, agenda.description);
	fs::path rep_courant=fs::current_path();
	fs::path AgendasRep = rep_courant / "Agendas";
	std::filesystem::path NewAgendaRep;
	fs::directory_entry de(AgendasRep);
	if(!de.exists())
	{
		fs::create_directory(AgendasRep);
		NewAgendaRep = NewAgenda(agenda);
	}
	else 
	{
		NewAgendaRep = NewAgenda(agenda);
	}
	menu2(NewAgendaRep);
}

void UserChoiceMenu1(char& choice)
{
	do{
		std::cout<<"F0";
		std::cin>>choice;
			switch (choice){
				case '1':
					AskMakeAgenda();
					break;
				case '2':
					LoadAgenda();
					break;
				case '3':
					DeleteAgenda();
					break;
				case '4':
					LeaveApp();
					break;
		}
		if(choice!=('1')&&choice!=('2')&&choice!=('3')&&choice!=('4'))
		{
			std::cout<<"Erreur, choix invalide, F0"<<choice<<" n'existe pas, veuillez ressaisir une fonctionnalité disponible"<<std::endl;
		}
	}while(choice!=('1')&&choice!=('2')&&choice!=('3')&&choice!=('4'));
}

void menu1()
{
	ClearScreen();
	std::cout<<"Bienvenue sur votre application d'agenda personnel, que voulez-vous faire ?"<<std::endl;
	std::cout<<"• Créer un agenda vide et l'ouvrir (F01) "<<std::endl
	<<"• Charger un agenda (F02)"<<std::endl
	<<"• Supprimer un agenda (F03)"<<std::endl
	<<"• Fermer le logiciel (F04)"<<std::endl
	<<std::endl
	<<"Saisissez votre choix. ";

	char choice='X';

	UserChoiceMenu1(choice);

}