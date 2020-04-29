#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//INT PRINT PRINT_VARS EXIT

int main() {

	char input[129];
	//enum command c;
	char *c;
	char **var_arr;
	char op, var;// +, -, /, *
	int *value_arr;
	int i, index_f, index_in, count, temp;
	int var1, var2, ret = 0;
	int flag_c, flag_f, flag_cal, flag_error1, flag_error2;
	int flag_exit;
	double val;

	// allocate arrays for dictionary 
	var_arr = (char**)malloc(32 * sizeof(char*));
	for (i = 0; i < 32; i++)
		var_arr[i] = (char*)malloc(31 * sizeof(char));

	value_arr = (int*)malloc(32 * sizeof(int));


	index_in = 0;
	flag_exit = 0;
	count = 0;

	while (1) {
		flag_c = 0, flag_f = 0;
		flag_cal = 0, flag_error1 = 1, flag_error2 = 1;

		if (flag_exit == 1)
			break;

		printf(">> ");
		fgets(input, 129, stdin);
		c = strtok(input, " ");

		/*
		 *classify the command that user inputs
		 */
		if (strncmp(c, "INT", 3) == 0)
			flag_c = 1;
		else if (strncmp(c, "PRINT", 5) == 0) {

			if (strncmp(c, "PRINT_VARS", 10) == 0)
				flag_c = 3;
			else
				flag_c = 2;
		}
		else if (strncmp(c, "EXIT", 4) == 0)
			flag_c = 4;
		else
			flag_c = 5;

		switch (flag_c) {
			/*INT
			 * :insert variabe name and integer value to arrays
			 */
		case 1: c = strtok(NULL, " ");
			strcpy(var_arr[index_in], c);

			c = strtok(NULL, " ");
			val = atof(c);
			if (val - (int)val == 0) {
				value_arr[index_in++] = (int)val;
				count++;
			}
			else
				printf("error\n");

			break;

			/* PRINT
		   :use for loop to find variable array index that matched input name and return the value in the index of value array
		  @return: value that matches with variable name that user inputs
		 */
		case 2: c = strtok(NULL, " ");

			for (i = 0; i < count; i++) {

				temp = strlen(var_arr[i]);
				if (strncmp(var_arr[i], c, temp) == 0) {
					index_f = i;
					flag_f = 1;
					break;
				}
			}
			if (flag_f == 0)
				printf("not found\n");
			else
				printf("%d\n", value_arr[index_f]);

			break;

			/* PRINT_VARS
		   : use for loop and print all the names and value of variables in the array
		   @return: 'variable_name = variable_value' all elements in the arraays
		*/
		case 3: if (count == 0)
			printf("empty\n");
				else {
			for (i = 0; i < count; i++) {
				printf("%s=%d\n", var_arr[i], value_arr[i]);
			}
		}
				break;

				/* EXIT
				   : set the flag_exit and make this while loop end
				 */
		case 4: flag_exit = 1;
			break;

			/* caculate
			   : calculate the values or variables by using switch and case expression
			   @return: calculation result value
			 */
		case 5: var = *c;
			if ('0' <= var && var <= '9') {
				flag_error1 = 0;
				var1 = atoi(c);
			}
			else {
				for (i = 0; i < count; i++) {
					temp = strlen(var_arr[i]);
					if (strncmp(var_arr[i], c, temp) == 0) {
						flag_error1 = 0;
						break;
					}
				}
				var1 = value_arr[i];
			}


			c = strtok(NULL, " ");
			op = *c;

			switch (op) {
			case '+': flag_cal = 1; break;
			case '-': flag_cal = 2; break;
			case '*': flag_cal = 3; break;
			case '/': flag_cal = 4; break;
			}

			c = strtok(NULL, " ");
			var = *c;
			if ('0' <= var && var <= '9') {
				var2 = atoi(c);
				flag_error2 = 0;
			}
			else {
				for (i = 0; i < count; i++) {
					temp = strlen(var_arr[i]);
					if (strncmp(var_arr[i], c, temp) == 0) {
						flag_error2 = 0;
						break;
					}
				}
				var2 = value_arr[i];
			}

			switch (flag_cal) {
			case 1: ret = var1 + var2; break;
			case 2: ret = var1 - var2; break;
			case 3: ret = var1 * var2; break;
			case 4: if (var2 == 0)
				flag_error2 = 1;
					else
				ret = var1 / var2;
				break;
			}

			if (flag_error1 + flag_error2 == 0)
				printf("%d\n", ret);
			else
				printf("error\n");

			break;
		}
	}


	/*free the allocated arrays*/
	for (i = 0; i < 32; i++)
		free(var_arr[i]);
	free(var_arr);
	free(value_arr);

	return 0;
}
