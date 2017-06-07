/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Milka Valkanova
* @idnumber 45155
* @task 1
* @compiler VC
*
*/

  #include "Dictionary.h"

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "Invalid arguments!\n";
		return 0;
	}
	Dictionary d(argv[1]);
	d.search(argv[2]);
	int i = 3;
	while (i < argc)
	{
		d.search(argv[i]);
		i++;
	}
	return 0;
}