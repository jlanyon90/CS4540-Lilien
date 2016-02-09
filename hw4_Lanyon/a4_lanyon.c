/*************************************************
* Course: CS 4540 – Fall 2015
* Assignment 4
* Name: Justin Lanyon
* E-mail: justin.j.lanyon@wmich.edu
* Submitted: 11/23/2015
/*************************************************/
#include <linux/init.h>  
#include <linux/kernel.h>  
#include <linux/module.h>  
#include <linux/slab.h>
#include <linux/list.h>

/* This function is called when the module is loade
d. */  
struct student {  
   int studentNumber;  
   int courseCredit;  
   float grade;  
   struct list_head list;  
}; 

static LIST_HEAD(student_list);

int simple_init(void)  
{  
	float totalPoint=0;
	int totalHour=0;
	int beforeDec =0;
	int afterDec =0;
	float gpa =0;
	float temp =0;
	printk(KERN_INFO "Loading Module\n"); 
	
	/*1st Class*/
	struct student *studentDemo;
    studentDemo = kmalloc(sizeof(*studentDemo), GFP_KERNEL);  
	studentDemo->studentNumber = 760120495;  
	studentDemo->courseCredit = 3;  
	studentDemo->grade = 3.0;  
	INIT_LIST_HEAD(&studentDemo->list); 
	list_add_tail(&studentDemo->list, &student_list);
	
	/*2nd Class*/
	struct student *studentDemo2;
    studentDemo2 = kmalloc(sizeof(*studentDemo2), GFP_KERNEL);  
	studentDemo2->studentNumber = 760120495;  
	studentDemo2->courseCredit = 2;  
	studentDemo2->grade = 1.0; 
	list_add_tail(&studentDemo2->list, &student_list);
	
	/*3rd Class*/
	struct student *studentDemo3;
    studentDemo3 = kmalloc(sizeof(*studentDemo3), GFP_KERNEL);  
	studentDemo3->studentNumber = 760120495;  
	studentDemo3->courseCredit = 4;  
	studentDemo3->grade = 3.5; 
	list_add_tail(&studentDemo3->list, &student_list);
	
	/*4th Class*/
	struct student *studentDemo4;
    studentDemo4 = kmalloc(sizeof(*studentDemo4), GFP_KERNEL);  
	studentDemo4->studentNumber = 760120495;  
	studentDemo4->courseCredit = 1;  
	studentDemo4->grade = 3.5; 
	list_add_tail(&studentDemo4->list, &student_list);
	
	/*5th Class*/
	struct student *studentDemo5;
    studentDemo5 = kmalloc(sizeof(*studentDemo5), GFP_KERNEL);  
	studentDemo5->studentNumber = 760120495;  
	studentDemo5->courseCredit = 2;  
	studentDemo5->grade = 3.0; 
	list_add_tail(&studentDemo5->list, &student_list);
	
	/*6th Class*/
	struct student *studentDemo6;
    studentDemo6 = kmalloc(sizeof(*studentDemo6), GFP_KERNEL);  
	studentDemo6->studentNumber = 760120495;  
	studentDemo6->courseCredit = 3;  
	studentDemo6->grade = 2.0; 
	list_add_tail(&studentDemo6->list, &student_list);


	struct student *ptr;  
	list_for_each_entry(ptr, &student_list, list) { 
   		/* on each iteration ptr points */  
   		/* to the next student struct */ 
   		temp = ptr->grade; 
   		beforeDec = temp;
   		temp = temp-beforeDec;
   		afterDec = temp*100;
		printk("Student: %d Course Credit: %d Grade: %d.%d\n",ptr->studentNumber,
			ptr->courseCredit, beforeDec, afterDec);	
		totalHour += ptr->courseCredit;
		totalPoint += (ptr->courseCredit * ptr->grade);	
	} 
    //printk("totalHour = %d\n",totalHour);
    gpa = totalPoint/totalHour;
    beforeDec =0;
    beforeDec =gpa;
    gpa = gpa-beforeDec;
    afterDec = gpa*100;
   
    //printk("totalPoint = %d.%d\n",beforeDec,afterDec);
    printk("Student: %d GPA %d.%d\n",studentDemo->studentNumber, beforeDec, afterDec);
    return 0;
}  
int simple_exit(void)
{
	struct student *ptr, *next;
	
	printk(KERN_INFO "Removing Module\n");
	list_for_each_entry_safe(ptr, next, &student_list, list){
		list_del(&ptr->list);
		kfree(ptr);
	}	
	return 0;

}
/* Macros for registering module entry and exit poi
nts.*/  
module_init(simple_init);  
module_exit(simple_exit);  
MODULE_LICENSE("GPL");  
MODULE_DESCRIPTION("Simple Module");  
MODULE_AUTHOR("SGG");  