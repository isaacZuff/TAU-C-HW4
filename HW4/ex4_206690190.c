#define MAX_NUM_PRODUCTS 20
#define MAX_PRODUCT_NAME_LENGTH 20
#define MAX_CATEGORY_LENGTH 10
#define BARCODE_LENGTH 12
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char * main_interface = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"\
"Welcome to CORONA market!\n"\
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"\
"Manage market menu:\n"\
"	1. Add product\n"\
"	2. Remove product\n"\
"	3. Check which products are expired\n"\
"	4. Print all the products\n"\
"	5. Update product\n"\
"	6. EXIT SYSTEM\n"\
"Please choose operation [1-6]:";

//operation 1 constant strings

const char *  adding_product_barcode = "Please enter product barcode:";
const char * barcode_already_exist = "This product already exist, please enter the number of products to add: ";
const char * too_much_products = "Can't add more products, not enough space!";
const char * adding_product_name = "Please enter product name:";
const char * adding_product_category = "Please enter product category:";
const char * adding_product_number = "Please enter number of products to add:";
const char * adding_product_price = "Please enter the price of the product:";
const char * adding_product_date = "Please enter expiration date of the product[dd/mm/yy]:";

//operation 2 constant strings
const char * store_empty = "The store is empty!";
const char * delete_barcode = "Please enter product barcode you want to delete:";
const char * delete_barcode_cant_find = "Couldn't find the product barcode, try again...";
const char * delete_barcode_succeed = "The product deleted successfully!";


//operation 3 constant strings
const char * expired_date_check = "What date you want to check[dd/mm/yy]:";
const char * expired_products = "~~~~~~~~~~~~~~~Expired Products~~~~~~~~~~~~~~~\n";
const char * expired_product_name = "Product name: ";
const char * expired_product_barcode = "Product barcode: ";
const char * expired_product_date = "Product expiration date: ";


//operation 4 constant strings
const char * print_products_head = "~~~~~~~~~~~~~~~All Products~~~~~~~~~~~~~~~\n";
const char * print_no_products = "No products in the store!\n";
const char * print_products = "----------";
const char * print_product_name = "Product name: ";
const char * print_product_barcode = "Product barcode: ";
const char * print_product_category = "Product category: ";
const char * print_product_number = "Product available quantity: ";
const char * print_product_price = "Product price: ";
const char * print_product_expireDate = "Product expiration date: ";
const char * print_total_number = "Total number of products: ";

//operation 5 constant strings
const char * update_barcode = "Please enter product barcode you want to update:";
const char * update_barcode_notFound = "Couldn’t find the product barcode, try again...";
const char * update_interface_string = ("What do you want to update?\n"\
	"	1. Product name\n"\
	"	2. Product category\n"\
	"	3. Product quantity\n"\
	"	4. Product price\n"\
	"	5. Product expiration date\n"\
	"Please choose operation [1-5]:");
const char * update_product_name = "Please enter new product name:";
const char * update_product_category = "Please enter new product category:";
const char * update_product_number = "Please enter new product quantity:";
const char * update_product_price = "Please enter new product price:";
const char * update_product_date = "Please enter new product expiration date[dd/mm/yy]:";

//operation 6 constant strings
const char * exitProgram = "exit...";

//my consts
const char * allocation_failed = "Memory allocation failed.\n";

typedef struct date
{
	int year;
	int month;
	int day;
} date;

typedef struct product
{
	char * product_name;
	char * product_category;
	char * barcode;
	int available;
	double price;
	date * expire_date;
} product;

typedef struct super_market
{
	product ** product_list;
	int number_of_products;
} super_market;


/*Inputs: char*
Return parameter: None
Function functionality: prints the string*/
void print_string(const char* str)
{
	printf("%s", str);
}

/*Inputs: char*
Return parameter: None
Function functionality: prints the string and \n*/
void print_line_string(const char* str)
{
	printf("%s\n", str);
}

/*Inputs: date
Return parameter: None
Function functionality: prints date and \n */
void print_line_date(date* print_date)
{
	printf("%d/%d/%d\n", print_date->day, print_date->month, print_date->year);
}

/*Inputs:  int
Return parameter: None
Function functionality: prints double and \n */
void print_line_integer(int n)
{
	printf("%d\n", n);
}

/*Inputs:double
Return parameter: None
Function functionality:  prints double and \n*/
void print_line_double(double n)
{
	printf("%g\n", n);
}

/*Inputs: pointer
Return parameter: zero if bad pointer 1 if good
Function functionality: check if allocation of memory was good*/
int validate_pointer(void* p)
{
	if (p == NULL)
	{
		free(p);
		print_string(allocation_failed);
		return 0;
	}
	return 1;
}

/*Inputs:
Return parameter: int
Function functionality: parse integer from user */
int get_integer()
{
	int n = 0;
	scanf("%d", &n);
	return n;
}

/*Inputs:
Return parameter: double 
Function functionality: parse decimal number from user info */
double get_double()
{
	double n = 0;
	scanf("%lf", &n);
	return n;
}

/*Inputs:
Return parameter: pointer to date struct
Function functionality: parse date info from user info*/
date* get_date()
{
	date* input_date = malloc(sizeof(date));
	if(validate_pointer(input_date) == 0)
	{
		return input_date;
	}
	
	scanf("%d/%d/%d", &input_date->day, &input_date->month, &input_date->year);
	return input_date;
}

/*Inputs: pointer to products array, index to remove
Return parameter: None
Function functionality: removes products from a specific index in the array */
void remove_single_product(int index,product*** product_array)
{
	product** list = (*product_array);
	free(list[index]->barcode);
	free(list[index]->product_name);
	free(list[index]->product_category);
	free(list[index]->expire_date);
	free(list[index]);
	list[index] = NULL;
}

/*Inputs:
Return parameter: super_market pointer
Function functionality: Allocating memory for super_market struct*/
super_market* init_super_market()
{
	super_market *market = (super_market*)malloc(sizeof(super_market));
	if(validate_pointer(market)==0)
	{
		exit(1);
	}
	market->number_of_products = 0; 
	market->product_list = (product**)malloc(MAX_NUM_PRODUCTS * sizeof(product*));
	if(validate_pointer(market->product_list)==0)
	{
		free(market);
		exit(1);
	}

	return market;
}

/*Inputs: pointer to super_market pointer
Return parameter: None
Function functionality: prints menu */
void print_interface()
{
	print_string(main_interface);
}

/*Inputs: pointer to super_market pointer
Return parameter: None
Function functionality: Add product to the market using user generated info*/
void add_product(super_market** market)
{
	print_string(adding_product_barcode);
	char barcode[BARCODE_LENGTH + 1];
	char product_name[MAX_PRODUCT_NAME_LENGTH + 1];
	char product_category[MAX_CATEGORY_LENGTH + 1];
	product* product_to_add = NULL;
	scanf("%s", barcode);

	super_market* ampm = *market;
	for (int i=0;i< MAX_NUM_PRODUCTS;i++)
	{
		if (ampm->product_list[i] == NULL) continue;
		if(strcmp(ampm->product_list[i]->barcode,barcode) == 0)
		{
			int product_num = 0;
			print_string(barcode_already_exist);
			product_num = get_integer();
			ampm->product_list[i]->available += product_num;
			printf("Additional %d products of %s added\n",
				product_num, ampm->product_list[i]->product_name);
			return;
		}
	}
	
	if(ampm->number_of_products == MAX_NUM_PRODUCTS)
	{
		print_line_string(too_much_products);
		return;
	}
	product_to_add = malloc(sizeof(product));
	if (validate_pointer(product_to_add) == 0)
	{
		return;
	}
	product_to_add->barcode = _strdup(barcode);
	if (validate_pointer(product_to_add->barcode) == 0)
	{
		free(product_to_add);
		return;
	}
	print_string(adding_product_name);
	scanf("\n%[^\n]s", product_name);
	product_to_add->product_name = _strdup(product_name);
	if (validate_pointer(product_to_add->product_name) == 0)
	{
		free(product_to_add->barcode);
		free(product_to_add);
		return;
	}
	print_string(adding_product_category);
	scanf("\n%[^\n]s", product_category);
	product_to_add->product_category = _strdup(product_category);
	if (validate_pointer(product_to_add->product_category) == 0)
	{
		free(product_to_add->barcode);
		free(product_to_add->product_name);
		free(product_to_add);
		return;
	}
	print_string(adding_product_number);
	product_to_add->available = get_integer();
	print_string(adding_product_price);
	product_to_add->price = get_double();
	print_string(adding_product_date);
	product_to_add->expire_date = get_date();
	for (int i =0;i<MAX_NUM_PRODUCTS;i++)
	{
		if (ampm->product_list[i] == NULL)
		{
			ampm->product_list[i] = product_to_add;
			ampm->number_of_products++;
			printf("The product %s -barcode:%s ,added successfully\n",
				product_to_add->product_name, product_to_add->barcode);
			return;
		}
	}
}

/*Inputs: pointer to super_market pointer
Return parameter: None
Function functionality: Remove specific product and frees the memory by finding specific barcode using for loop */
void remove_product(super_market** market)
{
	char barcode[BARCODE_LENGTH + 1];
	super_market* ampm = *market;
	if(ampm->number_of_products==0)
	{
		print_line_string(store_empty);
		return;
	}
	print_string(delete_barcode);
	
	scanf("%s", barcode);
	
	
	for (int i=0;i<MAX_NUM_PRODUCTS;i++)
	{
		if(ampm->product_list[i] == NULL) continue;
		if (strcmp(ampm->product_list[i]->barcode, barcode) == 0)
		{
			remove_single_product(i, &ampm->product_list);
			ampm->number_of_products--;
			print_line_string(delete_barcode_succeed);
			return;
		}
	}
	print_line_string(delete_barcode_cant_find);
	remove_product(market);
}

/*Inputs: pointer to super_market pointer
Return parameter: None
Function functionality: Lists expired barcode by looping on the market pointer */
void expired(super_market** market)
{
	date* expired_date;
	print_string(expired_date_check);
	expired_date = get_date();
	print_string(expired_products);
	
	super_market* ampm = *market;
	for (int i=0;i<MAX_NUM_PRODUCTS;i++)
	{
		if(ampm->product_list[i] == NULL) continue;
		if( ampm->product_list[i]->expire_date->year < expired_date->year ||
			ampm->product_list[i]->expire_date->year == expired_date->year&&
			ampm->product_list[i]->expire_date->month < expired_date->month||
			ampm->product_list[i]->expire_date->year == expired_date->year &&
			ampm->product_list[i]->expire_date->month == expired_date->month &&
			ampm->product_list[i]->expire_date->day < expired_date->day)
		{
			print_string(expired_product_name);
			print_line_string(ampm->product_list[i]->product_name);
			print_string(expired_product_barcode);
			print_line_string(ampm->product_list[i]->barcode);
			print_string(expired_product_date);
			print_line_date(ampm->product_list[i]->expire_date);
		}
	}

	free(expired_date);
}

/*Inputs: pointer to super_market pointer
Return parameter: None
Function functionality: prints all the products by looping on the market pointer */
void print_all_products(super_market** market)
{
	super_market* ampm = (*market);
	if(ampm->number_of_products == 0)
	{
		print_string(print_no_products);
		return;
	}

	print_string(print_products_head);
	for (int i = 0; i < MAX_NUM_PRODUCTS; i++)
	{
		if (ampm->product_list[i] == NULL) continue;
		print_line_string(print_products);
		print_string(print_product_name);
		print_line_string(ampm->product_list[i]->product_name);
		print_string(print_product_barcode);
		print_line_string(ampm->product_list[i]->barcode);
		print_string(print_product_category);
		print_line_string(ampm->product_list[i]->product_category);
		print_string(print_product_number);
		print_line_integer(ampm->product_list[i]->available);
		print_string(print_product_price);
		print_line_double(ampm->product_list[i]->price);
		print_string(print_product_expireDate);
		print_line_date(ampm->product_list[i]->expire_date);
	}
	print_string(print_total_number);
	print_line_integer(ampm->number_of_products);
}

/*Inputs: pointer to super_market pointer
Return parameter: None
Function functionality: Updates product from a user input barcode  */
void update_product(super_market** market)
{
	super_market* ampm = (*market);
	char barcode[BARCODE_LENGTH + 1];
	
	if (ampm->number_of_products == 0)
	{
		print_string(print_no_products);
		return;
	}

	print_string(update_barcode);
	scanf("%s", barcode);

	for (int i = 0; i < MAX_NUM_PRODUCTS; i++)
	{
		if (ampm->product_list[i] == NULL) continue;
		if (strcmp(ampm->product_list[i]->barcode, barcode) == 0)
		{
			print_string(update_interface_string);
			const int option = get_integer();
			switch (option)
			{
			case 1:
				print_string(update_product_name);
				char product_name[MAX_PRODUCT_NAME_LENGTH + 1];
				scanf("\n%[^\n]s", product_name);
				free(ampm->product_list[i]->product_name);
				ampm->product_list[i]->product_name = _strdup(product_name);
				if (validate_pointer(ampm->product_list[i]->product_name) == 0)
				{
					return;
				}
				break;
			case 2:
				print_string(update_product_category);
				char product_category[MAX_CATEGORY_LENGTH + 1];
				scanf("\n%[^\n]s", product_category);
				free(ampm->product_list[i]->product_category);
				ampm->product_list[i]->product_category = _strdup(product_category);
				if (validate_pointer(ampm->product_list[i]->product_category) == 0)
				{
					return;
				}
				break;
			case 3:
				print_string(update_product_number);
				ampm->product_list[i]->available = get_integer();
				break;
			case 4:
				print_string(update_product_price);
				ampm->product_list[i]->price = get_double();
				break;
			case 5:
				print_string(update_product_date);
				free(ampm->product_list[i]->expire_date);
				ampm->product_list[i]->expire_date = get_date();
				break;
			default:
				break;
			}
			return;
		}
	}

	print_line_string(update_barcode_notFound);
	update_product(market);
}

/*Inputs: pointer to super_market pointer
Return parameter: None
Function functionality: exits the system and frees all heap memory*/
void exit_system(super_market** market)
{
	super_market* ampm = *market;

	for (int i = 0; i < MAX_NUM_PRODUCTS; i++)
	{
		if (ampm->product_list[i] == NULL) continue;
		remove_single_product(i, &ampm->product_list);
		ampm->number_of_products--;
	}
	free(ampm->product_list);
	free(ampm);
	print_line_string(exitProgram);	
}

/*Inputs: pointer to super_market pointer
Return parameter: int
Function functionality: Simple case switch picker for the store menu*/
int pick_option(super_market** market)
{
	const int option = get_integer();
	switch (option)
	{
		case 1:
			add_product(market);
			break;
		case 2:
			remove_product(market);
			break;
		case 3:
			expired(market);
			break;
		case 4:
			print_all_products(market);
			break;
		case 5:
			update_product(market);
			break;
		case 6:
			exit_system(market);
			return 0;
		default:
			return 0;
	}
	return 1;
}

/*Inputs:
Return parameter: int
Function functionality: Main Func*/
int main()
{
	super_market *market = init_super_market();
	int loop = 1;
	for (int i = 0; i < MAX_NUM_PRODUCTS;i++)
	{
		market->product_list[i] = NULL;
	}
	
	
	while (loop)
	{
		print_interface();
		loop = pick_option(&market);
	}

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	_CrtDumpMemoryLeaks();
}
