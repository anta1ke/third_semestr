#include <iostream>
#include <string>
#include <vector>

#include "../lib/include/Archive.h"

/**
 * @brief Вывести результат поиска дел
 * @param archive - ссылка на архив
 * @param title - заголовок результата
 * @param found - массив найденных дел
 */
void printCases(const Archive& archive, const std::string& title, const std::vector<const CriminalCase*>& found);

/**
 * @brief Точка входа в программу
 * @return 0, если программа выполнена корректно
 */
int main() {
	// Объекты типов-наследников
	const Investigator smirnov("Смирнов Алексей Павлович", "14.05.1975", "майор юстиции");
	const Investigator kuznetsova("Кузнецова Ольга Игоревна", "02.09.1982", "капитан юстиции");
	const Convict orlov("Орлов Сергей Николаевич", "21.01.1990", "5 лет лишения свободы");
	const Convict volkov("Волков Дмитрий Андреевич", "11.11.1985", "8 лет лишения свободы");
	const Convict lebedev("Лебедев Игорь Олегович", "30.07.1979", "3 года условно");

	// Коллекция объектов базового типа, заполненная объектами типов-наследников
	const std::vector<const Person*> people = {&smirnov, &kuznetsova, &orlov, &volkov, &lebedev};

	std::cout << "Все люди в архиве:" << std::endl;
	for (const Person* person : people) {
		if (person == nullptr) continue;
		std::cout << person->getInfo() << std::endl;
	}

	const int smirnovId = smirnov.getId();
	const int kuznetsovaId = kuznetsova.getId();
	const int orlovId = orlov.getId();
	const int volkovId = volkov.getId();
	const int lebedevId = lebedev.getId();

	Archive archive;
	for (const Person* person : people) {
		if (person == nullptr) continue;
		archive.addPerson(*person);
	}

	const Article theft("ст. 158", "Кража");
	const Article fraud("ст. 159", "Мошенничество");
	const Article robbery("ст. 162", "Разбой");
	archive.addArticle(theft);
	archive.addArticle(fraud);
	archive.addArticle(robbery);

	CriminalCase case1("Д-2015/17", 2015, "Кража из магазина электроники, ущерб 300 тысяч рублей", theft, smirnovId);
	case1.addConvictId(orlovId);

	CriminalCase case2("Д-2018/42", 2018, "Мошенничество с недвижимостью, группа лиц", fraud, kuznetsovaId);
	case2.addConvictId(volkovId);
	case2.addConvictId(lebedevId);

	CriminalCase case3("Д-2020/05", 2020, "Разбойное нападение на ювелирный магазин", robbery, smirnovId);
	case3.addConvictId(orlovId);

	archive.addCase(case1);
	archive.addCase(case2);
	archive.addCase(case3);

	std::cout << "\nВсе дела:" << std::endl;
	for (const CriminalCase& c : archive.getCases()) {
		std::cout << archive.getCaseInfo(c) << std::endl;
	}

	printCases(archive, "Дела осужденного Орлов Сергей Николаевич:", archive.findByConvict("Орлов Сергей Николаевич"));
	printCases(archive, "Дела следователя Смирнов Алексей Павлович:", archive.findByInvestigator("Смирнов Алексей Павлович"));
	printCases(archive, "Дела, в содержании которых есть \"магазин\":", archive.findByContent("магазин"));
	printCases(archive, "Дела по статье ст. 159:", archive.findByArticle("ст. 159"));
	printCases(archive, "Дела по характеру преступления \"Кража\":", archive.findByArticle("Кража"));
	printCases(archive, "Дела осужденного Неизвестный Человек:", archive.findByConvict("Неизвестный Человек"));

	return 0;
}

void printCases(const Archive& archive, const std::string& title, const std::vector<const CriminalCase*>& found) {
	std::cout << "\n" << title << std::endl;
	if (found.empty()) {
		std::cout << "Ничего не найдено" << std::endl;
		return;
	}
	for (const CriminalCase* c : found) {
		if (c == nullptr) continue;
		std::cout << archive.getCaseInfo(*c) << std::endl;
	}
}
