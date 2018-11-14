#include <memory>
#include "pancake_house_menu.h"
#include "diner_menu.h"
#include "waitress.h"

void printMenu(); 

int main(int argc, char *argv[]) {
	auto pancakeHouseMenu = std::make_shared<PancakeHouseMenu>();
	auto dinerMenu = std::make_shared<DinerMenu>();

	Waitress waitress(pancakeHouseMenu, dinerMenu);
	waitress.printMenu();

	std::cout << "\n======= old way of printMenu ======\n";
	printMenu();
	return 0;
}

void printMenu() {
	PancakeHouseMenu pancakeHouseMenu;
	DinerMenu dinerMenu; 

	auto &breakfastItems = pancakeHouseMenu.getMenuItems();

	for (int i = 0; i < breakfastItems.size(); i++) {
		MenuItem &menuItem = breakfastItems[i];
		std::cout << menuItem.getName()
					<< "\t\t" << menuItem.getPrice() << '\n'
					<< "\t" << menuItem.getDescription()
					<< '\n';
	}

	MenuItem *lunchItems = dinerMenu.getMenuItems();

	for (int i = 0; i < dinerMenu.length(); i++) {
		MenuItem &menuItem = lunchItems[i];
		std::cout << menuItem.getName()
					<< "\t\t" << menuItem.getPrice() << '\n'
					<< "\t" << menuItem.getDescription()
					<< '\n';
	}
}
