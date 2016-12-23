#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct phonenumber
{
	char number[10];
	char type[10];
	struct phonenumber *next;
};

struct record
{
	char first_name[30];
	char last_name[30];
	char city[10];
	int age;
	float height;
	struct phonenumber *phno;
	struct record *next;

};

void print_record(struct record *lists)
{
	int count = 0;
	struct record *temp = lists;
	printf("the records are \n");
	for (count = 0; temp != NULL; count++, temp = temp->next)
	{
		printf("the record:%d is %d\n", count);
		struct phonenumber *phone = temp->phno;
		printf("firstname:%s\nlastname:%s\nage:%d\nheight:%f\n", temp->first_name, temp->last_name, temp->age, temp->height);
		for (; phone != NULL; phone = phone->next)
			printf("type:%s\nnumber:%s", phone->type, phone->number);
	}
}

struct record * makerecord(FILE *fp)
{
	char ch, temp[20], exp[50];
	int top = -1, i, j, k, count = 0, hcount = 0, fcount = 0, star = 0, v1, v2;
	char keywords[10][14] = { "firstName", "lastName", "age", "height", "phonenumbers", "type", "home", "fax", "number", "city" };
	struct record *tmp, *val, *head = NULL, *tail = NULL;
	struct phonenumber *phno, *ptail = NULL, *phead = NULL;
	val = (struct record *)malloc(sizeof(struct record));
	val->phno = NULL;
	do
	{
		ch = fgetc(fp);
		if (ch == '{' || ch == '[')
		{
			exp[++top] = ch;
		}
		if (ch == '"')
		{
			j = 0;
			while ((ch = fgetc(fp)) != '"')
			{
				temp[j++] = ch;

			}
			temp[j] = '\0';
			for (i = 0; i<10; i++)
			{
				if (strcmp(temp, keywords[i]) == 0)
				{
					break;
				}
			}
			if (i == 0 || i == 1 || i == 5 || i == 8 || i == 9)
			{

				if ((ch = fgetc(fp)) == ':')
				{
					while ((ch = fgetc(fp)) != '"')
					{

					}
					j = 0;
					while ((ch = fgetc(fp)) != '"')
					{
						temp[j++] = ch;
					}
					temp[j] = '\0';

					switch (i)
					{
					case 0:
						strcpy(val->first_name, temp);
						break;
					case 1:
						strcpy(val->last_name, temp);
						break;
					case 9:
						strcpy(val->city, temp);
						break;
					case 5:
					{


							  phno = (struct phonenumber *)malloc(sizeof(struct phonenumber));
							  strcpy(phno->type, temp);
							  break;
					}
					case 8:
					{
							  for (v1 = 0, v2 = 0; v1<strlen(temp); v1++)
							  {
								  if (temp[v1] >= '0'&& temp[v1] <= '9')
									  phno->number[v2++] = temp[v1];
							  }
							  phno->number[v2] = '\0';
							  phno->next = NULL;
							  phno->next = NULL;
							  if (val->phno == NULL)
							  {
								  val->phno = phno;
							  }
							  else
							  {
								  ptail = val->phno;
								  while (ptail->next != NULL)
								  {
									  ptail = ptail->next;
								  }
								  ptail->next = phno;
							  }

							  break;
					}
					}
				}
			}
			else if (i == 2 || i == 3)
			{
				if ((ch = fgetc(fp)) == ':')

				{
					do
					{
						ch = fgetc(fp);
					} while (!(ch >= '0'&&ch <= '9'));
					j = 0;
					while (ch != ',')
					{
						temp[j++] = ch;
						ch = fgetc(fp);
					}
					temp[j] = '\0';
					if (i == 2)
					{
						val->age = atoi(temp);
					}
					else
					{
						val->height = atof(temp);
					}
				}

			}
			else if (i == 4)
			{
				if (ch = fgetc(fp) == ':')
				{
					do
					{
						ch = fgetc(fp);
					} while (ch != ' ' || ch == '\t' || ch == '\n');
					if (ch == '[')
					{
						exp[++top] = ch;
					}
					else
					{
						printf("\n Error occured......");
						return;
					}
				}
			}

		}

		if (ch == '}' || ch == ']')
		{
			if ((ch == '}' && exp[top] == '{') || (ch == ']' && exp[top] == '['))
			{

				top--;
				if (top == -1)
				{
					val->next = NULL;
					if (head == NULL)
					{
						head = tail = val;
					}
					else
					{
						tail->next = val;
						tail = val;
					}
					val = (struct record *)malloc(sizeof(struct record));
					val->phno = NULL;
				}

			}
			else
			{
				printf("\n Error in file......");
				return;
			}

		}
	} while (ch != EOF);
	return head;
}

void get_details_by_last_name(struct record *lists, char *name)
{
	struct record *temp = lists;
	for (; temp != NULL&& strcmp(strlwr(name), strlwr(temp->last_name)) != 0; temp = temp->next);
	if (temp != NULL)
	{
		struct phonenumber *phone = temp->phno;
		printf("firstname:%s\nlastname:%s\nage:%d\nheight:%f\n", temp->first_name, temp->last_name, temp->age, temp->height);
		for (; phone != NULL; phone = phone->next)
			printf("type:%s\nnumber:%s\n", phone->type, phone->number);
		return;
	}
	printf("no record with %s(first name) found\n ", name);
}
void get_details_by_first_name(struct record *lists, char *name)
{
	struct record *temp = lists;
	for (; temp != NULL&& strcmp(strlwr(name), strlwr(temp->first_name)) != 0 ; temp = temp->next);
	if (temp != NULL)
	{
		struct phonenumber *phone = temp->phno;
		printf("firstname:%s\nlastname:%s\nage:%d\nheight:%f\n", temp->first_name, temp->last_name, temp->age, temp->height);
		for (; phone != NULL; phone = phone->next)
			printf("type:%s\nnumber:%s\n", phone->type, phone->number);
		return;
	}
	printf("no record with %s(first name) found \n", name);
	
}
void get_phoneno_byfirstname(struct record *lists,char *name)
{
	struct record *temp = lists;
	for (; temp != NULL && strcmp(strlwr(name), strlwr(temp->first_name)) != 0; temp = temp->next);
	if (temp != NULL)
	{
		printf("phone numbers are \n");
		for (struct phonenumber *phone = temp->phno; phone != NULL; phone = phone->next)
			printf("%s\t%s\n", phone->type, phone->number);
		return;
	}
	printf("no records found with person named %s (first name) \n", name);
}
int main(void)
{
	int count;
	struct record *lists = NULL;
	struct record temp;
	FILE *fp = fopen("testfile.txt", "r");
	if (fp == NULL)
	{
		printf("the file is not presnt \n");
		exit(1);
	}
	else
	{
		lists = makerecord(fp);
		print_record(lists);
	}
	printf("enter the name to get the details of the person \n");
	scanf("%s", temp.first_name);
	get_details_by_first_name(lists, temp.first_name);
	printf("enter the name to get his phone number\n");
	scanf("%s", temp.first_name);
	get_phoneno_byfirstname(lists, temp.first_name);
	scanf("%d", &count);
}