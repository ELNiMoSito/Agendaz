#ifndef __MENUS_HPP__
#define __MENUS_HPP__

#include <filesystem>

namespace fs=std::filesystem;

	struct information{
	std::string name;
	std::string description;
	std::string id;
	};
	void AskSave(fs::path& agenda);
	void CloseAgenda(fs::path& agenda);
	void menu1();
	void UserChoiceMenu1(char& choice);
	void UserChoiceMenu2(char& choice);
	void AgendaChoice(int i, int& num);
	void LeaveApp();
	void DeleteAgenda();
	void LoadAgenda();
	void AskMakeAgenda();
	void ClearScreen();
	std::filesystem::path CreateAgenda(information& agenda);
	void menu2(std::filesystem::path agendarep);
	void CloseAgenda(fs::path& agenda);
	void DeleteEvent(fs::path& agenda);
	void AddEvent(fs::path& agenda);
	void ExportHTML(fs::path&agenda);
	void PrintAgenda(fs::path& agenda);
	void LoadAgenda();
	std::string getUID(int& len);
	std::filesystem::path NewAgenda(information& agenda);
	std::filesystem::path TakeRep();

	//FAIRE 4 HPP, UN HPP MENU, UN HPP STYLE, UN HPP DATE, UN HPP AGENDA UN HPP POUR LES ERREURS
	//METTRE LES CONST POURFAIRE STYLER
	//
#endif