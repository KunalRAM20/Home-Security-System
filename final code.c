#include <REG51.h>
#define display P3
#define KEYPAD P1

sbit doorclose = P1^7;
sbit correct = P3^5;
sbit wrong= P3^4;
sbit key = P3^7;
void DelayMs(unsigned int);
void save (unsigned char);
void compare (void);

unsigned char keypad[4][3]= { '1', '2', '3',
                              '4', '5', '6',
			      			  '7', '8', '9',
			      			  '*', '0', '#'};

unsigned char displayb[4][3]= { 1 , 2 , 3 ,
                                4 , 5 , 6 ,
			      			    7 , 8 , 9 ,
                                0, 0 ,  0};

unsigned char code password[5]= "12345";
unsigned char user[30];	     //user is allowed to press 30 keys without entering						  
unsigned char q,a=0,z=0;
char t=1;
bit true;
char d;









void main(void)
{
unsigned char colloc,rowloc;



	while(1)
	{
	
		do
		{
			KEYPAD=0xF0;
			colloc=KEYPAD & 0xF0;
		}
    while(colloc ==0xF0);        // if any key pressed
	DelayMs(1);					 // some delay
	do
	{
	colloc=KEYPAD;
	colloc &=0xF0;
	}while(colloc==0xF0);		// to verify is really key pressed
    
		KEYPAD=0xFE;
		colloc=KEYPAD & 0xF0;
		if(colloc !=0xF0)
		{
			rowloc=0;
			goto next;
		}

		KEYPAD=0xFD;
		colloc=KEYPAD & 0xF0;
		if(colloc !=0xF0)
		{
			rowloc=1;
			goto next;
		}
		KEYPAD=0xFB;
		colloc=KEYPAD & 0xF0;
		if(colloc !=0xF0)
		{
			rowloc=2;
			goto next;
		}
				
		KEYPAD=0xF7;
		colloc=KEYPAD & 0xF0;
		rowloc=3;
		goto next;

next:			                                                                    
if (colloc==0xE0)
{
 key=0; 					// verifying that key is pressed
 DelayMs(145);
 key=1;
 display=((display & 0xf0) | (displayb[rowloc][0])); // display to 7 seg
 save(keypad[rowloc][0]);
}
else if(colloc==0xD0)
{
 key=0; 					// verifying that key is pressed
 DelayMs(145);
 key=1;
 display=((display & 0xf0) | (displayb[rowloc][1]));
 save(keypad[rowloc][1]);
}
else if(colloc==0xb0)
{
 key=0; 					// verifying that key is pressed
 DelayMs(145);
 key=1;
 display=((display & 0xf0) | (displayb[rowloc][2]));
 save(keypad[rowloc][2]);
}
DelayMs(100);	   // here this delay is important if this is less than 100ms then 
				   // controller understand 1 key as press 2 or 3 times becoz that 
				   //is fast as compaer o our pressing if u want to remove delay from here 
				   // then increse the above 1ms to 100 ms 
}
}

void save (unsigned char c)
{
 if(c=='*')
 {
  if(a!=0)
  a--;
  return;
 } 

 if(a==5 && c=='#')
 {
  a=0;
  compare();

	if(t==1)
	{
	  if(true==1) // if match ok
	  {
	   DelayMs(800);
       correct=0;
	   t=2;
       for(d=0; d<7; d++)	   // on and after 10 sec off nw keypad can't get data
       DelayMs(1000);	 // max delay u can get is DelayMs(65535) otherwise need looping for big delay
       correct=1;
	   z=0;
       a=0;           // start agian from 0 location of array
 
      }
	  else if(true==0)
	   goto error;

    }
	else if(t==2)
	  {
	    DelayMs(800);
	    doorclose=0;
		t=1;
	    for(d=0; d<5; d++)	 
        DelayMs(1000);	 
        doorclose=1;
	  }
  }
 
 else if((a>5 && c=='#') || (a<5 && c=='#'))
  {
   error:
   for(q=0; q<5; q++)
   {
    wrong=0;
    DelayMs(420);
    wrong=1;
    DelayMs(420);
    a=0;
   }
   z=z+1;

       if(z==4)
        {
		 for(q=0; q<10; q++)
		  {
	       wrong=0;
		   DelayMs(20000);
           wrong=1;
		   z=0;
           DelayMs(420);
		   }
	    }
        a=0;
  }
else
 {
  user[a]=c;
  a++;

  if(a==30)		// if the user press 31 keys without entering it will automatically indicate an error
   {
    display=((display & 0xf0) | (displayb[3][1])); //brings a zero display on the seven segment
    goto error;	//redirect to error code
   }
 }
 
}	  //end of save



void compare (void)
{
 unsigned char b;
  for(b=0;b<5;b++)
   {

    if(user[b]==password[b])
     true=1;
    else
    {
     true=0;
     break;
    }
   }
}


//---------------------------------------
// Delay mS function
//---------------------------------------
void DelayMs(unsigned int count) 
{  // mSec Delay 11.0592 Mhz 
    unsigned int i;		       		
    while(count) {
        i = 115; 
		while(i>0) i--;
        count--;
    }
}

