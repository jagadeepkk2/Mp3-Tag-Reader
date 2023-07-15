/*
Name:
Description:
Date:
Sample input:
Sample output:
 */
#include<stdio.h>
#include<stdlib.h>
#include "main.h" 
char tag[5];
OperationType check_operation_type(char *argv[])
{

	if(strcmp(argv[1],"-e")==0)
	{
		return e_edit;

	}

	else if(strcmp(argv[1],"-v")==0)
	{
		return e_view;
	}

	else if(strcmp(argv[1],"--help")==0)
	{
		return e_help;
	}
	else
	{
		return e_unsupported;
	}

}
Status read_and_validate_view_args(char *argv[])
{
	if(strstr(argv[2],".mp3" )!= NULL)                                  
	{
		return e_success;                      
	}
	else
	{
		return e_failure;                                                  
	}
}
Status read_and_validate_edit_args(char *argv[])
{
	if(strcmp(argv[2],"-t")==0)
	{
		strcpy(tag,"TIT2");			
	}
	else if(strcmp(argv[2],"-a")==0)
	{
		strcpy(tag,"TPE1");			
	}

	else if(strcmp(argv[2],"-A")==0)
	{
		strcpy(tag,"TALB");			
	}

	else if(strcmp(argv[2],"-y")==0)
	{
		strcpy(tag,"TYER");			
	}

	else if(strcmp(argv[2],"-m")==0)
	{
		strcpy(tag,"TCON");			
	}

	else if(strcmp(argv[2],"-c")==0)
	{
		strcpy(tag,"COMM");			
	}


	else
	{
		return e_failure;
	}

	if(strstr(argv[4],".mp3" )!= NULL)                                  
	{
		return e_success;                      
	}
	else
	{
		return e_failure;                                                  
	}
}
Status view(char *argv[])
{
	Mp3info mp3info;
	FILE *fp = fopen(argv[2], "r");    
	if (fp == NULL)                                    
	{
		perror("fopen");                                                       
		fprintf(stderr, "ERROR: Unable to open file %s\n", argv[2]);
		return e_failure;                                                       
	}
	char header[4];
	unsigned	char versn[2];
	int version=0;
	fread(header,1,3,fp);
	header[3]='\0';
	fread(versn,1,2,fp);
	version |= versn[1];
	version |= versn[0];

	if(strcmp(header,"ID3")==0 && version==3)
	{

		printf("-----------------------------------------------------\n");
		printf("\tMP3 TAG READER AND EDITOR FOR %sV2.%d\n",header,version);
		printf("-----------------------------------------------------\n");
	}
	else
	{
		return e_failure;
	}
	fseek(fp,1,SEEK_CUR);
	unsigned char sValue[4];
	int sresult=0;
	fread(sValue,1,4,fp);

	sresult |= sValue[0] << 24;
	sresult |= sValue[1] << 16;
	sresult |= sValue[2] << 8;
	sresult |= sValue[3];


	fseek(fp,10,SEEK_SET);

	int count =0;
	while(count <6)
	{
		fread(mp3info.frame_id,1,4,fp);
		mp3info.frame_id[4]='\0';
		printf("%s : ",mp3info.frame_id);
		unsigned char hexValue[4];
		int result=0;
		fread(hexValue,1,4,fp);
		//	hexValue[4]='\0';

		result |= hexValue[0] << 24;
		result |= hexValue[1] << 16;
		result |= hexValue[2] << 8;
		result |= hexValue[3];
		//	sscanf(buf, "%d", &num);

		printf("%d\n",result);

		fseek(fp,2,SEEK_CUR);
		char str[result+1];
		fread(str,1,result,fp);
		str[result]='\0';
		printf("%s \n",str+1);
		count ++;
		printf("\n\n");
	}
	printf("-----------------------------------------------------\n\n");
}

Status edit(char *argv[])
{
	FILE *fp = fopen(argv[4], "r");
	Mp3info mp3info;
	if (fp == NULL)
	{
		perror("fopen");
		fprintf(stderr, "ERROR: Unable to open file %s\n", argv[2]);
		return e_failure;

	}

	//Read header and version
	char header[4];
	unsigned    char versn[2];
	int version=0;
	fread(header,1,3,fp);
	header[3]='\0';
	fread(versn,1,2,fp);
	version |= versn[1];
	version |= versn[0];

	if(strcmp(header,"ID3")==0 && version==3)
	{

		printf(" %sV2.%d\n",header,version);
	}
	else
	{
		return e_failure;
	}





	fseek(fp,10,SEEK_SET);   //Move to fist frame


	FILE* fp1;
	int count =0;
	long int pos=0,posc=0;
	while(count <6)
	{

		char frm_header[5];
		char frm_size[5];
		int frm_size_n=0;
		char frm_flag[3];
		char temp;

		//Read frame header
		fread(frm_header,1,4,fp);
		frm_header[4]='\0';
		pos=ftell(fp);
		//Read framesize
		fread(frm_size,1,4,fp);
		frm_size[4]='\0';

		frm_size_n |= frm_size[0] << 24;
		frm_size_n |= frm_size[1] << 16;
		frm_size_n |= frm_size[2] << 8;
		frm_size_n |= frm_size[3];

		//Read frame flags
		fread(frm_flag,1,2,fp);
		frm_flag[2]='\0';

		//Skip frame content
		fseek(fp,frm_size_n,SEEK_CUR);
		posc=ftell(fp);

		if(strcmp(frm_header,tag)==0)
		{
			fp1=fopen("edited.mp3","w+");
			if (fp1 == NULL)
			{
				perror("fopen");
				fprintf(stderr, "ERROR: Unable to open file");
				return e_failure;
			}
			rewind(fp);

			char buffer[1];
			int j=0;
			int number=0; //new size
			char new_size[4];
			while (j<pos)
			{
				fread(buffer,1,1,fp) ;
				fwrite(buffer,1,1,fp1);
				j++;
			}
			number=strlen(argv[3])+1;
			unsigned char bytes[4];
			bytes[3] = number & 0xFF;
			bytes[2] = (number >> 8) & 0xFF;
			bytes[1] = (number >> 16) & 0xFF;
			bytes[0] = (number >> 24) & 0xFF;
			fwrite(bytes, sizeof(unsigned char), 4, fp1);


			fwrite(frm_flag,1,2,fp1);

			fwrite("",1,1,fp1);

			fwrite(argv[3],1,number-1,fp1);



			fseek(fp,posc,SEEK_SET);

			char ch;
			while (fread(&ch,1,1, fp) > 0)
			{
				fwrite(&ch,1,1,fp1);
			}
			break;
		}
		count ++;
	}
	fclose(fp);
	fclose(fp1);
}

