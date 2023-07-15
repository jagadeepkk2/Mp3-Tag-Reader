/*
Name:
Description:
Date:
Sample input:
Sample output:
 */
#include<stdio.h>
#include "main.h"
int main(int argc, char **argv)
{
	int op;
	if(argc<2)
	{
		printf("--------------------------------------------------\n\n"
				"ERROR: ./a.out : INVALID ARGUMENTS\n"
				"USAGE:\n"
				"To view please pass like : ./a.out -v mp3filename\n"
				"To edit please pass like : ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3_filename\n"
				"To get help pass like : ./a.out --help\n\n"
				"--------------------------------------------------\n");
		return 0;
	}
	else
	{
		if(check_operation_type(argv)== e_view)
		{
			if(read_and_validate_view_args(argv)==e_success)
			{
				printf("Read and validate Successful\n");

				printf("--------------- SELECTED VIEW DETAILS ---------------\n\n");

				view(argv);
				printf("-----------DETAILS DISPLAYED SUCCESSFULLY------------\n");

			}
			else
			{
				printf("Read and validate failed\n");
				return 0;
			}




		}
		else if(check_operation_type(argv)== e_edit)
		{

			if(read_and_validate_edit_args(argv)==e_success)
			{
				printf("Read and validate Successful\n");
				edit(argv);

			}
			else
			{
				printf("Read and validate failed\n");
				return 0;
			}

		}

		else if(check_operation_type(argv)== e_help)
		{
			printf("---------------------HELP MENU--------------------\n"
					"1. -v -> to view mp3 file contents\n"
					"2. -e -> to edit mp3 file contents\n"
					"\t 2.1. -t -> to edit song title\n"
					"\t 2.2. -a -> to edit artist name\n"
					"\t 2.3. -A -> to edit album name\n"
					"\t 2.4. -y -> to edit year\n"
					"\t 2.5. -m -> to edit content\n"
					"\t 2.6. -c -> to edit comment\n"
					"--------------------------------------------------\n");
		}

	}



return 0;
}
