#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Patron
{
	struct Patron* next; //
	struct Patron* MVP; //How we find the new MVP
	int coins; // number of coins
	char name[21]; //one Patron

} Patron; //real type name

int main(int argc, char* const argv[])
{
	int count; //use to count the size of the stack
	Patron* patrons = NULL; 
	char buffer[128];
	while (fgets(buffer, sizeof(buffer), stdin))
	{
		int command;
		Patron* patron;

		//Parsed command out
		if (sscanf(buffer, "%d", &command) != 1)
		{
			fprintf(stderr, "%s: Line not in correct format: '%s'\n", argv[0], buffer);
			exit(1);
		}
		int coins; // ammount of money
		char name[21]; // names
		switch (command)
		{
		case 0:
			// game is done
			exit(0);
			break;
		case 1:
			//Someone just entered the arcade
			if (sscanf(buffer, "%*d %d %20s", &coins, name)!= 2)
			{
				fprintf(stderr, "%s: Line not in correct format: '%s'\n", argv[0], buffer);
				exit(1);
			}
			// Creats a patron
			patron = (Patron*)malloc(sizeof(Patron));
			patron->coins = coins; //value we read
			strcpy(patron->name, name);
			if (patrons != NULL)
			{
				if (patron->coins >= patrons->MVP->coins)//this patron is now the new MVP
				{
					patron->MVP = patron;
				}
				else
				{
					patron->MVP = patrons->MVP; //Not the new MVP so he needs to point to the old MVP
				}
			}
			else
			{
				patron->MVP = patron; //only person on the stack
			}
			
			patron->next = patrons;
			patrons = patron; //All linked up now
			break;
		case 2:
			//Someone just left the arcade
			patron = patrons; //pointer to patron at the top of the stack
			patrons = patron->next; // getting a new on the top of the stack
			free(patron); //freeing memory
			break;
		case 3:
			//Who's the MVP
#if false
			patron = patrons; //Has the most money
			count = 0;
			for (Patron* p = patrons; p != NULL; p = p->next) //goes to the next guy
			{
				// if p coins are greater than patron's coins
				if (p->coins > patron->coins)
				{
					patron = p; //we found a new MVP
				}
				count++;
			}
			//Did we find a new mvp
			if (patron != NULL)
			{
				fprintf(stdout, "%d %s\n", count, patron->name);
			}
#else
			if (patrons != NULL)
			{
				fprintf(stdout, "%s\n", patrons->MVP->name);
			}
#endif
			break;
		default:
			//error statement
			fprintf(stderr, "%s: Unrecongized command : %d\n", argv[0], command);
			exit(1);
			break;

		}
	}
}