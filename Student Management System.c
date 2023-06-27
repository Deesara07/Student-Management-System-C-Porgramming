#include <stdio.h>		//header files
#include <string.h>
#include <stdlib.h>

typedef struct student	//student structure declare
{
	int index;
	char name[20];
	char department[20];
	struct course	
	{
		int courseid;
		char cname[20];
		float credit;	
	}crs[3];
	
	int CourseCount;
	float total;
	float grade;
}student;

typedef struct coursedetail	//course details structure declare
{
	int courseid;
	char cname[20];
	float credit;
	
}coursedetails;

float TempGrade;

void AddNewStudent()	//add new student details when the user enter "1" this function execute
{
	student *s;
	FILE *fp;
	FILE *fp1;
	int num, i = 0, j;
	float count;
	char check;
	int tempCourseID;
	system("cls");
	system("COLOR 0E");

	
	coursedetails c1;
	
	printf("\n\t\t\t\t\t=======================");
	printf("\n\t\t\t\t\tADD NEW STUDENT DETAILS");
	printf("\n\t\t\t\t\t=======================\n");
	
	printf("\nHow many Student do you need to Add? ");
	scanf("%d", &num);
	
	s = (student*)calloc(num, sizeof(student));
	fp = fopen("student.txt", "a");
	
	if (fp == NULL) 
    {   
    	printf("\nError! Could not open file\n"); 
    	exit(-1);
	}	
	for(i = 0; num > i; i++)
	{
		s[i].total = 0;
		s[i].grade = 0;	
		
		printf("\nEnter Student Index Number	: ");	scanf("%d", &s[i]);
		fflush(stdin);
	    printf("Enter Student Full Name		: ");		scanf("%[^\n]s", s[i].name);
	    fflush(stdin);
	    printf("Enter Department Name		: ");		scanf("%[^\n]s", s[i].department);
	
	    printf("\nHow Many Course/Courses following? ");
	    scanf("%f", &count);
	    
	    s[i].CourseCount = count;
	    Viewcourse();					//user can view what are available courses
    
		for(j = 0; count > j; j++)
		{
			fflush(stdin);
	    	printf("\nEnter Course ID You Want		:  ");			scanf("%d", &tempCourseID);
	    	
	    	fp1 = fopen("course.txt", "r");
	    	while(fread(&c1,sizeof(coursedetails), 1, fp1))		//using fread, read all details in course.txt file and assign matching course id name to student.txt 
			{
				if(c1.courseid == tempCourseID)
				{
					strcpy(s[i].crs[j].cname, c1.cname);
				}
			}
			fclose(fp1);
	
	    	printf("Enter Credit Value (4.0 to 0.0)	:  "); 			scanf("%f", &s[i].crs[j].credit);
	    	s[i].total += s[i].crs[j].credit;		//calculate total credit for student
		}
		printf("--------------------------------------");
		       
	    s[i].grade = (s[i].total)/count;			//calculate grade
	    fwrite(&s[i], sizeof(student), 1, fp);		//write entered student details in file
	}

    fclose(fp);
    if(num > 0)
   		printf("\n...Successfully Saved...\n");
   	else
   		printf("\n...No Record Entered...\n");
}

void AddNewCourse()	//add new course details, when the user enter "2" this function execute
{
	coursedetails *c;
	FILE *fp;
	int i, num;
	system("cls");
	
	printf("\n\t\t\t\t\t======================");
	printf("\n\t\t\t\t\tADD NEW COURSE DETAILS");
	printf("\n\t\t\t\t\t======================\n");
	
	printf("\nHow many Courses do you need to Add? ");
	scanf("%d", &num);
	
	c = (coursedetails*)calloc(num, sizeof(coursedetails));
	fp = fopen("course.txt", "a");
	
	if (fp == NULL) 
    {   
    	printf("\nError! Could not open file\n"); 
    	exit(-1);
	}
	
	for(i = 0; num > i; i++)
	{
		printf("\n");
		printf("Enter Course Id Number		: ");		scanf("%d", &c[i].courseid);
		fflush(stdin);
	    printf("Enter Course Name		: ");			scanf("%[^\n]s", c[i].cname);
	    fflush(stdin);
	    printf("Enter Course Credit Value	: ");		scanf("%f", &c[i].credit );
	
	    fwrite(&c[i], sizeof(coursedetails), 1, fp);		//write entered course details
	}
    fclose(fp);
        if(num > 0)
   		printf("\n...Successfully Saved...\n");
   	else
   		printf("\n...No Record Entered...\n");
}

void ViewStudentDetails()	//view all of student details, when the user enter "3" this function execute
{
	student s1;
	FILE *fp;
	int j;
	fp = fopen("student.txt", "r");
	system("cls");
	
	printf("\n\t\t\t\t\t===============");
	printf("\n\t\t\t\t\tSTUDENT DETAILS");
	printf("\n\t\t\t\t\t===============\n");
	
	if (fp == NULL) 
    {   
    	printf("\nError! Could not open file\n"); 
    	exit(-1);
	}
	
	while(fread(&s1,sizeof(student),1,fp))	//using fread, read all details in student.txt file
	{
		printf("\n\nIndex		:- %-6d \nName		:- %-20s \nDepartment	:- %-15s", s1.index, s1.name, s1.department);
		for(j = 0; j < s1.CourseCount; j++)
		{
			printf("\nCourse %d	:- %-15sCredit Value:- %-8.2f",(j+1) ,s1.crs[j].cname, s1.crs[j].credit);
			TempGrade = s1.crs[j].credit;
			
			if (TempGrade <= 4.0 && TempGrade >= 3.0)	//course grade selection
				printf("Grade: A");
			else if (TempGrade < 3.0 && TempGrade >= 2.5)
				printf("Grade: B");
			else if (TempGrade < 2.5 && TempGrade >= 1.5)
				printf("Grade: C");
			else if (TempGrade < 1.5 && TempGrade < 0)
				printf("Grade: D");
			else if(TempGrade < 0)
				printf("Grade: E");
			else
				printf("Grade:Invalid Credit");
		}
	}
	fclose(fp);
}

void Searchstudent()	//search student details using index number, when the user enter "4" this function execute
{
	student s1;
	int tempid, found;
	FILE *fp;
	int j;
	fp = fopen("student.txt", "r");
	system("cls");
	
	printf("\n\t\t\t\t\t======================");
	printf("\n\t\t\t\t\tSEARCH STUDENT DETAILS");
	printf("\n\t\t\t\t\t======================\n");
	
	if (fp == NULL) 
    {   
    	printf("\nError! Could not open file\n"); 
    	exit(-1);
	}
	
	printf("Enter Index Number to Search: ");
	scanf("%d", &tempid);
	
	while(fread(&s1,sizeof(student),1,fp))	//using fread, read all details in student.txt file
	{
		if(s1.index == tempid)	//check matching index to entered index number
		{
			found = 1;
			printf("\n\nIndex		:- %-6d \nName		:- %-20s \nDepartment	:- %-15s", s1.index, s1.name, s1.department);	//display only if match index and entered Ids
			
			for(j = 0; j < s1.CourseCount; j++)
			{
				printf("\nCourse %d	:- %-15sCredit Value:- %-8.2f",(j+1) ,s1.crs[j].cname, s1.crs[j].credit);
				TempGrade = s1.crs[j].credit;	
				if (TempGrade <= 4.0 && TempGrade >= 3.0)
					printf("Grade: A");
				else if (TempGrade < 3.0 && TempGrade >= 2.5)
					printf("Grade: B");
				else if (TempGrade < 2.5 && TempGrade >= 1.5)
					printf("Grade: C");
				else if (TempGrade < 1.5 && TempGrade < 0)
					printf("Grade: D");
				else if(TempGrade < 0)
					printf("Grade: E");
				else
					printf("Grade:Invalid Credit");
			}
		}	
	}
	if(!found)
		printf("\nNo Record Found\n");
		
	fclose(fp);
}

void Viewcourse()	//user can view stored course details, when the user enter "5" this function execute
{
	coursedetails c1;
	FILE *fp;
	int j;
	fp = fopen("course.txt", "r");
		
	printf("\n\t\t\t\t\t========================");
	printf("\n\t\t\t\t\tAvailable COURSE DETAILS");
	printf("\n\t\t\t\t\t========================\n");
	
	
	printf("\n\nCourse ID\tCourse Name\tCourse Total Credit\n");
	printf("-----------------------------------------------------\n\n");
	while(fread(&c1,sizeof(coursedetails), 1, fp))	//using fread, read all details in course.txt file
	{
		printf("%-15d %-20s %-7.2f\n", c1.courseid, c1.cname, c1.credit);
	}
	
	fclose(fp);
}

void Updatestudent()	//user can update student details using index number, when the user enter "6" this function execute
{
	student s1;
	int tempid, found = 0;
	float count;
	FILE *fp, *fp1;
	int j;
	
	printf("\n\t\t\t\t\t======================");
	printf("\n\t\t\t\t\tUPDATE STUDENT DETAILS");
	printf("\n\t\t\t\t\t======================\n");
	
	fp  = fopen("student.txt", "r");
	fp1 = fopen("tempstudent.txt", "w");
	
	printf("\n\n(If nothing to change relevent field please skip that input)");
	printf("\nEnter Index Number to Update: ");											//Take index number of student need to update
	scanf("%d", &tempid);
	
	while(fread(&s1, sizeof(student), 1, fp))	//using fread, read all details in student.txt
	{
		if(s1.index == tempid)	//check entered and read index values matching
		{
			found = 1;
			s1.total = 0;
			s1.grade = 0;
			fflush(stdin);
		    printf("Enter New Student Name		: ");	scanf("%[^\n]s", &s1.name);			
		    fflush(stdin);
		    printf("Enter New Department Name	: ");	scanf("%[^\n]s", &s1.department);
		    
		    count = s1.CourseCount;
	    
			for(j = 0; count > j; j++)
			{
				fflush(stdin);
		    	printf("\nEnter New Course %d Name	:  ", j+1);	scanf("%[^\n]s", &s1.crs[j].cname);			//user can enter new course name doesn't exit in courses or skip
		    	printf("Enter New Credit Value	:  ");	scanf("%f", &s1.crs[j].credit);
		    	s1.total += s1.crs[j].credit;
			}
		}
		s1.grade = (s1.total)/count;
		fwrite(&s1, sizeof(student), 1, fp1);
	}
	fclose(fp);
	fclose(fp1);
	
	if(found)
	{
		fp1 = fopen("tempstudent.txt", "r");
		fp = fopen("student.txt", "w");
		
		while(fread(&s1, sizeof(student), 1, fp1))		//using fread, read all details in tempstudent.txt
		{
			fwrite(&s1, sizeof(student), 1, fp);		//overwrite the readed details to student.txt
		}		
		fclose(fp);
		fclose(fp1);
	}
	printf("\n...Successfully Updated...\n");	
}

void Updatecourse()	//user can update course details using course ID, when the user enter "7" this function execute
{
	coursedetails c1;
	int tempid, found = 0;
	FILE *fp, *fp1;
	int j;
	
	fp = fopen("course.txt", "r");
	fp1 = fopen("tempcourse.txt", "w");
	
	printf("\n\t\t\t\t\t======================");
	printf("\n\t\t\t\t\tUPDATE 	COURSE DETAILS");
	printf("\n\t\t\t\t\t======================\n");
	
	printf("Enter Course ID to Update: ");
	scanf("%d", &tempid);								//Take course ID number of course need to update
	while(fread(&c1, sizeof(coursedetails), 1, fp))		//using fread, read all details in course.txt
	{
		if(c1.courseid  == tempid)						//check entered and read index values matching
		{
			found = 1;
			fflush(stdin);
		    printf("Enter New Course Name	: ");	scanf("%[^\n]s", c1.cname);
		    printf("Enter New Credit Value	: ");	scanf("%f", &c1.credit);
		}
		fwrite(&c1, sizeof(coursedetails), 1, fp1);
	}
	fclose(fp);
	fclose(fp1);
	
	if(found)
	{
		fp1 = fopen("tempcourse.txt", "r");
		fp = fopen("course.txt", "w");
		
		while(fread(&c1, sizeof(coursedetails), 1, fp1))	//using fread, read all details in tempstudent.txt
		{
			fwrite(&c1, sizeof(coursedetails), 1, fp);		//overwrite the readed details to student.txt
		}		
		fclose(fp);
		fclose(fp1);
	}
	printf("\n...Successfully Updated...\n");
}

void DeleteStudent()	//Delete stored student details using index number, when the user enter "8" this function execute
{
	student s1;
	int tempid;  
	int found = 0, count;
	FILE *fp, *fp1;
	int j;
	system("cls");
	
	printf("\n\t\t\t\t\t======================");
	printf("\n\t\t\t\t\tDELETE STUDENT DETAILS");
	printf("\n\t\t\t\t\t======================\n");
	
	fp = fopen("student.txt", "r");
	fp1 = fopen("tempstudent.txt", "w");
	
	printf("Enter Index Number to Delete: ");
	scanf("%d", &tempid);							//Take index number of student need to delete
	
	while(fread(&s1, sizeof(student), 1, fp))		//using fread, read all details in course.txt
	{
		if(s1.index == tempid)
		{
			found = 1;
		}
		else
			fwrite(&s1, sizeof(student), 1, fp1);	//write all of details in tempstudent.txt execept matching id details.
	}
	fclose(fp);
	fclose(fp1);
	
	if(found)
	{
		fp1 = fopen("tempstudent.txt", "r");
		fp = fopen("student.txt", "w");
		
		while(fread(&s1,sizeof(student),1,fp1))		//read all details in tempstudent.txt
		{
			fwrite(&s1,sizeof(student),1,fp);		//overwrite readed details in student.txt
		}		
		fclose(fp);
		fclose(fp1);
		printf("\n...Successfully Deleted...\n");
	}
	else
		printf("\n...No Record Found...");
}

void Deletecourse()	//Delete stored course details using course ID, when the user enter "9" this function execute
{
	coursedetails c1;
	int tempid, found = 0;
	FILE *fp, *fp1;
	int j;
	system("cls");
	
	fp = fopen("course.txt", "r");
	fp1 = fopen("tempcourse.txt", "w");
	
	printf("\n\t\t\t\t\t======================");
	printf("\n\t\t\t\t\tUPDATE COURSE DETAILS");
	printf("\n\t\t\t\t\t======================\n");
	
	printf("Enter Course ID Number to Delete: ");
	scanf("%d", &tempid);								//Take course ID number of course need to delete
	
	while(fread(&c1, sizeof(coursedetails), 1, fp))		//using fread, read all details in course.txt
	{
		if(c1.courseid == tempid)
		{
			found = 1;
		}
		else
			fwrite(&c1, sizeof(coursedetails), 1, fp1);	//write all of details in tempcours.txt execept matching id details.
	}
	fclose(fp);
	fclose(fp1);
	
	if(found)
	{
		fp1 = fopen("tempcourse.txt", "r");
		fp = fopen("course.txt", "w");
		
		while(fread(&c1, sizeof(coursedetails), 1, fp1))	//read all details in tempstudent.txt
		{
			fwrite(&c1, sizeof(coursedetails), 1, fp);		//overwrite readed details in student.txt
		}		
		fclose(fp);
		fclose(fp1);
		printf("\n...Successfully Deleted...\n");
	}
	else
		printf("\n...No Record Found...");
}

void FinalReport()	//Display Final report all of students, when the user enter "10" this function execute
{
	student s1;
	FILE *fp;
	int j;
	float TempGrade;
	system("cls");
	
	
	fp = fopen("student.txt", "r");
	
	printf("\n\t\t\t\t\t=====================");
	printf("\n\t\t\t\t\tSTUDENTS FINAL REPORT");
	printf("\n\t\t\t\t\t=====================\n");
	
	printf("\n\n-------------------------------------------------------------------------------");
	printf("\nIndex\t\tName\t\t\t\tDepartment\t\tGPA\n");
	printf("-------------------------------------------------------------------------------\n");

	while(fread(&s1,sizeof(student),1,fp))		//read all details of student.txt
	{
 		printf("\n%-15d%-30s%-25s%-8.2f", s1.index, s1.name, s1.department, s1.grade);			//display student details and GPA value
	}
	fclose(fp);
}

int main()	//main function begin
{
	int menu;
	system("COLOR 0E");
	
	printf("\n\t\t\t\t====================================");
	printf("\n\t\t\t\tWelcome to Student Management System");
	printf("\n\t\t\t\t====================================\n");

	printf ("\n\n\t\t\t\t1. Add New Student");
	printf ("\n\t\t\t\t2. Add New Course");
	printf ("\n\t\t\t\t3. View All Student Details");
	printf ("\n\t\t\t\t4. Search Student Using Index");
	printf ("\n\t\t\t\t5. View Available Courses");
	printf ("\n\t\t\t\t6. Update Student Details");
	printf ("\n\t\t\t\t7. Update Course Details");
	printf ("\n\t\t\t\t8. Delete Student Detials");
	printf ("\n\t\t\t\t9. Delete Course Details");
	printf ("\n\t\t\t\t10. Get Final Report of Students");
	printf ("\n\t\t\t\t0. EXIT");
	printf ("\n\n\t\t\t\t  	Enter Your Choice: ");

	scanf("%d", &menu);
	
	while(menu != -1)	//program run untill user enter -1
	{
		switch(menu)	//using switch case call relevent function
		{
			case 1:
				AddNewStudent();
			break;
			case 2:
				AddNewCourse();
			break;
			case 3:
				ViewStudentDetails();
			break;
			case 4:
				Searchstudent();
			break;
			case 5:
				Viewcourse();
			break;
			case 6:
				Updatestudent();
			break;
			case 7:
				Updatecourse();
			break;
			case 8:
				DeleteStudent();
			break;
			case 9:
				Deletecourse();
			break;
			case 10:
				FinalReport();
			break;
			case 0:
				printf("\n\t\t\t\t\t======================================");	
				printf("\n\t\t\t\t\tEnd of the Program.Have A Nice Day... ");
				printf("\n\t\t\t\t\t======================================");	
				return 0;
			default:
				printf("Invalid Menu Select Enter Again...");
		}
		printf ("\n\n\t\t\t\t1.   Add New Student");
		printf ("\n\t\t\t\t2.  Add New Course");
		printf ("\n\t\t\t\t3.  View All Student Details");
		printf ("\n\t\t\t\t4.  Search Student Using Index");
		printf ("\n\t\t\t\t5.  View Available Courses");
		printf ("\n\t\t\t\t6.  Update Student Details");
		printf ("\n\t\t\t\t7.  Update Course Details");
		printf ("\n\t\t\t\t8.  Delete Student Detials");
		printf ("\n\t\t\t\t9.  Delete Course Details");
		printf ("\n\t\t\t\t10. Get Final Report of Students");
		printf ("\n\t\t\t\t0.  EXIT");
		printf ("\n\n\t\t\t\t  	Enter Your Choice: ");
		scanf("%d", &menu);
	}
}

//program end






