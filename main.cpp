#include <iostream>
#include <stdio.h>
using namespace std;

#define RC4size 256
#define blocksize 256

void s_printf(char* c)
{
	int i = 0;
	while(c[i]!='\0')
	{
		printf("%c",c[i]);
		i++;
	}	
}

class RC4
{
	private:
		int S_box[RC4size];
		unsigned char K_box[RC4size];
		int keyLen;
		unsigned char swap[RC4size];
		int R_box[RC4size];
		void initialize()
		{
			int i,keylen = 0,j=0,temp;
			char a;
			for(i = 0;i<RC4size;i++)
			{
				S_box[i] = i;
			}
			
			/*
			printf("请输入RC4密钥："); 	
			while(scanf("%c",&a)!=EOF)
			{
				if(a=='\n')
				{
					break;
				}
				K_box[keylen] = a;
				keylen++;		
			}
			*/
			K_box[0]='s';
			K_box[1]='u';
			K_box[2]='s';
			K_box[3]='h';
			
			keylen = 4;
			keyLen = keylen;
			for(int j = 0;j<256;j++)
			{
				K_box[j] = K_box[j%keylen];
			}
			
			for(int i = 0;i<256;i++)
			{
				j=(j+S_box[i]+K_box[i])%256;
				temp = S_box[j];
				S_box[j] = S_box[i];
				S_box[i] = temp;
			}
		}
		
		void toRC4(unsigned char* c)
		{
			printf("\n密文:\n");
			int i,j,k,temp,R;
			j = k =0;
			for(i = 0;c[i]!='\0';i++)
			{
				j = (j+1)%256;
				k = (k+S_box[j])%256;
				
				temp = S_box[k];
				S_box[k] = S_box[j];
				S_box[j] = temp;
				
				R_box[i] = S_box[(S_box[j]+S_box[k])%256];
				c[i]^=R_box[i];
				printf("%02X ",c[i]);
			}
		}
	public :
		RC4()
		{
			printf("初始化RC4。。。\n");
			initialize();
		}
		
		void printfK_box()
		{
			printf("\nK_box:\n");
			for(int i = 0;i<RC4size;i++)
			{
				printf("%02X ",K_box[i]);
			}
		}
		
		void printfS_box()
		{
			printf("\nS_box:\n");
			for(int i = 0;i<RC4size;i++)
			{
				printf("%02X ",S_box[i]);
			}
		}
		void printKey()
		{
			printf("用户密钥为："); 
			for(int i = 0;i<keyLen;i++)
			{
				printf("%c",K_box[i]);
			}
			printf("\n"); 
		}
		

		
		void getRC4byPutin()
		{
			unsigned char tempC[blocksize];
			char a;
			int len = 0;
			printf("\n请输入明文："); 
			while(scanf("%c",&a)!=EOF)
			{
				if(a == '\n')
				{
					break;
				}
				tempC[len] = a;
				len++;
			}
			tempC[len+1] = '\0';
			
			toRC4(tempC);
			
		}
		
		
		
		void getRC4byFile()
		{
			fflush(stdin);
			char filename[50];
			printf("请输入文件名："); 
			scanf("%s",&filename); 
			printf("文件内容为：\n",filename);
			
			FILE* fp = fopen(filename,"rw");
			FILE* fp2 = fopen("sushmima.txt","w");
			if(fread(swap,sizeof(char),blocksize,fp)<0)
			{
				printf("read file error！！！");
				return ;
			}
			
			toRC4(swap);
			
			printf("\n");
			
			int miwen[RC4size];
			int i = 0;
			while(swap[i]!='\0')
			{
				miwen[i] = (int)swap[i];
				i++;
			}
			
			fwrite(miwen,sizeof(int),i,fp2);
		}
		
};




int main(int argc, char** argv) {
	RC4 rc4;
	rc4.getRC4byFile();
	//rc4.printKey();
	//rc4.getRC4byPutin();
	return 0;
}


