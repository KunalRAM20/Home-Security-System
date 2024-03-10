#include <AT892051.H>
sbit laser = P3^7;

void delay(int k)
{
	int i;
	TR0=0;
	for(i=0; i<k; i++)
		{
			TH0=0x3c;
			TL0=0xb0;
			TF0=0;
			TR0=1;
			while (TF0==0);
			TR0=0;
		}
}


void main()
{
  	char v,d,z=0;
  	P1=0x3f;
  	P3=0x00;


while(1)
	{
   switch(P1)
  		{


		case 25: 	P3=0x01;	   //day monitoring mode
					v=0;
					delay(90);
  					break;


		
 		case 27:	P3=0x0c;
					delay(60);
					P3=0x08;
					delay(60);
					break;
					
  					break;
		case 31:	P3=0x0e;
					delay(60);	   // 3 seconds
					P3=0x08;
					delay(60);	   // 3 seconds
					P3=0x0a;
					delay(60);	   // 3 seconds
					P3=0x0c;
					delay(60);	  // 3 seconds
  					break;


		case 17:	P3=0x0c;
					delay(6000);  // 5 minutes
					break;
		case 21:	P3=0x0e;
					delay(6000);  // 5 minutes
					break;



		case 29:	P3=0x07;	  //night monitoring mode
					v=0;
					break;
					 
		case 45:	P3=0x07;
					delay(40);
					v=1;
			      	break;
		            
					
		            

		case 41:	P3=0x05;
		            v=1;
					break;
		          
					break;
		case 37:	P3=0x07;
					break;    
			

		case 11:	P3=0x0c;
					delay(60);
					P3=0x08;
					delay(60);
 					break;

		case 15:	P3=0x0e;
					delay(60);	   // 3 seconds
					P3=0x08;
					delay(60);	   // 3 seconds
					P3=0x0a;
					delay(60);	   // 3 seconds
					P3=0x0c;
					delay(60);	  // 3 seconds
  					break; 

		case 9:   	if(v==1)
		            P3=0x05;
					else
					{
					for(d=0; d<70; d++)
					{
					P3=0x0e;
					delay(60);	   // 3 seconds
					P3=0x08;
					delay(60);	   // 3 seconds
					P3=0x0a;
					delay(60);	   // 3 seconds
					P3=0x0c;
					delay(60);	  // 3 seconds

					}
					}
					break;

	    case 57:    v=1;
		            break;

		case 13:    if(v==1)
					P3=0x07;
					else
					{
					for(d=0; d<70; d++)
					{
					P3=0x0e;
					delay(60);	   // 3 seconds
					P3=0x08;
					delay(60);	   // 3 seconds
					P3=0x0a;
					delay(60);	   // 3 seconds
					P3=0x0c;
					delay(60);	  // 3 seconds

					}
					}
		            break;

		case 61:    P3=0x07;
					v=1;
					delay(90);

		
		default:	v=0;
                 	P3=0x00;	  // enable/disable security system Manualy
					laser=1;
					
  	

		} 
	} 
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           

