#include"readtxt.h"

void tablefunc()
{
	int i=0;
	FILE *fp;                                    
    char filename[30]="pricetable.txt";
	                               
    if((fp=fopen(filename,"r"))==NULL)            
    {
        printf("\t无法打开该文件\n");      
        printf("\t\t");
    }       
    while(!feof(fp))                
    {
    	//fscanf(fp,"%s",planeprice[i].carrier);
    	
  		fscanf(fp,"%s",planetable[i].linetable); 
  		//printf("%s\n",planetable[i].linetable);
      	i++;
      	
    }
    fclose(fp);
	table_amount=i;
	//printf("%d",table_amount);
	//printf("%d",price_amount);
}

void seatfunc()
{
	int i=0;
	FILE *fp;                                    
    char filename[20]="seat.txt";
	                               
    if((fp=fopen(filename,"r"))==NULL)            
    {
        printf("\t无法打开该文件\n");      
        printf("\t\t");
    }       
    while(!feof(fp))                
    {
    	//fscanf(fp,"%s",planeprice[i].carrier);
    	
  		fscanf(fp,"%s%s%s%s%s%s%s%s",planeseat[i].company,planeseat[i].flightNo,planeseat[i].departure,planeseat[i].arrival,planeseat[i].departureDatime,planeseat[i].f_num,planeseat[i].c_num,planeseat[i].y_num); 
  		//printf("%s\n",planeseat[i].company);
      	i++;
      	
    }
    fclose(fp);
	seat_amount=i;
	//printf("%d",price_amount);
}

void pricefunc()
{
	int i=0;
	FILE *fp;                                    
    char filename[20]="price.txt";
	                               
    if((fp=fopen(filename,"r"))==NULL)            
    {
        printf("\t无法打开该文件\n");      
        printf("\t\t");
    }       
    while(!feof(fp))                
    {
    	//fscanf(fp,"%s",planeprice[i].carrier);
    	
  		fscanf(fp,"%s%s%s%s%s",planeprice[i].carrier,planeprice[i].departure,planeprice[i].arrival,planeprice[i].carbin,planeprice[i].amount); 
  		//printf("%s\n",planeprice[i].carrier);
      	i++;
      	
    }
    fclose(fp);
	price_amount=i;
	//printf("%d",price_amount);
}

void airfunc()
{
    FILE *air_fp;                                    
    char air_filename[20]="air.txt";
	                               
    if((air_fp=fopen(air_filename,"r"))==NULL)            
    {
        printf("\t无法打开该文件\n");      
        printf("\t\t");
    }     
	int i=0;  
    while(!feof(air_fp))                
    {
  		fscanf(air_fp,"%s%s%s%s%s%s",planeair[i].company,planeair[i].flightNo,planeair[i].departureDatime,planeair[i].arrivalDatetime,planeair[i].departure,planeair[i].arrival);
      	//airmessage_amount++;
      	i++;
    }
    fclose(air_fp);
	airmessage_amount=i;
	//printf("%s",planeair[airmessage_amount-1].company);
}
