#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
void yellow() 
  {
  printf("\033[1;33m");
  }
void Green()
   {
   	printf("\033[0;32m");
   }
void red ()
   {
      printf("\033[1;31m");
    }
void Blue()
	{
		printf("\033[0;34m");
	}
void Purple()
	{
		printf("\033[0;35m");
	 }
void Cyan() 
	 {
	 printf("\033[0;36m");
	  }
void White()
	{
	 printf("\033[0;37m");
	}

void loader() //create a loader
  {
     printf("\nloading");
	 Sleep(500);
	 printf(".");
	 Sleep(500);
	 printf(".");
	 Sleep(500);
	 printf(".\n");	
  }
struct user{
   char fullname[50];
   char user_name[50];
   char password[50];
   long long int p_number;	
  }detail;
typedef struct {
    int b_no;
    char s_des[100];// represent start destination 
    char e_des[100];//represent end destination
    int t_seat;// represent total seat
    int a_seat;// represent available seat
    float charge;
  }bus;
typedef struct {
   char user_name[100];
   char s_dest[100];
   char e_dest[100];
   int age;
   int id;
   int s_num;//s_num represent seat number
   int b_number;//b_num represent bus number	
   }passenger;
typedef struct{
	char admin_name[10];
	char admin_password[10];
  }admin;
bus buses[10];
passenger passengers[1000];
int user_count = 0;
int bus_count = 0;
int generate_id()
	{
    //generate the unique id
	   srand(time(0));  
       int num = rand() % 100 + 1; // use rand() function to get the random number
	   return num;
	}
// admin enter the list of bus in the system  
void list_bus() 
   {
		FILE *list;
		list=fopen("list.bin","ab+");
		if(list==NULL)
		{
			printf("sorry ! invalid data");
			exit(1);
		}
		else
		{
			Cyan();
			printf("\n==List of bus==");
			int b_no;
			printf("\nHow many bus you want enter in system:");
			scanf("%d",&b_no);
			if(b_no>10)
			  {
			  	exit(1);
			  }
			else
			{
		         int i=0;
				for(i=0;i<b_no;i++)
				{   
				    printf("\n\nDetails of %d Bus",i+1);
					printf("\nEnter the bus number:");
					scanf("%d",&buses[i].b_no);
					fflush(stdin);
					printf("Enter the source destination:");
					scanf("%s",&buses[i].s_des);
					fflush(stdin);
					printf("Enter the end destination:");
					scanf("%s",&buses[i].e_des);
					fflush(stdin);
					printf("Enter the total seat:");
					scanf("%d",&buses[i].t_seat);
					fflush(stdin);
					printf("Enter the available seat:");
					scanf("%d",&buses[i].a_seat);
					fflush(stdin);
					printf("Enter the travell cost:");
					scanf("%4f",&buses[i].charge);
					fflush(stdin);
					
					fwrite(&buses[i],sizeof(bus),1,list);
				}
			}
		}
	 fclose(list);
    }
//create a function for read the information of bus
void read_bus()
   {
	FILE *list;
	list=fopen("list.bin","rb");
	if(list==NULL)
		{
			printf("sorry ! invalid data");
			exit(1);
		}
	else
		{
			printf("\n=====DETAILS OF BUS=====");
			printf("\n-----------------------------------------------------------------------------------------------------------------------------------------------------------");
			printf("\nBus Number\t\tSource destination\t\t\tEnd destination\t\tTotal seat\t\tAvailable seat\t\tTravell charge");
			printf("\n-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			while(fread(&buses[bus_count],sizeof(bus),1,list))	
			{   
			    Green();
				printf("\n%-3d\t\t\t%-12s\t\t\t\t%+2s\t\t\t%-3.d\t\t\t%--3.d\t\t\t%3.3f",
				buses[bus_count].b_no,
				buses[bus_count].s_des,
				buses[bus_count].e_des,
				buses[bus_count].t_seat,
				buses[bus_count].a_seat,
				buses[bus_count].charge
				);
				fflush(stdin);
				printf("\n");
				bus_count++;
			}
	    }
		fclose(list);
   }
//create a function for booking ticket
void book_tick()
    {
    	int i,j,k,choice;
		int busNo;
		int seat_no;
		int age;
		char userName[100];
		char s_dest[100];
		char e_dest[100];
	    read_bus();
		yellow();
		printf("\n\nEnter the passenger number to proceed:");
		scanf("%d",&choice);
		for(i=0;i<choice;i++)
		{
			printf("\nEnter the bus number:");
			scanf("%d",&busNo);
			fflush(stdin);
			printf("Enter the source destination:");
			gets(s_dest);
			fflush(stdin);
			printf("Enter the end destination:");
			gets(e_dest);
			fflush(stdin);
			int bus_found=0;
			for(i=0;i<bus_count;i++)
			{
				if(buses[i].b_no==busNo)
				{
					bus_found=1;
					if(buses[i].a_seat>0 &&buses[i].t_seat>=buses[i].a_seat)
					{
				    if(strcmp(buses[i].s_des,s_dest)==0&&strcmp(buses[i].e_des,e_dest)==0)
						{
						 	fflush(stdin);
						 	printf("Enter your Name:");
						 	gets(userName);
						 	fflush(stdin);
						 	printf("Enter your age:");
						 	scanf("%d",&age);
						 	seat_no=buses[i].t_seat-buses[i].a_seat +1;
						 	passengers[user_count].b_number=busNo;
						 	passengers[user_count].id=generate_id();
						 	passengers[user_count].s_num=seat_no;
						 	passengers[user_count].age=age;
						 	strcpy(passengers[user_count].user_name,userName);
						 	strcpy(passengers[user_count].s_dest, s_dest);
                            strcpy(passengers[user_count].e_dest, e_dest);
						 	buses[i].a_seat--;
						 	FILE *ticket;
						 	ticket=fopen("tickets.bin","ab+");
						 	if(ticket==NULL)
						 	 {
						 	 	printf("sorry ! invalid data");
						 	 	exit(0);
							  }
							 else
								 {
								 	fwrite(&passengers[user_count],sizeof(passenger),1,ticket);
								 	fclose(ticket);
								 }
							user_count++;
							//update the bus details 
							FILE *blist;
							blist=fopen("list.bin","wb");
							if(blist==NULL)
							 {
							 	printf("sorry!not updated");
							 	exit(1);
							 }
							else
							  {
							  	for( j=0;j<bus_count;j++)
							  	   {
							  	  	 fwrite(&buses[j],sizeof(bus),1,blist);
								   }
								fclose(blist);
							  }
							//update passenger detail
							FILE *tlist;
							tlist=fopen("tickets.bin","wb");
							if(tlist==NULL)
							 {
							 	printf("sorry!not updated");
							 	exit(1);
							 }
							else
							  {
							  	for( k=0;k<user_count;k++)
							  	   {
							  	  	 fwrite(&passengers[k],sizeof(passenger),1,tlist);
								   }
								fclose(tlist);
							  }
							Purple();
							printf("\n\nTicket booked successfully!");
							White();
							printf("\n\nPassenger Details:");
							printf("\nBus_no:%d",busNo);
							printf("\nseat number:%d", seat_no);
							printf("\nPassenger age:%d",age);
							printf("\nSource destination:%s",s_dest);
							printf("\nEnd destination:%s\n",e_dest);
							
						 }
						 else 
							    {
							 	    red();
							        printf("sorry ! no seat available in this bus");
							    }
							    break;
					}
				}
			}
			if(!(bus_found))
			   {
					red();
					printf("sorry ! bus not found");	
				}
		}
	}
//function to show the details information of passengar
void infoPassenger()
	{
	FILE *info;
	passenger temp_pt;
	info=fopen("tickets.bin","rb");
	if(info==NULL)
		{
			printf("\ninvalid ! data");
			exit(1);
		}
	 else
	     printf("\n\n=====PASSENGER INFORMATION======\n");
	     printf("\n---------------------------------------------\n");
		{
		  while(fread(&temp_pt,sizeof(temp_pt),1,info)==1)
			{
				fflush(stdin);
			    printf("Passenger Id: %d\n", temp_pt.id);
				fflush(stdin);
				printf("Bus Number:%d",temp_pt.b_number);
				fflush(stdin);
				printf("\nSeat Number:%d",temp_pt.s_num);
				fflush(stdin);
				printf("\nPassenger Name:%s",temp_pt.user_name);
				fflush(stdin);
				printf("\npassenger Age:%d",temp_pt.age);
				fflush(stdin);
				printf("\nSource destination:%s",temp_pt.s_dest);
				fflush(stdin);
				printf("\nEnd destination:%s",temp_pt.e_dest);
				fflush(stdin);
				printf("\n\n------------------------------------------\n");
				printf("\n");	
				fflush(stdin);
			 }
		}	
		fclose(info);
	}
//function to delete the passenger information 
void show_delete_passenger(int u_id) 
 {
  FILE *RM,*UPDT;
  RM=fopen("tickets.bin","rb") ;
  UPDT=fopen("passen.bin","wb");
	  if(RM==NULL||UPDT==NULL)
	   {
	   	printf("error");
	   	exit(1);
		} 
	  else
	     { 
	      passenger pass;
	      int found=0;
	      while(fread(&pass,sizeof(passenger),1,RM)==1)
		      {
			  	if(pass.id!=u_id)
				  {
				  		fwrite(&pass,sizeof(passenger),1,UPDT);
				   }
				else
				{
					found =1;
				 } 
			}	
	fclose(RM);
	fclose(UPDT);
 if(found)
   {
   	remove("tickets.bin");
   	rename("passen.bin","tickets.bin");
   	printf("Passenger id %d remove sucessfully",u_id);
   }
 else
   {
   	remove("passen.bin");
   	printf("passenger id %d not found",u_id);
   }
}
}
	
//function to delete a bus record
void show_delete_bus(int busNumber)
   {
     FILE *fp;//create two file 
     fp=fopen("list.bin","rb");
     if(fp==NULL)
    	{
    		printf("sorry !data not found");
    		exit(1);
		}
	 int found=0;
	 bus temp_bus;
	 int b_count=0;
	 bus buses[10];
	 while(fread(&temp_bus,sizeof(temp_bus),1,fp))//read data from list.dat file 
		{
			buses[b_count]=temp_bus;
			b_count++;
		}
	  // rewind file pointer to beginning of file
     //fseek(fp, 0, SEEK_SET);
	 fclose(fp);
	 // find and remove bus data 
	 int i=0;
	 int j=0;
	 for(i=0;i<b_count;i++)
		{
			 if(buses[i].b_no==busNumber)
			  {
				  	found=1;
				  	for(j=i;j<b_count;j++)
				  	      {
				  	      	  buses[j]=buses[j+1];
					    	}
						b_count--;
						break;
			 }	
		}
	 if(!found)//if bus number not match then loop comes here
		{
			printf("Bus number %d not found",busNumber);
		}
	 else
	   {   
		    fp=fopen("list.bin","wb");
		    if(fp==NULL)
			    {
			    	printf(" data not found !");
			    	exit(0);
				}
			int i=0;
			for(i=0;i<b_count;i++)
				{
			//	fseek(fp,-1,SEEK_CUR);
				fwrite(&buses[i],sizeof(bus),1,fp);	
				}
			fclose(fp);
			printf("Remove bus number %d sucessfully",busNumber);
	   }
	     //update the bus information 
	     printf("\n\n\nUpdated bus infomation:");
	     printf("\n-----------------------------------------------------------------------------------------------------------------------------------------------------------");
		 printf("\nBus Number\t\tSource destination\t\t\tEnd destination\t\tTotal seat\t\tAvailable seat\t\tTravell charge");
		 printf("\n-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	     for(i=0;i<b_count;i++)
	      {
	      		printf("\n%-3d\t\t\t%-12s\t\t\t\t%+2s\t\t\t%-3.d\t\t\t%--3.d\t\t\t\t%3.3f",
				buses[i].b_no,
				buses[i].s_des,
				buses[i].e_des,
				buses[i].t_seat,
				buses[i].a_seat,
				buses[i].charge);
		  }
    }
void admin_menu()
    {
    	int adm;
    	update:
    	yellow();
    	printf("\n===Admin Menu===");
    	printf("\n1:Add list of Bus");
    	printf("\n2:Update_Bus Information");
    	printf("\n3:Update_passenger Information");
    	White();
    	printf("\nChoose the operation:");
		scanf("%d",&adm);
    	switch(adm)
    	 {
    	 	case 1:
    	 	  list_bus();
			  break;
			case 2:
				read_bus();
		        printf("\nIf you want to update bus detail(y/x):");//y for update  and x for exit
		        char st;
		        scanf("%c",&st);
			    if(st=='y')
				    {
				    int x, Num;;
	                printf("\nEnter how many bus you want to update:");
	                scanf("%d",&x);
	                int i;
	                for( i=0;i<x;i++)
				    {
						printf("\nEnter the bus number:");
						scanf("%d",&Num);
						show_delete_bus(Num);
				    }   
			    	}
			    break;
		    case 3:
			 	printf("===========================");
				infoPassenger();
				printf("=================================");
				char ch;
				printf("\nIf u want to update passenger information(y/n):");
				scanf("%s",&ch);
				if(ch=='y')
				{
					int u_id ;
					printf("\nEnter the passenger Id_number:");
					scanf("%d",&u_id);
				    show_delete_passenger(u_id);
				}
			default:
			  printf("sorry");    	 		
		 }
		Cyan();
	//	system("clear");
	    char ch[5];
		printf("If u do any more update(go/no):");
		scanf("%s",&ch);
		if(strcmp(ch,"go")==0)
		 {
		 	goto update;
		 }
	}
void signup()
	 	{
		FILE *signup;
	 	signup=fopen("login_up.bin","ab+");
	 	if(signup==NULL)
	 	   {
		 		printf("sorry!file not created");
		 		exit(1);
	        }
     	else
	    	{
	    	Green();
			printf("\nEnter the full name:"); 
		    fflush(stdin);
		    yellow();
			fgets(detail.fullname,sizeof(detail.fullname),stdin);
			detail.fullname[strcspn(detail.fullname,"\n")]= '\0';//remove a new line character
			
			Green();
			printf("Enter the user_name:");
			yellow();
			fgets(detail.user_name,sizeof(detail.user_name),stdin);
			detail.user_name[strcspn(detail.user_name,"\n")]='\0';//remove a new line character
			
			Green();
			printf("Enter the password:");
			yellow();	
			fgets(detail.password,sizeof(detail.password),stdin);
			detail.password[strcspn(detail.password,"\n")]='\0';//remove a new line character
			
			Green();
			printf("Enter the phone number:");
			yellow();
			scanf("%lld",&detail.p_number);
			fflush(stdin);
		    
		    fwrite(&detail,sizeof(detail),1,signup);
	    }
	   
	       fclose(signup);
    }
//create a login f
void login()
	{
	   FILE *signup;
	   signup=fopen("login_up.bin","rb");
	   if(signup==NULL)
		   {
		   	printf("sorry !invalid to file");
		   	exit(1);
		   }
	   else
		   {
		   	char user_name[50];
		   	char password[50];
		   	int match=0;
		   	printf("\nEnter the user name:");
		   	fflush(stdin);
		   	fgets(user_name,sizeof(user_name),stdin);
		   	user_name[strcspn(user_name,"\n")]='\0';//remove new line character
		   	
		   	printf("Enter the password:");
		   	fgets(password,sizeof(password),stdin);
		   	password[strcspn(password,"\n")]='\0';// remove new line character
		   	while(fread(&detail,sizeof(detail),1,signup)==1)
		     	{
			   	 if(strcmp(detail.user_name,user_name)==0 && strcmp(detail.password,password)==0 )
			   		{ 
			   		    loader(); 
						Green();
			   			printf("====Information of passanger===");
			   			printf("\nFull_name:%s",detail.fullname);
			   			printf("\nUser_name:%s",detail.user_name);
			   			printf("\nPhone_number:%lld",detail.p_number);
			   			Sleep(4444);
					    system("cls");
			   			match=1;
			   			break;
				    }
		     	 }
		     	if(!match)
					{
						loader();
						red ();
						printf("\t\t\t\t\t\tdata not found!");
						Sleep(4444);
					    system("cls");
				    }
			}
	fclose(signup);	
	}
void user_menu()
	{
		int us_m;
		yellow();
		printf("\n\n===Welcome To Bus Reservation system===");
		printf("\n1:Signup");
	    printf("\n2:Book Ticket");
	    printf("\n3:Passenger Informatfion");
	    White();
	    printf("\nChoose the option of menu:");
	    scanf("%d",&us_m);
	    switch(us_m)
	    {
	    	case 1:
	    	  signup();
	    	  break;
	    	case 2:
	    		login();
	    		book_tick();
	    		break;
	    	case 3:
	    	    infoPassenger();
	    	    break;
	    	default:
	    		printf("sorry");		
		} 
	}
int main()
  {
  	admin my_admin;
    strcpy(my_admin.admin_name,"admin");
    strcpy(my_admin.admin_password,"password");
  	 int option;
  	 yellow();
  	 printf("====BUS RESERVATION SYSTEM====");
  	 printf("\n1:ADMIN_MENU");
  	 printf("\n2:USER_MENU");
  	 White();
  	 printf("\nEnter the option:");
  	 scanf("%d",&option);
  	 switch(option)
  	  {
  	  	case 1:
  	  		Green();
  	  		char user_nm[100];
  	  		char passworx[100];
  	  		printf("\n\nEnter the admin name:");
  	  		yellow();
  	  		scanf("%s",user_nm);
  	  		Green();
  	  		printf("Enter the password:");
  	  		yellow();
  	  		scanf("%s",passworx);
  	  		if(strcmp(my_admin.admin_name,user_nm)==0&&strcmp(my_admin.admin_password,passworx)==0)
  	  		{
  	  			yellow();
  	  			admin_menu();
			}
  	  		break;
  	  	case 2:
  	  		yellow();
  	  		user_menu();
  	  		break;
  	  	default:
  	  		printf("\nsorry");
		}
	return 0;
}
