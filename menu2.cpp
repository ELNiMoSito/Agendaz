#include <iostream>
#include <filesystem>
#include<string>
#include <fstream>
#include<vector>
#include "date.hpp"
#include "menus.hpp"

void AskSave(fs::path& temp)
{
	char choice='X';
	std::cout<<"Le/les évenement(s) que vous venez de créer ne sont pas encore sauvegardés, que voulez-vous faire, les sauvegarder [O] ou les supprimer ? [N]"<<std::endl;
	std::cin>>choice;
	while ((choice != 'O') && (choice !='N'))
	{
		std::cout<<"Choix invalide, veuillez taper O pour sauvegarder ou N pour les effacer."<<std::endl;
		std::cin>>choice;
	}
	std::string ToMenu="z";
	if (choice == 'O')
	{
		fs::path parent=temp.parent_path();// On prend le dossier parent
		fs::path event=parent / "Evenements";
		fs::directory_entry de (event);
		if(!de.exists())
		{
			fs::create_directory(event);
			
		}
									//Creation du rep Evenements
		fs::copy(temp,event);
		fs::remove_all(temp);		
		std::cout<<"Les évenements temporaires sont sauvegardés"<<std::endl;
		std::cout<<"Appuyez sur n'importe quelle touche afin de revenir au menu principale."<<std::endl;
			std::cin>>ToMenu;
		CloseAgenda(temp);
	}
	else if (choice =='N')
	{
		fs::remove_all(temp);
		std::cout<<"Les évenements temporaires sont effacés."<<std::endl
		<<"Appuyez sur n'importe quelle touche afin de revenir au menu principale"<<std::endl;
		std::cin>>ToMenu;
		CloseAgenda(temp);
	}
}

void CloseAgenda(fs::path& agenda)
{
	fs::path eventrep=agenda / "Events of Agenda"; 
	fs::path temp=eventrep /"temp";
	fs::directory_entry de(temp);
	if((!de.exists()))
	{
		ClearScreen();
		menu1();
	}
	else 
	{
	AskSave(temp);
	ClearScreen();
	}
	
}

void DeleteEvent(fs::path& agenda)
{
	std::vector<fs::path> allfiles ={};
	ClearScreen();
	fs::path eventrep=agenda / "Events of Agenda";
	fs::path save = eventrep / "Evenements";
	fs::path temp = eventrep /"temp";
	fs::directory_entry des (save);
	fs::directory_entry dee (eventrep);
	fs::directory_entry det (temp);

	while((!dee.exists())||(is_empty(eventrep)))
	{
		std::cout<<"Aucun évenement n'a été crée (appuyez sur n'importe quelle touche afin de revenir au menu principale)"<<std::endl;
		std::string choice="X";
		std::cin>>choice;
		menu2(agenda);
	}
	if((dee.exists())&&(des.exists())&&(!det.exists()))
	{
		if(is_empty(save))
		{
		std::cout<<"Aucun évenement n'a été crée (appuyez sur n'importe quelle touche afin de revenir au menu principale)"<<std::endl;
		std::string choice="X";
		std::cin>>choice;
		menu2(agenda);
		}
		
	}
	if((dee.exists())&&(det.exists())&&(!des.exists()))
	{
		if(is_empty(temp))
		{
		std::cout<<"Aucun évenement n'a été crée (appuyez sur n'importe quelle touche afin de revenir au menu principale)"<<std::endl;
		std::string choice="X";
		std::cin>>choice;
		menu2(agenda);
		}
		
	}
	if ((des.exists())&&(!is_empty(save)))
	{
		std::cout<<"Quels évenements voulez-vous supprimer parmis vos évènements ci-dessous. (Évènements sauvegardés)"<<std::endl;
		fs::directory_iterator dis(save);
		unsigned short int num=0;
		short int choice;	
		for (const fs::directory_entry& diens: dis)
		{	
			num+=1;
			fs::path element = diens.path();
			std::cout<<element.filename()<<"("<<num<<")"<<std::endl;
			allfiles.push_back(element);
		}
	
		std::cin>>choice;
		while (choice > num || choice< 0)
		{
			std::cout<<"Choisissez un numéro valable"<<std::endl;
			std::cin>>choice;
		}
		fs::path eventchoice= allfiles[choice-1];
		remove(eventchoice);
		allfiles={};
	}
	if ((det.exists())&&(!is_empty(temp)))
	{
		std::cout<<"Quels évènements voulez-vous supprimer parmis vos évènements ci-dessous. (Évènements NON SAUVEGARDÉS)"<<std::endl;
		unsigned short int num=0;
		short int choice;	
		fs::directory_iterator dit(temp);
		for (const fs::directory_entry& dient: dit)
		{	
			num+=1;
			fs::path element = dient.path();
			std::cout<<element.filename()<<"("<<num<<")"<<std::endl;
			allfiles.push_back(element);
		}
	
		std::cin>>choice;
		while (choice > num || choice< 0)
		{
			std::cout<<"Choisissez un numéro valable"<<std::endl;
			std::cin>>choice;
		}
		fs::path eventchoice= allfiles[choice-1];
		remove(eventchoice);
		allfiles={};
	}	
	menu2(agenda);
}

void AddEvent(fs::path& agenda)
{
	fs::path eventrep=agenda /"Events of Agenda";
	fs::path temp=eventrep / "temp";

	fs::directory_entry de(eventrep);
	fs::directory_entry det(temp);
	if((!de.exists()))
		{
			fs::create_directory(eventrep);
			fs::create_directory(temp);
		}
	if((!det.exists()))
		fs::create_directory(temp);
	ClearScreen();
	std::cout<<"Vous voici dans le menu de création d'évènement"<<std::endl;
	information evenement;
	std::cin.ignore();
	std::cout<<"Saisissez un nom pour le nouvel évènement.(Minimum trois lettres)"<<std::endl;
	std::getline(std::cin, evenement.name);

	while(evenement.name.size()<3)
	{
		ClearScreen();
		std::cout<<"Le nom donné à votre évènement dois faire un minimum de trois lettres"<<std::endl;
		std::getline(std::cin, evenement.name);
	}
	int len=evenement.name.size();
	evenement.id = getUID(len);
	std::cout<<"Ecrivez une description pour votre nouvel évènement"<<std::endl;
	std::getline(std::cin, evenement.description);
	
	Date date1,date2;
	ChooseDateBegin(date1);
	ChooseDateEnd(date2,date1);
	
	std::string fichier_name=evenement.name+".txt";
	//STOCKER LES INFOS DATES NOMS ETC DANS LE FICHIER
	
	fs::path fichierEvent=temp/fichier_name;
	
	std::ofstream ofs(fichierEvent);
	ofs<<"INFORMATION SUR L'EVENEMENT:"<<std::endl;
	ofs<<"ID de l'evenement -> "<<evenement.id<<std::endl;
	ofs<<"Nom de l'evenement: "<<evenement.name<<std::endl;
	ofs<<"Description de l'événement: "<<evenement.description<<std::endl;
	ofs<<"Date de début de l'événement: "<<date1.day<<"/"<<date1.month<<"/"<<date1.year<<"  "<<date1.temps.minute<<":"<<date1.temps.hour<<std::endl;
	ofs<<"Date de fin de l'événement: "<<date2.day<<"/"<<date2.month<<"/"<<date2.year<<"  "<<date2.temps.minute<<":"<<date2.temps.hour<<std::endl;
	menu2(agenda);


}
void ExportHTML(fs::path& agenda)
{
	ClearScreen();
	fs::path fichierinfo=agenda / "Agenda_Information";
	fs::path html=agenda /"Agenda.html";
	fs::path eventrep=agenda / "Events of Agenda";
	fs::path save = eventrep / "Evenements";
	fs::directory_entry des (save);
	fs::directory_entry dee (eventrep);
	if(!dee.exists())
	{
		std:cout<<"Nous ne pouvons pas exporter l'agenda au format HTML (aucun évènement n'a été crée."<<std::endl;
		std::cout<<"Appuyer sur une touche pour revenir au menu de l'agenda"<<std::endl;
		std::cin>>pause;
		menu2(agenda);
	}
	else{
	std::ofstream ofs (html);
	ofs<<"<!DOCTYPE html>"<<std::endl;
	ofs<<"<html>"<<std::endl;
		ofs<<"<head>"<<std::endl;
		//ofs<<"<meta charset=";ofs<<"utf-8">""<<std::endl;
	//ofs<<"<meta name="viewport" content="width=device-width, initial-scale=1">
	ofs<<"<title>";
	ofs<<"Agenda Information</title>"<<std::endl;
	ofs<<"</head>"<<std::endl;
	ofs<<"<body>"<<std::endl;
	std::string line;
	std::ifstream info(fichierinfo);
	
	while(std::getline(info, line))
	{
		ofs<<"<h1>";
		ofs<<line;
		ofs<<"</h1>";
	}
	

	fs::directory_iterator di(save);
	for(const fs::directory_entry &de:di)
	{

		fs::path element= de.path();
		std::ifstream contenue (element);
		
		while(std::getline(contenue, line))
		{
			ofs<<"<p>";
			ofs<<line;
			ofs<<"</p>";
		}
		
	}
	ofs<<"<p>";ofs<<"</p>";
	ofs<<"</body>"<<std::endl;
	ofs<<"</html>"<<std::endl;
	std::cout<<std::endl;
	
	std::string pause ="X";


	std::cout<<"Appuyer sur une touche pour revenir au menu de l'agenda"<<std::endl;
	std::cin>>pause;
	menu2(agenda);
	}
}
void PrintAgenda(fs::path& agenda)
{	
	
	ClearScreen();
	fs::path fichierinfo=agenda / "Agenda_Information";
	
	fs::path eventrep=agenda / "Events of Agenda";
	fs::path save = eventrep / "Evenements";
	fs::directory_entry des (save);
	fs::directory_entry dee (eventrep);


	std::ifstream ifs (fichierinfo);
	std::string ligne;
	std::cout<<std::endl;
	if(ifs.is_open())
		
	{
		while(std::getline(ifs, ligne))
		{
			std::cout<<ligne<<std::endl;
		}
		std::cout<<std::endl;
		ifs.close();
	}	
	else
	{
		std::cerr<<"Impossible de lire le fichier";
	}

	std::string pause ="X";

	if ((!dee.exists()))
	{
		std::cout<<"AUCUN EVENEMENT"<<std::endl;
	}

	else if((dee.exists()))
	{
		if((!des.exists()))
		{
			std::cout<<"AUCUN EVENEMENT"<<std::endl;	
		}
		else if((des.exists()))
		{
			if(!is_empty(save))
			{
				fs::directory_iterator di(save);
				for (const fs::directory_entry& de: di)
				{
					fs::path element = de.path();
					std::ifstream readf(element);
					while(std::getline(readf, ligne))
						{
							std::cout<<ligne<<std::endl;
						}
							std::cout<<std::endl;

				}
			}
			else if(is_empty(save))
			{
				std::cout<<"AUCUN EVENEMENT"<<std::endl;
			}
		}
	}	
	std::cout<<"Appuyez sur une touche afin de revenir au menu de l'agenda"<<std::endl;
	std::cin>>pause;
	menu2(agenda);

}
void UserChoiceMenu2(char& choice, fs::path agenda)
{

	do{
		std::cout<<"F0";
		std::cin>>choice;
			switch (choice){
				case '5':
					PrintAgenda(agenda);
					break;
				case '6':
					ExportHTML(agenda);
					break;
				case '7':
					AddEvent(agenda);
					break;
				case '8':
					DeleteEvent(agenda);
					break;
				case '9':
					CloseAgenda(agenda);
					break;

		}
		if(choice!=('5')&&choice!=('6')&&choice!=('7')&&choice!=('8')&&choice!=('9'))
		{
			std::cout<<"Erreur, choix invalide, F0"<<choice<<" n'existe pas, veuillez ressaisir une fonctionnalité disponible"<<std::endl;
		}
	}while(choice!=('5')&&choice!=('6')&&choice!=('7')&&choice!=('8')&&choice!=('9'));
}

void menu2(std::filesystem::path agendarep)
{
	ClearScreen();
	std::cout<<agendarep.filename()<<" est ouvert, que voulez-vous faire ?"<<std::endl
	<<"• Afficher le contenu de l’agenda (F05) "<<std::endl
	<<"• Exporter l’agenda sous la forme d’une page HTML (F06)"<<std::endl
	<<"• Ajouter un événement (F07)"<<std::endl
	<<"• Supprimer un événement (F08)"<<std::endl
	<<"• Fermer l’agenda (F09)"<<std::endl
	<<"Saisissez votre choix. ";

	char choice='X';

	UserChoiceMenu2(choice, agendarep);

}
