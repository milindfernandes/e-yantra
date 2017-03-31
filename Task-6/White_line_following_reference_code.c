/*Note : This code is meant to serve as an outline for white line following algorithm
You will have to open Experiment2.aps to write your code*/


int flag;

#define threshold 0x28

//0x28 i.e 40 in decimal is the threshold value. You will have to practically determine the threshold value.

int main()
{
	
	while(1)
	{

		Left_white_line = 	//Getting data of Left WL Sensor
		Center_white_line = 	//Getting data of Center WL Sensor
		Right_white_line = 	//Getting data of Right WL Sensor

		flag=0;
		
		

		if(Center_white_line<threshold) //Center White line sensor on white
		{
			flag=1;
			forward();
			velocity(150,150); //you can try out different velocity values
		}

		if((Left_white_line>threshold) && (flag==0))  //Left White line sensor on black
		{
			flag=1;
			forward();
			velocity(130,50); //move right
		}

		if((Right_white_line>threshold) && (flag==0)) //Right White line sensor on black
		{
			flag=1;
			forward();
			velocity(50,130); //move left
		}

		if(Center_white_line>threshold && Left_white_line>threshold && Right_white_line>threshold) //all sensors on black
		{
			forward();
			velocity(0,0);
		}

	}
}
